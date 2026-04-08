#ifndef ___FCF_BASIS__BITS__PART_CALL_STORAGE__CALL_STORAGE_DEFINITION_HPP___
#define ___FCF_BASIS__BITS__PART_CALL_STORAGE__CALL_STORAGE_DEFINITION_HPP___

#include "CallStorageFunctionIndexes.hpp"
#include "CallStorageFunctionInfoVector.hpp"
#include "CallStorageSelectionFunctionGroup.hpp"

namespace fcf {

  struct CallStorage {
    public:
      CallStorageFunctionIndexes         indexes;
      CallStorageFunctionInfoVector      functions;
      CallStorageSelectionFunctionGroups groups;

      template <typename TFunctionResult, typename... TArgPack>
      inline void add(std::string a_name,
               TFunctionResult (*a_function)(TArgPack...));

      template <typename TSignaturesTuple, typename TFunctionResult, typename... TArgPack>
      inline void add(std::string a_name,
               TFunctionResult (*a_function)(TArgPack...),
               const TSignaturesTuple& a_phs);

      template <typename TTuplePlaceHolderSignatures, typename TFunctionResult, typename... TArgPack>
      void add(std::string a_name,
               const std::string& a_space,
               const std::string& a_sourceName,
               TFunctionResult (*a_function)(TArgPack...),
               TTuplePlaceHolderSignatures a_phs,
               std::string a_sourceCode = std::string());

      template <typename TPlaceHolderSignatures, typename TFunctionResult, typename... TArgPack>
      void addWithSignatures(std::string a_name,
               const std::string& a_space,
               const std::string& a_sourceName,
               TFunctionResult (*a_function)(TArgPack...),
               TPlaceHolderSignatures a_phs,
               std::string a_sourceCode = std::string());


    protected:
      inline std::string _rtrim(std::string a_str);

  };

  CallStorage& getCallStorage();

  #ifdef FCF_BASIS_IMPLEMENTATION
  CallStorage& getCallStorage(){
    static CallStorage storage;
    return storage;
  }
  #endif

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_CALL_STORAGE__CALL_STORAGE_DEFINITION_HPP___
