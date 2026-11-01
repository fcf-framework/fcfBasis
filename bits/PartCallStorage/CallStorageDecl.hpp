#ifndef _FCF_BASIS__BITS__PART_CALL_STORAGE__CALL_STORAGE_DEFINITION_HPP___
#define _FCF_BASIS__BITS__PART_CALL_STORAGE__CALL_STORAGE_DEFINITION_HPP___

#include "../../bits/PartCall/CallDetailsPack.hpp"
#include "CallStorageBaseDecl.hpp"

namespace fcf {

  struct CallStorage : public CallStorageBase {
    public:
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
               const CallDetailsPack<TPackCallDetails...>& a_phs,
               std::string a_sourceCode = std::string());

      template <typename TFunction, typename ... TPackCallDetails>
      void addEx(std::string a_name,
               const std::string& a_space,
               const std::string& a_sourceName,
               TFunction a_function,
               const std::tuple<TPackCallDetails...>& a_phs,
               std::string a_sourceCode = std::string());

      template <typename TFunction>
      unsigned int getIndex(const std::string& a_name) const;
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

#endif // #ifndef _FCF_BASIS__BITS__PART_CALL_STORAGE__CALL_STORAGE_DEFINITION_HPP___
