#ifndef ___FCF_BASIS__BITS__PART_CALL_STORAGE__CALL_STORAGE_DEFINITION_HPP___
#define ___FCF_BASIS__BITS__PART_CALL_STORAGE__CALL_STORAGE_DEFINITION_HPP___

#include "CallStorageFunctionIndexes.hpp"
#include "CallStorageFunctionInfoVector.hpp"
#include "CallStorageSelectionFunctionGroup.hpp"
#include "../../bits/PartCall/NDetails/CallPlaceHolderSignatures.hpp"

namespace fcf {

  struct CallStorage {
    public:
      CallStorageFunctionIndexes         indexes;
      CallStorageFunctionInfoVector      functions;
      CallStorageSelectionFunctionGroups groups;

      template <typename TFunction, typename ... TPackCallDetails>
      inline void add(std::string a_name,
                      TFunction a_function,
                      const std::tuple<TPackCallDetails...>& a_phs);

      template <typename TFunction, typename ... TPackCallDetails>
      inline void add(std::string a_name,
                     TFunction a_function,
                     const TPackCallDetails& ... a_packCallDetails);

      template <typename TFunction, typename ... TPackCallDetails>
      void addEx(std::string a_name,
               const std::string& a_space,
               const std::string& a_sourceName,
               TFunction a_function,
               const NDetails::CallPlaceHolderSignatures<TPackCallDetails...>& a_phs,
               std::string a_sourceCode = std::string());

      template <typename TFunction, typename ... TPackCallDetails>
      void addEx(std::string a_name,
               const std::string& a_space,
               const std::string& a_sourceName,
               TFunction a_function,
               const std::tuple<TPackCallDetails...>& a_phs,
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
