#include <fcfTest/test.hpp>
#include "../../basis.hpp"
#include <vector>
#include <iostream>
namespace FcfTest {
  namespace BasisTest {

    void sequenceTest();

    void staticVectorTest();
    void staticVectorCopyTest();
    void staticVectorExceptionTest();
    void staticVectorIteratorTest();
    void staticVectorPushTest();
    void staticVectorNotReduce();
    void staticVectorInsertTest();
    void staticVectorEraseTest();

    void declareCall();
    void placeHolderCall();

  } // BasisTest namespace
} // FcfTest namespace

void deepIndexCallInner();
void deepIndexCall();
void variantTest();
void indexTypesTest();
void deepIndexCallCaller();
void deepIndexSimpleCaller();
void deepIndexNearestCaller();
void iteratorTest();
void dynamicIteratorTest();
void deepIndexContainerCaller();
void tupleTest();

/*
 * 
Start test
End test
(int*, int*, int, int)     [Find, Call] : 81nsec
(int*, int*, int, variant) [Find, Call] : 176nsec
(int*, int*, int, variant) [Call]       : 25nsec
Start deepIndexNearestCaller...
Start variantTest...
 * 
 * 
 * */







/*
namespace fcf {
namespace Details {

  template <typename Ty, unsigned int Index>
  struct DeclCounter;

  template <typename Ty, typename TSpec, int Index, typename = void> struct DeclCounterExists : std::false_type {};
  template <typename Ty, typename TSpec, int Index> struct DeclCounterExists<Ty, TSpec, Index, decltype(void(sizeof(DeclCounter<Ty, Index>)))> : std::true_type {};


  template <typename Ty, typename TSpec, int Index, bool Exisis = true>
  struct DeclCounterLast {
    enum { value = DeclCounterLast<Ty, TSpec, Index+1, DeclCounterExists<Ty, TSpec, Index+1>::value >::value };
  };

  template <typename Ty, typename TSpec, int Index>
  struct DeclCounterLast<Ty, TSpec, Index, false> {
    enum { value = Index };
  };


  template <typename Ty = fcf::Nop>
  struct PrintList{
    void operator()(){
      int i = fcf::Details::DeclCounterLast<int, PrintList, -1>::value;
      std::cout << "E" << i << std::endl;
    }
  };
  
  template <>
  struct DeclCounter<int, fcf::Details::DeclCounterLast<int, int, -1>::value > {
    enum { value = fcf::Details::DeclCounterLast<int, int, -1>::value };
  };

  template <>
  struct DeclCounter<int, fcf::Details::DeclCounterLast<int, short, -1>::value > {
    enum { value = fcf::Details::DeclCounterLast<int, int, -1>::value };
  };

};
};
*/


/*

template <typename Ty>
struct TestStruct {
  TestStruct(){
    std::cout << "1" << std::endl;
  }
};

template <template <typename...> typename Templ, typename ... TArg>
struct TestStruct<Templ<TArg...> > {
  TestStruct(){
    std::cout << "2:"  << std::endl;
  }
};


namespace fcf::test1 {
  
}
*/

namespace fcf::Declarations::std::vector_specificator_declare {

  template <typename TCall, unsigned int Index>
  struct SpecificatorDeclCounter;

  template <typename TCall, unsigned int UniqueCounter, int Index, typename = void> 
  struct SpecificatorDeclCounterExists { 
    enum { value = false };
  };

  template <typename TCall, unsigned int UniqueCounter, int Index> 
  struct SpecificatorDeclCounterExists<TCall, UniqueCounter, Index, decltype(void(sizeof(SpecificatorDeclCounter<TCall, Index>)))> {
    enum { value = true };
  };

  template <typename TCall, unsigned int UniqueCounter, int Index = -1, bool Exisis = true>
  struct SpecificatorDeclCounterLast {
    enum { value = SpecificatorDeclCounterLast<TCall, UniqueCounter, Index+1, SpecificatorDeclCounterExists<TCall, UniqueCounter, Index+1>::value >::value };
  };

  template <typename TCall, unsigned int UniqueCounter, int Index>
  struct SpecificatorDeclCounterLast<TCall, UniqueCounter, Index, false> {
    enum { value = Index };
  };

  template <unsigned int Index>
  struct TemplateDeclCounter;

  template <unsigned int UniqueCounter, int Index, typename = void> 
  struct TemplateDeclCounterExists { 
    enum { value = false };
  };

  template <unsigned int UniqueCounter, int Index> 
  struct TemplateDeclCounterExists<UniqueCounter, Index, decltype(void(sizeof(TemplateDeclCounter<Index>)))> {
    enum { value = true };
  };

  template <unsigned int UniqueCounter, int Index = -1, bool Exisis = true>
  struct TemplateDeclCounterLast {
    enum { value = TemplateDeclCounterLast<UniqueCounter, Index+1, TemplateDeclCounterExists<UniqueCounter, Index+1>::value >::value };
  };

  template <unsigned int UniqueCounter, int Index>
  struct TemplateDeclCounterLast<UniqueCounter, Index, false> {
    enum { value = Index };
  };
}
// FCF_REMOVE_PARENTHESIS(FCF_REMOVE_PARENTHESIS_ARGUMENT a_placeHolder)


namespace fcf {
  template <typename TTT, typename Ty>
  struct TestTypeInfo;
}

#define FCF_TEMPLATE_TYPEID_DECLARE_001(a_template, a_templateName, a_templateArgumentsDeclaration, a_templateArguments, a_typeName) \
  namespace fcf::Declarations::a_template##_specificator_declare { \
    template <typename Ty, unsigned int Index, unsigned int Size> \
    struct TemplateSpecificatorAttachmentWalker{\
      TemplateSpecificatorAttachmentWalker(){\
        SpecificatorDeclCounter<Ty, Index>().template registration<Ty>();\
        TemplateSpecificatorAttachmentWalker<Ty, Index+1, Size>();\
      }\
    };\
    \
    template <typename Ty, unsigned int Index>\
    struct TemplateSpecificatorAttachmentWalker<Ty, Index, Index>{\
      TemplateSpecificatorAttachmentWalker(){}\
    };\
    \
    template <typename TSpecificator, unsigned int Index, unsigned int Size> \
    struct TemplateAttachmentWalker{\
      TemplateAttachmentWalker(){\
        TemplateDeclCounter<Index>().template registration<TSpecificator>();\
        TemplateAttachmentWalker<TSpecificator, Index+1, Size>();\
      }\
    };\
    \
    template <typename TSpecificator, unsigned int Index>\
    struct TemplateAttachmentWalker<TSpecificator, Index, Index>{\
      TemplateAttachmentWalker(){}\
    };\
    template <typename TCall, typename TSpecificator>\
    struct TemplateAttachment;\
  }\
  namespace fcf {\
    template <typename TTT, FCF_REMOVE_PARENTHESIS(FCF_REMOVE_PARENTHESIS_ARGUMENT a_templateArgumentsDeclaration) >\
    struct TestTypeInfo<TTT, a_template<FCF_REMOVE_PARENTHESIS(FCF_REMOVE_PARENTHESIS_ARGUMENT a_templateArguments)> > {\
      typedef a_template<FCF_REMOVE_PARENTHESIS(FCF_REMOVE_PARENTHESIS_ARGUMENT a_templateArguments)> type;\
      TestTypeInfo(){\
          ::fcf::Declarations::a_template##_specificator_declare::TemplateSpecificatorAttachmentWalker<\
            type, \
            0, \
            ::fcf::Declarations::a_template##_specificator_declare::SpecificatorDeclCounterLast<TTT, __COUNTER__>::value \
          > walker;\
      }\
      template <typename TCall>\
      void init(){\
          std::cout << ::fcf::Declarations::a_template##_specificator_declare::SpecificatorDeclCounterLast<TTT, __COUNTER__>::value << std::endl;\
          ::fcf::Declarations::a_template##_specificator_declare::TemplateSpecificatorAttachmentWalker<\
            type, \
            0, \
            ::fcf::Declarations::a_template##_specificator_declare::SpecificatorDeclCounterLast<TCall, __COUNTER__>::value \
          > walker;\
      }\
    };\
  }\

#define FCF_ASSOCIATION_TEMPLATE_SPECIFICATOR_DECLARE(a_template, a_specificator) \
  namespace fcf::Declarations::a_template##_specificator_declare { \
    template <typename TCall>\
    struct SpecificatorDeclCounter<TCall, SpecificatorDeclCounterLast<TCall, __COUNTER__>::value > {\
      template <typename Ty>\
      void registration() {\
        ::std::cout << "SpecificatorDeclCounter::registration" << ::std::endl;\
        ::fcf::SpecificatorRegistrar<Ty, a_specificator> registrar;\
      }\
    };\
    template <typename TCall>\
    struct TemplateAttachment<TCall, ::a_specificator> {\
      TemplateAttachment(){\
        ::fcf::Declarations::a_template##_specificator_declare::TemplateAttachmentWalker<\
          ::a_specificator, \
          0, \
          ::fcf::Declarations::a_template##_specificator_declare::TemplateDeclCounterLast<__COUNTER__>::value \
        > walker;\
      }\
    };\
  }\

#define _FCF_ASSOCIATION_TEMPLATE_SPECIFICATOR_REGISTRY_ONLY__ATTACH_COUNTER_001(x, y) x##y
#define _FCF_ASSOCIATION_TEMPLATE_SPECIFICATOR_REGISTRY_ONLY__ATTACH_COUNTER(x, y) _FCF_ASSOCIATION_TEMPLATE_SPECIFICATOR_REGISTRY_ONLY__ATTACH_COUNTER_001(x,y)
#define FCF_ASSOCIATION_TEMPLATE_SPECIFICATOR_REGISTRY_ONLY(a_template, a_specificator) \
  namespace fcf::Declarations::a_template##_specificator_declare { \
    TemplateAttachment<::a_specificator, ::a_specificator> _FCF_ASSOCIATION_TEMPLATE_SPECIFICATOR_REGISTRY_ONLY__ATTACH_COUNTER(templateAttachment_, __COUNTER__);\
  }\

#define FCF_ASSOCIATION_TEMPLATE_SPECIFICATOR_REGISTRY_FORCE(a_template, a_specificator) \
  FCF_ASSOCIATION_TEMPLATE_SPECIFICATOR_DECLARE(a_template, a_specificator)\
  FCF_ASSOCIATION_TEMPLATE_SPECIFICATOR_REGISTRY_ONLY(a_template, a_specificator);

#ifdef FCF_BASIS_IMPLEMENTATION
  #define FCF_ASSOCIATION_TEMPLATE_SPECIFICATOR_REGISTRY(a_template, a_specificator) \
    FCF_ASSOCIATION_TEMPLATE_SPECIFICATOR_REGISTRY_FORCE(a_template, a_specificator)
#else  // #ifdef FCF_BASIS_IMPLEMENTATION
  #define FCF_ASSOCIATION_TEMPLATE_SPECIFICATOR_REGISTRY(a_template, a_specificator) \
    FCF_ASSOCIATION_TEMPLATE_SPECIFICATOR_DECLARE(a_template, a_specificator)
#endif // #ifdef FCF_BASIS_IMPLEMENTATION




namespace fcf::Declarations {
  template <typename Ty>
  struct TemplateSpecificatorAttachment;
} // fcf namespace

#define _FCF_TEMPLATE_TYPEID_REGISTRY__ATTCH_COUNTER_001(x, y) x##y
#define _FCF_TEMPLATE_TYPEID_REGISTRY__ATTCH_COUNTER(x,y) _FCF_TEMPLATE_TYPEID_REGISTRY__ATTCH_COUNTER_001(x, y)
#define FCF_TEMPLATE_TYPEID_REGISTRY(a_template, a_type, a_typeName, a_typeIndex) \
    namespace fcf::Declarations {\
      template <>\
      struct TemplateSpecificatorAttachment<::a_type> {\
        TemplateSpecificatorAttachment(){\
          ::fcf::Declarations::a_template##_specificator_declare::TemplateSpecificatorAttachmentWalker<\
            ::a_type, \
            0, \
            ::fcf::Declarations::a_template##_specificator_declare::SpecificatorDeclCounterLast<::a_type, __COUNTER__>::value \
          > walker;\
        }\
      };\
    }\
    namespace fcf::Declarations {\
      TemplateSpecificatorAttachment<::a_type> _FCF_TEMPLATE_TYPEID_REGISTRY__ATTCH_COUNTER(templateSpecificatorAttachment_, __COUNTER__);\
    }\
    namespace fcf::Declarations::a_template##_specificator_declare { \
      template <>\
      struct TemplateDeclCounter< TemplateDeclCounterLast<__COUNTER__>::value > {\
        template <typename TSpecificator>\
        void registration() {\
          ::std::cout << "TemplateDeclCounter::registration" << ::std::endl;\
          ::fcf::SpecificatorRegistrar<::a_type, TSpecificator> registrar;\
        }\
      };\
    }\

template <typename Ty>
struct T1;


template <typename Ty>
struct T2{
  T2(){
    T1<Ty>();
  }
};

template <>
struct T1<int>{
};


FCF_TEMPLATE_TYPEID_DECLARE_001(std::vector, "std::vector", (typename Ty), (Ty), (Type<Ty>().name()));

//FCF_TEMPLATE_TYPEID_REGISTRY(std::vector, std::vector<int>, "std::vector<int>", 0);
//FCF_TEMPLATE_TYPEID_REGISTRY(std::vector, std::vector<short>, "std::vector<short>", 0);
FCF_ASSOCIATION_TEMPLATE_SPECIFICATOR_REGISTRY_FORCE(std::vector, fcf::DynamicIteratorSpecificator);
  
  
int main(int a_argc, char* a_argv[]){
 
  
 // fcf::TestTypeInfo<int, std::vector<int> >().init<int>();
  //return 0;
  //TestResolve< std::vector<int> > t2;
//  fcf::Details::PrintList<>()();
//  std::cout << "L!" << fcf::Details::DeclCounterLast<int, float, -1>::value << std::endl;
  FcfTest::BasisTest::sequenceTest();
  
  FcfTest::BasisTest::staticVectorTest();
  FcfTest::BasisTest::staticVectorCopyTest();
  FcfTest::BasisTest::staticVectorExceptionTest();
  FcfTest::BasisTest::staticVectorIteratorTest();
  FcfTest::BasisTest::staticVectorPushTest();
  FcfTest::BasisTest::staticVectorNotReduce();
  FcfTest::BasisTest::staticVectorInsertTest();
  FcfTest::BasisTest::staticVectorEraseTest();

  FcfTest::BasisTest::declareCall();

  FcfTest::BasisTest::placeHolderCall();

  deepIndexCallCaller();
  deepIndexCallInner();
  deepIndexCall();
  deepIndexSimpleCaller();
  deepIndexNearestCaller();
  variantTest();
  indexTypesTest();
  iteratorTest();
  dynamicIteratorTest();
  deepIndexContainerCaller();
  tupleTest();
  
  return 0;
}
