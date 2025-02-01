#include <iostream>

#include "../../libraries/fcfTest/test.hpp"
#include "../../../Nop.hpp"
#include "../../../Type.hpp"
#include "../../../FunctionSignature.hpp"
#include "../../../Details/IndexableFunction/Storage.hpp"

#include "../../../convert.hpp"

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
    unsigned int depth;
    unsigned int type;
  };

  template <bool IsContainer, typename Ty, typename... TPack>
  class InvariantCallSeekerImpl {
    public:
      AdaptCall operator()(const char* a_name, unsigned int a_depth = 0){
        {
          BaseFunctionSignature fs(1 + sizeof...(TPack));
          fs.rcode = Type<void>().index();
          fs.pacodes[0] = Type<Ty>().index();
          InvariantCallSeekerPackFiller<TPack...>()(fs.pacodes+1);
          auto it = Details::IndexableFunction::getStorage().indexes.find(fs);
          if (it != Details::IndexableFunction::getStorage().indexes.end()){
            auto it2 = it->second.find(a_name);
            if (it2 != it->second.end()) {
              return AdaptCall{it2->second, a_depth, 1};
            }
          }
        }
        {
          Details::IndexableFunction::Storage& storage = Details::IndexableFunction::getStorage();
          Details::IndexableFunction::Groups::iterator groupIt = storage.groups.find(a_name);
          if (groupIt != storage.groups.end()) {
            const std::map<unsigned int, SpecificatorTypeInfo>& typeSpecs = Type<Ty>().specificators();
            for(auto& specIndex : groupIt->second.specificators){
              std::map<unsigned int, SpecificatorTypeInfo>::const_iterator it = typeSpecs.find(specIndex);
              if (it == typeSpecs.end()) {
                continue;
              }
              if (!it->second.argc) {
                continue;
              }
              unsigned int s = 1 + sizeof...(TPack) + it->second.argc;
              BaseFunctionSignature fs(s);
              fs.rcode = Type<void>().index();
              fs.pacodes[0] = Type<Ty>().index();
              InvariantCallSeekerPackFiller<TPack...>()(fs.pacodes+1);
              // for(unsigned int i = 1 + sizeof...(TPack); i < s; ++i) {
              //   fs.pacodes[0] = Type<fcf::Union>().index();
              // }
            }
          }
        }
        typedef decltype(std::begin(*(Ty*)0))           iterator_type;
        typedef decltype(&(*(*(iterator_type*)0)))      pointer_type;
        typedef decltype(*std::declval<pointer_type>()) rnext_type;
        typedef typename std::remove_reference<rnext_type>::type next_type;
        {
          BaseFunctionSignature fs(2 + sizeof...(TPack));
          fs.rcode = Type<void>().index();
          fs.pacodes[0] = Type<pointer_type>().index();
          fs.pacodes[1] = Type<pointer_type>().index();
          InvariantCallSeekerPackFiller<TPack...>()(fs.pacodes+2);
          auto it = Details::IndexableFunction::getStorage().indexes.find(fs);
          if (it != Details::IndexableFunction::getStorage().indexes.end()){
            auto it2 = it->second.find(a_name);
            if (it2 != it->second.end()) {
              return AdaptCall{it2->second, a_depth, 2};
            }
          }
        }
        return InvariantCallSeekerImpl< Type<next_type>::container, next_type, TPack...>()(a_name, a_depth + 1);
      }
  };

  template <typename Ty, typename... TPack>
  class InvariantCallSeekerImpl< false, Ty, TPack...> {
    public:
      AdaptCall operator()(const char* a_name, unsigned int a_depth = 0){
        throw std::runtime_error(std::string() + "Function \"" + a_name + "\" not found");
        return AdaptCall{0,0,0};
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
      template <typename Ty, typename... TPack>
      static void call(const AdaptCall& a_adaptCall, void* a_function, unsigned int a_depth, Ty& a_container, TPack... a_pack){
        if (a_adaptCall.depth == a_depth && a_adaptCall.type == 1) {
          typedef void (*function_type)(Ty&, TPack...);
          function_type func = (function_type)a_function;
          func(a_container, a_pack...);
        }
        typedef decltype(std::begin(*(Ty*)0))                     iterator_type;
        typedef decltype(&(*(*(iterator_type*)0)))                pointer_type;
        typedef decltype(*(pointer_type)0)                        rvalue_type;
        typedef typename std::remove_reference<rvalue_type>::type value_type;
        if (a_adaptCall.depth == a_depth && a_adaptCall.type == 2) {
          if (Type<Ty>::flat) {
            typedef void (*function_type)(pointer_type, pointer_type, TPack...);
            function_type func = (function_type)a_function;
            pointer_type begin = &(*std::begin(a_container));
            pointer_type end = &(*std::end(a_container));
            func(begin, end, a_pack...);
            return;
          } else {
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
      template <typename Ty, typename... TPack>
      void operator()(AdaptCall a_adaptCall, Ty& a_container, TPack... a_pack) {
        const fcf::IndexableFunctionInfo& fi = fcf::Details::IndexableFunction::getStorage().functions[a_adaptCall.index];
        if (!fi.signature.asize) {
          throw std::runtime_error("Function cannot be called because there are no arguments");
        }
        InvariantAdaptCallerImpl<Type<Ty>::container>::call(a_adaptCall, fi.function, 0, a_container, a_pack...);
      }
    };


} // fcf namespace

void deepIndexCall(){
  std::cout << "Start deepIndexCall..." << std::endl;
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
  
}
