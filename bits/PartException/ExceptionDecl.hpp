#ifndef _FCF_BASIS__BITS__PART_EXCEPTION__EXCEPTION_DEFINITION_HPP___
#define _FCF_BASIS__BITS__PART_EXCEPTION__EXCEPTION_DEFINITION_HPP___

#include <exception>
#include "ExceptionPredecl.hpp"
#include "../../bits/PartStaticVector/StaticVectorDecl.hpp"
#include "../../bits/PartVariant/VariantDecl.hpp"

namespace fcf{

  /**
   * @brief Structured exception object with message formatting and nesting.
   *
   * The exception stores a short registered name, a message pattern,
   * source position, formatted arguments, and optional nested sub-exceptions.
   */
  class Exception: public std::exception{

    public:
      /**
       * @brief Destructor.
       */
      virtual ~Exception();

      /**
       * @brief Default constructor.
       *
       * Creates an empty exception object.
       */
      Exception();

      /**
       * @brief Copy constructor.
       *
       * Copies the exception state including nested sub-exceptions.
       *
       * @param a_exception Source exception object.
       */
      Exception(const Exception& a_exception);

      /**
       * @brief Copy constructor with optional sub-exception copy control.
       *
       * @param a_exception Source exception object.
       * @param a_copySub If true, nested sub-exceptions are copied.
       */
      Exception(const Exception& a_exception, bool a_copySub);

      /**
       * @brief Constructs an exception with default pattern and arguments.
       *
       * @tparam ...TArgPack Types of exception arguments.
       * @param a_file Source file name.
       * @param a_line Source line number.
       * @param a_argPack Arguments used to fill the message pattern.
       */
      template <typename ...TArgPack>
      Exception(const char* a_file, unsigned int a_line, const TArgPack&... a_argPack);

      /**
       * @brief Constructs an exception with short name, pattern and arguments.
       *
       * @tparam ...TArgPack Types of exception arguments.
       * @param a_shortMessage Short registered exception name.
       * @param a_patternMessage Message pattern used by message().
       * @param a_file Source file name.
       * @param a_line Source line number.
       * @param a_argPack Arguments used to fill the message pattern.
       */
      template <typename ...TArgPack>
      Exception(const char* a_shortMessage, const char* a_patternMessage, const char* a_file, unsigned int a_line, const TArgPack&... a_argPack);

      /**
       * @brief Constructs an exception with a nested sub-exception.
       *
       * @tparam ...TArgPack Types of exception arguments.
       * @param a_subexception Nested sub-exception.
       * @param a_file Source file name.
       * @param a_line Source line number.
       * @param a_argPack Arguments used to fill the message pattern.
       */
      template <typename ...TArgPack>
      Exception(const Exception& a_subexception, const char* a_file, unsigned int a_line, const TArgPack&... a_argPack);

      /**
       * @brief Constructs an exception with a nested sub-exception and custom message.
       *
       * @tparam ...TArgPack Types of exception arguments.
       * @param a_subexception Nested sub-exception.
       * @param a_shortMessage Short registered exception name.
       * @param a_patternMessage Message pattern used by message().
       * @param a_file Source file name.
       * @param a_line Source line number.
       * @param a_argPack Arguments used to fill the message pattern.
       */
      template <typename ...TArgPack>
      Exception(const Exception& a_subexception, const char* a_shortMessage, const char* a_patternMessage, const char* a_file, unsigned int a_line, const TArgPack&... a_argPack);

      /**
       * @brief Copies exception state.
       *
       * @param a_exception Source exception object.
       * @return Reference to the assigned exception object.
       */
      Exception& operator=(const Exception& a_exception);

      /**
       * @brief Returns the short exception name.
       *
       * @return Pointer to the short registered message name.
       */
      const char* operator()() const;

      /**
       * @brief Checks whether the exception is not empty.
       *
       * @return true if the exception contains a short message, false otherwise.
       */
      operator bool() const;

      /**
       * @brief Returns formatted exception description.
       *
       * The result may be lazily built and cached internally.
       *
       * @return C-style string with formatted exception description.
       */
      virtual const char* what() const throw();

      /**
       * @brief Returns the short registered exception name.
       *
       * @return Pointer to the short registered message name.
       */
      const char* name() const throw();

      /**
       * @brief Returns the source position of the exception.
       *
       * @return String in the file:line format.
       */
      std::string position() const throw();

      /**
       * @brief Returns the number of nested sub-exceptions.
       *
       * @return Number of stored nested exceptions.
       */
      size_t nestedSize() const throw();

      /**
       * @brief Returns a nested sub-exception by index.
       *
       * @param a_index Zero-based nested exception index.
       * @return Reference to the nested exception, or an empty exception if index is invalid.
       */
      const Exception& nested(size_t a_index) const throw();

      /**
       * @brief Returns the source file name.
       *
       * @return Pointer to the source file name.
       */
      const char* file() const throw();

      /**
       * @brief Returns the source line number.
       *
       * @return Source line number.
       */
      unsigned int line() const throw();

      /**
       * @brief Returns formatted exception information without nested errors.
       *
       * @return String containing exception name, message and position.
       */
      std::string info() const throw();

      /**
       * @brief Returns formatted exception information including nested errors.
       *
       * @return String containing exception details and nested sub-exceptions.
       */
      std::string full() const throw();

      /**
       * @brief Returns the formatted message.
       *
       * Message placeholders are replaced using stored arguments.
       *
       * @return Formatted message string.
       */
      std::string message() const throw();

    protected:

      /**
       * @brief Formats exception information with custom line prefixes.
       *
       * @param a_firstLinePrefix Prefix applied to the first formatted line.
       * @param a_linePrefix Prefix applied to subsequent formatted lines.
       * @return Formatted exception information string.
       */
      std::string _info(const char* a_firstLinePrefix, const char* a_linePrefix) const throw();

      FCF_FOREACH_METHOD_WRAPPER(ArgFiller, Exception, _fillArgs);

      /**
       * @brief Fills one argument into the exception argument storage.
       *
       * @tparam TType Type of the argument value.
       * @param a_value Argument value to store.
       */
      template <typename TType>
      void _fillArgs(size_t, const TType& a_value);

      /** @brief Cached formatted description returned by what(). */
      std::string*                  _pwhat;

      /** @brief Short registered exception name. */
      const char*                   _smessage;

      /** @brief Message pattern used by message(). */
      const char*                   _pmessage;

      /** @brief Source file name. */
      const char*                   _file;

      /** @brief Source line number. */
      unsigned int                  _line;

      /** @brief Exception message arguments. */
      StaticVector<fcf::Variant, 2> _args;

      /** @brief Nested sub-exceptions. */
      std::vector<Exception>        _sub;
  };

} // fcf namespace

#endif // #ifndef _FCF_BASIS__BITS__PART_EXCEPTION__EXCEPTION_DEFINITION_HPP___
