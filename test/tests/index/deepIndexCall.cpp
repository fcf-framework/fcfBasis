#include "../../../ArgPlaceHolder.hpp"

#include <iostream>

#include "../../libraries/fcfTest/test.hpp"
#include "../../../Nop.hpp"
#include "../../../Type.hpp"
#include "../../../FunctionSignature.hpp"
#include "../../../Details/IndexableFunction/Storage.hpp"

#include "../../../bits/functions/fill.hpp"
#include "../../../convert.hpp"

// asd asdasd
namespace fcf {

  template <typename Ty=Nop, typename... TPack>
  class InvariantCallSeekerPackFiller {
    public:
      void operator()(unsigned int* a_dst) {
        *a_dst = Type<Ty>().index();
        InvariantCallSeekerPackFiller<TPack...>()(++a_dst);
      }
  };

  template <>
  class InvariantCallSeekerPackFiller<Nop> {
    public:
      void operator()(unsigned int* a_dst) {
      }
  };


  template <typename Ty=Nop, typename... TPack>
  class InvariantAdaptCallEq {
    public:
      bool operator()(unsigned int* a_dst) {
        if (*a_dst != Type<Ty>().index()){
          return false;
        }
        return InvariantAdaptCallEq<TPack...>()(++a_dst);
      }
  };

  template <>
  class InvariantAdaptCallEq<Nop> {
    public:
      bool operator()(unsigned int* a_dst) {
        return true;
      }
  };


  struct AdaptCall{
    unsigned int index;
    void*        function;
    unsigned int depth;
    unsigned int type;
    unsigned int getterDepth;
    unsigned int getterCount;
    void*        getter;
  };

  template <bool IsContainer, typename Ty, typename... TPack>
  class InvariantCallSeekerImpl {
    public:
      AdaptCall operator()(const char* a_name, 
                           unsigned int a_depth = 0, 
                           AdaptCall* a_curAdaptCall = 0, 
                           const BaseFunctionSignature* a_adaptFullSignature = 0,
                           const BaseFunctionSignature* a_adaptShortSignature = 0,
                           const unsigned int* a_adaptIndex = 0,
                           bool* a_error = 0){
        {
          size_t size = 1 + sizeof...(TPack) + (a_curAdaptCall ? a_curAdaptCall->getterCount : 0);
          BaseFunctionSignature fs(size);
          fs.rcode = Type<void>().index();
          fs.pacodes[0] = Type<Ty>().index();
          InvariantCallSeekerPackFiller<TPack...>()(fs.pacodes+1);
          if (a_curAdaptCall) {
            for(size_t i = 1 + sizeof...(TPack); i < size; ++i){
              fs.pacodes[i] = Type<const Variant&>().index();
            }
          }
          auto it = Details::IndexableFunction::getStorage().indexes.find(fs);
          if (it != Details::IndexableFunction::getStorage().indexes.end()){
            auto it2 = it->second.find(a_name);
            if (it2 != it->second.end()) {
              return AdaptCall{ it2->second,
                                Details::IndexableFunction::getStorage().functions[it2->second].function,
                                a_depth,
                                1,
                                a_curAdaptCall ? a_curAdaptCall->getterDepth : 0,
                                a_curAdaptCall ? a_curAdaptCall->getterCount : 0,
                                a_curAdaptCall ? a_curAdaptCall->getter : 0
                              };
            }
          }
        }
        if (!a_curAdaptCall) {
          Details::IndexableFunction::Storage& storage = Details::IndexableFunction::getStorage();
          Details::IndexableFunction::CallFunctionGroups::iterator groupIt = storage.groups.find(a_name);
          if (groupIt != storage.groups.end()) {
            const std::map<unsigned int, SpecificatorTypeInfo>& typeSpecs = Type<Ty>().specificators();
            for(std::map<unsigned int, ::fcf::Details::IndexableFunction::ShortSignatures >::iterator itGrpSpec = groupIt->second.specificators.begin();
                itGrpSpec != groupIt->second.specificators.end();
                ++itGrpSpec
                ) {
              std::map<unsigned int, SpecificatorTypeInfo>::const_iterator itSpec = typeSpecs.find(itGrpSpec->first);
              /*
              for(std::map<unsigned int, SpecificatorTypeInfo>::const_iterator ittest = typeSpecs.begin(); ittest != typeSpecs.end(); ++ittest ){
                std::cout << ittest->first << std::endl;
              }
              */
              if (itSpec == typeSpecs.end()) {
                continue;
              }
              if (!itSpec->second.argc) {
                continue;
              }
              for(::fcf::Details::IndexableFunction::ShortSignatures::iterator itShortSignature = itGrpSpec->second.begin();
                  itShortSignature != itGrpSpec->second.end();
                  ++itShortSignature
                  ) {
                bool error = false;
                AdaptCall subac = {0, itShortSignature->second.caller, 0, 0, a_depth, itSpec->second.argc, itSpec->second.resolve};
                AdaptCall ac = InvariantCallSeekerImpl<IsContainer, Ty, TPack...>()(
                                                                                   a_name,
                                                                                   a_depth,
                                                                                   &subac,
                                                                                   &itShortSignature->second.fullSignature,
                                                                                   &itShortSignature->first,
                                                                                   &itShortSignature->second.index,
                                                                                   &error);
                if (!error) {
                  return ac;
                }
              }
            }
          }
        }
        /*
        if (!a_curAdaptCall) {
          Details::IndexableFunction::Storage& storage = Details::IndexableFunction::getStorage();
          std::cout << "storage.groups.size: " << storage.groups.size() << std::endl;
          Details::IndexableFunction::CallFunctionGroups::iterator groupIt = storage.groups.find(a_name);
          if (groupIt != storage.groups.end()) {
            std::cout << "storage.groups.find: 1" <<  std::endl;
            const std::map<unsigned int, SpecificatorTypeInfo>& typeSpecs = Type<Ty>().specificators();
            for(std::map<unsigned int, std::map<BaseFunctionSignature, unsigned int> >::iterator itGrpSpec = groupIt->second.specificators.begin();
                itGrpSpec != groupIt->second.specificators.end();
                ++itGrpSpec
                ) {
              std::map<unsigned int, SpecificatorTypeInfo>::const_iterator itSpec = typeSpecs.find(itGrpSpec->first);
              if (itSpec == typeSpecs.end()) {
                continue;
              }
              std::cout << "storage.groups.spec: 2" <<  std::endl;
              if (!itSpec->second.argc) {
                continue;
              }
              std::cout << "storage.groups.spec: 3" <<  std::endl;
              bool error = false;
              AdaptCall subac = {0, 0, 0, a_depth, itSpec->second.argc, itSpec->second.resolve};
              AdaptCall ac = InvariantCallSeekerImpl<IsContainer, Ty, TPack...>()(
                                                                                 a_name,
                                                                                 a_depth,
                                                                                 &subac,
                                                                                 &error);
              if (!error) {
                return ac;
              }
            }
          }
        }
        */
        typedef decltype(std::begin(*(Ty*)0))           iterator_type;
        typedef decltype(&(*(*(iterator_type*)0)))      pointer_type;
        typedef decltype(*std::declval<pointer_type>()) rnext_type;
        typedef typename std::remove_reference<rnext_type>::type next_type;

        BaseFunctionSignature fs(2 + sizeof...(TPack));
        fs.rcode = Type<void>().index();
        fs.pacodes[0] = Type<pointer_type>().index();
        fs.pacodes[1] = Type<pointer_type>().index();
        if (a_adaptShortSignature) {
          if (fs == *a_adaptShortSignature){
            return AdaptCall{ *a_adaptIndex,
                              a_curAdaptCall->function,
                              a_depth,
                              4,
                              a_curAdaptCall->getterDepth,
                              a_curAdaptCall->getterCount,
                              a_curAdaptCall->getter
                            };
          }
        } else {
          InvariantCallSeekerPackFiller<TPack...>()(fs.pacodes+2);
          auto it = Details::IndexableFunction::getStorage().indexes.find(fs);
          if (it != Details::IndexableFunction::getStorage().indexes.end()){
            auto it2 = it->second.find(a_name);
            if (it2 != it->second.end()) {
              return AdaptCall{ it2->second,
                                Details::IndexableFunction::getStorage().functions[it2->second].function,
                                a_depth,
                                2,
                                a_curAdaptCall ? a_curAdaptCall->getterDepth : 0,
                                a_curAdaptCall ? a_curAdaptCall->getterCount : 0,
                                a_curAdaptCall ? a_curAdaptCall->getter : 0
                              };
            }
          }
        }
        return InvariantCallSeekerImpl< Type<next_type>::container, next_type, TPack...>()(
                                                                                          a_name,
                                                                                          a_depth + 1,
                                                                                          a_curAdaptCall,
                                                                                          a_adaptFullSignature,
                                                                                          a_adaptShortSignature,
                                                                                          a_adaptIndex,
                                                                                          a_error);
      }
  };

  template <typename Ty, typename... TPack>
  class InvariantCallSeekerImpl< false, Ty, TPack...> {
    public:
      AdaptCall operator()(const char* a_name, 
                           unsigned int a_depth = 0, 
                           AdaptCall* a_curAdaptCall = 0, 
                           const BaseFunctionSignature* a_adaptFullSignature = 0,
                           const BaseFunctionSignature* a_adaptShortSignature = 0,
                           const unsigned int* a_adaptIndex = 0,
                           bool* a_error = 0){
        if (a_error) {
          *a_error = true;
        } else {
          throw std::runtime_error(std::string() + "Function \"" + a_name + "\" not found");
        }
        return AdaptCall{0,0,0,0,0};
      }
  };

  template <typename Ty, typename... TPack>
  class InvariantCallSeeker {
    public:
      AdaptCall operator()(const char* a_name){
        return InvariantCallSeekerImpl< Type<Ty>::container, Ty, TPack... >()(a_name);
     }
  };

  template <bool IsContainer = true>
  class InvariantAdaptCallerImpl {
    public:
      template <typename Ty, class... TPack>
      static void call(const AdaptCall& a_adaptCall, void* a_function, unsigned int a_depth, Ty& a_container, TPack... a_pack){
        /*
        if (a_adaptCall.depth == a_depth){
          if (a_adaptCall.type == 1){
            switch (a_adaptCall.getterCount) {
              case 0:
                {
                  typedef void (*function_type)(Ty&, TPack...);
                  function_type func = (function_type)a_function;
                  func(a_container, a_pack...);
                  return;
                }
              case 1:
                {
                  Variant varg1;
                  typedef void (*getter_type)(Ty&, Variant&);
                  typedef void (*function_type)(Ty&, TPack..., Variant&);
                  getter_type   getter = (getter_type)a_adaptCall.getter;
                  function_type func   = (function_type)a_function;
                  getter(a_container, varg1);
                  func(a_container, a_pack..., varg1);
                  return;
                }
              case 2:
                {
                  Variant varg1;
                  Variant varg2;
                  typedef void (*getter_type)(Ty&, Variant&, Variant&);
                  typedef void (*function_type)(Ty&, TPack..., Variant&, Variant&);
                  getter_type   getter = (getter_type)a_adaptCall.getter;
                  function_type func   = (function_type)a_function;
                  getter(a_container, varg1, varg2);
                  func(a_container, a_pack..., varg1, varg2);
                  return;
                }
              case 3:
                {
                  Variant varg1;
                  Variant varg2;
                  Variant varg3;
                  typedef void (*getter_type)(Ty&, Variant&, Variant&, Variant&);
                  typedef void (*function_type)(Ty&, TPack..., Variant&, Variant&, Variant&);
                  getter_type   getter = (getter_type)a_adaptCall.getter;
                  function_type func   = (function_type)a_function;
                  getter(a_container, varg1, varg2, varg3);
                  func(a_container, a_pack..., varg1, varg2, varg3);
                  return;
                }
              default:
                throw std::runtime_error("Predetermined function not found");
                break;
            }
          }
        }
        */
        typedef typename std::remove_reference<Ty>::type container_type;
        typedef decltype(std::begin(*(container_type*)0))                     iterator_type;
        typedef decltype(&(*(*(iterator_type*)0)))                pointer_type;
        typedef decltype(*(pointer_type)0)                        rvalue_type;
        typedef typename std::remove_reference<rvalue_type>::type value_type;
        if (a_adaptCall.depth == a_depth && a_adaptCall.type == 2) {
          if (Type<container_type>::flat) {
            
        std::tuple<TPack...> t = {a_pack...};
        //std::cout << std::get<0>(t) << std::endl;
        //std::cout << std::get<1>(t) << std::endl;
        
            
            typedef void (*function_type)(pointer_type, pointer_type, TPack...);
            function_type func = (function_type)a_function;
            pointer_type begin = &(*std::begin(a_container));
            pointer_type end = &(*std::end(a_container));
            func(begin, end, a_pack...);
            return;
          } else {
        std::tuple<TPack...> t = {a_pack...};
        std::cout << std::get<0>(t) << std::endl;
        std::cout << std::get<1>(t) << std::endl;

            typedef void (*function_type)(pointer_type, pointer_type, TPack...);
            function_type func = (function_type)a_function;
            iterator_type endIt = std::end(a_container);
            for(iterator_type it = std::begin(a_container); it != endIt; ++it) {
              pointer_type begin = &(*it);
              func(begin, begin+1, a_pack...);
            }
            return;
          }
        }
        iterator_type it = std::begin(a_container);
        iterator_type endIt = std::end(a_container);
        for(; it != endIt; ++it){
          InvariantAdaptCallerImpl<Type<value_type>::container>::call(a_adaptCall, a_function, a_depth+1, *it, a_pack...);
        }
      }
  };

  template <>
  class InvariantAdaptCallerImpl<false> {
    public:
      template <typename Ty, typename... TPack>
      static void call(const AdaptCall& a_adaptCall, void* a_function, unsigned int a_depth, Ty& a_container, TPack... a_pack){
      }
  };


  class InvariantAdaptCaller {
    public:
      template <typename Ty, typename... TPackArgs>
      void call(AdaptCall a_adaptCall, Ty& a_container, TPackArgs... a_pack) {
        /*
        const fcf::IndexableFunctionInfo& fi = fcf::Details::IndexableFunction::getStorage().functions[a_adaptCall.index];
        if (!fi.signature.asize) {
          throw std::runtime_error("Function cannot be called because there are no arguments");
        }
        */
        InvariantAdaptCallerImpl<Type<Ty>::container>::template call<Ty, TPackArgs...>(a_adaptCall, a_adaptCall.function, 0, a_container, a_pack...);
      }
    };



    struct PastArg{};


    template <typename TypeFind, typename Type = Nop, typename... TypePack>
    struct TypeCount {
      enum { value = ( std::is_same<TypeFind, Type>::value  ? 1 : 0 ) +  TypeCount<TypeFind, TypePack...>::value };
    };

    template <typename TypeFind>
    struct TypeCount<TypeFind> {
      enum { value = 0 };
    };

    template <int Pos, typename TypeFind, typename Type = Nop, typename... TypePack>
    struct TypePos {
      enum { value = std::is_same<TypeFind, Type>::value  ? Pos : TypePos<Pos+1, TypeFind, TypePack...>::value };
    };

    template <int Pos, typename TypeFind>
    struct TypePos<Pos, TypeFind> {
      enum { value = -1 };
    };


    template <size_t VariantArgCount, size_t VariantArgPos, typename TRealArg1 = Nop, typename TRealArg2 = Nop, typename TRealArg3 = Nop, typename TRealArg4 = Nop, typename TRealArg5 = Nop>
    struct PastArgCaller;

    template <typename TRealArg1, typename TRealArg2, typename TRealArg3, typename TRealArg4, typename TRealArg5>
    struct PastArgCaller<2, 0, TRealArg1, TRealArg2, TRealArg3, TRealArg4, TRealArg5>{
      template <typename T1, typename T2, typename T3>
      static void call(void* a_func, T1 a_arg1, T2 a_arg2, T3 a_arg3, Variant& a_varg1, Variant& a_varg2){
        {
          typedef void(*function_type)(TRealArg1, TRealArg2, TRealArg3, TRealArg4, TRealArg5);
          function_type func = (function_type)a_func;
          func(a_varg1.get< std::remove_reference<TRealArg1>::type >(),
               a_varg2.get< std::remove_reference<TRealArg2>::type >(),
               a_arg1,
               a_arg2,
               a_arg3);
        }
      }
    };

    template <typename TRealArg1, typename TRealArg2, typename TRealArg3, typename TRealArg4>
    struct PastArgCaller<2, 0, TRealArg1, TRealArg2, TRealArg3, TRealArg4, Nop>{
      template <typename T1, typename T2>
      static void call(void* a_func, T1 a_arg1, T2 a_arg2, Variant& a_varg1, Variant& a_varg2){
        {
          typedef void(*function_type)(TRealArg1, TRealArg2, TRealArg3, TRealArg4);
          function_type func = (function_type)a_func;
          func(a_varg1.get< std::remove_reference<TRealArg1>::type >(),
               a_varg2.get< std::remove_reference<TRealArg2>::type >(),
               a_arg1,
               a_arg2);
        }
      }
    };

    template <typename TRealArg1, typename TRealArg2, typename TRealArg3>
    struct PastArgCaller<2, 0, TRealArg1, TRealArg2, TRealArg3, Nop, Nop>{
      template <typename T1>
      static void call(void* a_func, T1 a_arg1, Variant& a_varg1, Variant& a_varg2){
        {
          typedef void(*function_type)(TRealArg1, TRealArg2, TRealArg3);
          function_type func = (function_type)a_func;
          func(a_varg1.get< std::remove_reference<TRealArg1>::type >(),
               a_varg2.get< std::remove_reference<TRealArg2>::type >(),
               a_arg1);
        }
      }
    };

    template <typename TRealArg1, typename TRealArg2>
    struct PastArgCaller<2, 0, TRealArg1, TRealArg2, Nop, Nop, Nop>{
      static void call(void* a_func, Variant& a_varg1, Variant& a_varg2){
        {
          typedef void(*function_type)(TRealArg1, TRealArg2);
          function_type func = (function_type)a_func;
          func(a_varg1.get< std::remove_reference<TRealArg1>::type >(),
               a_varg2.get< std::remove_reference<TRealArg2>::type >());
        }
      }
    };



    template <typename TRealArg1, typename TRealArg2, typename TRealArg3, typename TRealArg4, typename TRealArg5>
    struct PastArgCaller<2, 1, TRealArg1, TRealArg2, TRealArg3, TRealArg4, TRealArg5>{
      template <typename T1, typename T2, typename T3>
      static void call(void* a_func, T1 a_arg1, T2 a_arg2, T3 a_arg3, Variant& a_varg1, Variant& a_varg2){
        {
          typedef void(*function_type)(TRealArg1, TRealArg2, TRealArg3, TRealArg4, TRealArg5);
          function_type func = (function_type)a_func;
          func(a_arg1,
              a_varg1.get< std::remove_reference<TRealArg2>::type >(),
              a_varg2.get< std::remove_reference<TRealArg3>::type >(),
              a_arg2,
              a_arg3);
        }
      }
    };

    template <typename TRealArg1, typename TRealArg2, typename TRealArg3, typename TRealArg4>
    struct PastArgCaller<2, 1, TRealArg1, TRealArg2, TRealArg3, TRealArg4>{
      template <typename T1, typename T2>
      static void call(void* a_func, T1 a_arg1, T2 a_arg2, Variant& a_varg1, Variant& a_varg2){
        {
          typedef void(*function_type)(TRealArg1, TRealArg2, TRealArg3, TRealArg4);
          function_type func = (function_type)a_func;
          func(a_arg1,
              a_varg1.get< std::remove_reference<TRealArg2>::type >(),
              a_varg2.get< std::remove_reference<TRealArg3>::type >(),
              a_arg2);
        }
      }
    };

    template <typename TRealArg1, typename TRealArg2, typename TRealArg3>
    struct PastArgCaller<2, 1, TRealArg1, TRealArg2, TRealArg3>{
      template <typename T1>
      static void call(void* a_func, T1 a_arg1, Variant& a_varg1, Variant& a_varg2){
        {
          typedef void(*function_type)(TRealArg1, TRealArg2, TRealArg3);
          function_type func = (function_type)a_func;
          func(a_arg1,
               a_varg1.get< std::remove_reference<TRealArg2>::type >(),
               a_varg2.get< std::remove_reference<TRealArg3>::type >());
        }
      }
    };



    template <typename TRealArg1, typename TRealArg2, typename TRealArg3, typename TRealArg4, typename TRealArg5>
    struct PastArgCaller<2, 2, TRealArg1, TRealArg2, TRealArg3, TRealArg4, TRealArg5>{
      template <typename T1, typename T2, typename T3>
      static void call(void* a_func, T1 a_arg1, T2 a_arg2, T3 a_arg3, Variant& a_varg1, Variant& a_varg2){
        {
          typedef void(*function_type)(TRealArg1, TRealArg2, TRealArg3, TRealArg4, TRealArg5);
          function_type func = (function_type)a_func;
          func(a_arg1,
               a_arg2,
               a_varg1.get< std::remove_reference<TRealArg3>::type >(),
               a_varg2.get< std::remove_reference<TRealArg4>::type >(),
               a_arg3);
        }
      }
    };

    template <typename TRealArg1, typename TRealArg2, typename TRealArg3, typename TRealArg4>
    struct PastArgCaller<2, 2, TRealArg1, TRealArg2, TRealArg3, TRealArg4>{
      template <typename T1, typename T2>
      static void call(void* a_func, T1 a_arg1, T2 a_arg2, Variant& a_varg1, Variant& a_varg2){
        {
          typedef void(*function_type)(TRealArg1, TRealArg2, TRealArg3, TRealArg4);
          function_type func = (function_type)a_func;
          func(a_arg1,
               a_arg2,
               a_varg1.get< std::remove_reference<TRealArg3>::type >(),
               a_varg2.get< std::remove_reference<TRealArg4>::type >()
              );
        }
      }
    };



    template <typename TRealArg1, typename TRealArg2, typename TRealArg3, typename TRealArg4, typename TRealArg5>
    struct PastArgCaller<2, 3, TRealArg1, TRealArg2, TRealArg3, TRealArg4, TRealArg5>{
      template <typename T1, typename T2, typename T3>
      static void call(void* a_func, T1 a_arg1, T2 a_arg2, T3 a_arg3, Variant& a_varg1, Variant& a_varg2){
        {
          typedef void(*function_type)(TRealArg1, TRealArg2, TRealArg3, TRealArg4, TRealArg5);
          function_type func = (function_type)a_func;
          func(a_arg1,
               a_arg2,
               a_arg3,
               a_varg1.get< std::remove_reference<TRealArg4>::type >(),
               a_varg2.get< std::remove_reference<TRealArg5>::type >()
              );
        }
      }
    };
} // fcf namespace

namespace DeepIndexCallTest {
  class Array {
    public:
      Array(size_t a_size, float a_min, float a_max)
        : _array(a_size)
        , _min(a_min)
        , _max(a_max)
      {
      }
      float* begin(){
        return &_array.front();
      }
      float* end(){
        return &_array.back();
      }
      float min() const{
        return _min;
      }
      float max() const{
        return _max;
      }
    private:
      std::vector<float> _array;
      float              _min;
      float              _max;
  };
}


template <>
struct fcf::Type<DeepIndexCallTest::Array> : public fcf::BaseContainerType< DeepIndexCallTest::Array, true >{
  typedef DeepIndexCallTest::Array owner_type;
  typedef float data_type;
  typedef float value_type;
};
FCF_TYPEID_REGISTRY(DeepIndexCallTest::Array, "DeepIndexCallTest::Array", 0);

template <>
struct fcf::Type< DeepIndexCallTest::Array, fcf::MinMaxSpecificator > {
  static void resolve(const DeepIndexCallTest::Array& a_container, Variant& a_min, Variant& a_max) {
    a_min = a_container.min();
    a_max = a_container.max();
  }
};


::fcf::SpecificatorTypeRegistrator<DeepIndexCallTest::Array, fcf::MinMaxSpecificator> specificatorReg_Array;





namespace fcf {


  namespace Details {
    namespace Basis {
      namespace InvariantCaller {
/*

        template <size_t Index, typename... TPack>
        struct BindCallerGet;

        template <bool IsPlace, size_t ArgIndex, size_t CurArgIndex, typename TReal1 = Nop, typename... TRealPack>
        struct BindCallerExecutor {
          typedef typename BindCallerExecutor<false,  ArgIndex, CurArgIndex + 1, TRealPack...>::result_type result_type;

          template <typename TVars,
                    typename TTempl1, typename TTempl2 = Nop, typename TTempl3 = Nop, typename TTempl4 = Nop,
                    typename Ty, typename... TPack>
          inline static result_type call(TVars& a_vars, Ty& a_arg1, TPack&... a_argPack) {
            return BindCallerExecutor<::fcf::ArgPlaceHolder::IsPlaceHolder<TTempl2>::value, ArgIndex, CurArgIndex+1, TRealPack...>::
                  template call<TVars, TTempl2, TTempl3, TTempl4, Nop, TPack...>(
                      a_vars,
                      a_argPack...
                    );
          }
        };

        template <size_t ArgIndex, size_t CurArgIndex, typename TReal1, typename... TRealPack>
        struct BindCallerExecutor<true, ArgIndex, CurArgIndex, TReal1, TRealPack...> {
          typedef typename BindCallerExecutor<false,  ArgIndex, CurArgIndex + 1, TRealPack...>::result_type result_type;

          template <typename TVars,
                    typename TTempl1, typename TTempl2 = Nop, typename TTempl3 = Nop, typename TTempl4 = Nop,
                    typename Ty, typename... TPack>
          inline static result_type call(TVars& a_vars, Ty& a_arg1, TPack&... a_argPack) {
            return BindCallerExecutor<::fcf::ArgPlaceHolder::IsPlaceHolder<TTempl2>::value, ArgIndex, CurArgIndex+1, TRealPack...>::
                      template call<TVars, TTempl1, TTempl2, TTempl3, TTempl4, Ty, TPack...>(
                        a_vars,
                        a_arg1,
                        a_argPack...
                      );
            }
        };

        template <size_t ArgIndex, typename TReal1, typename... TRealPack>
        struct BindCallerExecutor<false, ArgIndex, ArgIndex, TReal1, TRealPack...> {
          typedef typename std::add_lvalue_reference<TReal1>::type result_type;
          template <typename TVars, typename TTempl1, typename TTempl2 = Nop, typename TTempl3 = Nop, typename TTempl4 = Nop, typename Ty, typename... TPack>
          inline static result_type call(TVars& a_vars, Ty& a_arg1, TPack&... a_argPack) {
            return a_arg1;
          }
        };

        template <size_t ArgIndex, typename TReal1, typename... TRealPack>
        struct BindCallerExecutor<true, ArgIndex, ArgIndex, TReal1, TRealPack...> {
          typedef typename std::add_lvalue_reference<TReal1>::type result_type;
          template <typename TVars, typename TTempl1, typename TTempl2 = Nop, typename TTempl3 = Nop, typename TTempl4 = Nop, typename... TPack>
          inline static result_type call(TVars& a_vars, TPack&... a_argPack) {
            typedef typename std::remove_reference<TTempl1>::type type;
            return a_vars[ type::value - 1 ].template convert<TReal1>();
          }
        };

        template <size_t Index, typename TTemplArgs, typename... TRealPack>
        struct BindCallerGetArg {
          typedef BindCallerExecutor<false, Index, 1, TRealPack...> getter_type;
          typedef typename getter_type::result_type result_type;
          template <typename TVars, typename... TArgPack>
          inline static result_type call(TVars& a_vargs, TArgPack&... a_args){
            return getter_type::template call<
                                TVars,
                                typename TTemplArgs::type1,
                                typename TTemplArgs::type2,
                                typename TTemplArgs::type3,
                                typename TTemplArgs::type4
                                >(a_vargs, a_args...);
          }
        };

        template <typename TTemplArgs, typename... TRealPack>
        struct BindCaller;

        template <typename TTemplArgs, typename... TRealPack>
        struct BindCaller<TTemplArgs, void(TRealPack...)> {
          template <typename TFuncArg1, typename TVars, typename... TArgPack>
          static void call(void(*a_function)(TFuncArg1), TVars& a_vargs, TArgPack&&... a_args){
            typedef BindCallerGetArg<1, TTemplArgs, TRealPack...>  getter1_type;
            a_function(getter1_type::call(a_vargs, a_args...));
          }
          template <typename TFuncArg1, typename TFuncArg2, typename TVars, typename... TArgPack>
          static void call(void(*a_function)(TFuncArg1, TFuncArg2), TVars& a_vargs, TArgPack&&... a_args){
            typedef BindCallerGetArg<1, TTemplArgs, TRealPack...>  getter1_type;
            typedef BindCallerGetArg<2, TTemplArgs, TRealPack...>  getter2_type;
            a_function(
              getter1_type::call(a_vargs, a_args...),
              getter2_type::call(a_vargs, a_args...)
            );
          }
          template <typename TFuncArg1, typename TFuncArg2, typename TFuncArg3, typename TVars, typename... TArgPack>
          static void call(void(*a_function)(TFuncArg1, TFuncArg2, TFuncArg3), TVars& a_vargs, TArgPack&&... a_args){
            typedef BindCallerGetArg<1, TTemplArgs, TRealPack...>  getter1_type;
            typedef BindCallerGetArg<2, TTemplArgs, TRealPack...>  getter2_type;
            typedef BindCallerGetArg<3, TTemplArgs, TRealPack...>  getter3_type;
            a_function(
              getter1_type::call(a_vargs, a_args...),
              getter2_type::call(a_vargs, a_args...),
              getter3_type::call(a_vargs, a_args...)
            );
          }
          template <typename TFuncArg1, typename TFuncArg2, typename TFuncArg3, typename TFuncArg4, typename TVars, typename... TArgPack>
          static void call(void(*a_function)(TFuncArg1, TFuncArg2, TFuncArg3, TFuncArg4), TVars& a_vargs, TArgPack&&... a_args){
            typedef BindCallerGetArg<1, TTemplArgs, TRealPack...>  getter1_type;
            typedef BindCallerGetArg<2, TTemplArgs, TRealPack...>  getter2_type;
            typedef BindCallerGetArg<3, TTemplArgs, TRealPack...>  getter3_type;
            typedef BindCallerGetArg<4, TTemplArgs, TRealPack...>  getter4_type;
            a_function(
              getter1_type::call(a_vargs, a_args...),
              getter2_type::call(a_vargs, a_args...),
              getter3_type::call(a_vargs, a_args...),
              getter4_type::call(a_vargs, a_args...)
            );
          }
        };
       */

        /*
        template <typename T1 = Nop, typename T2 = Nop, typename T3 = Nop, typename T4 = Nop, typename T5 = Nop,
                  typename T6 = Nop, typename T7 = Nop, typename T8 = Nop, typename T9 = Nop, typename T10 = Nop
                 >
        struct ShortFunctionTypeImpl{
          typedef ::fcf::ArgPlaceHolder::Arguments<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10> args_type;
          typedef void(*type)(typename args_type::type1,
                              typename args_type::type2,
                              typename args_type::type3,
                              typename args_type::type4,
                              typename args_type::type5,
                              typename args_type::type6,
                              typename args_type::type7,
                              typename args_type::type8,
                              typename args_type::type9,
                              typename args_type::type10
                              );
        };

        template <typename T1, typename T2, typename T3, typename T4, typename T5,
                  typename T6, typename T7, typename T8, typename T9>
        struct ShortFunctionTypeImpl<T1, T2, T3, T4, T5, T6, T7, T8, T9> {
          typedef ::fcf::ArgPlaceHolder::Arguments<T1, T2, T3, T4, T5, T6, T7, T8, T9> args_type;
          typedef void(*type)(typename args_type::type1,
                              typename args_type::type2,
                              typename args_type::type3,
                              typename args_type::type4,
                              typename args_type::type5,
                              typename args_type::type6,
                              typename args_type::type7,
                              typename args_type::type8,
                              typename args_type::type9
                              );
        };

        template <typename T1, typename T2, typename T3, typename T4, typename T5,
                  typename T6, typename T7, typename T8>
        struct ShortFunctionTypeImpl<T1, T2, T3, T4, T5, T6, T7, T8> {
          typedef ::fcf::ArgPlaceHolder::Arguments<T1, T2, T3, T4, T5, T6, T7, T8> args_type;
          typedef void(*type)(typename args_type::type1,
                              typename args_type::type2,
                              typename args_type::type3,
                              typename args_type::type4,
                              typename args_type::type5,
                              typename args_type::type6,
                              typename args_type::type7,
                              typename args_type::type8
                              );
        };

        template <typename T1, typename T2, typename T3, typename T4, typename T5,
                  typename T6, typename T7>
        struct ShortFunctionTypeImpl<T1, T2, T3, T4, T5, T6, T7> {
          typedef ::fcf::ArgPlaceHolder::Arguments<T1, T2, T3, T4, T5, T6, T7> args_type;
          typedef void(*type)(typename args_type::type1,
                              typename args_type::type2,
                              typename args_type::type3,
                              typename args_type::type4,
                              typename args_type::type5,
                              typename args_type::type6,
                              typename args_type::type7
                              );
        };

        template <typename T1, typename T2, typename T3, typename T4, typename T5,
                  typename T6>
        struct ShortFunctionTypeImpl<T1, T2, T3, T4, T5, T6> {
          typedef ::fcf::ArgPlaceHolder::Arguments<T1, T2, T3, T4, T5, T6> args_type;
          typedef void(*type)(typename args_type::type1,
                              typename args_type::type2,
                              typename args_type::type3,
                              typename args_type::type4,
                              typename args_type::type5,
                              typename args_type::type6
                              );
        };

        template <typename T1, typename T2, typename T3, typename T4, typename T5>
        struct ShortFunctionTypeImpl<T1, T2, T3, T4, T5> {
          typedef ::fcf::ArgPlaceHolder::Arguments<T1, T2, T3, T4, T5> args_type;
          typedef void(*type)(typename args_type::type1,
                              typename args_type::type2,
                              typename args_type::type3,
                              typename args_type::type4,
                              typename args_type::type5
                              );
        };

        template <typename T1, typename T2, typename T3, typename T4>
        struct ShortFunctionTypeImpl<T1, T2, T3, T4> {
          typedef ::fcf::ArgPlaceHolder::Arguments<T1, T2, T3, T4> args_type;
          typedef void(*type)(typename args_type::type1,
                              typename args_type::type2,
                              typename args_type::type3,
                              typename args_type::type4
                              );
        };

        template <typename T1, typename T2, typename T3>
        struct ShortFunctionTypeImpl<T1, T2, T3> {
          typedef ::fcf::ArgPlaceHolder::Arguments<T1, T2, T3> args_type;
          typedef void(*type)(typename args_type::type1,
                              typename args_type::type2,
                              typename args_type::type3
                              );
        };

        template <typename T1, typename T2>
        struct ShortFunctionTypeImpl<T1, T2> {
          typedef ::fcf::ArgPlaceHolder::Arguments<T1, T2> args_type;
          typedef void(*type)(typename args_type::type1,
                              typename args_type::type2
                              );
        };

        template <typename T1>
        struct ShortFunctionTypeImpl<T1> {
          typedef ::fcf::ArgPlaceHolder::Arguments<T1> args_type;
          typedef void(*type)(typename args_type::type1);
        };

        template <>
        struct ShortFunctionTypeImpl<> {
          typedef void(*type)();
        };

        template <typename... TArgPack>
        struct ShortFunctionType{
          typedef typename ShortFunctionTypeImpl<TArgPack...>::type type;
        };

        template <typename... TArgPack>
        struct ShortFunctionType<void (TArgPack...)>{
          typedef typename ShortFunctionTypeImpl<TArgPack...>::type type;
        };
        */

      }
    }
  }
}

#define MACRO1(a_type) #a_type

struct ValueSetter{
  template <typename Ty>
  void operator()(Ty& a_value){
    a_value = 999;
  }
  
};
template <typename... TPack>
void testFunction(TPack&&... a_args){
  std::tuple<TPack...> t = {a_args...};
  //std::cout << std::get<0>(t) << std::endl;
  ValueSetter()(a_args...);
  
}


void deepIndexCall(){
  std::cout << "Start deepIndexCall..." << std::endl;
  {
    int v = 1;
    testFunction(v);
    //std::cout << v << std::endl;
  }
  {
    DeepIndexCallTest::Array array(10, 1, 10);
    fcf::AdaptCall adaptCall = fcf::InvariantCallSeeker< DeepIndexCallTest::Array >()("random");
  }
  {
    fcf::AdaptCall adaptCall = fcf::InvariantCallSeeker< std::vector<float> , const float&, const float&>()("random");
    std::vector<float> vector(10);
    float a1 = 1;
    float a2 = 10;
    fcf::InvariantAdaptCaller().call<std::vector<float>, const float&, const float&>(adaptCall, vector, a1, a2);
    for(int i = 0; i < vector.size(); ++i) {
      FCF_TEST(vector[i] >= 1 && vector[i] <= 10, i, vector[i]);
    }
  }
  
  /*
  {
    fcf::AdaptCall adaptCall = fcf::InvariantCallSeeker< std::vector<float> , float, float>()("random");
    std::vector<float> vector(10);
    fcf::InvariantAdaptCaller()(adaptCall, vector, (float)1, (float)10);
    for(int i = 0; i < vector.size(); ++i) {
      FCF_TEST(vector[i] >= 1 && vector[i] <= 10, i, vector[i]);
    }
  }
  {
    fcf::AdaptCall adaptCall = fcf::InvariantCallSeeker< std::list<float> , float, float>()("random");
    std::list<float> list(10);
    fcf::InvariantAdaptCaller()(adaptCall, list, (float)1, (float)10);
    for(float& item : list) {
      FCF_TEST(item >= 1 && item <= 10, item);
    }
  }
  {
    typedef std::vector< std::vector<float> > container_type;
    fcf::AdaptCall adaptCall = fcf::InvariantCallSeeker< container_type , float, float>()("random");
    container_type container(5);
    for(auto& citm : container){
      citm.resize(5);
    }
    fcf::InvariantAdaptCaller()(adaptCall, container, (float)1, (float)10);
    for(auto& citem : container){
      for(auto& item : citem){
        FCF_TEST(item >= 1 && item <= 10, item);
      }
    }
  }
  */

}
