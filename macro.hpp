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
  #endif

  #ifndef FCF_TYPEID_REGISTRY
    #define FCF_TYPEID_REGISTRY__VARNAME2(a_varName, a_funcName, a_line) a_varName##_##a_funcName##_##a_line
    #define FCF_TYPEID_REGISTRY__VARNAME(a_varName, a_funcName, a_line) FCF_TYPEID_REGISTRY__VARNAME2(a_varName, a_funcName, a_line)
    #ifdef FCF_BASIS_IMPLEMENTATION
      #define FCF_TYPEID_REGISTRY(a_type, a_name, a_index) \
        template <>\
        struct fcf::TypeIdSource<a_type> {\
          unsigned int index() { return a_index; }\
          std::string name()   { return a_name; }\
        };\
        namespace { \
          fcf::TypeInitializer<a_type> \
            FCF_TYPEID_REGISTRY__VARNAME(typeInfoRegistry, type , __LINE__);\
        }
    #else
      #define FCF_TYPEID_REGISTRY(a_type, a_name, a_index) \
        template <>\
        struct fcf::TypeIdSource<a_type> {\
          unsigned int index() { return a_index; }\
          std::string name()   { return a_name; }\
        };
    #endif // #ifdef FCF_BASIS_IMPLEMENTATION
  #endif // #ifndef FCF_TYPEID_REGISTRY

  #ifndef FCF_TYPEID_TEMPLATE1_REGISTRY
    #define FCF_TYPEID_TEMPLATE1_REGISTRY(a_type, a_name) \
      template <typename T1>\
      struct fcf::TypeIdSource< a_type<T1> > {\
        unsigned int index() { return 0; }\
        std::string name()   { return std::string() + a_name; }\
      };
  #endif // #ifndef FCF_TYPEID_TEMPLATE1_REGISTRY

  #ifndef FCF_TYPEID_TEMPLATE2_REGISTRY
    #define FCF_TYPEID_TEMPLATE2_REGISTRY(a_type, a_name) \
      template <typename T1, typename T2>\
      struct fcf::TypeIdSource< a_type<T1, T2> > {\
        unsigned int index() { return 0; }\
        std::string name()   { return std::string() + a_name; }\
      };
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
        FCF_MATH_DELC_EXTERN FCF_MATH_DECL_EXPORT FCF_INITIAZE_GLOBAL_PTR__CONCAT(FCFInitializer_, a_variable, __LINE__) \
          FCF_INITIAZE_GLOBAL_PTR__CONCAT(_fcfinitializer_, a_variable, __LINE__);\
      }
  #endif // #ifndef FCF_INITIAZE_GLOBAL_PTR

  #ifndef FCF_DECLARE_FUNCTION
    #define FCF_DECLARE_FUNCTION__VARNAME2(a_varName, a_funcName, a_line) a_varName##_##a_funcName##_##a_line
    #define FCF_DECLARE_FUNCTION__VARNAME(a_varName, a_funcName, a_line) FCF_DECLARE_FUNCTION__VARNAME2(a_varName, a_funcName, a_line)
    #define FCF_DECLARE_FUNCTION(a_name, a_space, a_sourceName, a_signature, a_sourceCode) \
      a_sourceCode; \
      ::fcf::IndexableFunctionRegistrator \
        FCF_DECLARE_FUNCTION__VARNAME(functionRegistrator, a_name, __LINE__) \
          ( \
            #a_name, \
            a_space, \
            #a_sourceName, \
            static_cast<a_signature>(a_sourceName),\
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
            #a_sourceCode\
          );
  #endif // #ifndef FCF_EXTEND_FUNCTION

#endif // #ifndef ___FCF_BASIS__MACRO_HPP___

