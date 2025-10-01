#ifndef ___FCF__BASIS__BITS__CALL_STORAGE__CALL_STORAGE_FUNCTION_INFO_HPP___
#define ___FCF__BASIS__BITS__CALL_STORAGE__CALL_STORAGE_FUNCTION_INFO_HPP___

#include <string>
#include "../../FunctionSignature.hpp"
#include "CallStorageSpace.hpp"

namespace fcf {
 
  struct CallStorageFunctionInfo {
    std::string                   name;
    BaseFunctionSignature         signature;
    std::string                   sourceName;
    void*                         function;
    std::vector<CallStorageSpace> spaces;

    template <typename TSpaceNames>
    std::vector<CallStorageSpace>::const_iterator getSpace(const TSpaceNames& a_spaces) const{
      int                                      curWeight = 0;
      std::vector<CallStorageSpace>::const_iterator curIt     = spaces.cend();
      for(std::vector<CallStorageSpace>::const_iterator it = spaces.cbegin(); it != spaces.cend(); ++it) {
        int weight = 0;
        if (it->spaces.find("*") != it->spaces.end()){
          weight += 1;
        }
        for(auto& spaceName : a_spaces) {
          if (it->spaces.find(spaceName) != it->spaces.end()){
            weight += 1 << 8;
          }
        }
        if (weight > curWeight){
          curWeight = weight;
          curIt = it;
        }
      }
      return curIt;
    }
  };

} // namespace fcf

#endif // #ifndef ___FCF__BASIS__BITS__CALL_STORAGE__CALL_STORAGE_FUNCTION_INFO_HPP___
