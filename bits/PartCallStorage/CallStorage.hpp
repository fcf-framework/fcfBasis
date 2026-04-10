#ifndef ___FCF__BASIS__BITS__CALL_STORAGE__CALL_STORAGE_HPP___
#define ___FCF__BASIS__BITS__CALL_STORAGE__CALL_STORAGE_HPP___

#include "../../PartForeach.hpp"
#include "CallStorageSpace.hpp"
#include "../../bits/PartType/TypeIndexConverter.hpp"
#include "../../bits/PartCall/CallDetails.hpp"
#include "../../bits/PartCall/CallOptions.hpp"
#include "../../bits/PartCall/CallArgumentOptions.hpp"
#include "../PartCall/NDetails/CallWrapper.hpp"
#include "./NDetails/CallStoragePlaceHolderRegistrator.hpp"
#include "CallStorageFunctionInfo.hpp"
#include "CallStorageDefinition.hpp"



namespace fcf {

    template <typename TFunction, typename ... TPackCallDetails>
    void CallStorage::add(std::string a_name,
                          TFunction a_function,
                          const std::tuple<TPackCallDetails...>& a_phs){
      addEx(a_name, "engine_cpu", std::string(), a_function, a_phs, std::string());
    }

    template <typename TFunction, typename ... TPackCallDetails>
    void CallStorage::add(std::string a_name,
                          TFunction a_function,
                          const TPackCallDetails& ... /*a_packCallDetails*/){
      typedef std::tuple<TPackCallDetails...> DetailsTuple;
      addEx(a_name, "engine_cpu", std::string(), a_function, DetailsTuple(), std::string());
    }

    /*
    template <typename TFunctionResult, typename... TArgPack>
    void CallStorage::add(std::string a_name,
                          TFunctionResult (*a_function)(TArgPack...)){
      add(a_name, "engine_cpu", std::string(), a_function, std::tuple<>(), std::string());
    }
    */

    template <typename TFunction, typename ... TPackCallDetails>
    void CallStorage::addEx(std::string a_name,
             const std::string& a_space,
             const std::string& a_sourceName,
             TFunction a_function,
             const CallDetailsPack<TPackCallDetails...>& /*a_phs*/,
             std::string a_sourceCode) {
      typename CallDetailsPack<TPackCallDetails...>::signatures_type signaturesTuple;
      addEx(a_name,
          a_space,
          a_sourceName,
          a_function,
          signaturesTuple,
          a_sourceCode);
    }

    template <typename TFunction, typename ... TPackCallDetails>
    void CallStorage::addEx(std::string a_name,
             const std::string& a_space,
             const std::string& a_sourceName,
             TFunction a_function,
             const std::tuple<TPackCallDetails...>& a_phs,
             std::string a_sourceCode) {
      a_name = _rtrim(a_name);
      FunctionSignature<TFunction> fs;
      CallStorageFunctionIndexes::iterator it = indexes.find(fs);
      if (it == indexes.end()) {
        CallStorageFunctionIndexes::value_type newItem(fs, CallStorageFunctionIndexes::value_type::second_type());
        it = indexes.insert(newItem).first;
      }
      CallStorageFunctionIndexes::value_type::second_type::iterator indexIt = it->second.find(a_name);

      int weight = 0;
      std::set<std::string> spaces;
      size_t bspace = 0;
      size_t cspace = 0;
      size_t lspace = a_space.length();
      while(true) {
        bool isCh = cspace != lspace &&
                    (
                      ((unsigned char)a_space[cspace] >= (unsigned char)'a' && (unsigned char)a_space[cspace] <= (unsigned char)'z') ||
                      ((unsigned char)a_space[cspace] >= (unsigned char)'A' && (unsigned char)a_space[cspace] <= (unsigned char)'Z') ||
                      ((unsigned char)a_space[cspace] >= (unsigned char)'0' && (unsigned char)a_space[cspace] <= (unsigned char)'9') ||
                      a_space[bspace] >= '_' ||
                      a_space[bspace] >= '*'
                    );
        if (bspace != cspace && !isCh) {
          std::string str(&a_space[bspace], &a_space[cspace]);
          if (str == "*" || str == "engine_cpu") {
            weight = 1;
          }
          spaces.insert(str);
        }
        if (cspace == lspace){
          break;
        }
        ++cspace;
        if (!isCh) {
          bspace = cspace;
        }
      }

      unsigned int index;
      if (indexIt == it->second.end()) {
        index = (unsigned int)functions.size();

        CallStorageFunctionInfo sfi;
        sfi.name       = a_name;
        sfi.signature  = fs;
        sfi.sourceName = a_function && weight ? a_sourceName : std::string();
        sfi.function   = a_function && weight ? (void*)a_function : (void*)0;

        CallStorageSpace sfs;
        sfs.sourceName = a_sourceName;
        sfs.function   = (void*)a_function;
        sfs.spaces     = spaces;
        sfs.code       = a_sourceCode;
        sfi.spaces.push_back(sfs);

        functions.push_back(sfi);

        it->second[a_name] = index;
      } else {
        index = indexIt->second;

        CallStorageFunctionInfo& sfi = functions[indexIt->second];

        if (!sfi.function && a_function && weight){
          sfi.function = (void*)a_function;
          sfi.sourceName = a_sourceName;
        }

        CallStorageSpace sfs;
        sfs.sourceName = a_sourceName;
        sfs.function   = (void*)a_function;
        sfs.spaces     = spaces;
        sfs.code       = a_sourceCode;
        sfi.spaces.push_back(sfs);
      }
      CallStorageSelectionFunctionGroups::iterator groupIt = groups.find(a_name);
      if (groupIt == groups.end()) {
        std::pair<std::string, CallStorageSelectionFunctionGroup> item;
        item.first = a_name;
        groupIt = groups.insert(item).first;
      }

      typedef typename FunctionSignature<TFunction>::args_type ArgsTupleType;
      groupIt->second.maxArgumentCount = std::max(groupIt->second.maxArgumentCount, (unsigned int)std::tuple_size<ArgsTupleType>::value);

      BaseFunctionSignature scs = fs.getSimpleCallSignature();
      BaseFunctionSignature sscs = scs;
      sscs.rcode = Type<void>().index();
      groupIt->second.callers.insert({
          sscs,
          CallStorageSelectionFunctionInfo{
            scs,
            index,
            NDetails::CallWrapper<TFunction>::getWrapper(),
            NDetails::CallWrapper<TFunction>::getRWrapper(),
            CallStorageSelectionFunctionInfo::PlaceHolderType()
          }
        });
      CallStorageSelectionFunctionsByArgNumber::iterator itTree = groupIt->second.callersTree.find(scs.asize);
      if (itTree == groupIt->second.callersTree.end()) {
        itTree = groupIt->second.callersTree.insert({scs.asize, {}});
      }
      itTree->second.insert({
                  sscs,
                  CallStorageSelectionFunctionInfo{
                    scs,
                    index,
                    NDetails::CallWrapper<TFunction>::getWrapper(),
                    NDetails::CallWrapper<TFunction>::getRWrapper(),
                    CallStorageSelectionFunctionInfo::PlaceHolderType()
                  }
                });

      NDetails::CallStoragePlaceHolderRegistrator<TFunction> placeHolderRegistrator;
      placeHolderRegistrator.function = a_function;
      placeHolderRegistrator.index = index;
      placeHolderRegistrator.fs = fs;
      placeHolderRegistrator.scs = scs;
      placeHolderRegistrator.groupIt = groupIt;
      placeHolderRegistrator.registry(*this, a_phs);
    }

    std::string CallStorage::_rtrim(std::string a_str) {
      size_t len = a_str.length(), i = len;
      for(; i && a_str[i-1] == ':'; --i);
      a_str.erase(i, len);
      return a_str;
    }


} // fcf namespace

#endif // #ifndef ___FCF__BASIS__BITS__CALL_STORAGE__CALL_STORAGE_HPP___
