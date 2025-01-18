#ifndef ___FCF_BASIS__BITS__INDEXABLE_FUNCTION_INFO_HPP___
#define ___FCF_BASIS__BITS__INDEXABLE_FUNCTION_INFO_HPP___

#include <vector>
#include "../FunctionSignature.hpp"
#include "IndexableFunctionSpace.hpp"

namespace fcf {

  struct IndexableFunctionInfo {
    std::string                         name;
    BaseFunctionSignature               signature;
    std::string                         sourceName;
    void*                               function;
    std::vector<IndexableFunctionSpace> spaces;

    template <typename TSpaceNames>
    std::vector<IndexableFunctionSpace>::const_iterator getSpace(const TSpaceNames& a_spaces) const{
      int                                      curWeight = 0;
      std::vector<IndexableFunctionSpace>::const_iterator curIt     = spaces.cend();
      for(std::vector<IndexableFunctionSpace>::const_iterator it = spaces.cbegin(); it != spaces.cend(); ++it) {
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

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__INDEXABLE_FUNCTION_INFO_HPP___
