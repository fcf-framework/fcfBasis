#ifndef ___FCF_BASIS__DETAILS__INDEXABLE_FUNCTION__STORAGE_HPP___
#define ___FCF_BASIS__DETAILS__INDEXABLE_FUNCTION__STORAGE_HPP___

#include <vector>
#include <set>
#include <unordered_map>
#include <map>
#include "../../macro.hpp"
#include "../../bits/IndexableFunctionInfo.hpp"
#include "../../bits/ArgPlaceHolder/SignatureData.hpp"
namespace fcf {
  namespace Details {
    namespace IndexableFunction {


        typedef std::map< BaseFunctionSignature, std::map<std::string, unsigned int>  > CallFunctionIndexes;

        struct ShortSignature {
          BaseFunctionSignature fullSignature;
          unsigned int          index;
          void*                 caller;
        };
        typedef std::map<BaseFunctionSignature, ShortSignature> ShortSignatures;
        typedef std::vector<IndexableFunctionInfo> CallFunctionVector;

        struct CallFunctionInfo {
          BaseFunctionSignature                      callerSignature;
          unsigned int                               index;
          void                                      (*lcaller)(void*, void**);
          std::vector<ArgPlaceHolder::SignatureData> placeHolder;
        };

        typedef std::multimap<BaseFunctionSignature, CallFunctionInfo>           CallFunctionsMap;
        typedef std::unordered_multimap<unsigned int, CallFunctionsMap>          CallFunctionsByArgNumber;
        typedef std::unordered_multimap<BaseFunctionSignature, CallFunctionInfo> CallFunctions;

        struct CallFunctionGroup {
          std::map<unsigned int, ShortSignatures>   specificators;
          std::vector< std::vector<unsigned int> >  specificatorsByArgIndex;
          CallFunctions                             callers;
          CallFunctionsByArgNumber                  callersTree;
        };

        typedef std::unordered_map<std::string, CallFunctionGroup > CallFunctionGroups;
        //typedef std::map<std::string, CallFunctionGroup > CallFunctionGroups;

        struct Storage {
          CallFunctionIndexes indexes;
          CallFunctionVector  functions;
          CallFunctionGroups  groups;
        };

        FCF_BASIS_DELC_EXTERN FCF_BASIS_DECL_EXPORT Storage* g_storage;

        Storage& getStorage();

        #ifdef FCF_BASIS_IMPLEMENTATION
        Storage& getStorage(){
          if (!g_storage) {
            g_storage = new Storage();
          }
          return *g_storage;
        }
        #endif

        FCF_INITIAZE_GLOBAL_PTR(g_storage, Storage);

    } // IndexableFunctionRegistrator namespace
  } // Details namespace
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__DETAILS__INDEXABLE_FUNCTION_REGISTRATOR__STORAGE_HPP___
