#ifndef ___FCF__BASIS__BITS__CALL_STORAGE__CALL_STORAGE_REGISTRATOR_HPP___
#define ___FCF__BASIS__BITS__CALL_STORAGE__CALL_STORAGE_REGISTRATOR_HPP___

#include <algorithm>
#include "../../PartForeach.hpp"
#include "CallStorageSpace.hpp"
#include "../../bits/PartType/TypeIndexConverter.hpp"
#include "../../bits/PartCallPlaceHolder/NDetails/CallPlaceHolderSignatureGetter.hpp"
#include "../../bits/PartCall/CallOptions.hpp"
#include "../../bits/PartCall/CallArgumentOptions.hpp"
#include "../PartCall/NDetails/CallWrapper.hpp"
#include "CallStorageFunctionInfo.hpp"
#include "CallStorage.hpp"

namespace fcf {

    struct CallStorageRegistrator {

      template <typename TPlaceHolderSignatures, typename TFunctionResult, typename... TArgPack>
      CallStorageRegistrator(      std::string a_name,
                                   const std::string& a_space,
                                   const std::string& a_sourceName,
                                   TFunctionResult (*a_function)(TArgPack...),
                                   TPlaceHolderSignatures /*a_phs*/,
                                   std::string a_sourceCode = std::string()){
        a_name = _rtrim(a_name);
        typedef TFunctionResult (*function_type)(TArgPack...);
        FunctionSignature<TFunctionResult (TArgPack...)> fs;
        CallStorageFunctionIndexes::iterator it = getCallStorage().indexes.find(fs);
        if (it == getCallStorage().indexes.end()) {
          CallStorageFunctionIndexes::value_type newItem(fs, CallStorageFunctionIndexes::value_type::second_type());
          it = getCallStorage().indexes.insert(newItem).first;
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
          index = (unsigned int)getCallStorage().functions.size();

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

          getCallStorage().functions.push_back(sfi);

          it->second[a_name] = index;
        } else {
          index = indexIt->second;

          CallStorageFunctionInfo& sfi = getCallStorage().functions[indexIt->second];

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
        CallStorageSelectionFunctionGroups::iterator groupIt = getCallStorage().groups.find(a_name);
        if (groupIt == getCallStorage().groups.end()) {
          std::pair<std::string, CallStorageSelectionFunctionGroup> item;
          item.first = a_name;
          groupIt = getCallStorage().groups.insert(item).first;
        }
        groupIt->second.maxArgumentCount = std::max(groupIt->second.maxArgumentCount, (unsigned int)sizeof...(TArgPack));

        BaseFunctionSignature scs = fs.getSimpleCallSignature();
        BaseFunctionSignature sscs = scs;
        sscs.rcode = Type<void>().index();
        groupIt->second.callers.insert({
            sscs, 
            CallStorageSelectionFunctionInfo{
              scs, 
              index, 
              NDetails::CallWrapper<function_type>::getWrapper(),
              NDetails::CallWrapper<function_type>::getRWrapper(),
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
                      NDetails::CallWrapper<function_type>::getWrapper(),
                      NDetails::CallWrapper<function_type>::getRWrapper(),
                      CallStorageSelectionFunctionInfo::PlaceHolderType()
                    } 
                  });

        typename TPlaceHolderSignatures::signatures_type signatures;
        PlaceHolderRegistrator<function_type, TFunctionResult, TArgPack...> placeHolderRegistrator;
        placeHolderRegistrator.function = a_function;
        placeHolderRegistrator.index = index;
        placeHolderRegistrator.fs = fs;
        placeHolderRegistrator.scs = scs;
        placeHolderRegistrator.groupIt = groupIt;
        placeHolderRegistrator.registry(signatures);
      }

      inline std::string _rtrim(std::string a_str) {
        size_t len = a_str.length(), i = len;
        for(; i && a_str[i-1] == ':'; --i);
        a_str.erase(i, len);
        return a_str;
      }


      template <typename TFunction, typename TFunctionResult, typename ...TArgPack>
      struct PlaceHolderRegistrator {


        template <typename TSignatures>
        void registry(TSignatures& a_signatures){
          if (fs.asize >= groupIt->second.argumentOptions.size()){
            groupIt->second.argumentOptions.resize(fs.asize, 0);
          }

          _specificatorsData.clear();
          _argumentOptions.clear();
          fcf::foreach(a_signatures, *this);

          for(const std::pair<unsigned int, unsigned int>& options : _argumentOptions){
            groupIt->second.argumentOptions[options.first] |= options.second;

            std::pair<std::map<unsigned int, unsigned int>::iterator, bool> argumentOptionsInsertInfo
              = getCallStorage().functions[index].argumentOptions.insert({options.first, options.second});
            if (!argumentOptionsInsertInfo.second){
              argumentOptionsInsertInfo.first->second |= options.second;
            }
          }

          std::list<::fcf::CallPlaceHolderInfo> specDataState;
          invariantMapRegistry(_specificatorsData.begin(), specDataState);
        }

        void invariantMapRegistry(std::list<::fcf::CallPlaceHolderInfo>::iterator a_specDataIt, std::list<::fcf::CallPlaceHolderInfo>& a_specDataState){
          if (a_specDataIt == _specificatorsData.end()) {
            if (a_specDataState.size()) {
              mapRegistry(a_specDataState);
            }
            return;
          }
          std::list<::fcf::CallPlaceHolderInfo>::iterator nextSpecDataIt = a_specDataIt;
          ++nextSpecDataIt;

          invariantMapRegistry(nextSpecDataIt, a_specDataState);

          a_specDataState.push_back(*a_specDataIt);
          invariantMapRegistry(nextSpecDataIt, a_specDataState);
          a_specDataState.pop_back();
        }

        void mapRegistry(const std::list<::fcf::CallPlaceHolderInfo>& a_specDataState){
          BaseFunctionSignature phs = fs.getPlaceHolderSignature(a_specDataState.begin(), a_specDataState.end());
          phs.applySimpleCallSignature();
          phs.rcode = Type<void>().index();

          std::vector<::fcf::CallPlaceHolderInfo> placeHolder(a_specDataState.size());
          size_t i = 0;
          for(auto& sd : a_specDataState){
            placeHolder[i] = sd;
            ++i;
          }

          groupIt->second.callers.insert({
                                    phs,
                                    CallStorageSelectionFunctionInfo{
                                      scs,
                                      index,
                                      NDetails::CallWrapper<TFunction>::getWrapper(),
                                      NDetails::CallWrapper<TFunction>::getRWrapper(),
                                      placeHolder
                                      }
                                    });

          CallStorageSelectionFunctionsByArgNumber::iterator itTree = groupIt->second.callersTree.find(phs.asize);
          if (itTree == groupIt->second.callersTree.end()) {
            itTree = groupIt->second.callersTree.insert({phs.asize, {}});
          }
          BaseFunctionSignature sscs = scs;
          sscs.rcode = Type<void>().index();
          itTree->second.insert({ sscs, CallStorageSelectionFunctionInfo{
                                                                      scs,
                                                                      index,
                                                                      NDetails::CallWrapper<TFunction>::getWrapper(),
                                                                      NDetails::CallWrapper<TFunction>::getRWrapper(),
                                                                      placeHolder
                                                                      }
                                } );
        }

        template <typename Tuple, typename TIndex, unsigned int Flags>
        void _argOptionInitialize(Tuple& /*a_tuple*/, TIndex /*a_index*/, const CallArgumentOptions<Flags>& /*a_options*/, unsigned int a_argumentNumber) {
          _argumentOptions.push_back( {a_argumentNumber, Flags} );
        }

        template <typename Tuple, typename TIndex, typename TArg>
        void _argOptionInitialize(Tuple& /*a_tuple*/, TIndex /*a_index*/, const TArg& /*a_arg*/, unsigned int /*a_argumentNumber*/) {
        }

        FCF_FOREACH_METHOD_WRAPPER(ArgOptionInitializer, PlaceHolderRegistrator, _argOptionInitialize);

        template <typename Tuple, typename TIndex, typename TSignature>
        void operator()(Tuple& /*a_tuple*/, TIndex /*a_index*/, TSignature& /*a_signatureGetter*/) {
          unsigned int specificatorIndex = Type<typename TSignature::specificator_type>().index();
          if (specificatorIndex == Type<CallOptions>().index()){
            typename TSignature::short_function_signature_type::args_type tuple;
            ArgOptionInitializer argOptionInitializer(this);
            foreach(tuple, argOptionInitializer, (unsigned int) std::max((int)TSignature::ArgIndex-1, (int)0));
          } else {
            if (specificatorIndex == Type<Nop>().index()){
              specificatorIndex = 0;
            }

            if (!TSignature::ArgIndex) {
              return;
            }

            _specificatorsData.push_back(TSignature::getPlaceHolderInfo());

            if (TSignature::ArgIndex > groupIt->second.specificatorsByArgIndex.size()){
              groupIt->second.specificatorsByArgIndex.resize(TSignature::ArgIndex);
            }
            groupIt->second.specificatorsByArgIndex[TSignature::ArgIndex-1].push_back(specificatorIndex);
          }

        }

        TFunction                                             function;
        unsigned int                                          index;
        FunctionSignature<TFunctionResult (TArgPack...)>      fs;
        BaseFunctionSignature                                 scs;
        CallStorageSelectionFunctionGroups::iterator          groupIt;
        std::list<::fcf::CallPlaceHolderInfo>                 _specificatorsData;
        std::list< std::pair<unsigned int, unsigned int> >    _argumentOptions;
      };

      template <typename TFunction>
      static unsigned int getIndex(const std::string& a_name){
        FunctionSignature<TFunction> fs;
        CallStorageFunctionIndexes::iterator it = getCallStorage().indexes.find(fs);
        if (it == getCallStorage().indexes.end()) {
          throw FunctionNotFoundException(__FILE__, __LINE__, a_name);
        }
        CallStorageFunctionIndexes::value_type::second_type::iterator itFunc = it->second.find(a_name);
        if (itFunc == it->second.end()) {
          throw FunctionNotFoundException(__FILE__, __LINE__, a_name);
        }
        return itFunc->second;
      }

      static unsigned int getSize(){
        return (unsigned int)getCallStorage().functions.size();
      }

      static const CallStorageFunctionInfo& getFunctionInfo(unsigned int a_index){
        return getCallStorage().functions[a_index];
      }
    };

} // fcf namespace


#endif // #ifndef ___FCF__BASIS__BITS__CALL_STORAGE__CALL_STORAGE_REGISTRATOR_HPP___
