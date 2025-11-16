#ifndef ___FCF_BASIS__VARIANT_HPP___
#define ___FCF_BASIS__VARIANT_HPP___

#include <string>
#include <map>
#include <stdexcept>
#include "macro.hpp"
#include "bits/PartConvert/convertRuntime.hpp"
#include "bits/PartVariant/VariantPredefinition.hpp"
#include "bits/PartVariant/NDetails/VariantAllocator.hpp"
#include "bits/PartType/DynamicType.hpp"

namespace fcf {

  template <size_t innerBufferSize>
  class BasicVariant {
    public:

      template <size_t InputInnerBufferSize>
      friend class BasicVariant;

      typedef void (*convert_function_type)(void*, const void*);

      BasicVariant();

      BasicVariant(const BasicVariant& a_variant);

      template <size_t InputInnerBufferSize>
      BasicVariant(const BasicVariant<InputInnerBufferSize>& a_variant);

      template <typename Ty>
      BasicVariant(const Ty& a_value);

      BasicVariant(DynamicType a_dynamicType);

      template <typename Ty>
      BasicVariant(Type<Ty, Nop> a_type);

      BasicVariant(unsigned int a_typeIndex, const void* a_sourceData, unsigned int a_sourceTypeIndex = 0, ConvertOptions* a_options = 0, ConvertFunction a_convertFunction = 0);

      ~BasicVariant();

      void reset(DynamicType a_dynamicType);

      template <typename Ty>
      void reset(Type<Ty, Nop> a_dynamicType);

      BasicVariant& operator=(const BasicVariant& a_variant);

      template <size_t InputInnerBufferSize>
      BasicVariant& operator=(const BasicVariant<InputInnerBufferSize>& a_variant);

      template <typename Ty>
      BasicVariant& operator=(const Ty& a_value);

      void set(const BasicVariant& a_variant);

      template <typename Ty>
      void set(const Ty& a_value);

      void set(unsigned int a_typeIndex, const void* a_sourceData, unsigned int a_sourceTypeIndex = 0, ConvertOptions* a_options = 0, ConvertFunction a_convertFunction = 0);

      void clear();



      bool operator<(const BasicVariant& a_value) const;

      template <typename Ty>
      bool operator<(const Ty& a_value) const;

      bool operator<(const char* a_value) const;



      bool operator<=(const BasicVariant& a_value) const;

      template <typename Ty>
      bool operator<=(const Ty& a_value) const;

      bool operator<=(const char* a_value) const;



      bool operator==(const BasicVariant& a_value) const;

      template <typename Ty>
      bool operator==(const Ty& a_value) const;

      bool operator==(const char* a_value) const;



      bool operator!=(const BasicVariant& a_value) const;

      template <typename Ty>
      bool operator!=(const Ty& a_value) const;

      bool operator!=(const char* a_value) const;



      bool operator>(const BasicVariant& a_value) const;

      template <typename Ty>
      bool operator>(const Ty& a_value) const;

      bool operator>(const char* a_value) const;



      bool operator>=(const BasicVariant& a_value) const;

      template <typename Ty>
      bool operator>=(const Ty& a_value) const;

      bool operator>=(const char* a_value) const;


      BasicVariant& operator+=(const BasicVariant& a_value);

      template <typename Ty>
      BasicVariant& operator+=(const Ty&& a_value);

      BasicVariant operator+(const BasicVariant& a_value);

      template <typename Ty>
      BasicVariant operator+(const Ty&& a_value);

      BasicVariant& operator-=(const BasicVariant& a_value);

      template <typename Ty>
      BasicVariant& operator-=(const Ty&& a_value);

      BasicVariant operator-(const BasicVariant& a_value);

      template <typename Ty>
      BasicVariant operator-(const Ty&& a_value);

      unsigned int typeIndex() const;

      void* ptr();

      const void* ptr() const;

      inline bool empty() const { return ptr() == 0; }

      template <typename TResult>
      typename std::remove_const< typename std::remove_reference<TResult>::type >::type& as();

      template <typename TResult>
      typename std::remove_const< typename std::remove_reference<TResult>::type >::type& get();

      template <typename TResult>
      TResult cast() const;

      template <typename TResult>
      TResult strict_cast() const;

      template <typename TType>
      bool is() const;

    private:
      void _destroy();

      template <size_t InputInnerBufferSize>
      void _clone(const BasicVariant<InputInnerBufferSize>& a_variant);

      void _clone(const BasicVariant& a_variant);

      template <typename Ty>
      void _set(const Ty& a_value);

      void _set(unsigned int a_typeIndex, const void* a_sourceData, unsigned int a_sourceTypeIndex = 0, ConvertOptions* a_options = 0, ConvertFunction a_convertFunction = 0);

      template <typename Ty>
      bool _less(const Ty& a_value) const;

      template <typename Ty>
      bool _lessEqual(const Ty& a_value) const;

      template <typename Ty>
      bool _equal(const Ty& a_value) const;

      char            _mem[innerBufferSize];
      const TypeInfo* _typeInfo;
      void*           _ptr;
  };

} // fcf namespace

#include "Type.hpp"
#include "bits/registry.hpp"
#include "bits/PartSpecificator/StoredDataTypeSpecificator.hpp"
#include "bits/PartSpecificator/LessSpecificator.hpp"
#include "bits/PartSpecificator/EqualSpecificator.hpp"
#include "bits/PartSpecificator/AddToSpecificator.hpp"
#include "bits/PartSpecificator/SubToSpecificator.hpp"



namespace fcf{

  template <size_t innerBufferSize>
  std::ostream& operator<<(std::ostream& a_stream, const BasicVariant<innerBufferSize>& a_variant){
    a_stream << a_variant. template cast<std::string>();
    return a_stream;
  }

  template <size_t innerBufferSize>
  BasicVariant<innerBufferSize>::BasicVariant()
    : _typeInfo(0)
    , _ptr(0) {
  }

  template <size_t innerBufferSize>
  BasicVariant<innerBufferSize>::BasicVariant(unsigned int a_typeIndex, const void* a_sourceData, unsigned int a_sourceTypeIndex, ConvertOptions* a_convertOptions, ConvertFunction a_convertFunction) {
    _set(a_typeIndex, a_sourceData, a_sourceTypeIndex, a_convertOptions, a_convertFunction);
  }

  template <size_t innerBufferSize>
  template <size_t InputInnerBufferSize>
  BasicVariant<innerBufferSize>::BasicVariant(const BasicVariant<InputInnerBufferSize>& a_variant) {
    _clone(a_variant);
  }

  template <size_t innerBufferSize>
  BasicVariant<innerBufferSize>::BasicVariant(const BasicVariant& a_variant) {
    _clone(a_variant);
  }

  template <size_t innerBufferSize>
  template <typename Ty>
  BasicVariant<innerBufferSize>::BasicVariant(const Ty& a_value) {
    _set(a_value);
  }

  template <size_t innerBufferSize>
  BasicVariant<innerBufferSize>::BasicVariant(DynamicType a_dynamicType){
    const unsigned int index = a_dynamicType.index();
    if (!index){
      _typeInfo = 0;
      _ptr = 0;
      return;
    }
    _ptr = a_dynamicType.getTypeInfo()->initializer->create();
    _typeInfo = a_dynamicType.getTypeInfo();
  }

  template <size_t innerBufferSize>
  template <typename Ty>
  BasicVariant<innerBufferSize>::BasicVariant(Type<Ty, Nop> a_type){
    const unsigned int index = a_type.index();
    if (!index){
      _typeInfo = 0;
      _ptr = 0;
      return;
    }
    _ptr   = a_type.getTypeInfo()->initializer->create();
    _typeInfo = a_type.getTypeInfo();
  }


  template <size_t innerBufferSize>
  BasicVariant<innerBufferSize>::~BasicVariant(){
    _destroy();
  }
/*
  template <typename TDestinationType, typename TSourceType>
  BasicVariant::convert_function_type BasicVariant::getConverter(){
    return static_cast<ConvertFunction>(::fcf::convert<TDestinationType, TSourceType>);
      Details::Basis::Convert::ConvertIndex ci{ Type<TSourceType>().index(), Type<TDestinationType>().index()};
      auto it = fcf::Details::Basis::Convert::getStorage().functions.find(ci);
      if (it == fcf::Details::Basis::Convert::getStorage().functions.end()){
        return 0;
      }
      return (convert_function_type)it->second;
  }

  #ifdef FCF_BASIS_IMPLEMENTATION
    BasicVariant::convert_function_type BasicVariant::getConverter(unsigned int a_destinationTypeIndex, unsigned int a_sourceTypeIndex){
      Details::Basis::Convert::ConvertIndex ci{ a_sourceTypeIndex, a_destinationTypeIndex};
      auto it = fcf::Details::Basis::Convert::getStorage().functions.find(ci);
      if (it == fcf::Details::Basis::Convert::getStorage().functions.end()){
        return 0;
      }
      return (convert_function_type)it->second;
    }
  #endif // #ifdef FCF_BASIS_IMPLEMENTATION
*/

  template <size_t innerBufferSize>
  void BasicVariant<innerBufferSize>::reset(DynamicType a_dynamicType)
  {
    _destroy();
    _ptr = 0;
    _typeInfo = 0;

    const unsigned int index = a_dynamicType.index();
    if (!index){
      return;
    }

    _ptr = a_dynamicType.getTypeInfo()->initializer->create();
    _typeInfo = a_dynamicType.getTypeInfo();
  }

  template <size_t innerBufferSize>
  template <typename Ty>
  void BasicVariant<innerBufferSize>::reset(Type<Ty, Nop> a_type)
  {
    _destroy();
    _ptr = 0;
    _typeInfo = 0;

    const unsigned int index = a_type.index();
    if (!index){
      return;
    }

    _ptr = a_type.getTypeInfo()->initializer->create();
    _typeInfo = a_type.getTypeInfo();
  }

  template <size_t innerBufferSize>
  BasicVariant<innerBufferSize>& BasicVariant<innerBufferSize>::operator=(const BasicVariant<innerBufferSize>& a_variant)
  {
    _destroy();
    _ptr = 0;
    _typeInfo = 0;
    _clone(a_variant);
    return *this;
  }

  template <size_t innerBufferSize>
  template <size_t InputInnerBufferSize>
  BasicVariant<innerBufferSize>& BasicVariant<innerBufferSize>::operator=(const BasicVariant<InputInnerBufferSize>& a_variant)
  {
    _destroy();
    _ptr = 0;
    _typeInfo = 0;
    _clone(a_variant);
    return *this;
  }

  template <size_t innerBufferSize>
  template <typename Ty>
  BasicVariant<innerBufferSize>& BasicVariant<innerBufferSize>::operator=(const Ty& a_value)
  {
    _destroy();
    _ptr = 0;
    _typeInfo = 0;
    _set(a_value);
    return *this;
  }

  template <size_t innerBufferSize>
  void BasicVariant<innerBufferSize>::set(const BasicVariant<innerBufferSize>& a_variant)
  {
    _destroy();
    _ptr = 0;
    _typeInfo = 0;
    _clone(a_variant);
  }

  template <size_t innerBufferSize>
  template <typename Ty>
  void BasicVariant<innerBufferSize>::set(const Ty& a_value)
  {
    _destroy();
    _ptr = 0;
    _typeInfo = 0;
    _set(a_value);
  }

  template <size_t innerBufferSize>
  void BasicVariant<innerBufferSize>::set(unsigned int a_typeIndex, const void* a_sourceData, unsigned int a_sourceTypeIndex, ConvertOptions* a_convertOptions, ConvertFunction a_convertFunction){
    _destroy();
    _ptr = 0;
    _typeInfo = 0;
    _set(a_typeIndex, a_sourceData, a_sourceTypeIndex, a_convertOptions, a_convertFunction);
  }

  template <size_t innerBufferSize>
  void BasicVariant<innerBufferSize>::clear() {
    _destroy();
    _ptr = 0;
    _typeInfo = 0;
  }

  template <size_t innerBufferSize>
  bool BasicVariant<innerBufferSize>::operator<(const BasicVariant<innerBufferSize>& a_value) const {
    if (!a_value._typeInfo) {
      return false;
    } else if (_typeInfo == a_value._typeInfo) {
      return _typeInfo->getSafeSpecificatorCall<LessSpecificator>()(ptr(), a_value.ptr());
    } else if (!_typeInfo) {
      return true;
    } else {
      try {
        Variant buffer(_typeInfo->index, a_value.ptr(), a_value._typeInfo->index);
        return _typeInfo->getSafeSpecificatorCall<LessSpecificator>()(ptr(), buffer.ptr());
      } catch(...) {
        return _typeInfo->index < a_value._typeInfo->index;
      }
    }
  }

  template <size_t innerBufferSize>
  template <typename Ty>
  bool BasicVariant<innerBufferSize>::operator<(const Ty& a_value) const {
    return _less(a_value);
  }

  template <size_t innerBufferSize>
  bool BasicVariant<innerBufferSize>::operator<(const char* a_value) const {
    return _less(a_value);
  }

  template <size_t innerBufferSize>
  bool BasicVariant<innerBufferSize>::operator<=(const BasicVariant<innerBufferSize>& a_value) const {
    if (!_typeInfo) {
      return true;
    } else if (_typeInfo == a_value._typeInfo) {
      bool res = _typeInfo->getSafeSpecificatorCall<LessSpecificator>()(ptr(), a_value.ptr());
      if (res) {
        return true;
      }
      return _typeInfo->getSafeSpecificatorCall<EqualSpecificator>()(ptr(), a_value.ptr());
    } else if (!a_value._typeInfo) {
      return false;
    } else {
      try {
        Variant buffer(_typeInfo->index, a_value.ptr(), a_value._typeInfo->index);
        bool res = _typeInfo->getSafeSpecificatorCall<LessSpecificator>()(ptr(), buffer.ptr());
        if (res) {
          return true;
        }
        return _typeInfo->getSafeSpecificatorCall<EqualSpecificator>()(ptr(), buffer.ptr());
      } catch(...) {
        return _typeInfo->index < a_value._typeInfo->index;
      }
    }
  }

  template <size_t innerBufferSize>
  template <typename Ty>
  bool BasicVariant<innerBufferSize>::operator<=(const Ty& a_value) const {
    return _lessEqual(a_value);
  }

  template <size_t innerBufferSize>
  bool BasicVariant<innerBufferSize>::operator<=(const char* a_value) const {
    return _lessEqual(a_value);
  }

  template <size_t innerBufferSize>
  bool BasicVariant<innerBufferSize>::operator==(const BasicVariant<innerBufferSize>& a_value) const {
    if (!a_value._typeInfo) {
      return !_typeInfo;
    } else if (_typeInfo == a_value._typeInfo) {
      return _typeInfo->getSafeSpecificatorCall<EqualSpecificator>()(ptr(), a_value.ptr());
    } else if (!_typeInfo) {
      return false;
    } else {
      try {
        Variant buffer(_typeInfo->index, a_value.ptr(), a_value._typeInfo->index);
        return _typeInfo->getSafeSpecificatorCall<EqualSpecificator>()(ptr(), buffer.ptr());
      } catch(...) {
        return false;
      }
    }
  }

  template <size_t innerBufferSize>
  template <typename Ty>
  bool BasicVariant<innerBufferSize>::operator==(const Ty& a_value) const{
    return _equal(a_value);
  }

  template <size_t innerBufferSize>
  bool BasicVariant<innerBufferSize>::operator==(const char* a_value) const{
    return _equal(a_value);
  }

  template <size_t innerBufferSize>
  bool BasicVariant<innerBufferSize>::operator!=(const BasicVariant<innerBufferSize>& a_value) const {
    return !((*this) == a_value);
  }

  template <size_t innerBufferSize>
  template <typename Ty>
  bool BasicVariant<innerBufferSize>::operator!=(const Ty& a_value) const {
    return !((*this) == a_value);
  }

  template <size_t innerBufferSize>
  bool BasicVariant<innerBufferSize>::operator!=(const char* a_value) const {
    return !((*this) == a_value);
  }

  template <size_t innerBufferSize>
  bool BasicVariant<innerBufferSize>::operator>(const BasicVariant<innerBufferSize>& a_value) const {
    return !((*this) <= a_value);
  }

  template <size_t innerBufferSize>
  template <typename Ty>
  bool BasicVariant<innerBufferSize>::operator>(const Ty& a_value) const {
    return !((*this) <= a_value);
  }

  template <size_t innerBufferSize>
  bool BasicVariant<innerBufferSize>::operator>(const char* a_value) const {
    return !((*this) <= a_value);
  }

  template <size_t innerBufferSize>
  bool BasicVariant<innerBufferSize>::operator>=(const BasicVariant<innerBufferSize>& a_value) const {
    return !((*this) < a_value);
  }

  template <size_t innerBufferSize>
  template <typename Ty>
  bool BasicVariant<innerBufferSize>::operator>=(const Ty& a_value) const{
    return !((*this) < a_value);
  }

  template <size_t innerBufferSize>
  bool BasicVariant<innerBufferSize>::operator>=(const char* a_value) const{
    return !((*this) < a_value);
  }

  template <size_t innerBufferSize>
  BasicVariant<innerBufferSize>& BasicVariant<innerBufferSize>::operator+=(const BasicVariant<innerBufferSize>& a_value){
    if (!_typeInfo || !a_value._typeInfo) {
      return *this;
    } else if (_typeInfo == a_value._typeInfo) {
      _typeInfo->getSafeSpecificatorCall<AddToSpecificator>()(ptr(), a_value.ptr());
    } else {
      try {
        Variant buffer(_typeInfo->index, a_value.ptr(), a_value._typeInfo->index);
        _typeInfo->getSafeSpecificatorCall<AddToSpecificator>()(ptr(), buffer.ptr());
      } catch(...){
      }
    }
    return *this;
  }

  template <size_t innerBufferSize>
  template <typename Ty>
  BasicVariant<innerBufferSize>& BasicVariant<innerBufferSize>::operator+=(const Ty&& a_value){
    if (!_typeInfo) {
      return *this;
    }

    typedef typename std::remove_reference<Ty>::type ArgType;

    unsigned int argTypeIndex = Type<ArgType>().index();
    if (_typeInfo->index == argTypeIndex) {
      _typeInfo->getSafeSpecificatorCall<AddToSpecificator>()(ptr(), &a_value);
      return *this;
    }

    try {
      Variant buffer(_typeInfo->index, &a_value, argTypeIndex);
      _typeInfo->getSafeSpecificatorCall<AddToSpecificator>()(ptr(), buffer.ptr());
    } catch(...) {
    }

    return *this;
  }

  template <size_t innerBufferSize>
  BasicVariant<innerBufferSize> BasicVariant<innerBufferSize>::operator+(const BasicVariant<innerBufferSize>& a_value){
    BasicVariant<innerBufferSize> result(*this);
    result += a_value;
    return result;
  }

  template <size_t innerBufferSize>
  template <typename Ty>
  BasicVariant<innerBufferSize> BasicVariant<innerBufferSize>::operator+(const Ty&& a_value){
    return BasicVariant<innerBufferSize>(*this) += a_value;
  }

  template <size_t innerBufferSize>
  BasicVariant<innerBufferSize>& BasicVariant<innerBufferSize>::operator-=(const BasicVariant<innerBufferSize>& a_value){
    if (!_typeInfo || !a_value._typeInfo) {
      return *this;
    } else if (_typeInfo == a_value._typeInfo) {
      _typeInfo->getSafeSpecificatorCall<SubToSpecificator>()(ptr(), a_value.ptr());
    } else {
      try {
        Variant buffer(_typeInfo->index, a_value.ptr(), a_value._typeInfo->index);
        _typeInfo->getSafeSpecificatorCall<SubToSpecificator>()(ptr(), buffer.ptr());
      } catch(...) {
      }
    }
    return *this;
  }

  template <size_t innerBufferSize>
  template <typename Ty>
  BasicVariant<innerBufferSize>& BasicVariant<innerBufferSize>::operator-=(const Ty&& a_value){
    if (!_typeInfo) {
      return *this;
    }

    typedef typename std::remove_reference<Ty>::type ArgType;

    unsigned int argTypeIndex = Type<ArgType>().index();
    if (_typeInfo->index == argTypeIndex) {
      _typeInfo->getSafeSpecificatorCall<SubToSpecificator>()(ptr(), &a_value);
      return *this;
    }

    try {
      Variant buffer(_typeInfo->index, &a_value, argTypeIndex);
      _typeInfo->getSafeSpecificatorCall<SubToSpecificator>()(ptr(), buffer.ptr());
    } catch(...) {
    }

    return *this;
  }


  template <size_t innerBufferSize>
  BasicVariant<innerBufferSize> BasicVariant<innerBufferSize>::operator-(const BasicVariant<innerBufferSize>& a_value){
    return BasicVariant<innerBufferSize>(*this) -= a_value;
  }


  template <size_t innerBufferSize>
  template <typename Ty>
  BasicVariant<innerBufferSize> BasicVariant<innerBufferSize>::operator-(const Ty&& a_value){
    return BasicVariant<innerBufferSize>(*this) -= a_value;
  }


  template <size_t innerBufferSize>
  unsigned int BasicVariant<innerBufferSize>::typeIndex() const{
    return _typeInfo ? _typeInfo->index : 0;
  }

  template <size_t innerBufferSize>
  void* BasicVariant<innerBufferSize>::ptr(){
    return _ptr ? &((TypeWrapper<int>*)_ptr)->data : 0;
  }

  template <size_t innerBufferSize>
  const void* BasicVariant<innerBufferSize>::ptr() const{
    return _ptr ? &((TypeWrapper<int>*)_ptr)->data : 0;
  }

  template <size_t innerBufferSize>
  template <typename TResult>
  typename std::remove_const< typename std::remove_reference<TResult>::type >::type& BasicVariant<innerBufferSize>::as() {
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

  template <size_t innerBufferSize>
  template <typename TResult>
  typename std::remove_const< typename std::remove_reference<TResult>::type >::type& BasicVariant<innerBufferSize>::get() {
    typedef typename std::remove_const< typename std::remove_reference<TResult>::type >::type result_type;
    if (typeIndex() != Type<TResult>().index()){
      throw std::runtime_error(std::string() + "The type saved in the variant is not '" + Type<TResult>().name() + "' type");
    } else {
      return *(result_type*)ptr();
    }
  }

  template <size_t innerBufferSize>
  template <typename TResult>
  TResult BasicVariant<innerBufferSize>::cast() const{
    if (typeIndex() == Type<TResult>().index()){
      return *(TResult*)ptr();
    } else {
      TResult result;
      convertRuntimeByDestination(&result, ptr(), typeIndex());
      return result;
    }
  }

  template <size_t innerBufferSize>
  template <typename TResult>
  TResult BasicVariant<innerBufferSize>::strict_cast() const{
    if (typeIndex() != Type<TResult>().index()){
      throw std::runtime_error(std::string() + "The type saved in the variant is not '" + Type<TResult>().name() + "' type");
    }
    return *(TResult*)ptr();
  }


  template <size_t innerBufferSize>
  template <typename TType>
  bool BasicVariant<innerBufferSize>::is() const{
    return typeIndex() == Type<TType>().index();
  }

  template <size_t innerBufferSize>
  void BasicVariant<innerBufferSize>::_destroy(){
    if (_ptr == &_mem[0]){
      ((BaseTypeWrapper*)_ptr)->~BaseTypeWrapper();
    } else if (_ptr) {
      delete (BaseTypeWrapper*)_ptr;
    }
  }

  template <size_t innerBufferSize>
  void BasicVariant<innerBufferSize>::_clone(const BasicVariant& a_variant) {
    if (a_variant._ptr) {
      BaseTypeWrapper* wrp = (BaseTypeWrapper*)a_variant._ptr;
      if (a_variant._ptr == &a_variant._mem[0]){
        _ptr = wrp->clone(&_mem[0]);
      } else {
        _ptr = wrp->clone();
      }
      _typeInfo = a_variant._typeInfo;
    } else {
      _ptr = 0;
      _typeInfo = 0;
    }
  }

  template <size_t innerBufferSize>
  template <size_t InputInnerBufferSize>
  void BasicVariant<innerBufferSize>::_clone(const BasicVariant<InputInnerBufferSize>& a_variant) {
    if (a_variant._ptr) {
      BaseTypeWrapper* wrp = (BaseTypeWrapper*)a_variant._ptr;
      if (wrp->size() <= innerBufferSize){
        _ptr = wrp->clone(&_mem[0]);
      } else {
        _ptr = wrp->clone();
      }
      _typeInfo = a_variant._typeInfo;
    } else {
      _ptr = 0;
      _typeInfo = 0;
    }
  }

  template <size_t innerBufferSize>
  template <typename Ty>
  void BasicVariant<innerBufferSize>::_set(const Ty& a_value) {
    typedef typename Type<Ty, StoredDataTypeSpecificator>::type type;
    _ptr = NDetails::VariantAllocator<type, innerBufferSize>()(&_mem[0], a_value);
    /*
    if (sizeof(Details::Basis::Variant::Wrapper<type>) > innerBufferSize){
      _ptr = new Details::Basis::Variant::Wrapper<type>(a_value);
    } else {
      new (&_mem[0]) Details::Basis::Variant::Wrapper<type>(a_value);
      _ptr = &_mem[0];
    }
    */
    _typeInfo = Type<type>().getTypeInfo();
  }

  template <size_t innerBufferSize>
  void BasicVariant<innerBufferSize>::_set(unsigned int a_typeIndex, const void* a_sourceData, unsigned int a_sourceTypeIndex, ConvertOptions* a_convertOptions, ConvertFunction a_convertFunction) {
    a_typeIndex = a_typeIndex & ~0x0e000000;
    a_sourceTypeIndex = a_sourceTypeIndex & ~0x0e000000;
    if (a_sourceTypeIndex == a_typeIndex){
      a_sourceTypeIndex = 0;
    }
    DynamicType dt(a_typeIndex);
    const TypeInfo* ti = dt.getTypeInfo();
    size_t wsize = ti->initializer->size();
    if (wsize > innerBufferSize) {
      if (a_sourceData && !a_sourceTypeIndex && !a_convertFunction) {
        _ptr = dt.getTypeInfo()->initializer->clone(a_sourceData);
      } else {
        _ptr = dt.getTypeInfo()->initializer->create();
      }
    } else {
      if (a_sourceData && !a_sourceTypeIndex && !a_convertFunction) {
        _ptr = dt.getTypeInfo()->initializer->clone(&_mem[0], a_sourceData);
      } else {
        _ptr = dt.getTypeInfo()->initializer->create(&_mem[0]);
      }
    }
    _typeInfo = ti;

    if (a_sourceTypeIndex && !a_convertFunction){
      convertRuntime(ptr(), a_typeIndex, a_sourceData, a_sourceTypeIndex, a_convertOptions);
    } else if (a_convertFunction){
      a_convertFunction(ptr(), a_sourceData, a_convertOptions);
    }
  }

  template <size_t innerBufferSize>
  template <typename Ty>
  bool BasicVariant<innerBufferSize>::_less(const Ty& a_value) const{
    if (!_typeInfo) {
      return true;
    }

    typedef typename std::remove_reference<Ty>::type ArgType;

    unsigned int argTypeIndex = Type<ArgType>().index();
    if (_typeInfo->index == argTypeIndex) {
      return _typeInfo->getSafeSpecificatorCall<LessSpecificator>()(ptr(), &a_value);
    } else {
      try {
        Variant buffer(_typeInfo->index, &a_value, argTypeIndex);
        return _typeInfo->getSafeSpecificatorCall<LessSpecificator>()(ptr(), buffer.ptr());
      } catch(...) {
        return _typeInfo->index < argTypeIndex;
      }
    }
  }



  template <size_t innerBufferSize>
  template <typename Ty>
  bool BasicVariant<innerBufferSize>::_lessEqual(const Ty& a_value) const {
    if (!_typeInfo) {
      return true;
    }

    typedef typename std::remove_reference<Ty>::type ArgType;

    unsigned int argTypeIndex = Type<ArgType>().index();
    if (_typeInfo->index == argTypeIndex) {
      bool res = _typeInfo->getSafeSpecificatorCall<LessSpecificator>()(ptr(), &a_value);
      if (res) {
        return true;
      }
      return _typeInfo->getSafeSpecificatorCall<EqualSpecificator>()(ptr(), &a_value);
    } else {
      try {
        Variant buffer(_typeInfo->index, &a_value, argTypeIndex);
        bool res = _typeInfo->getSafeSpecificatorCall<LessSpecificator>()(ptr(), buffer.ptr());
        if (res) {
          return true;
        }
        return _typeInfo->getSafeSpecificatorCall<EqualSpecificator>()(ptr(), buffer.ptr());
      } catch(...) {
        return _typeInfo->index < argTypeIndex;
      }
    }
  }

  template <size_t innerBufferSize>
  template <typename Ty>
  bool BasicVariant<innerBufferSize>::_equal(const Ty& a_value) const {
    if (!_typeInfo) {
      return false;
    }

    typedef typename std::remove_reference<Ty>::type ArgType;

    unsigned int argTypeIndex = Type<ArgType>().index();
    if (_typeInfo->index == argTypeIndex) {
      return _typeInfo->getSafeSpecificatorCall<EqualSpecificator>()(ptr(), &a_value);
    }

    try {
      Variant buffer(_typeInfo->index, &a_value, argTypeIndex);
      return _typeInfo->getSafeSpecificatorCall<EqualSpecificator>()(ptr(), buffer.ptr());
    } catch(...) {
    }

    return false;
  }

}  // fcf namespace

#include "bits/PartSpecificator/ResolveSpecificator.hpp"

namespace fcf {

  template <size_t innerBufferSize>
  struct Type<BasicVariant<innerBufferSize>, ResolveSpecificator> : public TypeImpl<BasicVariant<innerBufferSize>, ResolveSpecificator>{
    inline ResolveData call(BasicVariant<innerBufferSize>* a_object){
      if (a_object) {
        return ResolveData{a_object->ptr(), a_object->typeIndex(), true};
      } else {
        return ResolveData{0, 0, true};
      }
    }
  };


} // fcf namespace


#endif // #ifndef ___FCF_BASIS__VARIANT_HPP___
