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

  #ifndef FCF_BASIS_VARNAME
    #define FCF_BASIS_VARNAME__IMPL2(a_varName, a_suffix, a_counter) a_varName##a_suffix##a_counter
    #define FCF_BASIS_VARNAME__IMPL1(a_varName, a_suffix, a_counter) FCF_BASIS_VARNAME__IMPL2(a_varName, a_suffix, a_counter)
    #define FCF_BASIS_VARNAME(a_varName, a_suffix) FCF_BASIS_VARNAME__IMPL1(a_varName, a_suffix, __COUNTER__)
  #endif // #ifndef FCF_BASIS_VARNAME

  #ifndef FCF_BASIS_CONCAT3
    #define FCF_BASIS_CONCAT3_IMPL1(a_varName, a_suffix, a_counter) a_varName##a_suffix##a_counter
    #define FCF_BASIS_CONCAT3(a_varName, a_suffix, a_counter) FCF_BASIS_CONCAT3_IMPL1(a_varName, a_suffix, a_counter)
  #endif // #ifndef FCF_BASIS_CONCAT3


  #ifndef FCF_SPECIFICATOR_REGISTRY
    #define FCF_SPECIFICATOR_REGISTRY__L2(a_itemName, a_counter) a_itemName##_##a_counter
    #define FCF_SPECIFICATOR_REGISTRY__L1(a_itemName, a_counter) FCF_SPECIFICATOR_REGISTRY__L2(a_itemName, a_counter)
    #ifdef FCF_BASIS_IMPLEMENTATION
      #define FCF_SPECIFICATOR_REGISTRY(a_type, a_specificator) \
        namespace { \
          ::fcf::SpecificatorTypeRegistrator<a_type, a_specificator> FCF_SPECIFICATOR_REGISTRY__L1(specificatorReg, __COUNTER__);\
        }
    #else
      #define FCF_SPECIFICATOR_REGISTRY(a_type, a_specificator)
    #endif // #ifdef FCF_BASIS_IMPLEMENTATION
  #endif // #ifndef FCF_SPECIFICATOR_REGISTRY

  #ifndef FCF_BASIS_EXPAND
    #define FCF_BASIS_EXPAND(...) __VA_ARGS__
  #endif // #ifndef FCF_BASIS_EXPAND

  #ifndef FCF_TYPEID_REGISTRY_IMPL_DECL_CLASS
    #define FCF_TYPEID_REGISTRY_IMPL_DECL_CLASS(a_type, a_templateArgs, a_name, a_index, a_basic_type) \
      template < FCF_BASIS_EXPAND a_templateArgs>\
      struct fcf::TypeId< FCF_BASIS_EXPAND a_type > {\
        typedef FCF_BASIS_EXPAND a_basic_type basic_type;\
        bool          autoIndex() { return ((a_index) & 0x00ffffff)== 0; }\
        unsigned int  index()     { return a_index; }\
        std::string   name()      { return std::string() + a_name; }\
      };
  #endif // #ifndef FCF_TYPEID_REGISTRY_IMPL_DECL_CLASS

  #ifndef FCF_TYPEID_REGISTRY_IMPL_DECL_CLASSES
    #define FCF_TYPEID_REGISTRY_IMPL_DECL_CLASSES(a_type, a_templateArgs, a_name, a_index)\
      FCF_TYPEID_REGISTRY_IMPL_DECL_CLASS((FCF_BASIS_EXPAND a_type), (FCF_BASIS_EXPAND a_templateArgs),    a_name, a_index, a_type) \
      FCF_TYPEID_REGISTRY_IMPL_DECL_CLASS((FCF_BASIS_EXPAND a_type &), (FCF_BASIS_EXPAND a_templateArgs),  a_name + "&", a_index | (1 << (24 + 1) ), a_type) \
      FCF_TYPEID_REGISTRY_IMPL_DECL_CLASS((FCF_BASIS_EXPAND a_type &&), (FCF_BASIS_EXPAND a_templateArgs), a_name + "&&", a_index | (2 << (24 + 1) ), a_type) \
      FCF_TYPEID_REGISTRY_IMPL_DECL_CLASS((FCF_BASIS_EXPAND a_type *), (FCF_BASIS_EXPAND a_templateArgs),  a_name + "*", a_index | (8 << (24 + 1) ), a_type) \
      FCF_TYPEID_REGISTRY_IMPL_DECL_CLASS((FCF_BASIS_EXPAND a_type **), (FCF_BASIS_EXPAND a_templateArgs), a_name + "**", a_index | (16 << (24 + 1) ), a_type) \
      FCF_TYPEID_REGISTRY_IMPL_DECL_CLASS((const FCF_BASIS_EXPAND a_type &), (FCF_BASIS_EXPAND a_templateArgs),  "const " + a_name + "&", a_index | ((1 | 4) << (24 + 1) ), a_type) \
      FCF_TYPEID_REGISTRY_IMPL_DECL_CLASS((const FCF_BASIS_EXPAND a_type &&), (FCF_BASIS_EXPAND a_templateArgs), "const " + a_name + "&&", a_index | ((2 | 4) << (24 + 1)), a_type)\
      FCF_TYPEID_REGISTRY_IMPL_DECL_CLASS((const FCF_BASIS_EXPAND a_type *), (FCF_BASIS_EXPAND a_templateArgs),  "const " + a_name + "*", a_index | ((8 | 4) << (24 + 1)), a_type) \
      FCF_TYPEID_REGISTRY_IMPL_DECL_CLASS((const FCF_BASIS_EXPAND a_type **), (FCF_BASIS_EXPAND a_templateArgs), "const " + a_name + "**", a_index | (16 << (24 + 1) ) | (4 << (24 + 1)), a_type)\
      FCF_TYPEID_REGISTRY_IMPL_DECL_CLASS((const FCF_BASIS_EXPAND a_type *&), (FCF_BASIS_EXPAND a_templateArgs), "const " + a_name + "*&", a_index | ((1 | 4 | 8) << (24 + 1)), a_type)\
      FCF_TYPEID_REGISTRY_IMPL_DECL_CLASS((const FCF_BASIS_EXPAND a_type **&), (FCF_BASIS_EXPAND a_templateArgs), "const " + a_name + "**&", a_index | ((1 | 4 | 16) << (24 + 1)), a_type)
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

  #ifndef FCF_TYPEID_REGISTRY
    #ifdef FCF_BASIS_IMPLEMENTATION
      #define FCF_TYPEID_REGISTRY(a_type, a_name, a_index) \
        FCF_TYPEID_REGISTRY_IMPL_DECL_CLASSES((a_type), (), a_name, a_index)\
        FCF_TYPEID_REGISTRY_IMPL_DECL_INITVAR(a_type, a_name, a_index)
    #else
      #define FCF_TYPEID_REGISTRY(a_type, a_name, a_index) \
        FCF_TYPEID_REGISTRY_IMPL_DECL_CLASSES((a_type), (), a_name, a_index)
    #endif
  #endif // #ifndef FCF_TYPEID_REGISTRY

  #ifndef FCF_TYPEID_REGISTRY_SINGLE
    #ifdef FCF_BASIS_IMPLEMENTATION
      #define FCF_TYPEID_REGISTRY_SINGLE(a_type, a_name, a_index) \
        FCF_TYPEID_REGISTRY_IMPL_DECL_CLASS((a_type), (), a_name, a_index, (a_type))\
        fcf::TypeInitializer<a_type> FCF_BASIS_VARNAME(typeInfoRegistry, _);
    #else
      #define FCF_TYPEID_REGISTRY_SINGLE(a_type, a_name, a_index) \
        FCF_TYPEID_REGISTRY_IMPL_DECL_CLASS((a_type), (), a_name, a_index, (a_type))
    #endif
  #endif // #ifndef FCF_TYPEID_REGISTRY_SINGLE

  #ifndef FCF_TYPEID_TEMPLATE1_REGISTRY
    #define FCF_TYPEID_TEMPLATE1_REGISTRY(a_type, a_name) \
      FCF_TYPEID_REGISTRY_IMPL_DECL_CLASSES((a_type<T1>), (typename T1), a_name + "<" + fcf::Type<T1>().name() + ">", 0)
  #endif // #ifndef FCF_TYPEID_TEMPLATE1_REGISTRY

  #ifndef FCF_TYPEID_SUBTEMPLATE1_REGISTRY
    #define FCF_TYPEID_SUBTEMPLATE1_REGISTRY(a_type, a_name) \
      FCF_TYPEID_REGISTRY_IMPL_DECL_CLASSES((a_type<T1> >), (typename T1), a_name + "<" + fcf::Type<T1>().name() + ">>", 0)
  #endif // #ifndef FCF_TYPEID_SUBTEMPLATE1_REGISTRY

  #ifndef FCF_TYPEID_TEMPLATE1_SUBTYPE_REGISTRY
    #define FCF_TYPEID_TEMPLATE1_SUBTYPE_REGISTRY(a_type, a_subtype, a_name, a_subname) \
      FCF_TYPEID_REGISTRY_IMPL_DECL_CLASSES((a_type<T1>::iterator), (typename T1), a_name + "<" + fcf::Type<T1>().name() + ">::" + a_subname, 0)
  #endif // #ifndef FCF_TYPEID_TEMPLATE1_REGISTRY

  #ifndef FCF_TYPEID_TEMPLATE2_REGISTRY
    #define FCF_TYPEID_TEMPLATE2_REGISTRY(a_type, a_name) \
      FCF_TYPEID_REGISTRY_IMPL_DECL_CLASSES((a_type<T1, T2>), (typename T1, typename T2), a_name + "<" + fcf::Type<T1>().name() + "," + fcf::Type<T1>().name() + ">", 0)
  #endif // #ifndef FCF_TYPEID_TEMPLATE2_REGISTRY

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
    #define FCF_DECLARE_FUNCTION__VARNAME2(a_varName, a_funcName, a_line) a_varName##_##a_funcName##_##a_line
    #define FCF_DECLARE_FUNCTION__VARNAME(a_varName, a_funcName, a_line) FCF_DECLARE_FUNCTION__VARNAME2(a_varName, a_funcName, a_line)
    #define FCF_DECLARE_FUNCTION(a_name, a_space, a_sourceName, a_signature, a_placeHolder, a_sourceCode) \
      a_sourceCode; \
      ::fcf::IndexableFunctionRegistrator \
        FCF_DECLARE_FUNCTION__VARNAME(functionRegistrator, a_name, __COUNTER__) \
          ( \
            #a_name, \
            a_space, \
            #a_sourceName, \
            static_cast<a_signature>(a_sourceName),\
            ::fcf::ArgPlaceHolder::Signature< a_signature, \
                                              ::fcf::Details::Basis::FunctionResultType<a_signature>::type  a_placeHolder \
                                            >(),\
            #a_sourceCode\
          );
  #endif // #ifndef FCF_DECLARE_FUNCTION

  #ifndef FCF_EXTEND_FUNCTION
    #define FCF_EXTEND_FUNCTION__VARNAME2(a_varName, a_funcName, a_line) a_varName##_##a_funcName##_##a_line
    #define FCF_EXTEND_FUNCTION__VARNAME(a_varName, a_funcName, a_line) FCF_EXTEND_FUNCTION__VARNAME2(a_varName, a_funcName, a_line)
    #define FCF_EXTEND_FUNCTION(a_name, a_space, a_sourceName, a_signature, a_sourceCode) \
      ::fcf::IndexableFunctionRegistrator \
        FCF_EXTEND_FUNCTION__VARNAME(functionRegistrator, a_name, __LINE__) \
          ( \
            #a_name, \
            a_space, \
            #a_sourceName, \
            static_cast<a_signature>((a_signature)(void*)0),\
            ::fcf::ArgPlaceHolder::Signature<::fcf::Nop, ::fcf::Nop, ::fcf::Nop >(),\
            #a_sourceCode\
          );
  #endif // #ifndef FCF_EXTEND_FUNCTION

  #ifndef FCF_GET_FUNCTION_INDEX
    #define FCF_GET_FUNCTION_INDEX(a_name, a_signature) \
      ::fcf::IndexableFunctionRegistrator::getIndex<a_signature>(a_name)
  #endif // #ifndef FCF_GET_FUNCTION_INDEX

  #ifndef FCF_GET_FUNCTION
    #define FCF_GET_FUNCTION(a_index) \
      ::fcf::Details::IndexableFunction::getStorage().functions[a_index].function
  #endif // #ifndef FCF_GET_FUNCTION

#endif // #ifndef ___FCF_BASIS__MACRO_HPP___

