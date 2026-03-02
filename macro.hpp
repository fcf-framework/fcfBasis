#ifndef ___FCF_BASIS__MACRO_HPP___
#define ___FCF_BASIS__MACRO_HPP___

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
        }\
        inline a_name(a_class&& a_owner)\
          : _owner(&a_owner){\
        }\
        inline a_name(a_class& a_owner)\
          : _owner(&a_owner){\
        }\
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


  #define FCF_REMOVE_PARENTHESIS_SELECTORFCF_REMOVE_PARENTHESIS_ARGUMENT
  #define FCF_REMOVE_PARENTHESIS_ARGUMENT(...) FCF_REMOVE_PARENTHESIS_ARGUMENT __VA_ARGS__
  #define FCF_REMOVE_PARENTHESIS_0(...) FCF_REMOVE_PARENTHESIS_SELECTOR##__VA_ARGS__
  #define FCF_REMOVE_PARENTHESIS(...) FCF_REMOVE_PARENTHESIS_0(__VA_ARGS__)

  #ifndef FCF_BASIS_VARNAME
    #define FCF_BASIS_VARNAME__IMPL2(a_varName, a_suffix, a_counter) a_varName##a_suffix##a_counter
    #define FCF_BASIS_VARNAME__IMPL1(a_varName, a_suffix, a_counter) FCF_BASIS_VARNAME__IMPL2(a_varName, a_suffix, a_counter)
    #define FCF_BASIS_VARNAME(a_varName, a_suffix) FCF_BASIS_VARNAME__IMPL1(a_varName, a_suffix, __COUNTER__)
  #endif // #ifndef FCF_BASIS_VARNAME

  #ifndef FCF_BASIS_CONCAT3
    #define FCF_BASIS_CONCAT3_IMPL1(a_varName, a_suffix, a_counter) a_varName##a_suffix##a_counter
    #define FCF_BASIS_CONCAT3(a_varName, a_suffix, a_counter) FCF_BASIS_CONCAT3_IMPL1(a_varName, a_suffix, a_counter)
  #endif // #ifndef FCF_BASIS_CONCAT3

  #ifndef FCF_CONCAT2
    #define FCF_CONCAT2_IMPL1(a_varName, a_suffix) a_varName##a_suffix
    #define FCF_CONCAT2(a_varName, a_suffix) FCF_CONCAT2_IMPL1(a_varName, a_suffix)
  #endif // #ifndef FCF_BASIS_CONCAT3


  #ifndef FCF_SPECIFICATOR_REGISTRY_FORCE
    #define __FCF_SPECIFICATOR_REGISTRY_FORCE__L2(a_itemName, a_counter) a_itemName##_##a_counter
    #define __FCF_SPECIFICATOR_REGISTRY_FORCE__L1(a_itemName, a_counter) __FCF_SPECIFICATOR_REGISTRY_FORCE__L2(a_itemName, a_counter)
    #define FCF_SPECIFICATOR_REGISTRY_FORCE(a_type, a_specificator) \
      namespace { \
        ::fcf::SpecificatorRegistrarHandler<a_type, a_specificator> __FCF_SPECIFICATOR_REGISTRY_FORCE__L1(specificatorReg, __COUNTER__);\
      }
  #endif // #ifndef FCF_SPECIFICATOR_REGISTRY

  #ifndef FCF_SPECIFICATOR_REGISTRY
    #ifdef FCF_BASIS_IMPLEMENTATION
      #define FCF_SPECIFICATOR_REGISTRY(a_type, a_specificator) FCF_SPECIFICATOR_REGISTRY_FORCE(a_type, a_specificator)
    #else
      #define FCF_SPECIFICATOR_REGISTRY(a_type, a_specificator)
    #endif // #ifdef FCF_BASIS_IMPLEMENTATION
  #endif // #ifndef FCF_SPECIFICATOR_REGISTRY

  #ifndef FCF_BASIS_EXPAND
    #define FCF_BASIS_EXPAND(...) __VA_ARGS__
  #endif // #ifndef FCF_BASIS_EXPAND

  #ifndef FCF_TYPEID_REGISTRY_IMPL_DECL_CLASS
    #define FCF_TYPEID_REGISTRY_IMPL_DECL_CLASS(a_type, a_templateArgs, a_name, a_index, a_basic_type, a_isTemplate) \
      template < FCF_BASIS_EXPAND a_templateArgs>\
      struct fcf::TypeId< FCF_BASIS_EXPAND a_type > {\
        typedef FCF_BASIS_EXPAND a_basic_type basic_type;\
        bool          autoIndex()   { return ((a_index) & 0x00ffffff)== 0; }\
        unsigned int  index()       { return a_index; }\
        std::string   name()        { return std::string() + a_name; }\
        bool          isTemplate()  { return a_isTemplate; }\
      };
  #endif // #ifndef FCF_TYPEID_REGISTRY_IMPL_DECL_CLASS

  #ifndef FCF_TYPEID_REGISTRY_IMPL_DECL_CLASSES
    #define FCF_TYPEID_REGISTRY_IMPL_DECL_CLASSES(a_type, a_templateArgs, a_name, a_index, a_isTemplate)\
      FCF_TYPEID_REGISTRY_IMPL_DECL_CLASS((FCF_BASIS_EXPAND a_type), (FCF_BASIS_EXPAND a_templateArgs),    a_name, a_index, a_type, a_isTemplate) \
      FCF_TYPEID_REGISTRY_IMPL_DECL_CLASS((FCF_BASIS_EXPAND a_type &), (FCF_BASIS_EXPAND a_templateArgs),  a_name + "&", a_index | (1 << (24 + 1) ), a_type, a_isTemplate) \
      FCF_TYPEID_REGISTRY_IMPL_DECL_CLASS((FCF_BASIS_EXPAND a_type &&), (FCF_BASIS_EXPAND a_templateArgs), a_name + "&&", a_index | (2 << (24 + 1) ), a_type, a_isTemplate) \
      FCF_TYPEID_REGISTRY_IMPL_DECL_CLASS((FCF_BASIS_EXPAND a_type *), (FCF_BASIS_EXPAND a_templateArgs),  a_name + "*", a_index | (8 << (24 + 1) ), a_type, a_isTemplate) \
      FCF_TYPEID_REGISTRY_IMPL_DECL_CLASS((FCF_BASIS_EXPAND a_type **), (FCF_BASIS_EXPAND a_templateArgs), a_name + "**", a_index | (16 << (24 + 1) ), a_type, a_isTemplate) \
      FCF_TYPEID_REGISTRY_IMPL_DECL_CLASS((FCF_BASIS_EXPAND a_type *&), (FCF_BASIS_EXPAND a_templateArgs),  a_name + "*&", a_index | ((1 | 8) << (24 + 1) ), a_type, a_isTemplate) \
      FCF_TYPEID_REGISTRY_IMPL_DECL_CLASS((FCF_BASIS_EXPAND a_type **&), (FCF_BASIS_EXPAND a_templateArgs),  a_name + "**&", a_index | ((1 | 16) << (24 + 1) ), a_type, a_isTemplate) \
      FCF_TYPEID_REGISTRY_IMPL_DECL_CLASS((const FCF_BASIS_EXPAND a_type), (FCF_BASIS_EXPAND a_templateArgs),  "const " + a_name , a_index | ((4) << (24 + 1) ), a_type, a_isTemplate) \
      FCF_TYPEID_REGISTRY_IMPL_DECL_CLASS((const FCF_BASIS_EXPAND a_type &), (FCF_BASIS_EXPAND a_templateArgs),  "const " + a_name + "&", a_index | ((1 | 4) << (24 + 1) ), a_type, a_isTemplate) \
      FCF_TYPEID_REGISTRY_IMPL_DECL_CLASS((const FCF_BASIS_EXPAND a_type &&), (FCF_BASIS_EXPAND a_templateArgs), "const " + a_name + "&&", a_index | ((2 | 4) << (24 + 1)), a_type, a_isTemplate)\
      FCF_TYPEID_REGISTRY_IMPL_DECL_CLASS((const FCF_BASIS_EXPAND a_type *), (FCF_BASIS_EXPAND a_templateArgs),  "const " + a_name + "*", a_index | ((8 | 4) << (24 + 1)), a_type, a_isTemplate) \
      FCF_TYPEID_REGISTRY_IMPL_DECL_CLASS((const FCF_BASIS_EXPAND a_type **), (FCF_BASIS_EXPAND a_templateArgs), "const " + a_name + "**", a_index | (16 << (24 + 1) ) | (4 << (24 + 1)), a_type, a_isTemplate)\
      FCF_TYPEID_REGISTRY_IMPL_DECL_CLASS((const FCF_BASIS_EXPAND a_type *&), (FCF_BASIS_EXPAND a_templateArgs), "const " + a_name + "*&", a_index | ((1 | 4 | 8) << (24 + 1)), a_type, a_isTemplate)\
      FCF_TYPEID_REGISTRY_IMPL_DECL_CLASS((const FCF_BASIS_EXPAND a_type **&), (FCF_BASIS_EXPAND a_templateArgs), "const " + a_name + "**&", a_index | ((1 | 4 | 16) << (24 + 1)), a_type, a_isTemplate)
  #endif // #ifndef FCF_TYPEID_REGISTRY_IMPL_DECL_CLASSES

  #ifndef FCF_TYPEID_REGISTRY_IMPL_DECL_INITVAR
    #define FCF_TYPEID_REGISTRY_IMPL_DECL_INITVAR(a_type, a_name, a_index) \
      namespace { \
        fcf::TypeInitializer<a_type> FCF_BASIS_VARNAME(typeInfoRegistry, _);\
        fcf::TypeInitializer<a_type*> FCF_BASIS_VARNAME(typeInfoRegistry, _);\
        fcf::TypeInitializer<a_type**> FCF_BASIS_VARNAME(typeInfoRegistry, _);\
        fcf::TypeInitializer<a_type&> FCF_BASIS_VARNAME(typeInfoRegistry, _);\
        fcf::TypeInitializer<a_type&&> FCF_BASIS_VARNAME(typeInfoRegistry, _);\
        fcf::TypeInitializer<const a_type*> FCF_BASIS_VARNAME(typeInfoRegistry, _);\
        fcf::TypeInitializer<const a_type*&> FCF_BASIS_VARNAME(typeInfoRegistry, _);\
        fcf::TypeInitializer<const a_type**> FCF_BASIS_VARNAME(typeInfoRegistry, _);\
        fcf::TypeInitializer<const a_type**&> FCF_BASIS_VARNAME(typeInfoRegistry, _);\
        fcf::TypeInitializer<const a_type&> FCF_BASIS_VARNAME(typeInfoRegistry, _);\
        fcf::TypeInitializer<const a_type&&> FCF_BASIS_VARNAME(typeInfoRegistry, _);\
      }
  #endif // #ifndef FCF_TYPEID_REGISTRY_IMPL_DECL_INITVAR

  #ifndef FCF_TYPEID_REGISTRY_FORCE
    #define FCF_TYPEID_REGISTRY_FORCE(a_type, a_name, a_index) \
      FCF_TYPEID_REGISTRY_IMPL_DECL_CLASSES((a_type), (), a_name, a_index, false)\
      FCF_TYPEID_REGISTRY_IMPL_DECL_INITVAR(a_type, a_name, a_index)
  #endif // #ifndef FCF_TYPEID_REGISTRY

  #ifndef FCF_TYPEID_REGISTRY
    #ifdef FCF_BASIS_IMPLEMENTATION
      #define FCF_TYPEID_REGISTRY(a_type, a_name, a_index) FCF_TYPEID_REGISTRY_FORCE(a_type, a_name, a_index)
    #else
      #define FCF_TYPEID_REGISTRY(a_type, a_name, a_index) \
        FCF_TYPEID_REGISTRY_IMPL_DECL_CLASSES((a_type), (), a_name, a_index, false)
    #endif
  #endif // #ifndef FCF_TYPEID_REGISTRY

  #ifndef FCF_TYPEID_REGISTRY_SINGLE
    #ifdef FCF_BASIS_IMPLEMENTATION
      #define FCF_TYPEID_REGISTRY_SINGLE(a_type, a_name, a_index) \
        FCF_TYPEID_REGISTRY_IMPL_DECL_CLASS((a_type), (), a_name, a_index, (a_type), false)\
        fcf::TypeInitializer<a_type> FCF_BASIS_VARNAME(typeInfoRegistry, _);
    #else
      #define FCF_TYPEID_REGISTRY_SINGLE(a_type, a_name, a_index) \
        FCF_TYPEID_REGISTRY_IMPL_DECL_CLASS((a_type), (), a_name, a_index, (a_type), false)
    #endif
  #endif // #ifndef FCF_TYPEID_REGISTRY_SINGLE

  #ifndef FCF_TYPEID_TEMPLATE1_REGISTRY
    #define FCF_TYPEID_TEMPLATE1_REGISTRY(a_type, a_name) \
      FCF_TYPEID_REGISTRY_IMPL_DECL_CLASSES((a_type<T1>), (typename T1), a_name + "<" + fcf::Type<T1>().name() + ">", 0, true)
  #endif // #ifndef FCF_TYPEID_TEMPLATE1_REGISTRY

  #ifndef FCF_TEMPLATE_TYPEID_DECLARE
    #define FCF_REMOVE_PARENTHESIS_SELECTORFCF_TEMPLATE_TYPEID_DECLARE__NAMESPACES__REMOVE_PARENTHESIS_ARGUMENT ::
    #define FCF_REMOVE_PARENTHESIS_SELECTORFCF_TEMPLATE_TYPEID_DECLARE__NAMESPACES__REMOVE_PARENTHESIS_ARGUMENT_EMPTY
    #define FCF_TEMPLATE_TYPEID_DECLARE__NAMESPACES__REMOVE_PARENTHESIS_ARGUMENT(...) FCF_TEMPLATE_TYPEID_DECLARE__NAMESPACES__REMOVE_PARENTHESIS_ARGUMENT_EMPTY
    #define FCF_TEMPLATE_TYPEID_DECLARE__NAMESPACES__REMOVE_PARENTHESIS_0(...) FCF_REMOVE_PARENTHESIS_SELECTOR##__VA_ARGS__
    #define FCF_TEMPLATE_TYPEID_DECLARE__NAMESPACES__REMOVE_PARENTHESIS(...) FCF_TEMPLATE_TYPEID_DECLARE__NAMESPACES__REMOVE_PARENTHESIS_0(__VA_ARGS__)
    #define FCF_TEMPLATE_TYPEID_DECLARE__NAMESPACES_1(a_a1, a_a2, a_a3,...)\
      FCF_TEMPLATE_TYPEID_DECLARE__NAMESPACES__REMOVE_PARENTHESIS(FCF_TEMPLATE_TYPEID_DECLARE__NAMESPACES__REMOVE_PARENTHESIS_ARGUMENT a_a1)\
      FCF_TEMPLATE_TYPEID_DECLARE__NAMESPACES__REMOVE_PARENTHESIS(FCF_TEMPLATE_TYPEID_DECLARE__NAMESPACES__REMOVE_PARENTHESIS_ARGUMENT a_a2)\
      FCF_TEMPLATE_TYPEID_DECLARE__NAMESPACES__REMOVE_PARENTHESIS(FCF_TEMPLATE_TYPEID_DECLARE__NAMESPACES__REMOVE_PARENTHESIS_ARGUMENT a_a3)
    #define FCF_TEMPLATE_TYPEID_DECLARE__NAMESPACES_0(...)\
      FCF_TEMPLATE_TYPEID_DECLARE__NAMESPACES_1(__VA_ARGS__, (), (), ())
    #define FCF_TEMPLATE_TYPEID_DECLARE__NAMESPACES(a_type) \
      FCF_TEMPLATE_TYPEID_DECLARE__NAMESPACES_0(FCF_REMOVE_PARENTHESIS( FCF_REMOVE_PARENTHESIS_ARGUMENT a_type))


    #define FCF_REMOVE_PARENTHESIS_SELECTORFCF_TEMPLATE_TYPEID_DECLARE__DECLNAMESPACES__REMOVE_PARENTHESIS_ARGUMENT { namespace 
    #define FCF_REMOVE_PARENTHESIS_SELECTORFCF_TEMPLATE_TYPEID_DECLARE__DECLNAMESPACES__REMOVE_PARENTHESIS_ARGUMENT_EMPTY
    #define FCF_TEMPLATE_TYPEID_DECLARE__DECLNAMESPACES__REMOVE_PARENTHESIS_ARGUMENT(...) FCF_TEMPLATE_TYPEID_DECLARE__DECLNAMESPACES__REMOVE_PARENTHESIS_ARGUMENT_EMPTY
    #define FCF_TEMPLATE_TYPEID_DECLARE__DECLNAMESPACES__REMOVE_PARENTHESIS_0(...) FCF_REMOVE_PARENTHESIS_SELECTOR##__VA_ARGS__
    #define FCF_TEMPLATE_TYPEID_DECLARE__DECLNAMESPACES__REMOVE_PARENTHESIS(...) FCF_TEMPLATE_TYPEID_DECLARE__DECLNAMESPACES__REMOVE_PARENTHESIS_0(__VA_ARGS__)
    #define FCF_TEMPLATE_TYPEID_DECLARE__DECLNAMESPACES_1(a_a1, a_a2, a_a3,...)\
      FCF_TEMPLATE_TYPEID_DECLARE__DECLNAMESPACES__REMOVE_PARENTHESIS(FCF_TEMPLATE_TYPEID_DECLARE__DECLNAMESPACES__REMOVE_PARENTHESIS_ARGUMENT a_a1)\
      FCF_TEMPLATE_TYPEID_DECLARE__DECLNAMESPACES__REMOVE_PARENTHESIS(FCF_TEMPLATE_TYPEID_DECLARE__DECLNAMESPACES__REMOVE_PARENTHESIS_ARGUMENT a_a2)\
      FCF_TEMPLATE_TYPEID_DECLARE__DECLNAMESPACES__REMOVE_PARENTHESIS(FCF_TEMPLATE_TYPEID_DECLARE__DECLNAMESPACES__REMOVE_PARENTHESIS_ARGUMENT a_a3)
    #define FCF_TEMPLATE_TYPEID_DECLARE__DECLNAMESPACES_0(...)\
      FCF_TEMPLATE_TYPEID_DECLARE__DECLNAMESPACES_1(__VA_ARGS__, (), (), ())
    #define FCF_TEMPLATE_TYPEID_DECLARE__DECLNAMESPACES(a_type) \
      FCF_TEMPLATE_TYPEID_DECLARE__DECLNAMESPACES_0(FCF_REMOVE_PARENTHESIS( FCF_REMOVE_PARENTHESIS_ARGUMENT a_type))

    #define FCF_TEMPLATE_TYPEID_DECLARE__DECLENDNAMESPACES__INPUT_0(a_a1, a_a2, ...) a_a2
    #define FCF_TEMPLATE_TYPEID_DECLARE__DECLENDNAMESPACES__INPUT(a_a1, a_a2, ...) FCF_TEMPLATE_TYPEID_DECLARE__DECLENDNAMESPACES__INPUT_0(a_a1, a_a2, __VA_ARGS__)
    #define FCF_REMOVE_PARENTHESIS_SELECTORFCF_TEMPLATE_TYPEID_DECLARE__DECLENDNAMESPACES__REMOVE_PARENTHESIS_ARGUMENT 
    #define FCF_REMOVE_PARENTHESIS_SELECTORFCF_TEMPLATE_TYPEID_DECLARE__DECLENDNAMESPACES__REMOVE_PARENTHESIS_ARGUMENT_EMPTY ,
    #define FCF_TEMPLATE_TYPEID_DECLARE__DECLENDNAMESPACES__REMOVE_PARENTHESIS_ARGUMENT(...) FCF_TEMPLATE_TYPEID_DECLARE__DECLENDNAMESPACES__REMOVE_PARENTHESIS_ARGUMENT_EMPTY
    #define FCF_TEMPLATE_TYPEID_DECLARE__DECLENDNAMESPACES__REMOVE_PARENTHESIS_0(...) FCF_TEMPLATE_TYPEID_DECLARE__DECLENDNAMESPACES__INPUT(FCF_REMOVE_PARENTHESIS_SELECTOR##__VA_ARGS__, })
    #define FCF_TEMPLATE_TYPEID_DECLARE__DECLENDNAMESPACES__REMOVE_PARENTHESIS(...) FCF_TEMPLATE_TYPEID_DECLARE__DECLENDNAMESPACES__REMOVE_PARENTHESIS_0(__VA_ARGS__)
    #define FCF_TEMPLATE_TYPEID_DECLARE__DECLENDNAMESPACES_1(a_a1, a_a2, a_a3,...)\
      FCF_TEMPLATE_TYPEID_DECLARE__DECLENDNAMESPACES__REMOVE_PARENTHESIS(FCF_TEMPLATE_TYPEID_DECLARE__DECLENDNAMESPACES__REMOVE_PARENTHESIS_ARGUMENT a_a1)\
      FCF_TEMPLATE_TYPEID_DECLARE__DECLENDNAMESPACES__REMOVE_PARENTHESIS(FCF_TEMPLATE_TYPEID_DECLARE__DECLENDNAMESPACES__REMOVE_PARENTHESIS_ARGUMENT a_a2)\
      FCF_TEMPLATE_TYPEID_DECLARE__DECLENDNAMESPACES__REMOVE_PARENTHESIS(FCF_TEMPLATE_TYPEID_DECLARE__DECLENDNAMESPACES__REMOVE_PARENTHESIS_ARGUMENT a_a3)
    #define FCF_TEMPLATE_TYPEID_DECLARE__DECLENDNAMESPACES_0(...)\
      FCF_TEMPLATE_TYPEID_DECLARE__DECLENDNAMESPACES_1(__VA_ARGS__, (), (), ())
    #define FCF_TEMPLATE_TYPEID_DECLARE__DECLENDNAMESPACES(a_type) \
      FCF_TEMPLATE_TYPEID_DECLARE__DECLENDNAMESPACES_0(FCF_REMOVE_PARENTHESIS( FCF_REMOVE_PARENTHESIS_ARGUMENT a_type))


    #define FCF_TEMPLATE_TYPEID_DECLARE(a_template, a_templateName, a_templateArgumentsDeclaration, a_templateArguments, a_templateArgumentsName) \
      FCF_TYPEID_REGISTRY_IMPL_DECL_CLASSES((FCF_TEMPLATE_TYPEID_DECLARE__NAMESPACES(a_template) < FCF_REMOVE_PARENTHESIS(FCF_REMOVE_PARENTHESIS_ARGUMENT a_templateArguments) >), \
                                            a_templateArgumentsDeclaration, \
                                            a_templateName + "<" + FCF_REMOVE_PARENTHESIS(FCF_REMOVE_PARENTHESIS_ARGUMENT a_templateArgumentsName) + ">", \
                                            0,\
                                            true)\
      namespace fcf {\
        namespace NDetails {\
          namespace Declarations \
            FCF_CONCAT2(FCF_TEMPLATE_TYPEID_DECLARE__DECLNAMESPACES(a_template), _specificator_declare) {\
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
            FCF_TEMPLATE_TYPEID_DECLARE__DECLENDNAMESPACES(a_template)\
          }\
        }\
      }\
      namespace fcf {\
        namespace NDetails {\
          template <typename TUnstatic, unsigned int UnstaticCounter, FCF_REMOVE_PARENTHESIS(FCF_REMOVE_PARENTHESIS_ARGUMENT a_templateArgumentsDeclaration), unsigned int Index, unsigned int Size >\
          struct SpecificatorRegistrarCallerWalker<TUnstatic, UnstaticCounter, FCF_TEMPLATE_TYPEID_DECLARE__NAMESPACES(a_template) <FCF_REMOVE_PARENTHESIS(FCF_REMOVE_PARENTHESIS_ARGUMENT a_templateArguments)>, Index, Size> {\
            SpecificatorRegistrarCallerWalker(){\
              typedef FCF_TEMPLATE_TYPEID_DECLARE__NAMESPACES(a_template) <FCF_REMOVE_PARENTHESIS(FCF_REMOVE_PARENTHESIS_ARGUMENT a_templateArguments)> type;\
              ::fcf::NDetails::Declarations FCF_CONCAT2(FCF_TEMPLATE_TYPEID_DECLARE__NAMESPACES(a_template),_specificator_declare)::PartialSpecificatorRegistrar<Index> registrar;\
              registrar.template registry<type>();\
              SpecificatorRegistrarCallerWalker<TUnstatic, UnstaticCounter, type, Index+1, Size> nextCaller;\
            }\
          };\
          template <typename TUnstatic, unsigned int UnstaticCounter, FCF_REMOVE_PARENTHESIS(FCF_REMOVE_PARENTHESIS_ARGUMENT a_templateArgumentsDeclaration), unsigned int Index>\
          struct SpecificatorRegistrarCallerWalker<TUnstatic, UnstaticCounter, FCF_TEMPLATE_TYPEID_DECLARE__NAMESPACES(a_template) <FCF_REMOVE_PARENTHESIS(FCF_REMOVE_PARENTHESIS_ARGUMENT a_templateArguments)>, Index, Index> {\
            SpecificatorRegistrarCallerWalker(){\
            }\
          };\
          template <typename TUnstatic, unsigned int UnstaticCounter,  FCF_REMOVE_PARENTHESIS(FCF_REMOVE_PARENTHESIS_ARGUMENT a_templateArgumentsDeclaration)>\
          struct SpecificatorRegistrarCaller<TUnstatic, UnstaticCounter, FCF_TEMPLATE_TYPEID_DECLARE__NAMESPACES(a_template) <FCF_REMOVE_PARENTHESIS(FCF_REMOVE_PARENTHESIS_ARGUMENT a_templateArguments)> > {\
            SpecificatorRegistrarCaller(){\
              SpecificatorRegistrarCallerWalker<TUnstatic, \
                                                UnstaticCounter, \
                                                FCF_TEMPLATE_TYPEID_DECLARE__NAMESPACES(a_template) <FCF_REMOVE_PARENTHESIS(FCF_REMOVE_PARENTHESIS_ARGUMENT a_templateArguments)>, \
                                                0, \
                                                ::fcf::NDetails::Declarations FCF_CONCAT2(FCF_TEMPLATE_TYPEID_DECLARE__NAMESPACES(a_template),_specificator_declare)::PartialSpecificatorRegistrarLast<TUnstatic, UnstaticCounter>::value\
              > registrer;\
            }\
          };\
        }\
      }
  #endif // #ifndef FCF_TEMPLATE_TYPEID_DECLARE

  #ifndef FCF_TEMPLATE_SPECIFICATOR_REGISTRY
    #define FCF_TEMPLATE_SPECIFICATOR_REGISTRY(a_template, a_specificator)\
      namespace fcf {\
        namespace NDetails {\
          namespace Declarations \
            FCF_CONCAT2(FCF_TEMPLATE_TYPEID_DECLARE__DECLNAMESPACES(a_template), _specificator_declare) {\
              template <>\
              struct PartialSpecificatorRegistrar< PartialSpecificatorRegistrarLast<void, __COUNTER__>::value > {\
                template <typename Ty>\
                void registry(){\
                  ::fcf::SpecificatorRegistrarHandler<Ty, a_specificator> registrar;\
                }\
              };\
            FCF_TEMPLATE_TYPEID_DECLARE__DECLENDNAMESPACES(a_template)\
          }\
        }\
      }
  #endif


  #ifndef FCF_TYPEID_SUBTEMPLATE1_REGISTRY
    #define FCF_TYPEID_SUBTEMPLATE1_REGISTRY(a_type, a_name) \
      FCF_TYPEID_REGISTRY_IMPL_DECL_CLASSES((a_type<T1> >), (typename T1), a_name + "<" + fcf::Type<T1>().name() + ">>", 0, false)
  #endif // #ifndef FCF_TYPEID_SUBTEMPLATE1_REGISTRY

  #ifndef FCF_TYPEID_TEMPLATE1_SUBTYPE_REGISTRY
    #define FCF_TYPEID_TEMPLATE1_SUBTYPE_REGISTRY(a_type, a_subtype, a_name, a_subname) \
      FCF_TYPEID_REGISTRY_IMPL_DECL_CLASSES((a_type<T1>::iterator), (typename T1), a_name + "<" + fcf::Type<T1>().name() + ">::" + a_subname, 0, false)
  #endif // #ifndef FCF_TYPEID_TEMPLATE1_REGISTRY

  #ifndef FCF_TYPEID_TEMPLATE2_REGISTRY
    #define FCF_TYPEID_TEMPLATE2_REGISTRY(a_type, a_name) \
      FCF_TYPEID_REGISTRY_IMPL_DECL_CLASSES((a_type<T1, T2>), (typename T1, typename T2), a_name + "<" + fcf::Type<T1>().name() + "," + fcf::Type<T1>().name() + ">", 0, false)
  #endif // #ifndef FCF_TYPEID_TEMPLATE2_REGISTRY

  #ifndef FCF_CONVERTERS_REGISTRY_FORCE
    #define FCF_CONVERTERS_REGISTRY_FORCE(a_crossGroup, a_type, a_enableToConversion, a_enableFromConversion) \
      namespace fcf { \
        namespace NDetails { \
          template <>\
          struct ConvertersRegistrarMarker<a_crossGroup, ConvertersRegistrarMarkerEnd<a_crossGroup, __COUNTER__>::value > {\
            typedef a_type type;\
            enum { fromConversion = a_enableFromConversion };\
            enum { toConversion = a_enableToConversion };\
          };\
          ConvertersRegistrarInitializer<a_crossGroup, __COUNTER__, a_type, ConvertersRegistrarMarkerEnd<a_crossGroup, __COUNTER__>::value, a_enableToConversion, a_enableFromConversion> FCF_BASIS_VARNAME(_g_converters_registrar, __COUNTER__);\
        }\
      }
  #endif



  #ifndef FCF_INITIAZE_GLOBAL_PTR
    #define FCF_INITIAZE_GLOBAL_PTR__CONCAT2(a_varName, a_funcName, a_line) a_varName##_##a_funcName##_##a_line
    #define FCF_INITIAZE_GLOBAL_PTR__CONCAT(a_varName, a_funcName, a_line) FCF_INITIAZE_GLOBAL_PTR__CONCAT2(a_varName, a_funcName, a_line)
    #define FCF_INITIAZE_GLOBAL_PTR(a_variable, a_type) \
      namespace {\
        struct FCF_INITIAZE_GLOBAL_PTR__CONCAT(FCFInitializer_, a_variable, __LINE__){\
          FCF_INITIAZE_GLOBAL_PTR__CONCAT(FCFInitializer_, a_variable, __LINE__)(){\
            if (!a_variable) {\
              a_variable = new a_type();\
            }\
          }\
        };\
        FCF_BASIS_DELC_EXTERN FCF_BASIS_DECL_EXPORT FCF_INITIAZE_GLOBAL_PTR__CONCAT(FCFInitializer_, a_variable, __LINE__) \
          FCF_INITIAZE_GLOBAL_PTR__CONCAT(_fcfinitializer_, a_variable, __LINE__);\
      }
  #endif // #ifndef FCF_INITIAZE_GLOBAL_PTR

  #ifndef FCF_DECLARE_FUNCTION

    #define _FCF_DECLARE_FUNCTION__SELECTOR_NOP_FCF_DECLARE_FUNCTION__REM_PARENTHESIS_NOP__EMPTY_SELECTOR ::fcf::Nop
    #define _FCF_DECLARE_FUNCTION__SELECTOR_NOP_ON_FCF_DECLARE_FUNCTION__REM_PARENTHESIS_NOP__EMPTY_SELECTOR
    #define _FCF_DECLARE_FUNCTION__REM_PARENTHESIS_NOP__EMPTY_SELECTOR(...) _ON_FCF_DECLARE_FUNCTION__REM_PARENTHESIS_NOP__EMPTY_SELECTOR __VA_ARGS__
    #define _FCF_DECLARE_FUNCTION__REM_PARENTHESIS_NOP_0(...) _FCF_DECLARE_FUNCTION__SELECTOR_NOP##__VA_ARGS__
    #define _FCF_DECLARE_FUNCTION__REM_PARENTHESIS_NOP(...) _FCF_DECLARE_FUNCTION__REM_PARENTHESIS_NOP_0(__VA_ARGS__)

    #define _FCF_DECLARE_FUNCTION__SELECTOR_FCF_DECLARE_FUNCTION__REM_PARENTHESIS__EMPTY_SELECTOR
    #define _FCF_DECLARE_FUNCTION__REM_PARENTHESIS__EMPTY_SELECTOR(...) _FCF_DECLARE_FUNCTION__REM_PARENTHESIS__EMPTY_SELECTOR __VA_ARGS__
    #define _FCF_DECLARE_FUNCTION__REM_PARENTHESIS_0(...) _FCF_DECLARE_FUNCTION__SELECTOR##__VA_ARGS__
    #define _FCF_DECLARE_FUNCTION__REM_PARENTHESIS(...) _FCF_DECLARE_FUNCTION__REM_PARENTHESIS_0(__VA_ARGS__)

    #define _FCF_DECLARE_FUNCTION__SIGNATURE(a_signature, a_arg) \
      typename ::fcf::NDetails::CallPlaceHolderSignatureGetter<a_signature, \
                                                ::fcf::NDetails::CallResultTypeGetter<a_signature>::type, \
                                                _FCF_DECLARE_FUNCTION__REM_PARENTHESIS_NOP(_FCF_DECLARE_FUNCTION__REM_PARENTHESIS_NOP__EMPTY_SELECTOR a_arg)\
                                                >::active_type

    #define _FCF_DECLARE_FUNCTION__RESOLVE_SIGNATURES_1(a_signature, a_arg1, a_arg2, a_arg3, ...) \
      _FCF_DECLARE_FUNCTION__SIGNATURE(a_signature, a_arg1),\
      _FCF_DECLARE_FUNCTION__SIGNATURE(a_signature, a_arg2),\
      _FCF_DECLARE_FUNCTION__SIGNATURE(a_signature, a_arg3)
    #define _FCF_DECLARE_FUNCTION__RESOLVE_SIGNATURES_0(a_signature, ...)\
              _FCF_DECLARE_FUNCTION__RESOLVE_SIGNATURES_1(a_signature, __VA_ARGS__, , , )

    #define _FCF_DECLARE_FUNCTION__RESOLVE_SIGNATURES(a_signature, a_placeHolder) \
      _FCF_DECLARE_FUNCTION__RESOLVE_SIGNATURES_0(a_signature, _FCF_DECLARE_FUNCTION__REM_PARENTHESIS(_FCF_DECLARE_FUNCTION__REM_PARENTHESIS__EMPTY_SELECTOR a_placeHolder) )

    #define _FCF_DECLARE_FUNCTION__VARNAME_RESOLVE_0(a_varName, a_line, a_arg1, a_arg2, a_arg3, a_arg4, a_arg5, ...)\
                                  a_varName##_##a_arg1##_##a_arg2##_##a_arg3##_##a_arg4##_##a_arg5##_##a_line
    #define _FCF_DECLARE_FUNCTION__VARNAME_RESOLVE(a_varName, a_line, a_arg1, a_arg2, a_arg3, a_arg4, a_arg5, ...)\
                                  _FCF_DECLARE_FUNCTION__VARNAME_RESOLVE_0(a_varName, a_line, a_arg1, a_arg2, a_arg3, a_arg4, a_arg5)

    #define _FCF_DECLARE_FUNCTION__NAME_RESOLVE_1(a_arg1, a_arg2, a_arg3, a_arg4, a_arg5, ...)\
                                  a_arg1 "::" a_arg2 "::" a_arg3 "::" a_arg4 "::" a_arg5
    #define _FCF_DECLARE_FUNCTION__NAME_RESOLVE_0(a_arg1, a_arg2, a_arg3, a_arg4, a_arg5, ...)\
                                  _FCF_DECLARE_FUNCTION__NAME_RESOLVE_1(#a_arg1, #a_arg2, #a_arg3, #a_arg4, #a_arg5)
    #define _FCF_DECLARE_FUNCTION__NAME_RESOLVE(a_arg1, a_arg2, a_arg3, a_arg4, a_arg5, ...)\
                                  _FCF_DECLARE_FUNCTION__NAME_RESOLVE_0(a_arg1, a_arg2, a_arg3, a_arg4, a_arg5)

    #define FCF_DECLARE_FUNCTION(a_name, a_space, a_sourceName, a_signature, a_placeHolder, a_sourceCode) \
      a_sourceCode; \
      ::fcf::CallStorageRegistrator \
        _FCF_DECLARE_FUNCTION__VARNAME_RESOLVE(functionRegistrator, __COUNTER__, FCF_REMOVE_PARENTHESIS(FCF_REMOVE_PARENTHESIS_ARGUMENT a_name),,,,,,,,) \
          (\
            _FCF_DECLARE_FUNCTION__NAME_RESOLVE( FCF_REMOVE_PARENTHESIS(FCF_REMOVE_PARENTHESIS_ARGUMENT a_name),,,,,,,,), \
            a_space, \
            #a_sourceName, \
            static_cast<a_signature>(a_sourceName),\
            ::fcf::NDetails::CallPlaceHolderSignatures <\
              _FCF_DECLARE_FUNCTION__RESOLVE_SIGNATURES(a_signature, a_placeHolder )\
            > (),\
            #a_sourceCode\
          );
  #endif // #ifndef FCF_DECLARE_FUNCTION


  #ifndef FCF_EXTEND_FUNCTION
    #define _FCF_EXTEND_FUNCTION__VARNAME_0(a_varName, a_funcName, a_line) a_varName##_##a_funcName##_##a_line
    #define _FCF_EXTEND_FUNCTION__VARNAME(a_varName, a_funcName, a_line) _FCF_EXTEND_FUNCTION__VARNAME_0(a_varName, a_funcName, a_line)
    #define FCF_EXTEND_FUNCTION(a_name, a_space, a_sourceName, a_signature, a_sourceCode) \
      ::fcf::CallStorageRegistrator \
        _FCF_EXTEND_FUNCTION__VARNAME(functionRegistrator, a_name, __LINE__) \
          (\
            #a_name, \
            a_space, \
            #a_sourceName, \
            static_cast<a_signature>((a_signature)(void*)0),\
            ::fcf::ArgPlaceHolder::CallPlaceHolderSignatureGetter<::fcf::Nop>(),\
            #a_sourceCode\
          );
  #endif // #ifndef FCF_EXTEND_FUNCTION

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

