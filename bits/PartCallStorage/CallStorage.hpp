#ifndef _FCF_BASIS__BITS__CALL_STORAGE__CALL_STORAGE_HPP___
#define _FCF_BASIS__BITS__CALL_STORAGE__CALL_STORAGE_HPP___

#include "../../PartForeach.hpp"
#include "CallStorageSpace.hpp"
#include "../../bits/PartType/TypeIndexConverter.hpp"
#include "../../bits/PartCall/CallDetails.hpp"
#include "../../bits/PartCall/CallOptions.hpp"
#include "../../bits/PartCall/CallArgumentOptions.hpp"
#include "../PartCall/NDetails/CallWrapper.hpp"
#include "./NDetails/CallStoragePlaceHolderRegistrator.hpp"
#include "CallStorageFunctionInfo.hpp"
#include "CallStorageDecl.hpp"
#include "CallStorageBase.hpp"




namespace fcf {

    template <typename TFunction, typename ... TPackCallDetails>
    void CallStorage::add(std::string a_name,
                          TFunction a_function,
                          const std::tuple<TPackCallDetails...>& a_phs){
      addEx(a_name, "cpu", std::string(), a_function, a_phs, std::string());
    }

    template <typename TFunction, typename ... TPackCallDetails>
    void CallStorage::add(std::string a_name,
                          TFunction a_function,
                          const TPackCallDetails& ... /*a_packCallDetails*/){
      typedef std::tuple<TPackCallDetails...> DetailsTuple;
      addEx(a_name, "cpu", std::string(), a_function, DetailsTuple(), std::string());
    }

    /*
    template <typename TFunctionResult, typename... TArgPack>
    void CallStorage::add(std::string a_name,
                          TFunctionResult (*a_function)(TArgPack...)){
      add(a_name, "cpu", std::string(), a_function, std::tuple<>(), std::string());
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
      FunctionSignature<TFunction> fs;

      typedef typename FunctionSignature<TFunction>::args_type ArgsTupleType;
      unsigned int argc = (unsigned int)std::tuple_size<ArgsTupleType>::value;

      CallStorageSelectionFunctionGroups::iterator groupIterator;
      BaseFunctionSignature simpleCallSignature = fs.getSimpleCallSignature();
      unsigned int index;

      this->_add(a_name,
                 a_space,
                 a_sourceName,
                 fs,
                 simpleCallSignature,
                 (void*)a_function,
                 argc,
                 a_sourceCode,
                 NDetails::CallWrapper<TFunction>::getWrapper(),
                 NDetails::CallWrapper<TFunction>::getRWrapper(),
                 index,
                 groupIterator
               );

      NDetails::CallStoragePlaceHolderRegistrator<TFunction> placeHolderRegistrator;
      placeHolderRegistrator.function = a_function;
      placeHolderRegistrator.index = index;
      placeHolderRegistrator.fs = fs;
      placeHolderRegistrator.scs = simpleCallSignature;
      placeHolderRegistrator.groupIt = groupIterator;
      placeHolderRegistrator.registry(*this, a_phs);
    }

    template <typename TFunction>
    unsigned int CallStorage::getIndex(const std::string& a_name) const{
      const static FunctionSignature<TFunction> signature;
      CallStorageFunctionIndexes::const_iterator it1 = indexes.find(signature);
      if (it1 == indexes.end()){
        return 0;
      }
      CallStorageFunctionIndexes::mapped_type::const_iterator it2 = it1->second.find(a_name);
      if (it2 == it1->second.end()){
        return 0;
      }
      return it2->second;
    }

    std::string CallStorage::_rtrim(std::string a_str) {
      size_t len = a_str.length(), i = len;
      for(; i && a_str[i-1] == ':'; --i);
      a_str.erase(i, len);
      return a_str;
    }


} // fcf namespace

#endif // #ifndef _FCF_BASIS__BITS__CALL_STORAGE__CALL_STORAGE_HPP___
