#ifndef ___FCF__BASIS__BITS__CALL_STORAGE__CALL_STORAGE_SPACE_HPP___
#define ___FCF__BASIS__BITS__CALL_STORAGE__CALL_STORAGE_SPACE_HPP___

#include <string>
#include <set>

namespace fcf {

  struct CallStorageSpace {
    std::string           sourceName;
    void*                 function;
    std::set<std::string> spaces;
    std::string           code;
  };

} // fcf namespace

#endif // #ifndef ___FCF__BASIS__BITS__CALL_STORAGE__CALL_STORAGE_SPACE_HPP___
