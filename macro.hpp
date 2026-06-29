#ifndef ___FCF_BASIS__MACRO_HPP___
#define ___FCF_BASIS__MACRO_HPP___

#include <stdexcept>

/**
 * @def FCF_IMPLEMENTATION
 * @brief Switch to activate the implementation of all framework libraries.
 * If defined, automatically defines FCF_BASIS_IMPLEMENTATION.
 */
#ifdef FCF_IMPLEMENTATION
  #ifndef FCF_BASIS_IMPLEMENTATION
    #define FCF_BASIS_IMPLEMENTATION
  #endif // #ifndef FCF_BASIS_IMPLEMENTATION
#endif // #ifdef FCF_IMPLEMENTATION

/**
 * @def FCF_EXPORT
 * @brief Switch to export symbols when building DLLs for all framework libraries.
 * If defined, automatically defines FCF_BASIS_EXPORT.
 */
#ifdef FCF_EXPORT
  #ifndef FCF_BASIS_EXPORT
    #define FCF_BASIS_EXPORT
    #endif // #ifndef FCF_BASIS_EXPORT
#endif // #ifdef FCF_EXPORT

/**
 * @def FCF_IMPORT
 * @brief Switch to import symbols when using DLLs for all framework libraries.
 * If defined, automatically defines FCF_BASIS_IMPORT.
 */
#ifdef FCF_IMPORT
  #ifndef FCF_BASIS_IMPORT
    #define FCF_BASIS_IMPORT
  #endif // #ifndef FCF_BASIS_IMPORT
#endif // #ifdef FCF_IMPORT

#ifndef FCF_BASIS_DELC_EXTERN
  #ifdef FCF_BASIS_IMPLEMENTATION
    #define FCF_BASIS_DELC_EXTERN
  #else
    #define FCF_BASIS_DELC_EXTERN extern
  #endif // #ifdef FCF_BASIS_IMPLEMENTATION
#endif // #ifndef FCF_BASIS_DELC_EXTERN

#ifndef FCF_BASIS_DECL_EXPORT
  #ifdef WIN32
    #if defined(FCF_BASIS_EXPORT)
      #define FCF_BASIS_DECL_EXPORT __declspec(dllexport)
    #elif defined(FCF_BASIS_IMPORT)
      #define FCF_BASIS_DECL_EXPORT __declspec(dllimport)
    #else
      #define FCF_BASIS_DECL_EXPORT
    #endif // #if defined(FCF_BASIS_EXPORT)
  #else
    #define FCF_BASIS_DECL_EXPORT
  #endif // #ifdef WIN32
#endif // #ifndef FCF_BASIS_DECL_EXPORT

/**
 * @def FCF_FOREACH_METHOD_WRAPPER(am_name, am_class, am_methodName)
 * @brief Creates a wrapper structure to call a class method in a foreach context.
 * @param am_name Name of the created structure.
 * @param am_class Type of the owner class.
 * @param am_methodName Name of the method in the owner class to be called.
 */
#ifndef FCF_FOREACH_METHOD_WRAPPER
#define FCF_FOREACH_METHOD_WRAPPER(am_name, am_class, am_methodName)\
      struct am_name {\
        inline am_name(am_class* a_owner)\
          : _owner(a_owner){\
            if (!a_owner) {\
              throw std::invalid_argument("The empty pointer to the object to execute foreach is specified");\
            }\
        }\
        inline am_name(am_class& a_owner)\
          : _owner(&a_owner){\
        }\
        inline am_name(const am_class& a_owner)\
          : _owner((am_class*)&a_owner){\
        }\
        inline am_name(am_class&& a_owner) = delete;\
        template <typename ... TPack>\
        inline void operator()(TPack&&... a_args){\
          _owner->am_methodName(a_args...);\
        }\
        am_class* _owner;\
      };
#endif

/**
 * @def FCF_FOREACH_FUNCTION_WRAPPER(am_name, am_functionName)
 * @brief Creates a wrapper structure to call a free function in a foreach context.
 * @param am_name Name of the created structure.
 * @param am_functionName Name of the function to call.
 */
#ifndef FCF_FOREACH_FUNCTION_WRAPPER
#define FCF_FOREACH_FUNCTION_WRAPPER(am_name, am_functionName)\
      struct am_name {\
        inline am_name(){\
        }\
        template <typename ... TPack>\
        inline void operator()(TPack&&... a_args){\
          am_functionName(a_args...);\
        }\
      };
#endif

/**
 * @def FCF_ATTRIBUTE_MINIMIZE
 * @brief A group of macros that includes compiler optimization for binary code size.
 * Example:
 * @code
 * FCF_ATTRIBUTE_MINIMIZE_BEGIN
 * template <typename Ty>
 * void FCF_ATTRIBUTE_MINIMIZE someFunction() {
 *   // implementation your function ...
 * }
 * FCF_ATTRIBUTE_MINIMIZE_END
 * @endcode
 */
#ifndef FCF_ATTRIBUTE_MINIMIZE
  #ifdef _MSC_VER
    #define FCF_ATTRIBUTE_MINIMIZE
    #define FCF_ATTRIBUTE_MINIMIZE_BEGIN  __pragma(optimize("s", on))
    #define FCF_ATTRIBUTE_MINIMIZE_END    __pragma(optimize("", on))
  #elif defined(__clang__)
    #define FCF_ATTRIBUTE_MINIMIZE_BEGIN
    #define FCF_ATTRIBUTE_MINIMIZE __attribute__((cold, minsize))
    #define FCF_ATTRIBUTE_MINIMIZE_END
  #else
    #define FCF_ATTRIBUTE_MINIMIZE_BEGIN
    #define FCF_ATTRIBUTE_MINIMIZE __attribute__((cold, optimize("Os")))
    #define FCF_ATTRIBUTE_MINIMIZE_END
  #endif
#endif

#ifndef _FCF_BASIS_SINGLE_EXPAND_ARGUMENTS
  #ifndef _MSC_VER
    #define _FCF_BASIS_SINGLE_EXPAND_ARGUMENTS(am_macro, ...) am_macro __VA_ARGS__
  #else
    #define _FCF_BASIS_SINGLE_EXPAND_ARGUMENTS(am_macro, am_args) am_macro am_args
  #endif
#endif

#ifndef _MSC_VER
  #define _FCF_BASIS_EXPAND_ARGUMENTS(am_macro, ...) am_macro __VA_ARGS__
#else
  #define _FCF_BASIS_EXPAND_ARGUMENTS_1(am_arg) am_arg
  #define _FCF_BASIS_EXPAND_ARGUMENTS_0(am_macro, am_arg) _FCF_BASIS_EXPAND_ARGUMENTS_1(am_macro am_arg)
  #define _FCF_BASIS_EXPAND_ARGUMENTS(am_macro, am_args) _FCF_BASIS_EXPAND_ARGUMENTS_0(am_macro, am_args)
#endif

#ifndef _FCF_BASIS_REMOVE_PARENTHESIS
  #define _FCF_REMOVE_PARENTHESIS_SELECTOR_FCF_BASIS_REMOVE_PARENTHESIS_ARGUMENT
  #define _FCF_BASIS_REMOVE_PARENTHESIS_ARGUMENT(...) _FCF_BASIS_REMOVE_PARENTHESIS_ARGUMENT __VA_ARGS__
  #define _FCF_REMOVE_PARENTHESIS_0(...) _FCF_REMOVE_PARENTHESIS_SELECTOR##__VA_ARGS__
  #define _FCF_BASIS_REMOVE_PARENTHESIS(...) _FCF_REMOVE_PARENTHESIS_0(__VA_ARGS__)
#endif

#ifndef _FCF_BASIS_VARNAME
  #define _FCF_BASIS_VARNAME__IMPL2(am_varName, am_suffix, am_counter) am_varName##am_suffix##am_counter
  #define _FCF_BASIS_VARNAME__IMPL1(am_varName, am_suffix, am_counter) _FCF_BASIS_VARNAME__IMPL2(am_varName, am_suffix, am_counter)
  #define _FCF_BASIS_VARNAME(am_varName, am_suffix) _FCF_BASIS_VARNAME__IMPL1(am_varName, am_suffix, __COUNTER__)
#endif // #ifndef _FCF_BASIS_VARNAME

#ifndef _FCF_BASIS_CONCAT2
  #define _FCF_BASIS_CONCAT2_IMPL2(am_varName, am_suffix) am_varName##am_suffix
  #define _FCF_BASIS_CONCAT2_IMPL1(am_varName, am_suffix) _FCF_BASIS_CONCAT2_IMPL2(am_varName, am_suffix)
  #define _FCF_BASIS_CONCAT2(am_varName, am_suffix) _FCF_BASIS_CONCAT2_IMPL1(am_varName, am_suffix)
#endif // #ifndef FCF_BASIS_CONCAT3

#ifndef _FCF_BASIS_CONCAT3
  #define _FCF_BASIS_CONCAT3_IMPL2(am_varName, am_varName2, am_suffix) am_varName##am_varName2##am_suffix
  #define _FCF_BASIS_CONCAT3_IMPL1(am_varName, am_varName2, am_suffix) _FCF_BASIS_CONCAT3_IMPL2(am_varName, am_varName2, am_suffix)
  #define _FCF_BASIS_CONCAT3(am_varName, am_varName2, am_suffix) _FCF_BASIS_CONCAT3_IMPL1(am_varName, am_varName2, am_suffix)
#endif // #ifndef FCF_BASIS_CONCAT3

/**
 * @def FCF_SPECIFIER_REGISTRATION_FORCE(am_type, am_specifier)
 * @brief Forced registration of a specifier.
 * @details Performs specifier registration regardless of the FCF_BASIS_IMPLEMENTATION state.
 * @param am_type The type for which the specifier is being registered.
 * @param am_specifier The type of the specifier.
 */
#ifndef FCF_SPECIFIER_REGISTRATION_FORCE
  #define _FCF_SPECIFIER_REGISTRATION_FORCE__L2(am_itemName, am_counter) am_itemName##_##am_counter
  #define _FCF_SPECIFIER_REGISTRATION_FORCE__L1(am_itemName, am_counter) _FCF_SPECIFIER_REGISTRATION_FORCE__L2(am_itemName, am_counter)
  #define FCF_SPECIFIER_REGISTRATION_FORCE(am_type, am_specifier) \
      namespace { \
        ::fcf::SpecifierRegistrarHandler<am_type, am_specifier> _FCF_SPECIFIER_REGISTRATION_FORCE__L1(specifierReg, __COUNTER__);\
      }
#endif // #ifndef FCF_SPECIFIER_REGISTRATION

/**
 * @def FCF_SPECIFIER_REGISTRATION(am_type, am_specifier)
 * @brief Registration of a specifier for a type. If FCF_BASIS_IMPLEMENTATION is not defined, the macro expands to an empty action.
 * @param am_type The type for which the specifier is being registered.
 * @param am_specifier The type of the specifier.
 */
#ifndef FCF_SPECIFIER_REGISTRATION
  #ifdef FCF_BASIS_IMPLEMENTATION
     #define FCF_SPECIFIER_REGISTRATION(am_type, am_specifier) FCF_SPECIFIER_REGISTRATION_FORCE(am_type, am_specifier)
  #else
    #define FCF_SPECIFIER_REGISTRATION(am_type, am_specifier)
  #endif // #ifdef FCF_BASIS_IMPLEMENTATION
#endif // #ifndef FCF_SPECIFIER_REGISTRATION

#ifndef _FCF_BASIS_EXPAND
#define _FCF_BASIS_EXPAND(...) __VA_ARGS__
#endif // #ifndef _FCF_BASIS_EXPAND

#ifndef _FCF_TYPE_REGISTRATION_IMPL_DECL_CLASS
#define _FCF_TYPE_REGISTRATION_IMPL_DECL_CLASS(am_type, am_templateArgs, am_name, am_index, am_basic_type, am_isTemplate) \
      template < _FCF_BASIS_EXPAND am_templateArgs>\
      struct fcf::TypeId< _FCF_BASIS_EXPAND am_type > {\
        typedef _FCF_BASIS_EXPAND am_basic_type basic_type;\
        bool          autoIndex()   { return ((am_index) & 0x00ffffff)== 0; }\
        TypeIndex     index()       { return am_index; }\
        FCF_ATTRIBUTE_MINIMIZE_BEGIN\
        std::string   FCF_ATTRIBUTE_MINIMIZE  name()  { return std::string() + am_name; }\
        FCF_ATTRIBUTE_MINIMIZE_END\
        bool          isTemplate()  { return am_isTemplate; }\
      };
#endif // #ifndef _FCF_TYPE_REGISTRATION_IMPL_DECL_CLASS

#ifndef _FCF_TYPE_REGISTRATION_IMPL_DECL_CLASSES
#define _FCF_TYPE_REGISTRATION_IMPL_DECL_CLASSES(am_type, am_templateArgs, am_name, am_index, am_isTemplate)\
      _FCF_TYPE_REGISTRATION_IMPL_DECL_CLASS((_FCF_BASIS_EXPAND am_type), (_FCF_BASIS_EXPAND am_templateArgs),    am_name, am_index, am_type, am_isTemplate) \
      _FCF_TYPE_REGISTRATION_IMPL_DECL_CLASS((_FCF_BASIS_EXPAND am_type &), (_FCF_BASIS_EXPAND am_templateArgs),  am_name + "&", am_index | (1 << (24 + 1) ), am_type, am_isTemplate) \
      _FCF_TYPE_REGISTRATION_IMPL_DECL_CLASS((_FCF_BASIS_EXPAND am_type &&), (_FCF_BASIS_EXPAND am_templateArgs), am_name + "&&", am_index | (2 << (24 + 1) ), am_type, am_isTemplate) \
      _FCF_TYPE_REGISTRATION_IMPL_DECL_CLASS((_FCF_BASIS_EXPAND am_type *), (_FCF_BASIS_EXPAND am_templateArgs),  am_name + "*", am_index | (8 << (24 + 1) ), am_type, am_isTemplate) \
      _FCF_TYPE_REGISTRATION_IMPL_DECL_CLASS((_FCF_BASIS_EXPAND am_type **), (_FCF_BASIS_EXPAND am_templateArgs), am_name + "**", am_index | (16 << (24 + 1) ), am_type, am_isTemplate) \
      _FCF_TYPE_REGISTRATION_IMPL_DECL_CLASS((_FCF_BASIS_EXPAND am_type *&), (_FCF_BASIS_EXPAND am_templateArgs),  am_name + "*&", am_index | ((1 | 8) << (24 + 1) ), am_type, am_isTemplate) \
      _FCF_TYPE_REGISTRATION_IMPL_DECL_CLASS((_FCF_BASIS_EXPAND am_type **&), (_FCF_BASIS_EXPAND am_templateArgs),  am_name + "**&", am_index | ((1 | 16) << (24 + 1) ), am_type, am_isTemplate) \
      _FCF_TYPE_REGISTRATION_IMPL_DECL_CLASS((const _FCF_BASIS_EXPAND am_type), (_FCF_BASIS_EXPAND am_templateArgs),  "const " + am_name , am_index | ((4) << (24 + 1) ), am_type, am_isTemplate) \
      _FCF_TYPE_REGISTRATION_IMPL_DECL_CLASS((const _FCF_BASIS_EXPAND am_type &), (_FCF_BASIS_EXPAND am_templateArgs),  "const " + am_name + "&", am_index | ((1 | 4) << (24 + 1) ), am_type, am_isTemplate) \
      _FCF_TYPE_REGISTRATION_IMPL_DECL_CLASS((const _FCF_BASIS_EXPAND am_type &&), (_FCF_BASIS_EXPAND am_templateArgs), "const " + am_name + "&&", am_index | ((2 | 4) << (24 + 1)), am_type, am_isTemplate)\
      _FCF_TYPE_REGISTRATION_IMPL_DECL_CLASS((const _FCF_BASIS_EXPAND am_type *), (_FCF_BASIS_EXPAND am_templateArgs),  "const " + am_name + "*", am_index | ((8 | 4) << (24 + 1)), am_type, am_isTemplate) \
      _FCF_TYPE_REGISTRATION_IMPL_DECL_CLASS((const _FCF_BASIS_EXPAND am_type **), (_FCF_BASIS_EXPAND am_templateArgs), "const " + am_name + "**", am_index | (16 << (24 + 1) ) | (4 << (24 + 1)), am_type, am_isTemplate)\
      _FCF_TYPE_REGISTRATION_IMPL_DECL_CLASS((const _FCF_BASIS_EXPAND am_type *&), (_FCF_BASIS_EXPAND am_templateArgs), "const " + am_name + "*&", am_index | ((1 | 4 | 8) << (24 + 1)), am_type, am_isTemplate)\
      _FCF_TYPE_REGISTRATION_IMPL_DECL_CLASS((const _FCF_BASIS_EXPAND am_type **&), (_FCF_BASIS_EXPAND am_templateArgs), "const " + am_name + "**&", am_index | ((1 | 4 | 16) << (24 + 1)), am_type, am_isTemplate)
#endif // #ifndef _FCF_TYPE_REGISTRATION_IMPL_DECL_CLASSES

#ifndef _FCF_TYPE_REGISTRATION_IMPL_DECL_INITVAR
#define _FCF_TYPE_REGISTRATION_IMPL_DECL_INITVAR(am_type, am_name, am_index) \
      namespace { \
        fcf::TypeInitializer<am_type> _FCF_BASIS_VARNAME(typeInfoRegistry, _);\
        fcf::TypeInitializer<am_type*> _FCF_BASIS_VARNAME(typeInfoRegistry, _);\
        fcf::TypeInitializer<am_type**> _FCF_BASIS_VARNAME(typeInfoRegistry, _);\
        fcf::TypeInitializer<am_type&> _FCF_BASIS_VARNAME(typeInfoRegistry, _);\
        fcf::TypeInitializer<am_type&&> _FCF_BASIS_VARNAME(typeInfoRegistry, _);\
        fcf::TypeInitializer<const am_type*> _FCF_BASIS_VARNAME(typeInfoRegistry, _);\
        fcf::TypeInitializer<const am_type*&> _FCF_BASIS_VARNAME(typeInfoRegistry, _);\
        fcf::TypeInitializer<const am_type**> _FCF_BASIS_VARNAME(typeInfoRegistry, _);\
        fcf::TypeInitializer<const am_type**&> _FCF_BASIS_VARNAME(typeInfoRegistry, _);\
        fcf::TypeInitializer<const am_type&> _FCF_BASIS_VARNAME(typeInfoRegistry, _);\
        fcf::TypeInitializer<const am_type&&> _FCF_BASIS_VARNAME(typeInfoRegistry, _);\
      }
#endif // #ifndef _FCF_TYPE_REGISTRATION_IMPL_DECL_INITVAR

/**
 * @def FCF_TYPE_REGISTRATION_FORCE(am_type, am_name, am_index)
 * @brief Forced registration of a type, including derived types for various modifiers (const, ref, pointer).
 * @details Performs type registration regardless of the FCF_BASIS_IMPLEMENTATION state.
 * @param am_type The type to register.
 * @param am_name String name of the type.
 * @param am_index Base type index. If set to 0, the system will set the type index itself.
 */
#ifndef FCF_TYPE_REGISTRATION_FORCE
  #define FCF_TYPE_REGISTRATION_FORCE(am_type, am_name, am_index) \
        _FCF_TYPE_REGISTRATION_IMPL_DECL_CLASSES((am_type), (), am_name, am_index, false)\
        _FCF_TYPE_REGISTRATION_IMPL_DECL_INITVAR(am_type, am_name, am_index)
#endif // #ifndef FCF_TYPE_REGISTRATION

#ifndef FCF_TYPE_REGISTRATION
  #ifdef FCF_BASIS_IMPLEMENTATION
    /**
     * @def FCF_TYPE_REGISTRATION(am_type, am_name, am_index)
     * @brief Registration of a type in the system, including derived types for various modifiers (const, ref, pointer).
     * @details If FCF_BASIS_IMPLEMENTATION is not defined, only class declarations are declared without initializers.
     * @param am_type The type to register.
     * @param am_name String name of the type.
     * @param am_index Base type index. If set to 0, the system will set the type index itself.
     */
    #define FCF_TYPE_REGISTRATION(am_type, am_name, am_index) \
            FCF_TYPE_REGISTRATION_FORCE(am_type, am_name, am_index)
  #else
    #define FCF_TYPE_REGISTRATION(am_type, am_name, am_index) \
            _FCF_TYPE_REGISTRATION_IMPL_DECL_CLASSES((am_type), (), am_name, am_index, false)
  #endif
#endif // #ifndef FCF_TYPE_REGISTRATION

/**
 * @def FCF_TYPE_REGISTRATION_SINGLE(am_type, am_name, am_index)
 * @brief Registration of a type with the creation of only one initializer for the specified type (without pointer, const, ref modifiers).
 * @param am_type The type to register.
 * @param am_name String name of the type.
 * @param am_index Base type index. If set to 0, the system will set the type index itself.
 */
#ifndef FCF_TYPE_REGISTRATION_SINGLE
  #ifdef FCF_BASIS_IMPLEMENTATION
    #define FCF_TYPE_REGISTRATION_SINGLE(am_type, am_name, am_index) \
      _FCF_TYPE_REGISTRATION_IMPL_DECL_CLASS((am_type), (), am_name, am_index, (am_type), false)\
      fcf::TypeInitializer<am_type> _FCF_BASIS_VARNAME(typeInfoRegistry, _);
  #else
    #define FCF_TYPE_REGISTRATION_SINGLE(am_type, am_name, am_index) \
      _FCF_TYPE_REGISTRATION_IMPL_DECL_CLASS((am_type), (), am_name, am_index, (am_type), false)
  #endif
#endif // #ifndef FCF_TYPE_REGISTRATION_SINGLE

/**
 * @def FCF_TEMPLATE_TYPE_REGISTRATION(am_template, am_templateName, am_templateArgumentsDeclaration, am_templateArguments, am_templateArgumentsName)
 * @brief Registration of a template type in the system.
 *
 * Declares information/declaration about the type.
 * Information for runtime access to data by type index
 * will be available immediately after creating an instance of fcf::Type<Ty>
 * or assigning a value to an fcf::Variant object (or other operations with explicit type specification).
 *
 * If you need to register a specific template implementation in the runtime storage,
 * you can call FCF_TYPE_REGISTRATION_FORCE for the given type.
 *
 * @code
 * FCF_TEMPLATE_TYPE_REGISTRATION((std, list), "std::list", (typename Ty), (Ty), (Type<Ty>().name()));
 * FCF_TYPE_REGISTRATION_FORCE(std::list<int>, "std::list<int>", 0)
 * @endcode
 *
 * @param am_template The template type.
 *                   If the name includes a namespace, individual parts of the name must be enclosed in parentheses.
 *                   Example:
 *                     fcf::NDetails::SomeClass -> (fcf, NDetails, SomeClass)
 * @param am_templateName Template name as a string (without template arguments and without <> characters).
 * @param am_templateArgumentsDeclaration List of template argument declarations.
 *                        This list must be enclosed in parentheses, and individual elements must be separated by commas.
 *                        Example for template <typename T1, typename T2>:
 *                          (typename T1, typename T2)
 * @param am_templateArguments List of template arguments (without declaration).
 *                        This list must be enclosed in parentheses, and individual elements must be separated by commas.
 *                        Example for template <typename T1, typename T2>:
 *                          (T1, T2)
 * @param am_templateArgumentsName String representation of template arguments for partial specialization.
 *                                 The code string for forming the string must be enclosed in parentheses.
 *                                 You can use runtime operations/calls.
 *                                 Example for template (typename T1, typename T2):
 *                                   (Type<T1>().name()+","+Type<T2>().name());
 *                                 This instruction is necessary to create the type name:
 *                                   template <typename TKey, typename TValue> class std::map; ->
 *                                            ________________
 *                                   std::map<int,std::string>
 */
#ifndef FCF_TEMPLATE_TYPE_REGISTRATION
  #define _FCF_REMOVE_PARENTHESIS_SELECTOR_FCF_TEMPLATE_TYPE_REGISTRATION__NAMESPACES__REMOVE_PARENTHESIS_ARGUMENT ::
  #define _FCF_REMOVE_PARENTHESIS_SELECTOR_FCF_TEMPLATE_TYPE_REGISTRATION__NAMESPACES__REMOVE_PARENTHESIS_ARGUMENT_EMPTY
  #define _FCF_TEMPLATE_TYPE_REGISTRATION__NAMESPACES__REMOVE_PARENTHESIS_ARGUMENT(...) _FCF_TEMPLATE_TYPE_REGISTRATION__NAMESPACES__REMOVE_PARENTHESIS_ARGUMENT_EMPTY
  #define _FCF_TEMPLATE_TYPE_REGISTRATION__NAMESPACES__REMOVE_PARENTHESIS_0(...) _FCF_REMOVE_PARENTHESIS_SELECTOR##__VA_ARGS__
  #define _FCF_TEMPLATE_TYPE_REGISTRATION__NAMESPACES__REMOVE_PARENTHESIS(...) _FCF_TEMPLATE_TYPE_REGISTRATION__NAMESPACES__REMOVE_PARENTHESIS_0(__VA_ARGS__)
  #define _FCF_TEMPLATE_TYPE_REGISTRATION__NAMESPACES_1(am_a1, am_a2, am_a3,...)\
          _FCF_TEMPLATE_TYPE_REGISTRATION__NAMESPACES__REMOVE_PARENTHESIS(_FCF_TEMPLATE_TYPE_REGISTRATION__NAMESPACES__REMOVE_PARENTHESIS_ARGUMENT am_a1)\
          _FCF_TEMPLATE_TYPE_REGISTRATION__NAMESPACES__REMOVE_PARENTHESIS(_FCF_TEMPLATE_TYPE_REGISTRATION__NAMESPACES__REMOVE_PARENTHESIS_ARGUMENT am_a2)\
          _FCF_TEMPLATE_TYPE_REGISTRATION__NAMESPACES__REMOVE_PARENTHESIS(_FCF_TEMPLATE_TYPE_REGISTRATION__NAMESPACES__REMOVE_PARENTHESIS_ARGUMENT am_a3)
  #define _FCF_TEMPLATE_TYPE_REGISTRATION__NAMESPACES_0(...)\
          _FCF_BASIS_EXPAND_ARGUMENTS(_FCF_TEMPLATE_TYPE_REGISTRATION__NAMESPACES_1, (__VA_ARGS__, (), (), ()))
  #define _FCF_TEMPLATE_TYPE_REGISTRATION__NAMESPACES(am_type) \
          _FCF_TEMPLATE_TYPE_REGISTRATION__NAMESPACES_0(_FCF_BASIS_REMOVE_PARENTHESIS( _FCF_BASIS_REMOVE_PARENTHESIS_ARGUMENT am_type))

  #define _FCF_REMOVE_PARENTHESIS_SELECTOR_FCF_TEMPLATE_TYPE_REGISTRATION__DECLNAMESPACES__REMOVE_PARENTHESIS_ARGUMENT { namespace
  #define _FCF_REMOVE_PARENTHESIS_SELECTOR_FCF_TEMPLATE_TYPE_REGISTRATION__DECLNAMESPACES__REMOVE_PARENTHESIS_ARGUMENT_EMPTY
  #define _FCF_TEMPLATE_TYPE_REGISTRATION__DECLNAMESPACES__REMOVE_PARENTHESIS_ARGUMENT(...) _FCF_TEMPLATE_TYPE_REGISTRATION__DECLNAMESPACES__REMOVE_PARENTHESIS_ARGUMENT_EMPTY
  #define _FCF_TEMPLATE_TYPE_REGISTRATION__DECLNAMESPACES__REMOVE_PARENTHESIS_0(...) _FCF_REMOVE_PARENTHESIS_SELECTOR##__VA_ARGS__
  #define _FCF_TEMPLATE_TYPE_REGISTRATION__DECLNAMESPACES__REMOVE_PARENTHESIS(...) _FCF_TEMPLATE_TYPE_REGISTRATION__DECLNAMESPACES__REMOVE_PARENTHESIS_0(__VA_ARGS__)
  #define _FCF_TEMPLATE_TYPE_REGISTRATION__DECLNAMESPACES_1(am_a1, am_a2, am_a3,...)\
          _FCF_TEMPLATE_TYPE_REGISTRATION__DECLNAMESPACES__REMOVE_PARENTHESIS(_FCF_TEMPLATE_TYPE_REGISTRATION__DECLNAMESPACES__REMOVE_PARENTHESIS_ARGUMENT am_a1)\
          _FCF_TEMPLATE_TYPE_REGISTRATION__DECLNAMESPACES__REMOVE_PARENTHESIS(_FCF_TEMPLATE_TYPE_REGISTRATION__DECLNAMESPACES__REMOVE_PARENTHESIS_ARGUMENT am_a2)\
          _FCF_TEMPLATE_TYPE_REGISTRATION__DECLNAMESPACES__REMOVE_PARENTHESIS(_FCF_TEMPLATE_TYPE_REGISTRATION__DECLNAMESPACES__REMOVE_PARENTHESIS_ARGUMENT am_a3)
  #define _FCF_TEMPLATE_TYPE_REGISTRATION__DECLNAMESPACES_0(...)\
          _FCF_BASIS_EXPAND_ARGUMENTS( _FCF_TEMPLATE_TYPE_REGISTRATION__DECLNAMESPACES_1, (__VA_ARGS__, (), (), ()) )
  #define _FCF_TEMPLATE_TYPE_REGISTRATION__DECLNAMESPACES(am_type) \
          _FCF_TEMPLATE_TYPE_REGISTRATION__DECLNAMESPACES_0(_FCF_BASIS_REMOVE_PARENTHESIS( _FCF_BASIS_REMOVE_PARENTHESIS_ARGUMENT am_type))

  #define _FCF_TEMPLATE_TYPE_REGISTRATION__DECLENDNAMESPACES__INPUT_0(am_a1, am_a2, ...) am_a2
  #define _FCF_TEMPLATE_TYPE_REGISTRATION__DECLENDNAMESPACES__INPUT(am_a1, am_a2, ...) _FCF_TEMPLATE_TYPE_REGISTRATION__DECLENDNAMESPACES__INPUT_0(am_a1, am_a2, __VA_ARGS__)
  #define _FCF_REMOVE_PARENTHESIS_SELECTOR_FCF_TEMPLATE_TYPE_REGISTRATION__DECLENDNAMESPACES__REMOVE_PARENTHESIS_ARGUMENT
  #define _FCF_REMOVE_PARENTHESIS_SELECTOR_FCF_TEMPLATE_TYPE_REGISTRATION__DECLENDNAMESPACES__REMOVE_PARENTHESIS_ARGUMENT_EMPTY ,
  #define _FCF_TEMPLATE_TYPE_REGISTRATION__DECLENDNAMESPACES__REMOVE_PARENTHESIS_ARGUMENT(...) _FCF_TEMPLATE_TYPE_REGISTRATION__DECLENDNAMESPACES__REMOVE_PARENTHESIS_ARGUMENT_EMPTY
  #define _FCF_TEMPLATE_TYPE_REGISTRATION__DECLENDNAMESPACES__REMOVE_PARENTHESIS_0(...) _FCF_BASIS_SINGLE_EXPAND_ARGUMENTS(_FCF_TEMPLATE_TYPE_REGISTRATION__DECLENDNAMESPACES__INPUT, (_FCF_REMOVE_PARENTHESIS_SELECTOR##__VA_ARGS__, }))
  #define _FCF_TEMPLATE_TYPE_REGISTRATION__DECLENDNAMESPACES__REMOVE_PARENTHESIS(...) _FCF_TEMPLATE_TYPE_REGISTRATION__DECLENDNAMESPACES__REMOVE_PARENTHESIS_0(__VA_ARGS__)
  #define _FCF_TEMPLATE_TYPE_REGISTRATION__DECLENDNAMESPACES_1(am_a1, am_a2, am_a3,...)\
          _FCF_TEMPLATE_TYPE_REGISTRATION__DECLENDNAMESPACES__REMOVE_PARENTHESIS(_FCF_TEMPLATE_TYPE_REGISTRATION__DECLENDNAMESPACES__REMOVE_PARENTHESIS_ARGUMENT am_a1)\
          _FCF_TEMPLATE_TYPE_REGISTRATION__DECLENDNAMESPACES__REMOVE_PARENTHESIS(_FCF_TEMPLATE_TYPE_REGISTRATION__DECLENDNAMESPACES__REMOVE_PARENTHESIS_ARGUMENT am_a2)\
          _FCF_TEMPLATE_TYPE_REGISTRATION__DECLENDNAMESPACES__REMOVE_PARENTHESIS(_FCF_TEMPLATE_TYPE_REGISTRATION__DECLENDNAMESPACES__REMOVE_PARENTHESIS_ARGUMENT am_a3)
  #define _FCF_TEMPLATE_TYPE_REGISTRATION__DECLENDNAMESPACES_0(...)\
          _FCF_BASIS_EXPAND_ARGUMENTS(_FCF_TEMPLATE_TYPE_REGISTRATION__DECLENDNAMESPACES_1, (__VA_ARGS__, (), (), ()))
  #define _FCF_TEMPLATE_TYPE_REGISTRATION__DECLENDNAMESPACES(am_type) \
          _FCF_TEMPLATE_TYPE_REGISTRATION__DECLENDNAMESPACES_0(_FCF_BASIS_REMOVE_PARENTHESIS( _FCF_BASIS_REMOVE_PARENTHESIS_ARGUMENT am_type))


  #define FCF_TEMPLATE_TYPE_REGISTRATION(am_template, am_templateName, am_templateArgumentsDeclaration, am_templateArguments, am_templateArgumentsName) \
          _FCF_TYPE_REGISTRATION_IMPL_DECL_CLASSES((_FCF_TEMPLATE_TYPE_REGISTRATION__NAMESPACES(am_template) < _FCF_BASIS_REMOVE_PARENTHESIS(_FCF_BASIS_REMOVE_PARENTHESIS_ARGUMENT am_templateArguments) >), \
                                              am_templateArgumentsDeclaration, \
                                              am_templateName + "<" + _FCF_BASIS_REMOVE_PARENTHESIS(_FCF_BASIS_REMOVE_PARENTHESIS_ARGUMENT am_templateArgumentsName) + ">", \
                                              0,\
                                              true)\
        namespace fcf {\
          namespace NDetails {\
            namespace Declarations \
              _FCF_TEMPLATE_TYPE_REGISTRATION__DECLNAMESPACES(am_template) {\
                template <unsigned int Index>\
                struct PartialSpecifierRegistrar;\
                template <typename TUnstatic, unsigned int UnstaticCounter, int Index, typename = void>\
                struct PartialSpecifierRegistrarExists {\
                  enum { value = false };\
                };\
                template <typename TUnstatic, unsigned int UnstaticCounter, int Index>\
                struct PartialSpecifierRegistrarExists<TUnstatic, UnstaticCounter, Index, decltype(void(PartialSpecifierRegistrar<Index>()))> {\
                  enum { value = true };\
                };\
                template <typename TUnstatic, unsigned int UnstaticCounter, int Index = -1, bool Exisis = true>\
                struct PartialSpecifierRegistrarLast {\
                  enum { value = PartialSpecifierRegistrarLast<TUnstatic, UnstaticCounter, Index+1, PartialSpecifierRegistrarExists<TUnstatic, UnstaticCounter, Index+1>::value >::value };\
                };\
                template <typename TUnstatic, unsigned int UnstaticCounter, int Index>\
                struct PartialSpecifierRegistrarLast<TUnstatic, UnstaticCounter, Index, false> {\
                  enum { value = Index };\
                };\
              _FCF_TEMPLATE_TYPE_REGISTRATION__DECLENDNAMESPACES(am_template)\
            }\
          }\
        }\
        namespace fcf {\
          namespace NDetails {\
            template <typename TUnstatic, unsigned int UnstaticCounter, _FCF_BASIS_REMOVE_PARENTHESIS(_FCF_BASIS_REMOVE_PARENTHESIS_ARGUMENT am_templateArgumentsDeclaration), unsigned int Index, unsigned int Size >\
            struct SpecifierRegistrarCallerWalker<TUnstatic, UnstaticCounter, _FCF_TEMPLATE_TYPE_REGISTRATION__NAMESPACES(am_template) <_FCF_BASIS_REMOVE_PARENTHESIS(_FCF_BASIS_REMOVE_PARENTHESIS_ARGUMENT am_templateArguments)>, Index, Size> {\
              SpecifierRegistrarCallerWalker(){\
                typedef _FCF_TEMPLATE_TYPE_REGISTRATION__NAMESPACES(am_template) <_FCF_BASIS_REMOVE_PARENTHESIS(_FCF_BASIS_REMOVE_PARENTHESIS_ARGUMENT am_templateArguments)> type;\
                ::fcf::NDetails::Declarations _FCF_TEMPLATE_TYPE_REGISTRATION__NAMESPACES(am_template)::PartialSpecifierRegistrar<Index> registrar;\
                registrar.template registry<type>();\
                SpecifierRegistrarCallerWalker<TUnstatic, UnstaticCounter, type, Index+1, Size> nextCaller;\
              }\
            };\
            template <typename TUnstatic, unsigned int UnstaticCounter, _FCF_BASIS_REMOVE_PARENTHESIS(_FCF_BASIS_REMOVE_PARENTHESIS_ARGUMENT am_templateArgumentsDeclaration), unsigned int Index>\
            struct SpecifierRegistrarCallerWalker<TUnstatic, UnstaticCounter, _FCF_TEMPLATE_TYPE_REGISTRATION__NAMESPACES(am_template) <_FCF_BASIS_REMOVE_PARENTHESIS(_FCF_BASIS_REMOVE_PARENTHESIS_ARGUMENT am_templateArguments)>, Index, Index> {\
              SpecifierRegistrarCallerWalker(){\
              }\
            };\
            template <typename TUnstatic, unsigned int UnstaticCounter,  _FCF_BASIS_REMOVE_PARENTHESIS(_FCF_BASIS_REMOVE_PARENTHESIS_ARGUMENT am_templateArgumentsDeclaration)>\
            struct SpecifierRegistrarCaller<TUnstatic, UnstaticCounter, _FCF_TEMPLATE_TYPE_REGISTRATION__NAMESPACES(am_template) <_FCF_BASIS_REMOVE_PARENTHESIS(_FCF_BASIS_REMOVE_PARENTHESIS_ARGUMENT am_templateArguments)> > {\
              SpecifierRegistrarCaller(){\
                SpecifierRegistrarCallerWalker<TUnstatic, \
                                                  UnstaticCounter, \
                                                  _FCF_TEMPLATE_TYPE_REGISTRATION__NAMESPACES(am_template) <_FCF_BASIS_REMOVE_PARENTHESIS(_FCF_BASIS_REMOVE_PARENTHESIS_ARGUMENT am_templateArguments)>, \
                                                  0, \
                                                  ::fcf::NDetails::Declarations _FCF_TEMPLATE_TYPE_REGISTRATION__NAMESPACES(am_template)::PartialSpecifierRegistrarLast<TUnstatic, UnstaticCounter>::value\
                > registrer;\
              }\
            };\
          }\
        }
#endif // #ifndef FCF_TEMPLATE_TYPE_REGISTRATION

/**
* @def FCF_TEMPLATE_SPECIFIER_REGISTRATION(am_template, am_specifier)
* @brief Register a specifier for a template type.
* @param am_template Template type (No template arguments and no <> characters).
* @param am_specifier The type of the specifier.
*/
#ifndef FCF_TEMPLATE_SPECIFIER_REGISTRATION
#define FCF_TEMPLATE_SPECIFIER_REGISTRATION(am_template, am_specifier)\
      namespace fcf {\
        namespace NDetails {\
          namespace Declarations \
            _FCF_TEMPLATE_TYPE_REGISTRATION__DECLNAMESPACES(am_template) {\
              template <>\
              struct PartialSpecifierRegistrar< PartialSpecifierRegistrarLast<void, __COUNTER__>::value > {\
                template <typename Ty>\
                void registry(){\
                  ::fcf::SpecifierRegistrarHandler<Ty, am_specifier> registrar;\
                }\
              };\
            _FCF_TEMPLATE_TYPE_REGISTRATION__DECLENDNAMESPACES(am_template)\
          }\
        }\
      }
#endif


/**
 * @def FCF_CONVERTERS_REGISTRATION_FORCE(am_crossGroup, am_type, am_enableToConversion, am_enableFromConversion)
 * @brief Forced registration of converters for a group of types.
 * @details Performs type registration regardless of the FCF_BASIS_IMPLEMENTATION state.
 * @param am_crossGroup Name of the converter group.
 * @param am_type The type to register.
 * @param am_enableToConversion Flag to enable conversion "to" this type.
 * @param am_enableFromConversion Flag to enable conversion "from" this type.
 */
#ifndef FCF_CONVERTERS_REGISTRATION_FORCE
#define FCF_CONVERTERS_REGISTRATION_FORCE(am_crossGroup, am_type, am_enableToConversion, am_enableFromConversion) \
      namespace fcf { \
        namespace NDetails { \
          template <>\
          struct ConvertersRegistrarMarker<am_crossGroup, ConvertersRegistrarMarkerEnd<am_crossGroup, __COUNTER__>::value > {\
            typedef am_type type;\
            enum { fromConversion = am_enableFromConversion };\
            enum { toConversion = am_enableToConversion };\
          };\
          ConvertersRegistrarInitializer<am_crossGroup, __COUNTER__, am_type, ConvertersRegistrarMarkerEnd<am_crossGroup, __COUNTER__>::value, am_enableToConversion, am_enableFromConversion> _FCF_BASIS_VARNAME(_g_converters_registrar, __COUNTER__);\
        }\
      }
#endif

/**
 * @def FCF_CONVERTERS_REGISTRATION(am_crossGroup, am_type, am_enableToConversion, am_enableFromConversion)
 * @brief Registration of converters for a group of types. If FCF_BASIS_IMPLEMENTATION is not defined, the macro expands to an empty action.
 * @param am_crossGroup Name of the converter group.
 * @param am_type The type to register.
 * @param am_enableToConversion Flag to enable conversion "to" this type.
 * @param am_enableFromConversion Flag to enable conversion "from" this type.
 */
#ifdef FCF_BASIS_IMPLEMENTATION
  #define FCF_CONVERTERS_REGISTRATION(am_crossGroup, am_type, am_enableToConversion, am_enableFromConversion) \
    FCF_CONVERTERS_REGISTRATION_FORCE(am_crossGroup, am_type, am_enableToConversion, am_enableFromConversion)
#else
  #define FCF_CONVERTERS_REGISTRATION(am_crossGroup, am_type, am_enableToConversion, am_enableFromConversion)
#endif


/**
 * @def FCF_CONVERTER_REGISTRATION_FORCE(am_destinationType, am_sourceType)
 * @brief Forced registration of a converter between two specific types.
 * @details Performs type registration regardless of the FCF_BASIS_IMPLEMENTATION state.
 * @param am_destinationType Destination type.
 * @param am_sourceType Source type.
 */
#define FCF_CONVERTER_REGISTRATION_FORCE(am_destinationType, am_sourceType) \
  namespace fcf { \
    namespace NDetails { \
      namespace {\
        ::fcf::ConverterRegistration<am_destinationType, am_sourceType> _FCF_BASIS_VARNAME(_g_fcf_convert_registration, __COUNTER__);\
      }\
    }\
  }\

/**
 * @def FCF_CONVERTER_REGISTRATION(am_destinationType, am_sourceType)
 * @brief Registration of a converter between two types. If FCF_BASIS_IMPLEMENTATION is not defined, the macro expands to an empty action.
 * @param am_destinationType Destination type.
 * @param am_sourceType Source type.
 */
#ifdef FCF_BASIS_IMPLEMENTATION
  #define FCF_CONVERTER_REGISTRATION(am_destinationType, am_sourceType) \
    FCF_CONVERTER_REGISTRATION_FORCE(am_destinationType, am_sourceType)
#else
  #define FCF_CONVERTER_REGISTRATION(am_destinationType, am_sourceType)
#endif



/**
 * @def FCF_FUNCTION_REGISTRATION(am_name, am_space, am_source, am_signature, am_placeHolder, am_includeSourceCode, am_sourceCode)
 * @brief Registration of a function for dynamic invocation.
 * @param am_source The source function.
 *                           If the function is a template and has commas in its name,
 *                           the entire argument can be enclosed in parentheses.
 * @param am_name Function name (including namespace).
 * @param am_space Execution engine name. Multiple can be specified via comma
 *                       (For normal operation, use "cpu" - only on cpu, or "*" - for all).
 * @param am_signature Function signature.
 *                     If the return value is a template class and has commas,
 *                     the entire argument can be enclosed in parentheses.
 * @param am_placeHolder Function call options.
 *                       Multiple parameters enclosed in parentheses can be passed.
 *                       Each parameter consists of at least three arguments:
 *                         1. A specifier or fcf::CallOptions type.
 *                            If a specifier is provided, Placeholder rules are filled.
 *                            If fcf::CallOptions type is provided, function argument parameters are set.
 *                         2. Argument number.
 *                            For a specifier, it is the argument number from which data is taken.
 *                            For fcf::CallOptions type, it is the argument number for which options will be specified.
 *                         3. Further parameters depending on the first argument.
 *                            If a specifier is provided, function argument types follow, specifying
 *                            Placeholder insertion using fcf::Arg1 ... fcf::ArgN types.
 *                            If fcf::CallOptions type is provided, parameter flags are passed via fcf::CallArgumentOptions object.
 *                       )
 * @param am_includeSourceCode (values: true, false) - If true, the code from am_sourceCode
 *                                                             is added to the cpp file.
 * @param am_sourceCode Source code (for other engines).
 *
 * Example:
 * @code
 * FCF_FUNCTION_REGISTRATION(
 *                  fcf::fill,
 *                  "fill",
 *                  "cpu",
 *                  void(*) (FcfTest::BasisTest::CallIterationsTest::Item*, FcfTest::BasisTest::CallIterationsTest::Item*, int),
 *                 (
 *                  (fcf::CallOptions, 1, fcf::CallArgumentOptions<fcf::CAO_RESOLVE_POINTER|fcf::CAO_PAIR_ITERATION_POINTER|fcf::CAO_PAIR_SEGMENTATION>),
 *                  (fcf::ValueSpecifier, 1, FcfTest::BasisTest::CallIterationsTest::Item*, FcfTest::BasisTest::CallIterationsTest::Item*, fcf::Arg1)
 *                 ),
 *                 false,
 *                );
 * @endcode
 */
#ifndef FCF_FUNCTION_REGISTRATION
  #define _FCF_FUNCTION_REGISTRATION__SELECTOR_NOP_FCF_FUNCTION_REGISTRATION__REM_PARENTHESIS_NOP__EMPTY_SELECTOR ::fcf::Nop
  #define _FCF_FUNCTION_REGISTRATION__SELECTOR_NOP_ON_FCF_FUNCTION_REGISTRATION__REM_PARENTHESIS_NOP__EMPTY_SELECTOR
  #define _FCF_FUNCTION_REGISTRATION__REM_PARENTHESIS_NOP__EMPTY_SELECTOR(...) _ON_FCF_FUNCTION_REGISTRATION__REM_PARENTHESIS_NOP__EMPTY_SELECTOR __VA_ARGS__
  #define _FCF_FUNCTION_REGISTRATION__REM_PARENTHESIS_NOP_0(...) _FCF_FUNCTION_REGISTRATION__SELECTOR_NOP##__VA_ARGS__
  #define _FCF_FUNCTION_REGISTRATION__REM_PARENTHESIS_NOP(...) _FCF_FUNCTION_REGISTRATION__REM_PARENTHESIS_NOP_0(__VA_ARGS__)

  #define _FCF_FUNCTION_REGISTRATION__SELECTOR_FCF_FUNCTION_REGISTRATION__REM_PARENTHESIS__EMPTY_SELECTOR
  #define _FCF_FUNCTION_REGISTRATION__REM_PARENTHESIS__EMPTY_SELECTOR(...) _FCF_FUNCTION_REGISTRATION__REM_PARENTHESIS__EMPTY_SELECTOR __VA_ARGS__
  #define _FCF_FUNCTION_REGISTRATION__REM_PARENTHESIS_0(...) _FCF_FUNCTION_REGISTRATION__SELECTOR##__VA_ARGS__
  #define _FCF_FUNCTION_REGISTRATION__REM_PARENTHESIS(...) _FCF_FUNCTION_REGISTRATION__REM_PARENTHESIS_0(__VA_ARGS__)

  #define _FCF_FUNCTION_REGISTRATION__SIGNATURE(am_signature, am_arg) \
        typename ::fcf::CallDetails<\
                                                  _FCF_FUNCTION_REGISTRATION__REM_PARENTHESIS_NOP(_FCF_FUNCTION_REGISTRATION__REM_PARENTHESIS_NOP__EMPTY_SELECTOR am_arg)\
                                                  >::active_type

  #define _FCF_FUNCTION_REGISTRATION__RESOLVE_SIGNATURES_1(am_signature, am_arg1, am_arg2, am_arg3, ...) \
        _FCF_FUNCTION_REGISTRATION__SIGNATURE(am_signature, am_arg1),\
        _FCF_FUNCTION_REGISTRATION__SIGNATURE(am_signature, am_arg2),\
        _FCF_FUNCTION_REGISTRATION__SIGNATURE(am_signature, am_arg3)
  #define _FCF_FUNCTION_REGISTRATION__RESOLVE_SIGNATURES_0(am_signature, ...)\
                _FCF_BASIS_EXPAND_ARGUMENTS(_FCF_FUNCTION_REGISTRATION__RESOLVE_SIGNATURES_1, (am_signature, __VA_ARGS__, , , ))
  #define _FCF_FUNCTION_REGISTRATION__RESOLVE_SIGNATURES(am_signature, am_placeHolder) \
        _FCF_FUNCTION_REGISTRATION__RESOLVE_SIGNATURES_0(am_signature, _FCF_FUNCTION_REGISTRATION__REM_PARENTHESIS(_FCF_FUNCTION_REGISTRATION__REM_PARENTHESIS__EMPTY_SELECTOR am_placeHolder) )

  #define _FCF_FUNCTION_REGISTRATION_INCLUDE_SOURCE_CODE_false(...)
  #define _FCF_FUNCTION_REGISTRATION_INCLUDE_SOURCE_CODE_(...)
  #define _FCF_FUNCTION_REGISTRATION_INCLUDE_SOURCE_CODE_0(...)
  #define _FCF_FUNCTION_REGISTRATION_INCLUDE_SOURCE_CODE_1(am_sourceCode) _FCF_BASIS_REMOVE_PARENTHESIS(_FCF_BASIS_REMOVE_PARENTHESIS_ARGUMENT am_sourceCode)
  #define _FCF_FUNCTION_REGISTRATION_INCLUDE_SOURCE_CODE_true(am_sourceCode) _FCF_BASIS_REMOVE_PARENTHESIS(_FCF_BASIS_REMOVE_PARENTHESIS_ARGUMENT am_sourceCode)
  #define _FCF_FUNCTION_REGISTRATION_INCLUDE_SOURCE_CALL_1(am_macro, am_sourceCode)\
        am_macro(am_sourceCode)
  #define _FCF_FUNCTION_REGISTRATION_INCLUDE_SOURCE_CALL_0(am_macro, am_sourceCode)\
        _FCF_FUNCTION_REGISTRATION_INCLUDE_SOURCE_CALL_1(am_macro, am_sourceCode)
  #define _FCF_FUNCTION_REGISTRATION_INCLUDE_SOURCE_CALL(am_includeSourceCode, am_sourceCode)\
        _FCF_FUNCTION_REGISTRATION_INCLUDE_SOURCE_CALL_0(_FCF_BASIS_CONCAT3(_FCF_FUNCTION_REGISTRATION_INCLUDE_SOURCE_CODE,_, am_includeSourceCode), am_sourceCode)

  #define FCF_FUNCTION_REGISTRATION(am_source, am_name, am_space, am_signature, am_placeHolder, am_includeSourceCode, am_sourceCode) \
        _FCF_FUNCTION_REGISTRATION_INCLUDE_SOURCE_CALL(am_includeSourceCode, am_sourceCode); \
        namespace {\
        ::fcf::CallStorageRegistrator \
            _FCF_BASIS_VARNAME(_g_fcf_functionRegistrator, __COUNTER__) \
            (\
              _FCF_BASIS_REMOVE_PARENTHESIS(_FCF_BASIS_REMOVE_PARENTHESIS_ARGUMENT am_name), \
              am_space, \
              #am_source, \
              static_cast< _FCF_BASIS_REMOVE_PARENTHESIS(_FCF_BASIS_REMOVE_PARENTHESIS_ARGUMENT am_signature)>(am_source),\
              ::fcf::CallDetailsPack <\
                _FCF_FUNCTION_REGISTRATION__RESOLVE_SIGNATURES(am_signature, am_placeHolder )\
              > (),\
              #am_sourceCode\
            );\
        }
#endif // #ifndef FCF_FUNCTION_REGISTRATION


/**
 * @def FCF_GET_FUNCTION_INDEX(am_name, am_signature)
 * @brief Gets the index of a registered function by its name and signature.
 * @param am_name Function name.
 * @param am_signature Function signature.
 *                    Example: int(int, int)
 *                    or:    int(*)(int, int)
 * @return Function index in storage.
 */
#ifndef FCF_GET_FUNCTION_INDEX
#define FCF_GET_FUNCTION_INDEX(am_name, am_signature) \
      ::fcf::getCallStorage().getIndex<am_signature>(am_name)
#endif // #ifndef FCF_GET_FUNCTION_INDEX

/**
 * @def FCF_GET_FUNCTION(am_index)
 * @brief Gets a pointer to a function by its index.
 * @param am_index Function index.
 * @return Function pointer.
 */
#ifndef FCF_GET_FUNCTION
#define FCF_GET_FUNCTION(am_index) \
      ::fcf::getCallStorage().functions[am_index].function
#endif // #ifndef FCF_GET_FUNCTION

#define _FCF_EXCEPTION_DECLARE_A0(am_type, am_name, am_message) \
    class am_type: public ::fcf::Exception { \
      public:\
        am_type(const char* a_file, unsigned int a_line)\
          : ::fcf::Exception(am_name, am_message, a_file, a_line){\
        }\
        template <typename TArg1>\
        am_type(const Exception& a_subexception, const char* a_file, unsigned int a_line)\
          : ::fcf::Exception(a_subexception, am_name, am_message, a_file, a_line){\
        }\
    };

#define _FCF_EXCEPTION_DECLARE_A1(am_type, am_name, am_message) \
    class am_type: public ::fcf::Exception { \
      public:\
        template <typename TArg1>\
        am_type(const char* a_file, unsigned int a_line, const TArg1& a_arg1)\
          : ::fcf::Exception(am_name, am_message, a_file, a_line, a_arg1){\
        }\
        template <typename TArg1>\
        am_type(const Exception& a_subexception, const char* a_file, unsigned int a_line, const TArg1& a_arg1)\
          : ::fcf::Exception(a_subexception, am_name, am_message, a_file, a_line, a_arg1){\
        }\
    };

#define _FCF_EXCEPTION_DECLARE_A2(am_type, am_name, am_message) \
    class am_type: public ::fcf::Exception { \
      public:\
        template <typename TArg1, typename TArg2>\
        am_type(const char* a_file, unsigned int a_line, const TArg1& a_arg1, const TArg2& a_arg2)\
          : ::fcf::Exception(am_name, am_message, a_file, a_line, a_arg1, a_arg2){\
        }\
        template <typename TArg1, typename TArg2>\
        am_type(const Exception& a_subexception, const char* a_file, unsigned int a_line, const TArg1& a_arg1, const TArg2& a_arg2)\
          : ::fcf::Exception(a_subexception, am_name, am_message, a_file, a_line, a_arg1, a_arg2){\
        }\
    };

#define _FCF_EXCEPTION_DECLARE_A3(am_type, am_name, am_message) \
    class am_type: public ::fcf::Exception { \
      public:\
        template <typename TArg1, typename TArg2, typename TArg3>\
        am_type(const char* a_file, unsigned int a_line, const TArg1& a_arg1, const TArg2& a_arg2, const TArg3& a_arg3)\
          : ::fcf::Exception(am_name, am_message, a_file, a_line, a_arg1, a_arg2, a_arg3){\
        }\
        template <typename TArg1, typename TArg2, typename TArg3>\
        am_type(const Exception& a_subexception, const char* a_file, unsigned int a_line, const TArg1& a_arg1, const TArg2& a_arg2, const TArg3& a_arg3)\
          : ::fcf::Exception(a_subexception, am_name, am_message, a_file, a_line, a_arg1, a_arg2, a_arg3){\
        }\
    };

#define _FCF_EXCEPTION_DECLARE_A4(am_type, am_name, am_message) \
    class am_type: public ::fcf::Exception { \
      public:\
        template <typename TArg1, typename TArg2, typename TArg3, typename TArg4>\
        am_type(const char* a_file, unsigned int a_line, const TArg1& a_arg1, const TArg2& a_arg2, const TArg3& a_arg3, const TArg4& a_arg4)\
          : ::fcf::Exception(am_name, am_message, a_file, a_line, a_arg1, a_arg2, a_arg3, a_arg4){\
        }\
        template <typename TArg1, typename TArg2, typename TArg3, typename TArg4>\
        am_type(const Exception& a_subexception, const char* a_file, unsigned int a_line, const TArg1& a_arg1, const TArg2& a_arg2, const TArg3& a_arg3, const TArg4& a_arg4)\
          : ::fcf::Exception(a_subexception, am_name, am_message, a_file, a_line, a_arg1, a_arg2, a_arg3, a_arg4){\
        }\
    };

#define _FCF_EXCEPTION_DECLARE_A5(am_type, am_name, am_message) \
    class am_type: public ::fcf::Exception { \
      public:\
        template <typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5>\
        am_type(const char* a_file, unsigned int a_line, const TArg1& a_arg1, const TArg2& a_arg2, const TArg3& a_arg3, const TArg4& a_arg4, const TArg5& a_arg5)\
          : ::fcf::Exception(am_name, am_message, a_file, a_line, a_arg1, a_arg2, a_arg3, a_arg4, a_arg5){\
        }\
        template <typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5>\
        am_type(const Exception& a_subexception, const char* a_file, unsigned int a_line, const TArg1& a_arg1, const TArg2& a_arg2, const TArg3& a_arg3, const TArg4& a_arg4, const TArg5& a_arg5)\
          : ::fcf::Exception(a_subexception, am_name, am_message, a_file, a_line, a_arg1, a_arg2, a_arg3, a_arg4, a_arg5){\
        }\
    };


#define _FCF_EXCEPTION_DECLARE_A6(am_type, am_name, am_message) \
    class am_type: public ::fcf::Exception { \
      public:\
        template <typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5, typename TArg6>\
        am_type(const char* a_file, unsigned int a_line, const TArg1& a_arg1, const TArg2& a_arg2, const TArg3& a_arg3, const TArg4& a_arg4, const TArg5& a_arg5, const TArg6& a_arg6)\
          : ::fcf::Exception(am_name, am_message, a_file, a_line, a_arg1, a_arg2, a_arg3, a_arg4, a_arg5, a_arg6){\
        }\
        template <typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5, typename TArg6>\
        am_type(const Exception& a_subexception, const char* a_file, unsigned int a_line, const TArg1& a_arg1, const TArg2& a_arg2, const TArg3& a_arg3, const TArg4& a_arg4, const TArg5& a_arg5, const TArg6& a_arg6)\
          : ::fcf::Exception(a_subexception, am_name, am_message, a_file, a_line, a_arg1, a_arg2, a_arg3, a_arg4, a_arg5, a_arg6){\
        }\
    };

#define _FCF_EXCEPTION_DECLARE_A7(am_type, am_name, am_message) \
    class am_type: public ::fcf::Exception { \
      public:\
        template <typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5, typename TArg6, typename TArg7>\
        am_type(const char* a_file, unsigned int a_line, const TArg1& a_arg1, const TArg2& a_arg2, const TArg3& a_arg3, const TArg4& a_arg4, const TArg5& a_arg5, const TArg6& a_arg6, const TArg7& a_arg7)\
          : ::fcf::Exception(am_name, am_message, a_file, a_line, a_arg1, a_arg2, a_arg3, a_arg4, a_arg5, a_arg6, a_arg7){\
        }\
        template <typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5, typename TArg6, typename TArg7>\
        am_type(const Exception& a_subexception, const char* a_file, unsigned int a_line, const TArg1& a_arg1, const TArg2& a_arg2, const TArg3& a_arg3, const TArg4& a_arg4, const TArg5& a_arg5, const TArg6& a_arg6, const TArg7& a_arg7)\
          : ::fcf::Exception(a_subexception, am_name, am_message, a_file, a_line, a_arg1, a_arg2, a_arg3, a_arg4, a_arg5, a_arg6, a_arg7){\
        }\
    };

#define _FCF_EXCEPTION_DECLARE_A8(am_type, am_name, am_message) \
    class am_type: public ::fcf::Exception { \
      public:\
        template <typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5, typename TArg6, typename TArg7, typename TArg8>\
        am_type(const char* a_file, unsigned int a_line, const TArg1& a_arg1, const TArg2& a_arg2, const TArg3& a_arg3, const TArg4& a_arg4, const TArg5& a_arg5, const TArg6& a_arg6, const TArg7& a_arg7, const TArg8& a_arg8)\
          : ::fcf::Exception(am_name, am_message, a_file, a_line, a_arg1, a_arg2, a_arg3, a_arg4, a_arg5, a_arg6, a_arg7, a_arg8){\
        }\
        template <typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5, typename TArg6, typename TArg7, typename TArg8>\
        am_type(const Exception& a_subexception, const char* a_file, unsigned int a_line, const TArg1& a_arg1, const TArg2& a_arg2, const TArg3& a_arg3, const TArg4& a_arg4, const TArg5& a_arg5, const TArg6& a_arg6, const TArg7& a_arg7, const TArg8& a_arg8)\
          : ::fcf::Exception(a_subexception, am_name, am_message, a_file, a_line, a_arg1, a_arg2, a_arg3, a_arg4, a_arg5, a_arg6, a_arg7, a_arg8){\
        }\
    };

#define _FCF_EXCEPTION_DECLARE_A9(am_type, am_name, am_message) \
    class am_type: public ::fcf::Exception { \
      public:\
        template <typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5, typename TArg6, typename TArg7, typename TArg8, typename TArg9>\
        am_type(const char* a_file, unsigned int a_line, const TArg1& a_arg1, const TArg2& a_arg2, const TArg3& a_arg3, const TArg4& a_arg4, const TArg5& a_arg5, const TArg6& a_arg6, const TArg7& a_arg7, const TArg8& a_arg8, const TArg9& a_arg9)\
          : ::fcf::Exception(am_name, am_message, a_file, a_line, a_arg1, a_arg2, a_arg3, a_arg4, a_arg5, a_arg6, a_arg7, a_arg8, a_arg9){\
        }\
        template <typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5, typename TArg6, typename TArg7, typename TArg8, typename TArg9>\
        am_type(const Exception& a_subexception, const char* a_file, unsigned int a_line, const TArg1& a_arg1, const TArg2& a_arg2, const TArg3& a_arg3, const TArg4& a_arg4, const TArg5& a_arg5, const TArg6& a_arg6, const TArg7& a_arg7, const TArg8& a_arg8, const TArg9& a_arg9)\
          : ::fcf::Exception(a_subexception, am_name, am_message, a_file, a_line, a_arg1, a_arg2, a_arg3, a_arg4, a_arg5, a_arg6, a_arg7, a_arg8, a_arg9){\
        }\
    };

#define _FCF_EXCEPTION_DECLARE_0(a_macro, am_type, am_name, am_message, am_argCount) \
    a_macro(am_type, am_name, am_message)

/**
 * @def FCF_EXCEPTION_DECLARE(am_type, am_name, am_message, am_argCount)
 * @brief Macro for declaring a custom exception.
 * @param am_type Name of the new exception class.
 * @param am_name String name of the error.
 * @param am_message Message template.
 *                   Supports inserting exception arguments into the message.
 *                   Substitution format: "some_text ${{ARGUMENT_NUMBER}}$ some_text".
 *                   Argument indices (ARGUMENT_NUMBER) start from one.
 * @param am_argCount Number of arguments that the exception will store.
 */
#define FCF_EXCEPTION_DECLARE(am_type, am_name, am_message, am_argCount) \
    _FCF_EXCEPTION_DECLARE_0(_FCF_EXCEPTION_DECLARE_A##am_argCount, am_type, am_name, am_message, am_argCount)

/**
 * @def FCF_INVARIANT_EXCEPTION_CALL(am_call, am_enableThrow, am_errorVariableName, ...)
 * @brief Performs a call and handles potential exceptions based on a toggle.
 * @details If `am_enableThrow` is true, the call is executed normally, and any exception is thrown.
 *          If false, the call is executed, and if it fails, the resulting exception is assigned to `am_errorVariableName`.
 * @param am_call The function or expression to be called.
 * @param am_enableThrow Boolean flag: true to throw exception, false to assign it to a variable.
 * @param am_errorVariableName The variable where the exception will be stored if `am_enableThrow` is false.
 * @param ... Additional arguments to be passed to the `am_call`.
 */
#ifndef FCF_INVARIANT_EXCEPTION_CALL
  #define _FCF_INVARIANT_EXCEPTION_CALL__CONCAT_ARGS__COMMA_SELECTOR__ARG_A20(am_a1, am_a2, am_a3, am_a4, am_a5, am_a6, am_a7, am_a8, am_a9, am_a10, \
                                               am_a11, am_a12, am_a13, am_a14, am_a15, am_a16, am_a17, am_a18, am_a19, am_a20, \
                                               ...) am_a20
  #define _FCF_INVARIANT_EXCEPTION_CALL__CONCAT_ARGS__COMMA_SELECTOR__ARG_LIST(...) \
            _FCF_BASIS_EXPAND(_FCF_INVARIANT_EXCEPTION_CALL__CONCAT_ARGS__COMMA_SELECTOR__ARG_A20(__VA_ARGS__, CM, CM, CM, CM, CM, CM, CM, CM, CM, \
                                                              CM, CM, CM, CM, CM, CM, CM, CM, CM, CM))
  #define _FCF_INVARIANT_EXCEPTION_CALL__CONCAT_ARGS__COMMA_SELECTOR__PARENTHESIS(...) , , , , , , , , , , \
                                                        , , , , , , , , , ,

  #define _FCF_INVARIANT_EXCEPTION_CALL__CONCAT_ARGS__COMMA_SELECTOR(...) \
            _FCF_INVARIANT_EXCEPTION_CALL__CONCAT_ARGS__COMMA_SELECTOR__ARG_LIST ( _FCF_INVARIANT_EXCEPTION_CALL__CONCAT_ARGS__COMMA_SELECTOR__PARENTHESIS  __VA_ARGS__ ( ))

  #define _FCF_INVARIANT_EXCEPTION_CALL__CONCAT_ARGS__RESULT(am_argument, ...) am_argument
  #define _FCF_INVARIANT_EXCEPTION_CALL__CONCAT_ARGS__RESULTCM(am_argument, ...) __VA_ARGS__, am_argument

  #define _FCF_INVARIANT_EXCEPTION_CALL__CONCAT_ARGS__CALL_RESULT1(am_macro, am_argument, ...) am_macro(am_argument, __VA_ARGS__)
  #define _FCF_INVARIANT_EXCEPTION_CALL__CONCAT_ARGS__CALL_RESULT0(am_macro, am_argument, ...) \
            _FCF_INVARIANT_EXCEPTION_CALL__CONCAT_ARGS__CALL_RESULT1(_FCF_INVARIANT_EXCEPTION_CALL__CONCAT_ARGS__RESULT##am_macro, am_argument, __VA_ARGS__)
  #define _FCF_INVARIANT_EXCEPTION_CALL__CONCAT_ARGS__CALL_RESULT(am_macro, am_argument, ...) \
            _FCF_INVARIANT_EXCEPTION_CALL__CONCAT_ARGS__CALL_RESULT0(am_macro, am_argument, __VA_ARGS__)

  #define _FCF_INVARIANT_EXCEPTION_CALL__CONCAT_ARGS(am_error, ...) \
            _FCF_INVARIANT_EXCEPTION_CALL__CONCAT_ARGS__CALL_RESULT(_FCF_INVARIANT_EXCEPTION_CALL__CONCAT_ARGS__COMMA_SELECTOR(__VA_ARGS__), am_error, __VA_ARGS__)

  #define FCF_INVARIANT_EXCEPTION_CALL(am_call, am_enableThrow, am_errorVariableName, ...)\
    ((am_enableThrow) \
      ? _FCF_BASIS_REMOVE_PARENTHESIS(_FCF_BASIS_REMOVE_PARENTHESIS_ARGUMENT am_call)(__VA_ARGS__))\
      : _FCF_BASIS_REMOVE_PARENTHESIS(_FCF_BASIS_REMOVE_PARENTHESIS_ARGUMENT am_call)(_FCF_INVARIANT_EXCEPTION_CALL__CONCAT_ARGS(am_errorVariableName, __VA_ARGS__))
#endif

/**
 * @def FCF_INVARIANT_EXCEPTION(am_enableThrow, am_errorVariableName, am_exception)
 * @brief Conditional exception throwing or assignment.
 * @details If `am_enableThrow` is true, the specified `am_exception` is thrown.
 *          If false, the exception is assigned to `am_errorVariableName` instead of being thrown.
 * @param am_enableThrow Boolean flag: true to throw, false to assign.
 * @param am_errorVariableName The variable to receive the exception if not thrown.
 * @param am_exception The exception object to be thrown or assigned.
 */
#ifndef FCF_INVARIANT_EXCEPTION
  #define FCF_INVARIANT_EXCEPTION(am_enableThrow, am_errorVariableName, am_exception)\
      if (am_enableThrow) {\
        throw _FCF_BASIS_REMOVE_PARENTHESIS(_FCF_BASIS_REMOVE_PARENTHESIS_ARGUMENT am_exception);\
      } else {\
        if (am_errorVariableName) {\
          *(Exception*)am_errorVariableName = _FCF_BASIS_REMOVE_PARENTHESIS(_FCF_BASIS_REMOVE_PARENTHESIS_ARGUMENT am_exception);\
        }\
      }
#endif

#endif // #ifndef ___FCF_BASIS__MACRO_HPP___
