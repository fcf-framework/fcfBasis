#ifndef ___FCF_BASIS__BITS__PART_CALL_STORAGE__NDETAILS__CALL_STORAGE_PLACE_HOLDER_REGISTRATOR_HPP___
#define ___FCF_BASIS__BITS__PART_CALL_STORAGE__NDETAILS__CALL_STORAGE_PLACE_HOLDER_REGISTRATOR_HPP___

#include "../../../PartForeach.hpp"
#include "../../PartCall/NDetails/CallWrapper.hpp"
#include "../CallStorageDefinition.hpp"

namespace fcf{

  namespace NDetails {

    template <typename TFunction, typename TFunctionResult, typename ...TArgPack>
    struct CallStoragePlaceHolderRegistrator {

      template <typename TSignatures>
      inline void registry(TSignatures& a_signatures){
        registry(getCallStorage(), a_signatures);
      }

      template <typename TSignatures>
      void registry(CallStorage& a_storage, TSignatures& a_signatures){
        if (fs.asize >= groupIt->second.argumentOptions.size()){
          groupIt->second.argumentOptions.resize(fs.asize, 0);
        }

        _specificatorsData.clear();
        _argumentOptions.clear();
        fcf::foreach(a_signatures, *this);

        for(const std::pair<unsigned int, unsigned int>& options : _argumentOptions){
          groupIt->second.argumentOptions[options.first] |= options.second;

          std::pair<std::map<unsigned int, unsigned int>::iterator, bool> argumentOptionsInsertInfo
            = a_storage.functions[index].argumentOptions.insert({options.first, options.second});
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

      FCF_FOREACH_METHOD_WRAPPER(ArgOptionInitializer, CallStoragePlaceHolderRegistrator, _argOptionInitialize);

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

  } // NDetails namespace

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_CALL_STORAGE__NDETAILS__CALL_STORAGE_PLACE_HOLDER_REGISTRATOR_HPP___
