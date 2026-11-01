#ifndef _FCF_BASIS__BITS__PART_EXCEPTION__ERROR_DECL_HPP___
#define _FCF_BASIS__BITS__PART_EXCEPTION__ERROR_DECL_HPP___

#include "../../macro.hpp"
#include "ExceptionPredecl.hpp"

namespace fcf {

  struct FCF_BASIS_DECL_EXPORT Error {
    bool        loud;
    const char* error;
    Exception*  exception;

    inline Error();

    inline Error(bool a_loud);

    inline Error(Exception*  a_exception);

    inline Error(bool a_loud, Exception*  a_exception);

    inline operator bool();

    inline bool operator!();

    inline void clear();

    template <typename TException, typename ...TArgPack>
    void raise(TArgPack&& ...a_argPack);
  };

} // fcf namespace

#endif // #ifndef _FCF_BASIS__BITS__PART_EXCEPTION__ERROR_DECL_HPP___
