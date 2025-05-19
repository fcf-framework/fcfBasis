#ifndef ___FCF_BASIS__VARIANT_HPP___
#define ___FCF_BASIS__VARIANT_HPP___

#include <string>
#include <map>
#include <stdexcept>
#include "macro.hpp"
#include "Details/MaxTypesSize.hpp"
#include "Details/Variant/Wrapper.hpp"
#include "Details/Variant/NobodyWrapper.hpp"
#include "bits/Convert/convertRuntime.hpp"
#include "Type.hpp"
#include "specificators.hpp"
#include "bits/registry.hpp"

namespace fcf {

  class FCF_BASIS_DECL_EXPORT Variant {
    public:
      typedef void (*convert_function_type)(void*, const void*);

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

      Variant(unsigned int a_typeIndex, const void* a_sourceData, unsigned int a_sourceTypeIndex = 0, ConvertOptions* a_options = 0, ConvertFunction a_convertFunction = 0);

      ~Variant();
/*
      template <typename TDestinationType, typename TSourceType>
      static convert_function_type getConverter();

      static convert_function_type getConverter(unsigned int a_destinationTypeIndex, unsigned int a_sourceTypeIndex);
*/
      Variant& operator=(const Variant& a_variant);

      template <typename Ty>
      Variant& operator=(const Ty& a_value);

      void set(const Variant& a_variant);

      template <typename Ty>
      void set(const Ty& a_value);

      void set(unsigned int a_typeIndex, const void* a_sourceData, unsigned int a_sourceTypeIndex = 0, ConvertOptions* a_options = 0, ConvertFunction a_convertFunction = 0);

      void clear();

      unsigned int typeIndex() const;

      void* ptr();

      const void* ptr() const;

      inline bool empty() const { return ptr() == 0; }

      template <typename TResult>
      typename std::remove_const< typename std::remove_reference<TResult>::type >::type& convert();

      template <typename TResult>
      TResult as() const;

      template <typename TResult>
      TResult get() const;

      template <typename TType>
      bool is() const;

    private:
      void _destroy();

      void _clone(const Variant& a_variant);

      template <typename Ty>
      void _set(const Ty& a_value);

      void _set(unsigned int a_typeIndex, const void* a_sourceData, unsigned int a_sourceTypeIndex = 0, ConvertOptions* a_options = 0, ConvertFunction a_convertFunction = 0);

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

  #ifdef FCF_BASIS_IMPLEMENTATION
    Variant::Variant(unsigned int a_typeIndex, const void* a_sourceData, unsigned int a_sourceTypeIndex, ConvertOptions* a_convertOptions, ConvertFunction a_convertFunction) {
      _set(a_typeIndex, a_sourceData, a_sourceTypeIndex, a_convertOptions, a_convertFunction);
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
/*
  template <typename TDestinationType, typename TSourceType>
  Variant::convert_function_type Variant::getConverter(){
    return static_cast<ConvertFunction>(::fcf::convert<TDestinationType, TSourceType>);
      Details::Basis::Convert::ConvertIndex ci{ Type<TSourceType>().index(), Type<TDestinationType>().index()};
      auto it = fcf::Details::Basis::Convert::getStorage().functions.find(ci);
      if (it == fcf::Details::Basis::Convert::getStorage().functions.end()){
        return 0;
      }
      return (convert_function_type)it->second;
  }

  #ifdef FCF_BASIS_IMPLEMENTATION
    Variant::convert_function_type Variant::getConverter(unsigned int a_destinationTypeIndex, unsigned int a_sourceTypeIndex){
      Details::Basis::Convert::ConvertIndex ci{ a_sourceTypeIndex, a_destinationTypeIndex};
      auto it = fcf::Details::Basis::Convert::getStorage().functions.find(ci);
      if (it == fcf::Details::Basis::Convert::getStorage().functions.end()){
        return 0;
      }
      return (convert_function_type)it->second;
    }
  #endif // #ifdef FCF_BASIS_IMPLEMENTATION
*/
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
    void Variant::set(const Variant& a_variant) 
    {
      _destroy();
      _ptr = 0;
      _index = 0;
      _clone(a_variant);
    }
  #endif // #ifdef FCF_BASIS_IMPLEMENTATION

  template <typename Ty>
  void Variant::set(const Ty& a_value)
  {
    _destroy();
    _ptr = 0;
    _index = 0;
    _set(a_value);
  }

  #ifdef FCF_BASIS_IMPLEMENTATION
    void Variant::set(unsigned int a_typeIndex, const void* a_sourceData, unsigned int a_sourceTypeIndex, ConvertOptions* a_convertOptions, ConvertFunction a_convertFunction){
      _destroy();
      _ptr = 0;
      _index = 0;
      _set(a_typeIndex, a_sourceData, a_sourceTypeIndex, a_convertOptions, a_convertFunction);
    }
  #endif // #ifdef FCF_BASIS_IMPLEMENTATION

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
      result_type result;
      convertRuntimeByDestination(&result, ptr(), typeIndex());
      *this = result;
      return *(result_type*)ptr();
    }
  }

  template <typename TResult>
  TResult Variant::as() const{
    if (typeIndex() == Type<TResult>().index()){
      return *(TResult*)ptr();
    } else {
      TResult result;
      convertRuntimeByDestination(&result, ptr(), typeIndex());
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

  template <typename TType>
  bool Variant::is() const{
    return typeIndex() == Type<TType>().index();
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

  #ifdef FCF_BASIS_IMPLEMENTATION
    void Variant::_set(unsigned int a_typeIndex, const void* a_sourceData, unsigned int a_sourceTypeIndex, ConvertOptions* a_convertOptions, ConvertFunction a_convertFunction) {
      a_typeIndex = a_typeIndex & ~0x0e000000;
      a_sourceTypeIndex = a_sourceTypeIndex & ~0x0e000000;
      if (a_sourceTypeIndex == a_typeIndex){
        a_sourceTypeIndex = 0;
      }
      ::fcf::Details::Basis::Variant::NobodyWrapperStorage::iterator wrapperIt = ::fcf::Details::Basis::Variant::getStorage().find(a_typeIndex);
      if (wrapperIt == ::fcf::Details::Basis::Variant::getStorage().end()) {
        throw std::runtime_error("The specified type index is not registered for the object variant");
      }
      size_t wsize = wrapperIt->second->size();
      if (wsize > innerBufferSize) {
        if (a_sourceData && !(!!a_sourceTypeIndex || !!a_convertFunction)) {
          _ptr = wrapperIt->second->clone(a_sourceData);
        } else {
          _ptr = wrapperIt->second->create();
        }
      } else {
        if (a_sourceData && !(!!a_sourceTypeIndex || !!a_convertFunction)) {
          _ptr = wrapperIt->second->clone(&_mem[0], a_sourceData);
        } else {
          _ptr = wrapperIt->second->create(&_mem[0]);
        }
      }
      _index = a_typeIndex;

      if (a_sourceTypeIndex || !a_convertFunction){
        convertRuntime(ptr(), a_typeIndex, a_sourceData, a_sourceTypeIndex, a_convertOptions);
      } else if (a_convertFunction){
        a_convertFunction(ptr(), a_sourceData, a_convertOptions);
      }
    }
  #endif // #ifdef FCF_BASIS_IMPLEMENTATION

  template <>
  struct Type<Variant, RawDataSpecificator> {
    enum { enable = true };
    const void* operator()(const Variant* a_value = 0, unsigned int* a_type = 0, bool* a_invariantType = 0, bool* a_mayBeUnintialized = 0){
      if (a_invariantType){
        *a_invariantType = true;
      }
      if (a_mayBeUnintialized){
        *a_mayBeUnintialized = true;
      }
      if (a_value) {
        if (a_type) {
          *a_type = a_value->typeIndex();
        }
        return a_value->ptr();
      } else {
        return 0;
      }
    }
  };

} // fcf namespace


#endif // #ifndef ___FCF_BASIS__VARIANT_HPP___

