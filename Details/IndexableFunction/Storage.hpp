#ifndef ___FCF_BASIS__DETAILS__INDEXABLE_FUNCTION__STORAGE_HPP___
#define ___FCF_BASIS__DETAILS__INDEXABLE_FUNCTION__STORAGE_HPP___

#include <set>
#include <unordered_map>
#include <map>
#include "../../macro.hpp"
#include "../../bits/IndexableFunctionInfo.hpp"
namespace fcf {
  namespace Details {
    namespace IndexableFunction {

        typedef std::map< BaseFunctionSignature, std::map<std::string, unsigned int>  > Indexes;

        struct ShortSignature {
          BaseFunctionSignature fullSignature;
          unsigned int          index;
          void*                 caller;
        };
        typedef std::map<BaseFunctionSignature, ShortSignature> ShortSignatures;

        struct CallerInfo {
          BaseFunctionSignature callerSignature;
          unsigned int          index;
          unsigned int          adaptSpecificator;
          void*                 caller;
        };

        typedef std::map<BaseFunctionSignature, CallerInfo>           CallersMap;
        typedef std::unordered_map<unsigned int, CallersMap>          CallersTree;
        typedef std::unordered_map<BaseFunctionSignature, CallerInfo> Callers;

        struct FunctionGroup {
          std::map<unsigned int, ShortSignatures>   specificators;
          Callers                                   callers;
          CallersTree                               callersTree;
        };

        typedef std::unordered_map<std::string, FunctionGroup > Groups;
        //typedef std::map<std::string, FunctionGroup > Groups;

        struct Storage {
          Indexes                              indexes;
          std::vector<IndexableFunctionInfo>   functions;
          Groups                               groups;
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
