#ifndef ___FCF_BASIS__VARIANT_HPP___
#define ___FCF_BASIS__VARIANT_HPP___

#include <string>
#include <map>
#include <stdexcept>
#include "macro.hpp"
#include "Details/MaxTypesSize.hpp"
#include "Details/Variant/Wrapper.hpp"
#include "Details/Convert/Storage.hpp"
#include "Type.hpp"
#include "specificators.hpp"
#include "bits/registry.hpp"

namespace fcf {

  class FCF_BASIS_DECL_EXPORT Variant {
    public:
      enum { 
        innerBufferSize = fcf::Details::Basis::MaxTypesSize<
                          typename Details::Basis::Variant::Wrapper<std::string>,
                          typename Details::Basis::Variant::Wrapper<std::wstring>,
                          typename Details::Basis::Variant::Wrapper< std::map<std::string, std::string> >
                          >::size
      };

      Variant();

      template <typename Ty>
      Variant(const Ty& a_value);

      Variant(const Variant& a_variant);

      ~Variant();

      Variant& operator=(const Variant& a_variant);

      template <typename Ty>
      Variant& operator=(const Ty& a_value);

      void clear();

      unsigned int typeIndex() const;

      void* ptr();

      const void* ptr() const;

      template <typename TResult>
      typename std::remove_const< typename std::remove_reference<TResult>::type >::type& convert();

      template <typename TResult>
      TResult as() const;

      template <typename TResult>
      TResult get() const;

    private:
      void _destroy();

      void _clone(const Variant& a_variant);

      template <typename Ty>
      void _set(const Ty& a_value);

      char         _mem[innerBufferSize];
      unsigned int _index;
      void*        _ptr;
  };

  #ifdef FCF_BASIS_IMPLEMENTATION
    Variant::Variant()
      : _index(0)
      , _ptr(0) {
    }
  #endif // #ifdef FCF_BASIS_IMPLEMENTATION

  template <typename Ty>
  Variant::Variant(const Ty& a_value) {
    _set(a_value);
  }

  #ifdef FCF_BASIS_IMPLEMENTATION
    Variant::Variant(const Variant& a_variant) {
      _clone(a_variant);
    }
  #endif // #ifdef FCF_BASIS_IMPLEMENTATION

  #ifdef FCF_BASIS_IMPLEMENTATION
    Variant::~Variant(){
      _destroy();
    }
  #endif // #ifdef FCF_BASIS_IMPLEMENTATION

  #ifdef FCF_BASIS_IMPLEMENTATION
    Variant& Variant::operator=(const Variant& a_variant) 
    {
      _destroy();
      _ptr = 0;
      _index = 0;
      _clone(a_variant);
      return *this;
    }
  #endif // #ifdef FCF_BASIS_IMPLEMENTATION

  template <typename Ty>
  Variant& Variant::operator=(const Ty& a_value) 
  {
    _destroy();
    _ptr = 0;
    _index = 0;
    _set(a_value);
    return *this;
  }

  #ifdef FCF_BASIS_IMPLEMENTATION
    void Variant::clear() {
      _destroy();
      _ptr = 0;
      _index = 0;
    }
  #endif // #ifdef FCF_BASIS_IMPLEMENTATION

  #ifdef FCF_BASIS_IMPLEMENTATION
    unsigned int Variant::typeIndex() const{
      return _index;
    }
  #endif // #ifdef FCF_BASIS_IMPLEMENTATION

  #ifdef FCF_BASIS_IMPLEMENTATION
    void* Variant::ptr(){
      return &((Details::Basis::Variant::Wrapper<int>*)_ptr)->data;
    }
  #endif // #ifdef FCF_BASIS_IMPLEMENTATION

  #ifdef FCF_BASIS_IMPLEMENTATION
    const void* Variant::ptr() const{
      return &((Details::Basis::Variant::Wrapper<int>*)_ptr)->data;
    }
  #endif // #ifdef FCF_BASIS_IMPLEMENTATION

  template <typename TResult>
  typename std::remove_const< typename std::remove_reference<TResult>::type >::type& Variant::convert() {
    typedef typename std::remove_const< typename std::remove_reference<TResult>::type >::type result_type;
    if (typeIndex() == Type<TResult>().index()){
      return *(result_type*)ptr();
    } else {
      Details::Basis::Convert::ConvertIndex ci{ typeIndex(), Type<result_type>().index()};
      auto it = fcf::Details::Basis::Convert::getStorage().functions.find(ci);
      if (it == fcf::Details::Basis::Convert::getStorage().functions.end()){
        throw std::runtime_error(std::string() + "Can't find conver function");
      }
      result_type result;
      it->second(&result, ptr());
      *this = result;
      return *(result_type*)ptr();
    }
  }

  template <typename TResult>
  TResult Variant::as() const{
    if (typeIndex() == Type<TResult>().index()){
      return *(TResult*)ptr();
    } else {
      Details::Basis::Convert::ConvertIndex ci{ typeIndex(), Type<TResult>().index()};
      auto it = fcf::Details::Basis::Convert::getStorage().functions.find(ci);
      if (it == fcf::Details::Basis::Convert::getStorage().functions.end()){
        throw std::runtime_error(std::string() + "Can't find conver function");
      }
      TResult result;
      it->second(&result, ptr());
      return result;
    }
  }

  template <typename TResult>
  TResult Variant::get() const{
    if (typeIndex() != Type<TResult>().index()){
      throw std::runtime_error(std::string() + "The type saved in the variant is not '" + Type<TResult>().name() + "' type");
    }
    return *(TResult*)ptr();
  }

  #ifdef FCF_BASIS_IMPLEMENTATION
    void Variant::_destroy(){
      if (_ptr == &_mem[0]){
        ((Details::Basis::Variant::BaseWrapper*)_ptr)->~BaseWrapper();
      } else if (_ptr) {
        delete (Details::Basis::Variant::BaseWrapper*)_ptr;
      }
    }
  #endif // #ifdef FCF_BASIS_IMPLEMENTATION

  #ifdef FCF_BASIS_IMPLEMENTATION
    void Variant::_clone(const Variant& a_variant) {
      Details::Basis::Variant::BaseWrapper* wrp = (Details::Basis::Variant::BaseWrapper*)a_variant._ptr;
      if (a_variant._ptr == &_mem[0]){
        wrp->clone(&_mem[0]);
      } else {
        _ptr = wrp->clone();
      }
      _index = a_variant._index;
    }
  #endif // #ifdef FCF_BASIS_IMPLEMENTATION

  template <typename Ty>
  void Variant::_set(const Ty& a_value) {
    typedef typename Type<Ty, MemoryTypeSpecificator>::type type;
    if (sizeof(type) > innerBufferSize){
      _ptr = new Details::Basis::Variant::Wrapper<type>(a_value);
    } else {
      new (&_mem[0]) Details::Basis::Variant::Wrapper<type>(a_value);
      _ptr = &_mem[0];
    }
    _index = Type< typename Type<Ty, MemoryTypeSpecificator>::type >().index();
  }

  template <>
  struct Type<Variant, RawDataSpecificator> {
    enum { enable = true };
    unsigned int type(const Variant* a_source){
      return a_source ? a_source->typeIndex() : 0;
    }
    void* resolve(Variant& a_source){
      return a_source.ptr();
    }
  };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__VARIANT_HPP___

