#ifndef ___FCF_BASIS__BITS__PART_EXCEPTION__EXCEPTION_DEFINITION_HPP___
#define ___FCF_BASIS__BITS__PART_EXCEPTION__EXCEPTION_DEFINITION_HPP___

#include <exception>
#include "../../bits/PartStaticVector/StaticVectorDefinition.hpp"
#include "../../bits/PartVariant/VariantDefinition.hpp"


namespace fcf{

  class Exception: public std::exception{

    public:
      virtual ~Exception();

      Exception();

      Exception(const Exception& a_exception, bool a_copySub);

      Exception(const Exception& a_exception);

      template <typename ...TArgPack>
      Exception(const char* a_file, unsigned int a_line, const TArgPack&... a_argPack);

      template <typename ...TArgPack>
      Exception(const char* a_shortMessage, const char* a_patternMessage, const char* a_file, unsigned int a_line, const TArgPack&... a_argPack);

      template <typename ...TArgPack>
      Exception(const Exception& a_subexception, const char* a_file, unsigned int a_line, const TArgPack&... a_argPack);

      template <typename ...TArgPack>
      Exception(const Exception& a_subexception, const char* a_shortMessage, const char* a_patternMessage, const char* a_file, unsigned int a_line, const TArgPack&... a_argPack);

      Exception& operator=(const Exception& a_exception);

      const char* operator()() const;

      operator bool() const;

      virtual const char* what() const throw();

      const char* name() const throw();

      std::string position() const throw();

      size_t subSize() const throw();

      const Exception& sub(size_t a_index) const;

      Exception& sub(size_t a_index);

      const char* file() const throw();

      unsigned int line() const throw();

      std::string info() const throw();

      std::string full() const throw();

      std::string message() const throw();

    protected:


      std::string _info(const char* a_firstLinePrefix, const char* a_linePrefix) const throw();

      FCF_FOREACH_METHOD_WRAPPER(ArgFiller, Exception, _fillArgs);
      template <typename TType>
      void _fillArgs(size_t, const TType& a_value);

      std::string*                  _pwhat;
      const char*                   _smessage;
      const char*                   _pmessage;
      const char*                   _file;
      unsigned int                  _line;
      StaticVector<fcf::Variant, 2> _args;
      std::vector<Exception>        _sub;
  };

  
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_EXCEPTION__EXCEPTION_DEFINITION_HPP___
