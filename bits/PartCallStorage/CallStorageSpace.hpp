#ifndef _FCF_BASIS__BITS__CALL_STORAGE__CALL_STORAGE_SPACE_HPP___
#define _FCF_BASIS__BITS__CALL_STORAGE__CALL_STORAGE_SPACE_HPP___

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

#endif // #ifndef _FCF_BASIS__BITS__CALL_STORAGE__CALL_STORAGE_SPACE_HPP___
