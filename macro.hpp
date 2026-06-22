#ifndef ___FCF_BASIS__MACRO_HPP___
#define ___FCF_BASIS__MACRO_HPP___

#include <stdexcept>

#ifdef FCF_IMPLEMENTATION
#ifndef FCF_BASIS_IMPLEMENTATION
#define FCF_BASIS_IMPLEMENTATION
#endif // #ifndef FCF_BASIS_IMPLEMENTATION
#endif // #ifdef FCF_IMPLEMENTATION

#ifdef FCF_EXPORT
#ifndef FCF_BASIS_EXPORT
#define FCF_BASIS_EXPORT
#endif // #ifndef FCF_BASIS_EXPORT
#endif // #ifdef FCF_EXPORT

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

#ifndef FCF_FOREACH_METHOD_WRAPPER
#define FCF_FOREACH_METHOD_WRAPPER(a_name, a_class, a_methodName)\
      struct a_name {\
        inline a_name(a_class* a_owner)\
          : _owner(a_owner){\
            if (!a_owner) {\
              throw std::invalid_argument("The empty pointer to the object to execute foreach is specified");\
            }\
        }\
        inline a_name(a_class& a_owner)\
          : _owner(&a_owner){\
        }\
        inline a_name(const a_class& a_owner)\
          : _owner((a_class*)&a_owner){\
        }\
        inline a_name(a_class&& a_owner) = delete;\
        template <typename ... TPack>\
        inline void operator()(TPack&&... a_args){\
          _owner->a_methodName(a_args...);\
        }\
        a_class* _owner;\
      };
#endif

#ifndef FCF_FOREACH_FUNCTION_WRAPPER
#define FCF_FOREACH_FUNCTION_WRAPPER(a_name, a_functionName)\
      struct a_name {\
        inline a_name(){\
        }\
        template <typename ... TPack>\
        inline void operator()(TPack&&... a_args){\
          a_functionName(a_args...);\
        }\
      };
#endif

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
  #define _FCF_BASIS_VARNAME__IMPL2(a_varName, a_suffix, a_counter) a_varName##a_suffix##a_counter
  #define _FCF_BASIS_VARNAME__IMPL1(a_varName, a_suffix, a_counter) _FCF_BASIS_VARNAME__IMPL2(a_varName, a_suffix, a_counter)
  #define _FCF_BASIS_VARNAME(a_varName, a_suffix) _FCF_BASIS_VARNAME__IMPL1(a_varName, a_suffix, __COUNTER__)
#endif // #ifndef _FCF_BASIS_VARNAME

#ifndef _FCF_BASIS_CONCAT2
  #define _FCF_BASIS_CONCAT2_IMPL2(a_varName, a_suffix) a_varName##a_suffix
  #define _FCF_BASIS_CONCAT2_IMPL1(a_varName, a_suffix) _FCF_BASIS_CONCAT2_IMPL2(a_varName, a_suffix)
  #define _FCF_BASIS_CONCAT2(a_varName, a_suffix) _FCF_BASIS_CONCAT2_IMPL1(a_varName, a_suffix)
#endif // #ifndef FCF_BASIS_CONCAT3

#ifndef FCF_SPECIFICATOR_REGISTRATION_FORCE
  #define _FCF_SPECIFICATOR_REGISTRATION_FORCE__L2(a_itemName, a_counter) a_itemName##_##a_counter
  #define _FCF_SPECIFICATOR_REGISTRATION_FORCE__L1(a_itemName, a_counter) _FCF_SPECIFICATOR_REGISTRATION_FORCE__L2(a_itemName, a_counter)
  #define FCF_SPECIFICATOR_REGISTRATION_FORCE(a_type, a_specificator) \
      namespace { \
        ::fcf::SpecificatorRegistrarHandler<a_type, a_specificator> _FCF_SPECIFICATOR_REGISTRATION_FORCE__L1(specificatorReg, __COUNTER__);\
      }
#endif // #ifndef FCF_SPECIFICATOR_REGISTRATION

#ifndef FCF_SPECIFICATOR_REGISTRATION
  #ifdef FCF_BASIS_IMPLEMENTATION
    #define FCF_SPECIFICATOR_REGISTRATION(a_type, a_specificator) FCF_SPECIFICATOR_REGISTRATION_FORCE(a_type, a_specificator)
  #else
    #define FCF_SPECIFICATOR_REGISTRATION(a_type, a_specificator)
  #endif // #ifdef FCF_BASIS_IMPLEMENTATION
#endif // #ifndef FCF_SPECIFICATOR_REGISTRATION

#ifndef _FCF_BASIS_EXPAND
#define _FCF_BASIS_EXPAND(...) __VA_ARGS__
#endif // #ifndef _FCF_BASIS_EXPAND

#ifndef _FCF_TYPE_REGISTRATION_IMPL_DECL_CLASS
#define _FCF_TYPE_REGISTRATION_IMPL_DECL_CLASS(a_type, a_templateArgs, a_name, a_index, a_basic_type, a_isTemplate) \
      template < _FCF_BASIS_EXPAND a_templateArgs>\
      struct fcf::TypeId< _FCF_BASIS_EXPAND a_type > {\
        typedef _FCF_BASIS_EXPAND a_basic_type basic_type;\
        bool          autoIndex()   { return ((a_index) & 0x00ffffff)== 0; }\
        unsigned int  index()       { return a_index; }\
        FCF_ATTRIBUTE_MINIMIZE_BEGIN\
        std::string   FCF_ATTRIBUTE_MINIMIZE  name()  { return std::string() + a_name; }\
        FCF_ATTRIBUTE_MINIMIZE_END\
        bool          isTemplate()  { return a_isTemplate; }\
      };
#endif // #ifndef _FCF_TYPE_REGISTRATION_IMPL_DECL_CLASS

#ifndef _FCF_TYPE_REGISTRATION_IMPL_DECL_CLASSES
#define _FCF_TYPE_REGISTRATION_IMPL_DECL_CLASSES(a_type, a_templateArgs, a_name, a_index, a_isTemplate)\
      _FCF_TYPE_REGISTRATION_IMPL_DECL_CLASS((_FCF_BASIS_EXPAND a_type), (_FCF_BASIS_EXPAND a_templateArgs),    a_name, a_index, a_type, a_isTemplate) \
      _FCF_TYPE_REGISTRATION_IMPL_DECL_CLASS((_FCF_BASIS_EXPAND a_type &), (_FCF_BASIS_EXPAND a_templateArgs),  a_name + "&", a_index | (1 << (24 + 1) ), a_type, a_isTemplate) \
      _FCF_TYPE_REGISTRATION_IMPL_DECL_CLASS((_FCF_BASIS_EXPAND a_type &&), (_FCF_BASIS_EXPAND a_templateArgs), a_name + "&&", a_index | (2 << (24 + 1) ), a_type, a_isTemplate) \
      _FCF_TYPE_REGISTRATION_IMPL_DECL_CLASS((_FCF_BASIS_EXPAND a_type *), (_FCF_BASIS_EXPAND a_templateArgs),  a_name + "*", a_index | (8 << (24 + 1) ), a_type, a_isTemplate) \
      _FCF_TYPE_REGISTRATION_IMPL_DECL_CLASS((_FCF_BASIS_EXPAND a_type **), (_FCF_BASIS_EXPAND a_templateArgs), a_name + "**", a_index | (16 << (24 + 1) ), a_type, a_isTemplate) \
      _FCF_TYPE_REGISTRATION_IMPL_DECL_CLASS((_FCF_BASIS_EXPAND a_type *&), (_FCF_BASIS_EXPAND a_templateArgs),  a_name + "*&", a_index | ((1 | 8) << (24 + 1) ), a_type, a_isTemplate) \
      _FCF_TYPE_REGISTRATION_IMPL_DECL_CLASS((_FCF_BASIS_EXPAND a_type **&), (_FCF_BASIS_EXPAND a_templateArgs),  a_name + "**&", a_index | ((1 | 16) << (24 + 1) ), a_type, a_isTemplate) \
      _FCF_TYPE_REGISTRATION_IMPL_DECL_CLASS((const _FCF_BASIS_EXPAND a_type), (_FCF_BASIS_EXPAND a_templateArgs),  "const " + a_name , a_index | ((4) << (24 + 1) ), a_type, a_isTemplate) \
      _FCF_TYPE_REGISTRATION_IMPL_DECL_CLASS((const _FCF_BASIS_EXPAND a_type &), (_FCF_BASIS_EXPAND a_templateArgs),  "const " + a_name + "&", a_index | ((1 | 4) << (24 + 1) ), a_type, a_isTemplate) \
      _FCF_TYPE_REGISTRATION_IMPL_DECL_CLASS((const _FCF_BASIS_EXPAND a_type &&), (_FCF_BASIS_EXPAND a_templateArgs), "const " + a_name + "&&", a_index | ((2 | 4) << (24 + 1)), a_type, a_isTemplate)\
      _FCF_TYPE_REGISTRATION_IMPL_DECL_CLASS((const _FCF_BASIS_EXPAND a_type *), (_FCF_BASIS_EXPAND a_templateArgs),  "const " + a_name + "*", a_index | ((8 | 4) << (24 + 1)), a_type, a_isTemplate) \
      _FCF_TYPE_REGISTRATION_IMPL_DECL_CLASS((const _FCF_BASIS_EXPAND a_type **), (_FCF_BASIS_EXPAND a_templateArgs), "const " + a_name + "**", a_index | (16 << (24 + 1) ) | (4 << (24 + 1)), a_type, a_isTemplate)\
      _FCF_TYPE_REGISTRATION_IMPL_DECL_CLASS((const _FCF_BASIS_EXPAND a_type *&), (_FCF_BASIS_EXPAND a_templateArgs), "const " + a_name + "*&", a_index | ((1 | 4 | 8) << (24 + 1)), a_type, a_isTemplate)\
      _FCF_TYPE_REGISTRATION_IMPL_DECL_CLASS((const _FCF_BASIS_EXPAND a_type **&), (_FCF_BASIS_EXPAND a_templateArgs), "const " + a_name + "**&", a_index | ((1 | 4 | 16) << (24 + 1)), a_type, a_isTemplate)
#endif // #ifndef _FCF_TYPE_REGISTRATION_IMPL_DECL_CLASSES

#ifndef _FCF_TYPE_REGISTRATION_IMPL_DECL_INITVAR
#define _FCF_TYPE_REGISTRATION_IMPL_DECL_INITVAR(a_type, a_name, a_index) \
      namespace { \
        fcf::TypeInitializer<a_type> _FCF_BASIS_VARNAME(typeInfoRegistry, _);\
        fcf::TypeInitializer<a_type*> _FCF_BASIS_VARNAME(typeInfoRegistry, _);\
        fcf::TypeInitializer<a_type**> _FCF_BASIS_VARNAME(typeInfoRegistry, _);\
        fcf::TypeInitializer<a_type&> _FCF_BASIS_VARNAME(typeInfoRegistry, _);\
        fcf::TypeInitializer<a_type&&> _FCF_BASIS_VARNAME(typeInfoRegistry, _);\
        fcf::TypeInitializer<const a_type*> _FCF_BASIS_VARNAME(typeInfoRegistry, _);\
        fcf::TypeInitializer<const a_type*&> _FCF_BASIS_VARNAME(typeInfoRegistry, _);\
        fcf::TypeInitializer<const a_type**> _FCF_BASIS_VARNAME(typeInfoRegistry, _);\
        fcf::TypeInitializer<const a_type**&> _FCF_BASIS_VARNAME(typeInfoRegistry, _);\
        fcf::TypeInitializer<const a_type&> _FCF_BASIS_VARNAME(typeInfoRegistry, _);\
        fcf::TypeInitializer<const a_type&&> _FCF_BASIS_VARNAME(typeInfoRegistry, _);\
      }
#endif // #ifndef _FCF_TYPE_REGISTRATION_IMPL_DECL_INITVAR

#ifndef FCF_TYPE_REGISTRATION_FORCE
#define FCF_TYPE_REGISTRATION_FORCE(a_type, a_name, a_index) \
      _FCF_TYPE_REGISTRATION_IMPL_DECL_CLASSES((a_type), (), a_name, a_index, false)\
      _FCF_TYPE_REGISTRATION_IMPL_DECL_INITVAR(a_type, a_name, a_index)
#endif // #ifndef FCF_TYPE_REGISTRATION

#ifndef FCF_TYPE_REGISTRATION
#ifdef FCF_BASIS_IMPLEMENTATION
#define FCF_TYPE_REGISTRATION(a_type, a_name, a_index) FCF_TYPE_REGISTRATION_FORCE(a_type, a_name, a_index)
#else
#define FCF_TYPE_REGISTRATION(a_type, a_name, a_index) \
        _FCF_TYPE_REGISTRATION_IMPL_DECL_CLASSES((a_type), (), a_name, a_index, false)
#endif
#endif // #ifndef FCF_TYPE_REGISTRATION

#ifndef FCF_TYPE_REGISTRATION_SINGLE
#ifdef FCF_BASIS_IMPLEMENTATION
#define FCF_TYPE_REGISTRATION_SINGLE(a_type, a_name, a_index) \
        _FCF_TYPE_REGISTRATION_IMPL_DECL_CLASS((a_type), (), a_name, a_index, (a_type), false)\
        fcf::TypeInitializer<a_type> _FCF_BASIS_VARNAME(typeInfoRegistry, _);
#else
#define FCF_TYPE_REGISTRATION_SINGLE(a_type, a_name, a_index) \
        _FCF_TYPE_REGISTRATION_IMPL_DECL_CLASS((a_type), (), a_name, a_index, (a_type), false)
#endif
#endif // #ifndef FCF_TYPE_REGISTRATION_SINGLE

#ifndef FCF_TEMPLATE_TYPE_REGISTRATION
  #define _FCF_REMOVE_PARENTHESIS_SELECTOR_FCF_TEMPLATE_TYPE_REGISTRATION__NAMESPACES__REMOVE_PARENTHESIS_ARGUMENT ::
  #define _FCF_REMOVE_PARENTHESIS_SELECTOR_FCF_TEMPLATE_TYPE_REGISTRATION__NAMESPACES__REMOVE_PARENTHESIS_ARGUMENT_EMPTY
  #define _FCF_TEMPLATE_TYPE_REGISTRATION__NAMESPACES__REMOVE_PARENTHESIS_ARGUMENT(...) _FCF_TEMPLATE_TYPE_REGISTRATION__NAMESPACES__REMOVE_PARENTHESIS_ARGUMENT_EMPTY
  #define _FCF_TEMPLATE_TYPE_REGISTRATION__NAMESPACES__REMOVE_PARENTHESIS_0(...) _FCF_REMOVE_PARENTHESIS_SELECTOR##__VA_ARGS__
  #define _FCF_TEMPLATE_TYPE_REGISTRATION__NAMESPACES__REMOVE_PARENTHESIS(...) _FCF_TEMPLATE_TYPE_REGISTRATION__NAMESPACES__REMOVE_PARENTHESIS_0(__VA_ARGS__)
  #define _FCF_TEMPLATE_TYPE_REGISTRATION__NAMESPACES_1(a_a1, a_a2, a_a3,...)\
          _FCF_TEMPLATE_TYPE_REGISTRATION__NAMESPACES__REMOVE_PARENTHESIS(_FCF_TEMPLATE_TYPE_REGISTRATION__NAMESPACES__REMOVE_PARENTHESIS_ARGUMENT a_a1)\
          _FCF_TEMPLATE_TYPE_REGISTRATION__NAMESPACES__REMOVE_PARENTHESIS(_FCF_TEMPLATE_TYPE_REGISTRATION__NAMESPACES__REMOVE_PARENTHESIS_ARGUMENT a_a2)\
          _FCF_TEMPLATE_TYPE_REGISTRATION__NAMESPACES__REMOVE_PARENTHESIS(_FCF_TEMPLATE_TYPE_REGISTRATION__NAMESPACES__REMOVE_PARENTHESIS_ARGUMENT a_a3)
  #define _FCF_TEMPLATE_TYPE_REGISTRATION__NAMESPACES_0(...)\
          _FCF_BASIS_EXPAND_ARGUMENTS(_FCF_TEMPLATE_TYPE_REGISTRATION__NAMESPACES_1, (__VA_ARGS__, (), (), ()))
  #define _FCF_TEMPLATE_TYPE_REGISTRATION__NAMESPACES(a_type) \
          _FCF_TEMPLATE_TYPE_REGISTRATION__NAMESPACES_0(_FCF_BASIS_REMOVE_PARENTHESIS( _FCF_BASIS_REMOVE_PARENTHESIS_ARGUMENT a_type))


  #define _FCF_REMOVE_PARENTHESIS_SELECTOR_FCF_TEMPLATE_TYPE_REGISTRATION__DECLNAMESPACES__REMOVE_PARENTHESIS_ARGUMENT { namespace 
  #define _FCF_REMOVE_PARENTHESIS_SELECTOR_FCF_TEMPLATE_TYPE_REGISTRATION__DECLNAMESPACES__REMOVE_PARENTHESIS_ARGUMENT_EMPTY
  #define _FCF_TEMPLATE_TYPE_REGISTRATION__DECLNAMESPACES__REMOVE_PARENTHESIS_ARGUMENT(...) _FCF_TEMPLATE_TYPE_REGISTRATION__DECLNAMESPACES__REMOVE_PARENTHESIS_ARGUMENT_EMPTY
  #define _FCF_TEMPLATE_TYPE_REGISTRATION__DECLNAMESPACES__REMOVE_PARENTHESIS_0(...) _FCF_REMOVE_PARENTHESIS_SELECTOR##__VA_ARGS__
  #define _FCF_TEMPLATE_TYPE_REGISTRATION__DECLNAMESPACES__REMOVE_PARENTHESIS(...) _FCF_TEMPLATE_TYPE_REGISTRATION__DECLNAMESPACES__REMOVE_PARENTHESIS_0(__VA_ARGS__)
  #define _FCF_TEMPLATE_TYPE_REGISTRATION__DECLNAMESPACES_1(a_a1, a_a2, a_a3,...)\
          _FCF_TEMPLATE_TYPE_REGISTRATION__DECLNAMESPACES__REMOVE_PARENTHESIS(_FCF_TEMPLATE_TYPE_REGISTRATION__DECLNAMESPACES__REMOVE_PARENTHESIS_ARGUMENT a_a1)\
          _FCF_TEMPLATE_TYPE_REGISTRATION__DECLNAMESPACES__REMOVE_PARENTHESIS(_FCF_TEMPLATE_TYPE_REGISTRATION__DECLNAMESPACES__REMOVE_PARENTHESIS_ARGUMENT a_a2)\
          _FCF_TEMPLATE_TYPE_REGISTRATION__DECLNAMESPACES__REMOVE_PARENTHESIS(_FCF_TEMPLATE_TYPE_REGISTRATION__DECLNAMESPACES__REMOVE_PARENTHESIS_ARGUMENT a_a3)
  #define _FCF_TEMPLATE_TYPE_REGISTRATION__DECLNAMESPACES_0(...)\
          _FCF_BASIS_EXPAND_ARGUMENTS( _FCF_TEMPLATE_TYPE_REGISTRATION__DECLNAMESPACES_1, (__VA_ARGS__, (), (), ()) )
  #define _FCF_TEMPLATE_TYPE_REGISTRATION__DECLNAMESPACES(a_type) \
          _FCF_TEMPLATE_TYPE_REGISTRATION__DECLNAMESPACES_0(_FCF_BASIS_REMOVE_PARENTHESIS( _FCF_BASIS_REMOVE_PARENTHESIS_ARGUMENT a_type))

  #define _FCF_TEMPLATE_TYPE_REGISTRATION__DECLENDNAMESPACES__INPUT_0(a_a1, a_a2, ...) a_a2
  #define _FCF_TEMPLATE_TYPE_REGISTRATION__DECLENDNAMESPACES__INPUT(a_a1, a_a2, ...) _FCF_TEMPLATE_TYPE_REGISTRATION__DECLENDNAMESPACES__INPUT_0(a_a1, a_a2, __VA_ARGS__)
  #define _FCF_REMOVE_PARENTHESIS_SELECTOR_FCF_TEMPLATE_TYPE_REGISTRATION__DECLENDNAMESPACES__REMOVE_PARENTHESIS_ARGUMENT 
  #define _FCF_REMOVE_PARENTHESIS_SELECTOR_FCF_TEMPLATE_TYPE_REGISTRATION__DECLENDNAMESPACES__REMOVE_PARENTHESIS_ARGUMENT_EMPTY ,
  #define _FCF_TEMPLATE_TYPE_REGISTRATION__DECLENDNAMESPACES__REMOVE_PARENTHESIS_ARGUMENT(...) _FCF_TEMPLATE_TYPE_REGISTRATION__DECLENDNAMESPACES__REMOVE_PARENTHESIS_ARGUMENT_EMPTY
  #define _FCF_TEMPLATE_TYPE_REGISTRATION__DECLENDNAMESPACES__REMOVE_PARENTHESIS_0(...) _FCF_BASIS_SINGLE_EXPAND_ARGUMENTS(_FCF_TEMPLATE_TYPE_REGISTRATION__DECLENDNAMESPACES__INPUT, (_FCF_REMOVE_PARENTHESIS_SELECTOR##__VA_ARGS__, }))
  #define _FCF_TEMPLATE_TYPE_REGISTRATION__DECLENDNAMESPACES__REMOVE_PARENTHESIS(...) _FCF_TEMPLATE_TYPE_REGISTRATION__DECLENDNAMESPACES__REMOVE_PARENTHESIS_0(__VA_ARGS__)
  #define _FCF_TEMPLATE_TYPE_REGISTRATION__DECLENDNAMESPACES_1(a_a1, a_a2, a_a3,...)\
          _FCF_TEMPLATE_TYPE_REGISTRATION__DECLENDNAMESPACES__REMOVE_PARENTHESIS(_FCF_TEMPLATE_TYPE_REGISTRATION__DECLENDNAMESPACES__REMOVE_PARENTHESIS_ARGUMENT a_a1)\
          _FCF_TEMPLATE_TYPE_REGISTRATION__DECLENDNAMESPACES__REMOVE_PARENTHESIS(_FCF_TEMPLATE_TYPE_REGISTRATION__DECLENDNAMESPACES__REMOVE_PARENTHESIS_ARGUMENT a_a2)\
          _FCF_TEMPLATE_TYPE_REGISTRATION__DECLENDNAMESPACES__REMOVE_PARENTHESIS(_FCF_TEMPLATE_TYPE_REGISTRATION__DECLENDNAMESPACES__REMOVE_PARENTHESIS_ARGUMENT a_a3)
  #define _FCF_TEMPLATE_TYPE_REGISTRATION__DECLENDNAMESPACES_0(...)\
          _FCF_BASIS_EXPAND_ARGUMENTS(_FCF_TEMPLATE_TYPE_REGISTRATION__DECLENDNAMESPACES_1, (__VA_ARGS__, (), (), ()))
  #define _FCF_TEMPLATE_TYPE_REGISTRATION__DECLENDNAMESPACES(a_type) \
          _FCF_TEMPLATE_TYPE_REGISTRATION__DECLENDNAMESPACES_0(_FCF_BASIS_REMOVE_PARENTHESIS( _FCF_BASIS_REMOVE_PARENTHESIS_ARGUMENT a_type))


  #define FCF_TEMPLATE_TYPE_REGISTRATION(a_template, a_templateName, a_templateArgumentsDeclaration, a_templateArguments, a_templateArgumentsName) \
          _FCF_TYPE_REGISTRATION_IMPL_DECL_CLASSES((_FCF_TEMPLATE_TYPE_REGISTRATION__NAMESPACES(a_template) < _FCF_BASIS_REMOVE_PARENTHESIS(_FCF_BASIS_REMOVE_PARENTHESIS_ARGUMENT a_templateArguments) >), \
                                              a_templateArgumentsDeclaration, \
                                              a_templateName + "<" + _FCF_BASIS_REMOVE_PARENTHESIS(_FCF_BASIS_REMOVE_PARENTHESIS_ARGUMENT a_templateArgumentsName) + ">", \
                                              0,\
                                              true)\
        namespace fcf {\
          namespace NDetails {\
            namespace Declarations \
              _FCF_BASIS_CONCAT2(_FCF_TEMPLATE_TYPE_REGISTRATION__DECLNAMESPACES(a_template), _specificator_declare) {\
                template <unsigned int Index>\
                struct PartialSpecificatorRegistrar;\
                template <typename TUnstatic, unsigned int UnstaticCounter, int Index, typename = void>\
                struct PartialSpecificatorRegistrarExists {\
                  enum { value = false };\
                };\
                template <typename TUnstatic, unsigned int UnstaticCounter, int Index>\
                struct PartialSpecificatorRegistrarExists<TUnstatic, UnstaticCounter, Index, decltype(void(PartialSpecificatorRegistrar<Index>()))> {\
                  enum { value = true };\
                };\
                template <typename TUnstatic, unsigned int UnstaticCounter, int Index = -1, bool Exisis = true>\
                struct PartialSpecificatorRegistrarLast {\
                  enum { value = PartialSpecificatorRegistrarLast<TUnstatic, UnstaticCounter, Index+1, PartialSpecificatorRegistrarExists<TUnstatic, UnstaticCounter, Index+1>::value >::value };\
                };\
                template <typename TUnstatic, unsigned int UnstaticCounter, int Index>\
                struct PartialSpecificatorRegistrarLast<TUnstatic, UnstaticCounter, Index, false> {\
                  enum { value = Index };\
                };\
              _FCF_TEMPLATE_TYPE_REGISTRATION__DECLENDNAMESPACES(a_template)\
            }\
          }\
        }\
        namespace fcf {\
          namespace NDetails {\
            template <typename TUnstatic, unsigned int UnstaticCounter, _FCF_BASIS_REMOVE_PARENTHESIS(_FCF_BASIS_REMOVE_PARENTHESIS_ARGUMENT a_templateArgumentsDeclaration), unsigned int Index, unsigned int Size >\
            struct SpecificatorRegistrarCallerWalker<TUnstatic, UnstaticCounter, _FCF_TEMPLATE_TYPE_REGISTRATION__NAMESPACES(a_template) <_FCF_BASIS_REMOVE_PARENTHESIS(_FCF_BASIS_REMOVE_PARENTHESIS_ARGUMENT a_templateArguments)>, Index, Size> {\
              SpecificatorRegistrarCallerWalker(){\
                typedef _FCF_TEMPLATE_TYPE_REGISTRATION__NAMESPACES(a_template) <_FCF_BASIS_REMOVE_PARENTHESIS(_FCF_BASIS_REMOVE_PARENTHESIS_ARGUMENT a_templateArguments)> type;\
                ::fcf::NDetails::Declarations _FCF_BASIS_CONCAT2(_FCF_TEMPLATE_TYPE_REGISTRATION__NAMESPACES(a_template),_specificator_declare)::PartialSpecificatorRegistrar<Index> registrar;\
                registrar.template registry<type>();\
                SpecificatorRegistrarCallerWalker<TUnstatic, UnstaticCounter, type, Index+1, Size> nextCaller;\
              }\
            };\
            template <typename TUnstatic, unsigned int UnstaticCounter, _FCF_BASIS_REMOVE_PARENTHESIS(_FCF_BASIS_REMOVE_PARENTHESIS_ARGUMENT a_templateArgumentsDeclaration), unsigned int Index>\
            struct SpecificatorRegistrarCallerWalker<TUnstatic, UnstaticCounter, _FCF_TEMPLATE_TYPE_REGISTRATION__NAMESPACES(a_template) <_FCF_BASIS_REMOVE_PARENTHESIS(_FCF_BASIS_REMOVE_PARENTHESIS_ARGUMENT a_templateArguments)>, Index, Index> {\
              SpecificatorRegistrarCallerWalker(){\
              }\
            };\
            template <typename TUnstatic, unsigned int UnstaticCounter,  _FCF_BASIS_REMOVE_PARENTHESIS(_FCF_BASIS_REMOVE_PARENTHESIS_ARGUMENT a_templateArgumentsDeclaration)>\
            struct SpecificatorRegistrarCaller<TUnstatic, UnstaticCounter, _FCF_TEMPLATE_TYPE_REGISTRATION__NAMESPACES(a_template) <_FCF_BASIS_REMOVE_PARENTHESIS(_FCF_BASIS_REMOVE_PARENTHESIS_ARGUMENT a_templateArguments)> > {\
              SpecificatorRegistrarCaller(){\
                SpecificatorRegistrarCallerWalker<TUnstatic, \
                                                  UnstaticCounter, \
                                                  _FCF_TEMPLATE_TYPE_REGISTRATION__NAMESPACES(a_template) <_FCF_BASIS_REMOVE_PARENTHESIS(_FCF_BASIS_REMOVE_PARENTHESIS_ARGUMENT a_templateArguments)>, \
                                                  0, \
                                                  ::fcf::NDetails::Declarations _FCF_BASIS_CONCAT2(_FCF_TEMPLATE_TYPE_REGISTRATION__NAMESPACES(a_template),_specificator_declare)::PartialSpecificatorRegistrarLast<TUnstatic, UnstaticCounter>::value\
                > registrer;\
              }\
            };\
          }\
        }
#endif // #ifndef FCF_TEMPLATE_TYPE_REGISTRATION

#ifndef FCF_TEMPLATE_SPECIFICATOR_REGISTRATION
#define FCF_TEMPLATE_SPECIFICATOR_REGISTRATION(a_template, a_specificator)\
      namespace fcf {\
        namespace NDetails {\
          namespace Declarations \
            _FCF_BASIS_CONCAT2(_FCF_TEMPLATE_TYPE_REGISTRATION__DECLNAMESPACES(a_template), _specificator_declare) {\
              template <>\
              struct PartialSpecificatorRegistrar< PartialSpecificatorRegistrarLast<void, __COUNTER__>::value > {\
                template <typename Ty>\
                void registry(){\
                  ::fcf::SpecificatorRegistrarHandler<Ty, a_specificator> registrar;\
                }\
              };\
            _FCF_TEMPLATE_TYPE_REGISTRATION__DECLENDNAMESPACES(a_template)\
          }\
        }\
      }
#endif


#ifndef FCF_CONVERTERS_REGISTRATION_FORCE
#define FCF_CONVERTERS_REGISTRATION_FORCE(a_crossGroup, a_type, a_enableToConversion, a_enableFromConversion) \
      namespace fcf { \
        namespace NDetails { \
          template <>\
          struct ConvertersRegistrarMarker<a_crossGroup, ConvertersRegistrarMarkerEnd<a_crossGroup, __COUNTER__>::value > {\
            typedef a_type type;\
            enum { fromConversion = a_enableFromConversion };\
            enum { toConversion = a_enableToConversion };\
          };\
          ConvertersRegistrarInitializer<a_crossGroup, __COUNTER__, a_type, ConvertersRegistrarMarkerEnd<a_crossGroup, __COUNTER__>::value, a_enableToConversion, a_enableFromConversion> _FCF_BASIS_VARNAME(_g_converters_registrar, __COUNTER__);\
        }\
      }
#endif

#ifdef FCF_BASIS_IMPLEMENTATION
  #define FCF_CONVERTERS_REGISTRATION(a_crossGroup, a_type, a_enableToConversion, a_enableFromConversion) \
    FCF_CONVERTERS_REGISTRATION_FORCE(a_crossGroup, a_type, a_enableToConversion, a_enableFromConversion)
#else
  #define FCF_CONVERTERS_REGISTRATION(a_crossGroup, a_type, a_enableToConversion, a_enableFromConversion)
#endif


#define FCF_CONVERTER_REGISTRATION_FORCE(am_destinationType, am_sourceType) \
  namespace fcf { \
    namespace NDetails { \
      namespace {\
        ::fcf::ConverterRegistration<am_destinationType, am_sourceType> _FCF_BASIS_VARNAME(_g_fcf_convert_registration, __COUNTER__);\
      }\
    }\
  }\

#ifdef FCF_BASIS_IMPLEMENTATION
  #define FCF_CONVERTER_REGISTRATION(am_destinationType, am_sourceType) \
    FCF_CONVERTER_REGISTRATION_FORCE(am_destinationType, am_sourceType)
#else
  #define FCF_CONVERTER_REGISTRATION(am_destinationType, am_sourceType)
#endif



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

  #define _FCF_FUNCTION_REGISTRATION__SIGNATURE(a_signature, a_arg) \
        typename ::fcf::CallDetails<\
                                                  _FCF_FUNCTION_REGISTRATION__REM_PARENTHESIS_NOP(_FCF_FUNCTION_REGISTRATION__REM_PARENTHESIS_NOP__EMPTY_SELECTOR a_arg)\
                                                  >::active_type

  #define _FCF_FUNCTION_REGISTRATION__RESOLVE_SIGNATURES_1(a_signature, a_arg1, a_arg2, a_arg3, ...) \
        _FCF_FUNCTION_REGISTRATION__SIGNATURE(a_signature, a_arg1),\
        _FCF_FUNCTION_REGISTRATION__SIGNATURE(a_signature, a_arg2),\
        _FCF_FUNCTION_REGISTRATION__SIGNATURE(a_signature, a_arg3)
  #define _FCF_FUNCTION_REGISTRATION__RESOLVE_SIGNATURES_0(a_signature, ...)\
                _FCF_BASIS_EXPAND_ARGUMENTS(_FCF_FUNCTION_REGISTRATION__RESOLVE_SIGNATURES_1, (a_signature, __VA_ARGS__, , , ))

  #define _FCF_FUNCTION_REGISTRATION__RESOLVE_SIGNATURES(a_signature, a_placeHolder) \
        _FCF_FUNCTION_REGISTRATION__RESOLVE_SIGNATURES_0(a_signature, _FCF_FUNCTION_REGISTRATION__REM_PARENTHESIS(_FCF_FUNCTION_REGISTRATION__REM_PARENTHESIS__EMPTY_SELECTOR a_placeHolder) )

  #define _FCF_FUNCTION_REGISTRATION__VARNAME_RESOLVE_0(a_varName, a_line, a_arg1, a_arg2, a_arg3, a_arg4, a_arg5, ...)\
                                    a_varName##_##a_arg1##_##a_arg2##_##a_arg3##_##a_arg4##_##a_arg5##_##a_line
  #define _FCF_FUNCTION_REGISTRATION__VARNAME_RESOLVE(a_varName, a_line, a_arg1, a_arg2, a_arg3, a_arg4, a_arg5, ...)\
                                    _FCF_BASIS_EXPAND_ARGUMENTS(_FCF_FUNCTION_REGISTRATION__VARNAME_RESOLVE_0, (a_varName, a_line, a_arg1, a_arg2, a_arg3, a_arg4, a_arg5))

  #define _FCF_FUNCTION_REGISTRATION__NAME_RESOLVE_1(a_arg1, a_arg2, a_arg3, a_arg4, a_arg5, ...)\
                                    a_arg1 "::" a_arg2 "::" a_arg3 "::" a_arg4 "::" a_arg5
  #define _FCF_FUNCTION_REGISTRATION__NAME_RESOLVE_0(a_arg1, a_arg2, a_arg3, a_arg4, a_arg5, ...)\
                                    _FCF_FUNCTION_REGISTRATION__NAME_RESOLVE_1(#a_arg1, #a_arg2, #a_arg3, #a_arg4, #a_arg5)
  #define _FCF_FUNCTION_REGISTRATION__NAME_RESOLVE(a_arg1, a_arg2, a_arg3, a_arg4, a_arg5, ...)\
                                    _FCF_BASIS_EXPAND_ARGUMENTS(_FCF_FUNCTION_REGISTRATION__NAME_RESOLVE_0, (a_arg1, a_arg2, a_arg3, a_arg4, a_arg5))

  #define FCF_FUNCTION_REGISTRATION(a_name, a_space, a_sourceName, a_signature, a_placeHolder, a_sourceCode) \
        a_sourceCode; \
        ::fcf::CallStorageRegistrator \
          _FCF_FUNCTION_REGISTRATION__VARNAME_RESOLVE(functionRegistrator, __COUNTER__, _FCF_BASIS_REMOVE_PARENTHESIS(_FCF_BASIS_REMOVE_PARENTHESIS_ARGUMENT a_name),,,,,,,,) \
            (\
              _FCF_FUNCTION_REGISTRATION__NAME_RESOLVE( _FCF_BASIS_REMOVE_PARENTHESIS(_FCF_BASIS_REMOVE_PARENTHESIS_ARGUMENT a_name),,,,,,,,), \
              a_space, \
              #a_sourceName, \
              static_cast<a_signature>(a_sourceName),\
              ::fcf::CallDetailsPack <\
                _FCF_FUNCTION_REGISTRATION__RESOLVE_SIGNATURES(a_signature, a_placeHolder )\
              > (),\
              #a_sourceCode\
            );
#endif // #ifndef FCF_FUNCTION_REGISTRATION


#ifndef FCF_GET_FUNCTION_INDEX
#define FCF_GET_FUNCTION_INDEX(a_name, a_signature) \
      ::fcf::CallStorageRegistrator::getIndex<a_signature>(a_name)
#endif // #ifndef FCF_GET_FUNCTION_INDEX

#ifndef FCF_GET_FUNCTION
#define FCF_GET_FUNCTION(a_index) \
      ::fcf::getCallStorage().functions[a_index].function
#endif // #ifndef FCF_GET_FUNCTION
/*
  #define FCF_EXCEPTION_DECLARE(am_type, am_name, am_message) \
    class am_type: public ::fcf::Exception { \
      public:\
        template <typename ...TArgPack>\
        am_type(const char* a_file, unsigned int a_line, const TArgPack&... a_argPack)\
          : ::fcf::Exception(am_name, am_message, a_file, a_line, a_argPack... ){\
        }\
        template <typename ...TArgPack>\
        am_type(const Exception& a_subexception, const char* a_file, unsigned int a_line, const TArgPack&... a_argPack)\
          : ::fcf::Exception(a_subexception, am_name, am_message, a_file, a_line, a_argPack... ){\
        }\
    };
*/
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

#define FCF_EXCEPTION_DECLARE(am_type, am_name, am_message, am_argCount) \
    _FCF_EXCEPTION_DECLARE_0(_FCF_EXCEPTION_DECLARE_A##am_argCount, am_type, am_name, am_message, am_argCount)

#endif // #ifndef ___FCF_BASIS__MACRO_HPP___

