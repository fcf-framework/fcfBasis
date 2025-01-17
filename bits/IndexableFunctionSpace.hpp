#ifndef ___FCF_BASIS__INDEXABLE_FUNCTION_SPACE_HPP___
#define ___FCF_BASIS__INDEXABLE_FUNCTION_SPACE_HPP___

#include <string>
#include <set>

namespace fcf {

  struct IndexableFunctionSpace {
    std::string           sourceName;
    void*                 function;
    std::set<std::string> spaces;
    std::string           code;
  };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__INDEXABLE_FUNCTION_SPACE_HPP___
