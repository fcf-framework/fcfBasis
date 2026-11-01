#ifndef _FCF_BASIS__BITS__PART_EXCEPTION__ERROR_IPP___
#define _FCF_BASIS__BITS__PART_EXCEPTION__ERROR_IPP___

#include "ErrorDecl.hpp"
#include "../PartException/ExceptionDecl.hpp"

namespace fcf{

  Error::Error()
    : loud(false)
    , error(0)
    , exception(0)
  {}

  Error::Error(bool a_loud)
    : loud(a_loud)
    , error(0)
    , exception(0) {
  }

  Error::Error(Exception*  a_exception)
    : loud(false)
    , error(a_exception && a_exception->name()[0] ? a_exception->name() : 0)
    , exception(a_exception)
  {}

  Error::Error(bool a_loud, Exception*  a_exception)
    : loud(a_loud)
    , error(a_exception && a_exception->name()[0] ? a_exception->name() : 0)
    , exception(a_exception)
  {}

  Error::operator bool(){
    return !!error;
  }

  bool Error::operator!(){
    return !error;
  }

  void Error::clear() {
    error = 0;
    if (exception){
      *exception = Exception();
    }
  }

  template <typename TException, typename ...TArgPack>
  void Error::raise(TArgPack&& ...a_argPack) {
    error = TException::registeredName();
    if (exception) {
      *exception = TException(a_argPack...);
    }
    if (loud) {
      throw TException(a_argPack...);
    }
  }

} // fcf namespace

#endif // #ifndef _FCF_BASIS__BITS__PART_EXCEPTION__ERROR_IPP___



