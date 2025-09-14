#ifndef ___FCF_BASIS__BITS__INDEXABLE_FUNCTION_REGISTRATOR_HPP___
#define ___FCF_BASIS__BITS__INDEXABLE_FUNCTION_REGISTRATOR_HPP___

#include "../foreach.hpp"
#include "../bits/ArgPlaceHolder/Caller.hpp"
#include "./IndexableFunctionSpace.hpp"
#include "./IndexableFunctionInfo.hpp"
#include "../Details/IndexableFunction/Storage.hpp"
#include "../Details/IndexableFunction/SimpleCaller.hpp"
#include "Type/Details/TypeIndex.hpp"
#include "ArgPlaceHolder/Signature.hpp"
#include "Call/Details/CallWrapper.hpp"

namespace fcf {

    struct IndexableFunctionRegistrator {
      template <typename TPlaceHolderSignatures, typename TFunctionResult, typename... TArgPack>
      IndexableFunctionRegistrator(const std::string& a_name,
                                   const std::string& a_space,
                                   const std::string& a_sourceName,
                                   TFunctionResult (*a_function)(TArgPack...),
                                   TPlaceHolderSignatures a_phs,
                                   std::string a_sourceCode = std::string()){
        typedef TFunctionResult (*function_type)(TArgPack...);
        FunctionSignature<TFunctionResult (TArgPack...)> fs;
        Details::IndexableFunction::CallFunctionIndexes::iterator it = Details::IndexableFunction::getStorage().indexes.find(fs);
        if (it == Details::IndexableFunction::getStorage().indexes.end()) {
          Details::IndexableFunction::CallFunctionIndexes::value_type newItem(fs, Details::IndexableFunction::CallFunctionIndexes::value_type::second_type());
          it = Details::IndexableFunction::getStorage().indexes.insert(newItem).first;
        }
        Details::IndexableFunction::CallFunctionIndexes::value_type::second_type::iterator indexIt = it->second.find(a_name);

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
          index = Details::IndexableFunction::getStorage().functions.size();

          IndexableFunctionInfo sfi;
          sfi.name       = a_name;
          sfi.signature  = fs;
          sfi.sourceName = a_function && weight ? a_sourceName : std::string();
          sfi.function   = a_function && weight ? (void*)a_function : (void*)0;

          IndexableFunctionSpace sfs;
          sfs.sourceName = a_sourceName;
          sfs.function   = (void*)a_function;
          sfs.spaces     = spaces;
          sfs.code       = a_sourceCode;
          sfi.spaces.push_back(sfs);

          Details::IndexableFunction::getStorage().functions.push_back(sfi);

          it->second[a_name] = index;
        } else {
          index = indexIt->second;

          IndexableFunctionInfo& sfi = Details::IndexableFunction::getStorage().functions[indexIt->second];

          if (!sfi.function && a_function && weight){
            sfi.function = (void*)a_function;
            sfi.sourceName = a_sourceName;
          }

          IndexableFunctionSpace sfs;
          sfs.sourceName = a_sourceName;
          sfs.function   = (void*)a_function;
          sfs.spaces     = spaces;
          sfs.code       = a_sourceCode;
          sfi.spaces.push_back(sfs);
        }
        fcf::Details::IndexableFunction::CallFunctionGroups::iterator groupIt = Details::IndexableFunction::getStorage().groups.find(a_name);
        if (groupIt == Details::IndexableFunction::getStorage().groups.end()) {
          std::pair<std::string, fcf::Details::IndexableFunction::CallFunctionGroup> item;
          item.first = a_name;
          groupIt = Details::IndexableFunction::getStorage().groups.insert(item).first;
        }

        BaseFunctionSignature scs = fs.getSimpleCallSignature();
        groupIt->second.callers.insert({scs, Details::IndexableFunction::CallFunctionInfo{scs, index, (void*)Details::IndexableFunction::getSimpleCaller(a_function), Details::CallWrapper<function_type>::getWrapper()}});
        Details::IndexableFunction::CallFunctionsByArgNumber::iterator itTree = groupIt->second.callersTree.find(scs.asize);
        if (itTree == groupIt->second.callersTree.end()) {
          itTree = groupIt->second.callersTree.insert({scs.asize, {}});
        }
        itTree->second.insert({ scs, Details::IndexableFunction::CallFunctionInfo{scs, index, (void*)Details::IndexableFunction::getSimpleCaller(a_function), Details::CallWrapper<function_type>::getWrapper(),} });

        typename TPlaceHolderSignatures::signatures_type signatures;
        PlaceHolderRegistrator<function_type, TFunctionResult, TArgPack...> placeHolderRegistrator;
        placeHolderRegistrator.function = a_function;
        placeHolderRegistrator.index = index;
        placeHolderRegistrator.fs = fs;
        placeHolderRegistrator.scs = scs;
        placeHolderRegistrator.groupIt = groupIt;
        placeHolderRegistrator.registry(signatures);
        //fcf::foreach(signatures, placeHolderRegistrator);

        //placeHolderRegistrator.specificatorsData;



        //::fcf::ArgPlaceHolder::SignatureData sd =

        /*
        if (TPlaceHolderSignatures::enable) {
          unsigned int specificatorIndex =
            ::fcf::Details::Basis::Type::TypeIndex< typename TPlaceHolderSignatures::specificator_type >::index();
          std::map<unsigned int, Details::IndexableFunction::ShortSignatures>::iterator itGrpSpec =
            groupIt->second.specificators.find(specificatorIndex);
          if (itGrpSpec == groupIt->second.specificators.end()) {
            std::pair<unsigned int, Details::IndexableFunction::ShortSignatures> item;
            item.first = specificatorIndex;
            itGrpSpec = groupIt->second.specificators.insert(item).first;
          }
          typename TPlaceHolderSignatures::short_function_signature_type sfs;
          fcf::Details::IndexableFunction::ShortSignature ss;
          ss.fullSignature = fs;
          ss.index = index;
          typedef ::fcf::ArgPlaceHolder::Caller<typename TPlaceHolderSignatures::arguments_type, TFunctionResult (TArgPack...)> caller_type;
          ss.caller = (void*)static_cast<typename caller_type::caller_type>(caller_type::call);
          itGrpSpec->second[sfs] = ss;

          BaseFunctionSignature scsfs = sfs.getSimpleCallSignature();
          Details::IndexableFunction::CallFunctionsByArgNumber::iterator itTree = groupIt->second.callersTree.find(scsfs.asize);
          if (itTree == groupIt->second.callersTree.end()) {
            itTree = groupIt->second.callersTree.insert({scsfs.asize, {}}).first;
          }
          itTree->second[scsfs] = Details::IndexableFunction::CallFunctionInfo{scsfs, index, (void*)ss.caller};
        }
        */
      }

      template <typename TFunction, typename TFunctionResult, typename ...TArgPack>
      struct PlaceHolderRegistrator {


        template <typename TSignatures>
        void registry(TSignatures& a_signatures){
          _specificatorsData.clear();
          fcf::foreach(a_signatures, *this);

          std::list<ArgPlaceHolder::SignatureData> specDataState;
          invariantMapRegistry(_specificatorsData.begin(), specDataState);
        }

        void invariantMapRegistry(std::list<ArgPlaceHolder::SignatureData>::iterator a_specDataIt, std::list<ArgPlaceHolder::SignatureData>& a_specDataState){
          if (a_specDataIt == _specificatorsData.end()) {
            if (a_specDataState.size()) {
              mapRegistry(a_specDataState);
            }
            return;
          }
          std::list<ArgPlaceHolder::SignatureData>::iterator nextSpecDataIt = a_specDataIt;
          ++nextSpecDataIt;

          invariantMapRegistry(nextSpecDataIt, a_specDataState);

          a_specDataState.push_back(*a_specDataIt);
          invariantMapRegistry(nextSpecDataIt, a_specDataState);
          a_specDataState.pop_back();
        }

        void mapRegistry(const std::list<ArgPlaceHolder::SignatureData>& a_specDataState){
          BaseFunctionSignature phs = fs.getPlaceHolderSignature(a_specDataState.begin(), a_specDataState.end());
          phs.applySimpleCallSignature();

          std::vector<ArgPlaceHolder::SignatureData> placeHolder(a_specDataState.size());
          size_t i = 0;
          for(auto& sd : a_specDataState){
            placeHolder[i] = sd;
            ++i;
          }

          groupIt->second.callers.insert({ 
                                    phs, 
                                    Details::IndexableFunction::CallFunctionInfo{
                                      scs, 
                                      index, 
                                      (void*)Details::IndexableFunction::getSimpleCaller(function), 
                                      Details::CallWrapper<TFunction>::getWrapper(),
                                      placeHolder
                                      } 
                                    });

          Details::IndexableFunction::CallFunctionsByArgNumber::iterator itTree = groupIt->second.callersTree.find(phs.asize);
          if (itTree == groupIt->second.callersTree.end()) {
            itTree = groupIt->second.callersTree.insert({phs.asize, {}});
          }
          itTree->second.insert({ scs, Details::IndexableFunction::CallFunctionInfo{
                                                                      scs,
                                                                      index,
                                                                      (void*)Details::IndexableFunction::getSimpleCaller(function),
                                                                      Details::CallWrapper<TFunction>::getWrapper(),
                                                                      placeHolder
                                                                      }
                                } );
        }

        template <typename Tuple, typename TIndex, typename TSignature>
        void operator()(Tuple& a_tuple, TIndex a_index, TSignature& a_signature) {
          unsigned int specificatorIndex =
            ::fcf::Details::Basis::Type::TypeIndex< typename TSignature::specificator_type >::index();

          if (!TSignature::ArgIndex) {
            return;
          }

          _specificatorsData.push_back(TSignature::getSignatureData());

          if (TSignature::ArgIndex > groupIt->second.specificatorsByArgIndex.size()){
            groupIt->second.specificatorsByArgIndex.resize(TSignature::ArgIndex);
          }
          groupIt->second.specificatorsByArgIndex[TSignature::ArgIndex-1].push_back(specificatorIndex);

          std::map<unsigned int, Details::IndexableFunction::ShortSignatures>::iterator itGrpSpec =
            groupIt->second.specificators.find(specificatorIndex);
          if (itGrpSpec == groupIt->second.specificators.end()) {
            std::pair<unsigned int, Details::IndexableFunction::ShortSignatures> item;
            item.first = specificatorIndex;
            itGrpSpec = groupIt->second.specificators.insert(item).first;
          }
          typename TSignature::short_function_signature_type sfs;
          fcf::Details::IndexableFunction::ShortSignature ss;
          ss.fullSignature = fs;
          ss.index = index;
          typedef ::fcf::ArgPlaceHolder::Caller<typename TSignature::arguments_type, TFunctionResult (TArgPack...)> caller_type;
          ss.caller = (void*)static_cast<typename caller_type::caller_type>(caller_type::call);
          itGrpSpec->second[sfs] = ss;

          /*
          BaseFunctionSignature scsfs = sfs.getSimpleCallSignature();
          Details::IndexableFunction::CallFunctionsByArgNumber::iterator itTree = groupIt->second.callersTree.find(scsfs.asize);
          if (itTree == groupIt->second.callersTree.end()) {
            itTree = groupIt->second.callersTree.insert({scsfs.asize, {}}).first;
          }
          itTree->second[scsfs] = Details::IndexableFunction::CallFunctionInfo{scsfs, index, (void*)ss.caller};
          */
        }

        TFunction                                                       function;
        unsigned int                                                    index;
        FunctionSignature<TFunctionResult (TArgPack...)>                fs;
        BaseFunctionSignature                                           scs;
        fcf::Details::IndexableFunction::CallFunctionGroups::iterator   groupIt;
        std::list<ArgPlaceHolder::SignatureData>                        _specificatorsData;
      };

      template <typename TFunction>
      static unsigned int getIndex(const std::string& a_name){
        FunctionSignature<TFunction> fs;
        Details::IndexableFunction::CallFunctionIndexes::iterator it = Details::IndexableFunction::getStorage().indexes.find(fs);
        if (it == Details::IndexableFunction::getStorage().indexes.end()) {
          throw std::runtime_error(std::string() + "Function \"" + a_name + "\" not found");
        }
        Details::IndexableFunction::CallFunctionIndexes::value_type::second_type::iterator itFunc = it->second.find(a_name);
        if (itFunc == it->second.end()) {
          throw std::runtime_error(std::string() + "Function \"" + a_name + "\" not found");
        }
        return itFunc->second;
      }

      static unsigned int getSize(){
        return (unsigned int)Details::IndexableFunction::getStorage().functions.size();
      }

      static const IndexableFunctionInfo& getFunctionInfo(unsigned int a_index){
        return Details::IndexableFunction::getStorage().functions[a_index];
      }
    };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__INDEXABLE_FUNCTION_REGISTRATOR_HPP___
