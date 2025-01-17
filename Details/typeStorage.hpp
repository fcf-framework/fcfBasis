#ifndef ___FCF_BASIS__DETAILS__TYPE_STORAGE_HPP___
#define ___FCF_BASIS__DETAILS__TYPE_STORAGE_HPP___

#include <map>
#include "../macro.hpp"

namespace fcf {
  namespace Details {

    typedef std::map<std::string, unsigned int> TypeStorage;

    FCF_BASIS_DELC_EXTERN FCF_BASIS_DECL_EXPORT TypeStorage typeStorage;

  } // Details namespace
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__DETAILS__TYPE_STORAGE_HPP___
