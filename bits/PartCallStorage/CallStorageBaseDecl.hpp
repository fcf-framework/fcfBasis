#ifndef _FCF_BASIS__BITS__PART_CALL_STORAGE__CALL_STORAGE_BASE_DECL_HPP___
#define _FCF_BASIS__BITS__PART_CALL_STORAGE__CALL_STORAGE_BASE_DECL_HPP___

#include <string>
#include "CallStorageFunctionIndexes.hpp"
#include "CallStorageFunctionInfoVector.hpp"
#include "CallStorageSelectionFunctionGroup.hpp"
#include "../../bits/PartCall/FunctionSignature.hpp"

namespace fcf{

  struct CallStorageBase {
    public:
      CallStorageFunctionIndexes         indexes;
      CallStorageFunctionInfoVector      functions;
      CallStorageSelectionFunctionGroups groups;

    protected:
      void _add(std::string a_name,
                const std::string& a_space,
                const std::string& a_sourceName,
                const BaseFunctionSignature& a_functionSignature,
                const BaseFunctionSignature& a_simpleCallSignature,
                void* a_function,
                unsigned int a_argc,
                std::string a_sourceCode,
                void (*a_wrapper)(void*, void**),
                Variant (*a_rwrapper)(void*, void**),
                unsigned int& a_dstIndex,
                CallStorageSelectionFunctionGroups::iterator& a_dstGroupIterator
               );
      std::string _rtrim(std::string a_str);
  };

} // fcf namespace

#endif // #ifndef _FCF_BASIS__BITS__PART_CALL_STORAGE__CALL_STORAGE_BASE_DECL_HPP___
