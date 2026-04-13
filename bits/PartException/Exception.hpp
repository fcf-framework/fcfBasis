#ifndef ___FCF_BASIS__BITS__PART_EXCEPTION__EXCEPTION_HPP___
#define ___FCF_BASIS__BITS__PART_EXCEPTION__EXCEPTION_HPP___

#include <exception>
#include "ExceptionDefinition.hpp"
#include "../../PartForeach.hpp"
#include "../../PartStaticVector.hpp"
#include "../../PartVariant.hpp"

namespace fcf{

#ifdef FCF_BASIS_IMPLEMENTATION
  Exception::~Exception()
  {
    if (_pwhat){
      delete _pwhat;
    }
  }
#endif

#ifdef FCF_BASIS_IMPLEMENTATION
  Exception::Exception()
    : _smessage(0)
  {
  }
#endif

#ifdef FCF_BASIS_IMPLEMENTATION
  Exception::Exception(const Exception& a_exception, bool a_copySub)
    : _pwhat(0)
    , _smessage(a_exception._smessage)
    , _pmessage(a_exception._pmessage)
    , _file(a_exception._file)
    , _line(a_exception._line)
    , _args(a_exception._args)
  {
    if (a_copySub){
      _sub = a_exception._sub;
    }
  }
#endif

#ifdef FCF_BASIS_IMPLEMENTATION
  Exception::Exception(const Exception& a_exception)
    : _pwhat(0)
    , _smessage(a_exception._smessage)
    , _pmessage(a_exception._pmessage)
    , _file(a_exception._file)
    , _line(a_exception._line)
    , _args(a_exception._args)
    , _sub(a_exception._sub)
  {
  }
#endif

  template <typename ...TArgPack>
  Exception::Exception(const char* a_file, unsigned int a_line, const TArgPack&... a_argPack)
    : _pwhat(0)
    , _smessage("FCF_EXCEPTION")
    , _pmessage("${{1}}$")
    , _file(a_file)
    , _line(a_line)
  {
    _args.reserve(sizeof...(a_argPack));
    std::tuple<const TArgPack&...> tuple(a_argPack...);
    ArgFiller filler(this);
    fcf::foreach(tuple, filler);
  }

  template <typename ...TArgPack>
  Exception::Exception(const char* a_shortMessage, const char* a_patternMessage, const char* a_file, unsigned int a_line, const TArgPack&... a_argPack)
    : _pwhat(0)
    , _smessage(a_shortMessage)
    , _pmessage(a_patternMessage)
    , _file(a_file)
    , _line(a_line)
  {
    _args.reserve(sizeof...(a_argPack));
    std::tuple<const TArgPack&...> tuple(a_argPack...);
    ArgFiller filler(this);
    fcf::foreach(tuple, filler);
  }

  template <typename ...TArgPack>
  Exception::Exception(const Exception& a_subexception, const char* a_file, unsigned int a_line, const TArgPack&... a_argPack)
    : _pwhat(0)
    , _smessage("FCF_EXCEPTION")
    , _pmessage("${{1}}$")
    , _file(a_file)
    , _line(a_line)
  {
    _args.reserve(sizeof...(a_argPack));
    std::tuple<const TArgPack&...> tuple(a_argPack...);
    ArgFiller filler(this);
    fcf::foreach(tuple, filler);
    _sub.reserve(a_subexception._sub.size()+1);
    _sub.push_back(Exception(a_subexception, false));
    for(size_t i = 0; i < a_subexception._sub.size(); ++i){
      _sub.push_back(Exception(a_subexception._sub[i], false));
    }
  }

  template <typename ...TArgPack>
  Exception::Exception(const Exception& a_subexception, const char* a_shortMessage, const char* a_patternMessage, const char* a_file, unsigned int a_line, const TArgPack&... a_argPack)
    : _pwhat(0)
    , _smessage(a_shortMessage)
    , _pmessage(a_patternMessage)
    , _file(a_file)
    , _line(a_line)
  {
    _args.reserve(sizeof...(a_argPack));
    std::tuple<const TArgPack&...> tuple(a_argPack...);
    ArgFiller filler(this);
    fcf::foreach(tuple, filler);
    _sub.reserve(a_subexception._sub.size()+1);
    _sub.push_back(Exception(a_subexception, false));
    for(size_t i = 0; i < a_subexception._sub.size(); ++i){
      _sub.push_back(Exception(a_subexception._sub[i], false));
    }
  }

#ifdef FCF_BASIS_IMPLEMENTATION
  Exception& Exception::operator=(const Exception& a_exception){
    if (_pwhat){
      delete _pwhat;
      _pwhat = 0;
    }
    _smessage = a_exception._smessage;
    _pmessage = a_exception._pmessage;
    _file = a_exception._file;
    _line= a_exception._line;
    _args = a_exception._args;
    _sub = a_exception._sub;
    return *this;
  }
#endif

#ifdef FCF_BASIS_IMPLEMENTATION
  const char* Exception::operator()() const{
    return _smessage;
  }
#endif

#ifdef FCF_BASIS_IMPLEMENTATION
  Exception::operator bool() const{
    return !!_smessage;
  }
#endif
  
#ifdef FCF_BASIS_IMPLEMENTATION
  const char* Exception::what() const throw() {
    if (!_smessage){
      return "";
    }
    if (_pwhat){
      return _pwhat->c_str();
    }
    Exception* pthis = (Exception*)this;
    //!!!!!!!!!!!!!! memory leak for multy tread !!!!!!!!!!!
    std::string* pmessage = new std::string();
    *pmessage = message();
    *pmessage += "\nPosition: ";
    *pmessage += position();
    pthis->_pwhat = pmessage;
    return _pwhat->c_str();
  }
#endif

#ifdef FCF_BASIS_IMPLEMENTATION
  const char* Exception::name() const throw() {
    if (!_smessage){
      return "";
    }
    return _smessage;
  }
#endif

#ifdef FCF_BASIS_IMPLEMENTATION
  std::string Exception::position() const throw() {
    if (!_smessage){
      return "";
    }
    std::string res;
    res += _file;
    res += ":";
    res += std::to_string(_line);
    return res;
  }
#endif

#ifdef FCF_BASIS_IMPLEMENTATION
  size_t Exception::subSize() const throw() {
    return _sub.size();
  }
#endif

#ifdef FCF_BASIS_IMPLEMENTATION
  const Exception& Exception::sub(size_t a_index) const{
    return _sub[a_index];
  }
#endif

#ifdef FCF_BASIS_IMPLEMENTATION
  Exception& Exception::sub(size_t a_index) {
    return _sub[a_index];
  }
#endif

#ifdef FCF_BASIS_IMPLEMENTATION
  const char* Exception::file() const throw() {
    if (!_smessage){
      return "";
    }
    return _file;
  }
#endif

#ifdef FCF_BASIS_IMPLEMENTATION
  unsigned int Exception::line() const throw() {
    if (!_smessage){
      return 0;
    }
    return _line;
  }
#endif

#ifdef FCF_BASIS_IMPLEMENTATION
  std::string Exception::info() const throw() {
    return _info("",  "");
  }
#endif

#ifdef FCF_BASIS_IMPLEMENTATION
  std::string Exception::full() const throw() {
    if (!_smessage){
      return "";
    }
    std::string res = info();
    if (_sub.size()){
      res += "\nSub errors:\n";
      for(size_t i = 0; i < _sub.size(); ++i){
        std::string num = std::to_string(i+1);
        std::string prefix;
        prefix.append(12 >= (num.size()+2) ? 12 - (num.size()+2) : 0, ' ');
        prefix += num;
        prefix += "] ";
        res += _sub[i]._info(prefix.c_str(), "            ");
      }
    }
    return res;
  }
#endif

#ifdef FCF_BASIS_IMPLEMENTATION  
  std::string Exception::message() const throw() {
    std::string result;
    if (!_smessage || !_pmessage) {
      return result;
    }
    int           s = 0;
    const char*   p = _pmessage;
    unsigned int  i = 0;
    while(*p){
      unsigned char c = (unsigned char)*p;
      switch (s) {
        case 0:
          if (c == '$') {
            ++s;
          } else {
            result += c;
          }
          break;
        case 1:
          if (c == '{') {
            ++s;
          } else {
            s = 0;
            result += '$';
            result += c;
          }
          break;
        case 2:
          if (c == '{') {
            ++s;
          } else {
            s = 0;
            result += "${";
            result += c;
          }
          break;
        case 3:
          if (c >= (unsigned int)'0' && c <= (unsigned int)'9') {
            i *= 10;
            i += (unsigned int)(c - (unsigned int)'0');
          } else if (c == '}'){
            s = 4;
          }
          break;
        case 4:
          if (c == '}') {
            s = 5;
          } else {
            s = 3;
            --p;
          }
          break;
        case 5:
          if (c == '$') {
            --i;
            if (i < _args.size()){
              try {
                result += _args[i].cast<std::string>();
              } catch(...){
              }
            }
            i = 0;
            s = 0;
          } else {
            s = 3;
            --p;
          }
          break;
      }
      ++p;
    }
    return result;
  }
#endif

#ifdef FCF_BASIS_IMPLEMENTATION
  std::string Exception::_info(const char* a_firstLinePrefix, const char* a_linePrefix) const throw() {
    if (!_smessage){
      return "";
    }
    std::string res;
    res += a_firstLinePrefix;
      res += "Error:    ";
      res += _smessage;
      res += '\n';
    res += a_linePrefix;
      res += "Message:  ";
      res += message();
      res += '\n';
    res += a_linePrefix;
      res += "Position: ";
      res += position();
    return res;
  }
#endif

template <typename TType>
void Exception::_fillArgs(size_t, const TType& a_value){
  _args.push_back(a_value);
}

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_EXCEPTION__EXCEPTION_HPP___
