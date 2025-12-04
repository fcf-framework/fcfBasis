#ifndef ___FCF_BASIS__VARIANT_HPP___
#define ___FCF_BASIS__VARIANT_HPP___

#include "bits/PartVariant/VariantDefinition.hpp"

#include "Type.hpp"
#include "bits/registry.hpp"
#include "bits/PartConvert/convertRuntime.hpp"
#include "bits/PartSpecificator/StoredDataTypeSpecificator.hpp"
#include "bits/PartSpecificator/LessSpecificator.hpp"
#include "bits/PartSpecificator/EqualSpecificator.hpp"
#include "bits/PartSpecificator/AddSpecificator.hpp"
#include "bits/PartSpecificator/SubSpecificator.hpp"
#include "bits/PartSpecificator/MulSpecificator.hpp"
#include "bits/PartSpecificator/DivSpecificator.hpp"
#include "bits/PartSpecificator/BoolSpecificator.hpp"
#include "bits/PartSpecificator/ContainerAccessSpecificator.hpp"
#include "bits/PartVariant/NDetails/VariantAllocator.hpp"
#include "bits/PartContainerAccess/VariantCursor.hpp"


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
  BasicVariant<innerBufferSize>::BasicVariant(unsigned int a_typeIndex, const void* a_sourceData, unsigned int a_sourceTypeIndex, ConvertOptions* a_convertOptions, ConvertFunction a_convertFunction)
  : _typeInfo(0) {
    _set(a_typeIndex, a_sourceData, a_sourceTypeIndex, a_convertOptions, a_convertFunction);
  }

  template <size_t innerBufferSize>
  template <size_t InputInnerBufferSize>
  BasicVariant<innerBufferSize>::BasicVariant(const BasicVariant<InputInnerBufferSize>& a_variant)
    : _typeInfo(0) {
    _clone(a_variant, RESET);
  }

  template <size_t innerBufferSize>
  template <size_t InputInnerBufferSize>
  BasicVariant<innerBufferSize>::BasicVariant(BasicVariant<InputInnerBufferSize>& a_variant)
    : _typeInfo(0) {
    _clone(a_variant, RESET);
  }

  template <size_t innerBufferSize>
  template <size_t InputInnerBufferSize>
  BasicVariant<innerBufferSize>::BasicVariant(const BasicVariant<InputInnerBufferSize>& a_variant, DataSetMode a_dataMode)
    : _typeInfo(0) {
    if (a_dataMode == FORCE_REFERENCE) {
      _set(a_variant, a_dataMode);
    } else {
      _clone(a_variant, a_dataMode);
    }
  }

  template <size_t innerBufferSize>
  template <size_t InputInnerBufferSize>
  BasicVariant<innerBufferSize>::BasicVariant(BasicVariant<InputInnerBufferSize>& a_variant, DataSetMode a_dataMode)
    : _typeInfo(0) {
    _clone(a_variant, a_dataMode);
  }

  template <size_t innerBufferSize>
  BasicVariant<innerBufferSize>::BasicVariant(const BasicVariant& a_variant)
    : _typeInfo(0) {
    _clone(a_variant, RESET);
  }

  template <size_t innerBufferSize>
  BasicVariant<innerBufferSize>::BasicVariant(const BasicVariant& a_variant, DataSetMode a_dataMode)
    : _typeInfo(0) {
    if (a_dataMode == FORCE_REFERENCE) {
      _set(a_variant, a_dataMode);
    } else {
      _clone(a_variant, a_dataMode);
    }
  }

  template <size_t innerBufferSize>
  BasicVariant<innerBufferSize>::BasicVariant(BasicVariant& a_variant, DataSetMode a_dataMode)
    : _typeInfo(0) {
    if (a_dataMode == FORCE_REFERENCE) {
      _set(a_variant, a_dataMode);
    } else {
      _clone(a_variant, a_dataMode);
    }
  }

  template <size_t innerBufferSize>
  template <typename Ty>
  BasicVariant<innerBufferSize>::BasicVariant(const Ty& a_value)
    : _typeInfo(0) {
    _set(a_value, RESET);
  }

  template <size_t innerBufferSize>
  template <typename Ty, typename TSource>
  BasicVariant<innerBufferSize>::BasicVariant(const Type<Ty>& /*a_type*/, const TSource& a_value)
    : _typeInfo(0) {
    typedef typename std::remove_reference< typename std::remove_const<Ty>::type >::type      ResType;
    typedef typename std::remove_reference< typename std::remove_const<TSource>::type >::type SrcType;
    if (std::is_same<ResType, SrcType>::value) {
      _set<Ty>(a_value, RESET);
    } else {
      Variant buffer(Type<ResType>().index(), &a_value, Type<SrcType>().index());
      _clone(buffer, RESET);
    }
  }

  template <size_t innerBufferSize>
  template <typename Ty>
  BasicVariant<innerBufferSize>::BasicVariant(const Ty& a_value, DataSetMode a_dataMode)
    : _typeInfo(0) {
    _set(a_value, a_dataMode);
  }

  template <size_t innerBufferSize>
  template <typename Ty>
  BasicVariant<innerBufferSize>::BasicVariant(Ty& a_value, DataSetMode a_dataMode)
    : _typeInfo(0) {
    _set(a_value, a_dataMode);
  }


  template <size_t innerBufferSize>
  template <typename Ty, typename TSource>
  BasicVariant<innerBufferSize>::BasicVariant(const Type<Ty>& /*a_type*/, TSource& a_value, DataSetMode a_dataMode)
    : _typeInfo(0) {
    typedef typename std::remove_reference< typename std::remove_const<Ty>::type >::type      ResType;
    typedef typename std::remove_reference< typename std::remove_const<TSource>::type >::type SrcType;
    if (std::is_same<ResType, SrcType>::value) {
      _set<Ty>(a_value, a_dataMode);
    } else {
      if (a_dataMode & (REFERENCE|FORCE_REFERENCE)) {
        throw std::runtime_error("You cannot link to an inappropriate type");
      }
      Variant buffer(Type<ResType>().index(), &a_value, Type<SrcType>().index());
      _clone(buffer, a_dataMode);
    }
  }

  template <size_t innerBufferSize>
  template <typename Ty, typename TSource>
  BasicVariant<innerBufferSize>::BasicVariant(const Type<Ty>& /*a_type*/, const TSource& a_value, DataSetMode a_dataMode)
    : _typeInfo(0) {
    typedef typename std::remove_reference< typename std::remove_const<Ty>::type >::type      ResType;
    typedef typename std::remove_reference< typename std::remove_const<TSource>::type >::type SrcType;
    if (std::is_same<ResType, SrcType>::value) {
      if (!std::is_const<Ty>::value && a_dataMode & (REFERENCE|FORCE_REFERENCE)){
        throw std::runtime_error("It is impossible to establish a non-constant reference to constant data");
      }
      _set<Ty>(a_value, a_dataMode);
    } else {
      if (a_dataMode & (REFERENCE|FORCE_REFERENCE)) {
        throw std::runtime_error("You cannot link to an inappropriate type");
      }
      Variant buffer(Type<ResType>().index(), &a_value, Type<SrcType>().index());
      _clone(buffer, a_dataMode);
    }
  }

  template <size_t innerBufferSize>
  BasicVariant<innerBufferSize>::BasicVariant(const char* a_value)
    : _typeInfo(0) {
    _set(a_value, RESET);
  }

  template <size_t innerBufferSize>
  BasicVariant<innerBufferSize>::BasicVariant(const char* a_value, DataSetMode a_dataMode)
    : _typeInfo(0) {
    _set(a_value, a_dataMode);
  }

  template <size_t innerBufferSize>
  template <typename Ty>
  BasicVariant<innerBufferSize>::BasicVariant(Type<Ty, Nop> a_type){
    size_t wrapperSize = a_type.getWrapperSize();
    if (wrapperSize <= innerBufferSize) {
      _ptr = a_type.getTypeInfo()->initializer->create(&_mem[0])->ptr();
    } else {
      _ptr = a_type.getTypeInfo()->initializer->create()->ptr();
    }
    _typeInfo = a_type.getTypeInfo();
  }

  template <size_t innerBufferSize>
  BasicVariant<innerBufferSize>::BasicVariant(DynamicType a_dynamicType){
    const unsigned int index = a_dynamicType.index();
    if (!index){
      _typeInfo = 0;
      _ptr = 0;
      return;
    }
    size_t wrapperSize = a_dynamicType.getWrapperSize();
    if (wrapperSize <= innerBufferSize) {
      _ptr = a_dynamicType.getTypeInfo()->initializer->create(&_mem[0])->ptr();
    } else {
      _ptr = a_dynamicType.getTypeInfo()->initializer->create()->ptr();
    }
    _typeInfo = a_dynamicType.getTypeInfo();
  }

  template <size_t innerBufferSize>
  BasicVariant<innerBufferSize>::BasicVariant(const TypeInfo* a_typeInfo) {
    if (!a_typeInfo) {
      _typeInfo = 0;
      _ptr = 0;
      return;
    }
    size_t wrapperSize = a_typeInfo->initializer->size();
    if (wrapperSize <= innerBufferSize) {
      _ptr = a_typeInfo->initializer->create(&_mem[0])->ptr();
    } else {
      _ptr = a_typeInfo->initializer->create()->ptr();
    }
    _typeInfo = a_typeInfo;
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

    size_t wrapperSize = a_dynamicType.getWrapperSize();
    if (wrapperSize <= innerBufferSize) {
      _ptr = a_dynamicType.getTypeInfo()->initializer->create(&_mem[0])->ptr();
    } else {
      _ptr = a_dynamicType.getTypeInfo()->initializer->create()->ptr();
    }
    _typeInfo = a_dynamicType.getTypeInfo();
  }

  template <size_t innerBufferSize>
  void BasicVariant<innerBufferSize>::reset(const TypeInfo* a_typeInfo){
    _destroy();
    _ptr = 0;
    _typeInfo = 0;

    const unsigned int index = a_typeInfo->index;
    if (!index){
      return;
    }

    size_t wrapperSize = a_typeInfo->initializer->size();
    if (wrapperSize <= innerBufferSize) {
      _ptr = a_typeInfo->initializer->create(&_mem[0])->ptr();
    } else {
      _ptr = a_typeInfo->initializer->create()->ptr();
    }

    _typeInfo = a_typeInfo;
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

    size_t wrapperSize = a_type.getWrapperSize();
    if (wrapperSize <= innerBufferSize) {
      _ptr = a_type.getTypeInfo()->initializer->create(&_mem[0])->ptr();
    } else {
      _ptr = a_type.getTypeInfo()->initializer->create()->ptr();
    }

    _typeInfo = a_type.getTypeInfo();
  }

  template <size_t innerBufferSize>
  BasicVariant<innerBufferSize>& BasicVariant<innerBufferSize>::operator=(const BasicVariant<innerBufferSize>& a_variant)
  {
    _clone(a_variant, WRITE);
    return *this;
  }

  template <size_t innerBufferSize>
  template <size_t InputInnerBufferSize>
  BasicVariant<innerBufferSize>& BasicVariant<innerBufferSize>::operator=(const BasicVariant<InputInnerBufferSize>& a_variant)
  {
    _clone(a_variant, WRITE);
    return *this;
  }

  template <size_t innerBufferSize>
  template <typename Ty>
  BasicVariant<innerBufferSize>& BasicVariant<innerBufferSize>::operator=(const Ty& a_value)
  {
    _reset(a_value, WRITE);
    return *this;
  }

  template <size_t innerBufferSize>
  BasicVariant<innerBufferSize>& BasicVariant<innerBufferSize>::operator=(const char* a_value)
  {
    _reset(a_value, WRITE);
    return *this;
  }

  template <size_t innerBufferSize>
  void BasicVariant<innerBufferSize>::set(const BasicVariant<innerBufferSize>& a_variant)
  {
    _clone(a_variant, WRITE);
  }

  template <size_t innerBufferSize>
  void BasicVariant<innerBufferSize>::set(const BasicVariant<innerBufferSize>& a_variant, DataSetMode a_dataMode)
  {
    _clone(a_variant, a_dataMode);
  }

  template <size_t innerBufferSize>
  template <typename Ty>
  void BasicVariant<innerBufferSize>::set(const Ty& a_value)
  {
    _reset(a_value, WRITE);
  }

  template <size_t innerBufferSize>
  template <typename Ty>
  void BasicVariant<innerBufferSize>::set(const Ty& a_value, DataSetMode a_dataMode)
  {
    _reset(a_value, a_dataMode);
  }

  template <size_t innerBufferSize>
  void BasicVariant<innerBufferSize>::set(const char* a_value)
  {
    _reset(a_value, WRITE);
  }

  template <size_t innerBufferSize>
  void BasicVariant<innerBufferSize>::set(const char* a_value, DataSetMode a_dataMode)
  {
    _reset(a_value, a_dataMode);
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
  Variant BasicVariant<innerBufferSize>::operator[](const Variant& a_key){
    UniversalCall call = _typeInfo->getSpecificator<ContainerAccessSpecificator>();
    if (!call) {
      return Variant();
    }
    Variant vdca = call(ptr(), 0, 0);
    DynamicContainerAccessBase* pdca = (DynamicContainerAccessBase*)vdca.ptr();
    pdca->setPosition(a_key, true);
    return pdca->getRefValue();
  }

  template <size_t innerBufferSize>
  template <typename Ty>
  Variant BasicVariant<innerBufferSize>::operator[](const Ty& a_key){
    return operator[](fcf::Variant(a_key));
  }

  template <size_t innerBufferSize>
  Variant BasicVariant<innerBufferSize>::operator[](const char* a_key){
    return operator[](fcf::Variant(a_key));
  }

  template <size_t innerBufferSize>
  BasicVariant<innerBufferSize>::operator bool() const{
    const void* p = ptr();
    if (p) {
      return false;
    }
    BoolSpecificator::CallType c = _typeInfo->getSpecificatorCall<BoolSpecificator>();
    if (!c) {
      return true;
    }
    return c(p);
  }


  template <size_t innerBufferSize>
  bool BasicVariant<innerBufferSize>::operator<(const BasicVariant<innerBufferSize>& a_value) const {
    if (!a_value._typeInfo) {
      return false;
    } else if (!_typeInfo) {
      return true;
    } else if (_typeInfo->dataIndex == a_value._typeInfo->dataIndex) {
      return _typeInfo->getSafeSpecificatorCall<LessSpecificator>()(ptr(), a_value.ptr());
    } else {
      try {
        Variant buffer(_typeInfo->index, a_value.ptr(), a_value._typeInfo->dataIndex);
        return _typeInfo->getSafeSpecificatorCall<LessSpecificator>()(ptr(), buffer.ptr());
      } catch(...) {
        return _typeInfo->dataIndex < a_value._typeInfo->dataIndex;
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
    } else if (!a_value._typeInfo) {
      return false;
    } else if (_typeInfo->dataIndex == a_value._typeInfo->dataIndex) {
      bool res = _typeInfo->getSafeSpecificatorCall<LessSpecificator>()(ptr(), a_value.ptr());
      if (res) {
        return true;
      }
      return _typeInfo->getSafeSpecificatorCall<EqualSpecificator>()(ptr(), a_value.ptr());
    } else {
      try {
        Variant buffer(_typeInfo->dataIndex, a_value.ptr(), a_value._typeInfo->dataIndex);
        bool res = _typeInfo->getSafeSpecificatorCall<LessSpecificator>()(ptr(), buffer.ptr());
        if (res) {
          return true;
        }
        return _typeInfo->getSafeSpecificatorCall<EqualSpecificator>()(ptr(), buffer.ptr());
      } catch(...) {
        return _typeInfo->dataIndex < a_value._typeInfo->dataIndex;
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
    } else if (!_typeInfo) {
      return false;
    } else if (_typeInfo->dataIndex == a_value._typeInfo->dataIndex) {
      return _typeInfo->getSafeSpecificatorCall<EqualSpecificator>()(ptr(), a_value.ptr());
    } else {
      try {
        Variant buffer(_typeInfo->dataIndex, a_value.ptr(), a_value._typeInfo->dataIndex);
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
    if (!_typeInfo) {
      return *this;
    } else if (TypeIndexConverter<>().isConst(typeIndex())){
      throw std::runtime_error("The data in the Variant object is read-only");
    } else if (!a_value._typeInfo) {
      return *this;
    } else if (_typeInfo->dataIndex == a_value._typeInfo->dataIndex) {
      _typeInfo->getSafeSpecificatorCall<AddSpecificator>()(ptr(), ptr(), a_value.ptr());
    } else {
      try {
        Variant buffer(_typeInfo->dataIndex, a_value.ptr(), a_value._typeInfo->dataIndex);
        _typeInfo->getSafeSpecificatorCall<AddSpecificator>()(ptr(), ptr(), buffer.ptr());
      } catch(...){
      }
    }
    return *this;
  }

  template <size_t innerBufferSize>
  template <typename Ty>
  BasicVariant<innerBufferSize>& BasicVariant<innerBufferSize>::operator+=(const Ty& a_value){
    return _appendTo(a_value);
  }

  template <size_t innerBufferSize>
  BasicVariant<innerBufferSize>& BasicVariant<innerBufferSize>::operator+=(const char* a_value){
    return _appendTo(a_value);
  }

  template <size_t innerBufferSize>
  BasicVariant<innerBufferSize> BasicVariant<innerBufferSize>::operator+(const BasicVariant<innerBufferSize>& a_value) const{
    if (!_typeInfo || !a_value._typeInfo) {
      return BasicVariant<innerBufferSize>(*this);
    } else if (_typeInfo->dataIndex == a_value._typeInfo->dataIndex) {
      BasicVariant<innerBufferSize> result(_typeInfo);
      _typeInfo->getSafeSpecificatorCall<AddSpecificator>()(result.ptr(), ptr(), a_value.ptr());
      return result;
    } else {
      BasicVariant<innerBufferSize> result(_typeInfo);
      try {
        Variant buffer(_typeInfo->dataIndex, a_value.ptr(), a_value._typeInfo->dataIndex);
        _typeInfo->getSafeSpecificatorCall<AddSpecificator>()(result.ptr(), ptr(), buffer.ptr());
      } catch(...){
        return BasicVariant<innerBufferSize>(*this);
      }
      return result;
    }
  }

  template <size_t innerBufferSize>
  template <typename Ty>
  BasicVariant<innerBufferSize> BasicVariant<innerBufferSize>::operator+(const Ty& a_value) const {
    return _append(a_value);
  }

  template <size_t innerBufferSize>
  BasicVariant<innerBufferSize> BasicVariant<innerBufferSize>::operator+(const char* a_value) const {
    return _append(a_value);
  }

  template <size_t innerBufferSize>
  BasicVariant<innerBufferSize>& BasicVariant<innerBufferSize>::operator-=(const BasicVariant<innerBufferSize>& a_value){
    if (!_typeInfo) {
      return *this;
    } else if (TypeIndexConverter<>().isConst(typeIndex())){
      throw std::runtime_error("The data in the Variant object is read-only");
    } else if (!a_value._typeInfo) {
      return *this;
    } else if (_typeInfo->dataIndex == a_value._typeInfo->dataIndex) {
      _typeInfo->getSafeSpecificatorCall<SubSpecificator>()(ptr(), ptr(), a_value.ptr());
    } else {
      try {
        Variant buffer(_typeInfo->dataIndex, a_value.ptr(), a_value._typeInfo->dataIndex);
        _typeInfo->getSafeSpecificatorCall<SubSpecificator>()(ptr(), ptr(), buffer.ptr());
      } catch(...){
      }
    }
    return *this;
  }

  template <size_t innerBufferSize>
  template <typename Ty>
  BasicVariant<innerBufferSize>& BasicVariant<innerBufferSize>::operator-=(const Ty& a_value){
    return _subTo(a_value);
  }

  template <size_t innerBufferSize>
  BasicVariant<innerBufferSize>& BasicVariant<innerBufferSize>::operator-=(const char* a_value){
    return _subTo(a_value);
  }

  template <size_t innerBufferSize>
  BasicVariant<innerBufferSize> BasicVariant<innerBufferSize>::operator-(const BasicVariant<innerBufferSize>& a_value) const{
    if (!_typeInfo || !a_value._typeInfo) {
      return BasicVariant<innerBufferSize>(*this);
    } else if (_typeInfo->dataIndex == a_value._typeInfo->dataIndex) {
      BasicVariant<innerBufferSize> result(_typeInfo);
      _typeInfo->getSafeSpecificatorCall<SubSpecificator>()(result.ptr(), ptr(), a_value.ptr());
      return result;
    } else {
      BasicVariant<innerBufferSize> result(_typeInfo);
      try {
        Variant buffer(_typeInfo->dataIndex, a_value.ptr(), a_value._typeInfo->dataIndex);
        _typeInfo->getSafeSpecificatorCall<SubSpecificator>()(result.ptr(), ptr(), buffer.ptr());
      } catch(...){
        return BasicVariant<innerBufferSize>(*this);
      }
      return result;
    }
  }

  template <size_t innerBufferSize>
  template <typename Ty>
  BasicVariant<innerBufferSize> BasicVariant<innerBufferSize>::operator-(const Ty& a_value) const{
    return _sub(a_value);
  }

  template <size_t innerBufferSize>
  BasicVariant<innerBufferSize> BasicVariant<innerBufferSize>::operator-(const char* a_value) const{
    return _sub(a_value);
  }

  template <size_t innerBufferSize>
  BasicVariant<innerBufferSize>& BasicVariant<innerBufferSize>::operator*=(const BasicVariant<innerBufferSize>& a_value){
    if (!_typeInfo) {
      return *this;
    } else if (TypeIndexConverter<>().isConst(typeIndex())){
      throw std::runtime_error("The data in the Variant object is read-only");
    } else if (!a_value._typeInfo) {
      return *this;
    } else if (_typeInfo->dataIndex == a_value._typeInfo->dataIndex) {
      _typeInfo->getSafeSpecificatorCall<MulSpecificator>()(ptr(), ptr(), a_value.ptr());
    } else {
      try {
        Variant buffer(_typeInfo->dataIndex, a_value.ptr(), a_value._typeInfo->dataIndex);
        _typeInfo->getSafeSpecificatorCall<MulSpecificator>()(ptr(), ptr(), buffer.ptr());
      } catch(...){
      }
    }
    return *this;
  }

  template <size_t innerBufferSize>
  template <typename Ty>
  BasicVariant<innerBufferSize>& BasicVariant<innerBufferSize>::operator*=(const Ty& a_value){
    return _mulTo(a_value);
  }

  template <size_t innerBufferSize>
  BasicVariant<innerBufferSize>& BasicVariant<innerBufferSize>::operator*=(const char* a_value){
    return _mulTo(a_value);
  }


  template <size_t innerBufferSize>
  BasicVariant<innerBufferSize> BasicVariant<innerBufferSize>::operator*(const BasicVariant<innerBufferSize>& a_value) const{
    if (!_typeInfo || !a_value._typeInfo) {
      return BasicVariant<innerBufferSize>(*this);
    } else if (_typeInfo->dataIndex == a_value._typeInfo->dataIndex) {
      BasicVariant<innerBufferSize> result(_typeInfo);
      _typeInfo->getSafeSpecificatorCall<MulSpecificator>()(result.ptr(), ptr(), a_value.ptr());
      return result;
    } else {
      BasicVariant<innerBufferSize> result(_typeInfo);
      try {
        Variant buffer(_typeInfo->dataIndex, a_value.ptr(), a_value._typeInfo->dataIndex);
        _typeInfo->getSafeSpecificatorCall<MulSpecificator>()(result.ptr(), ptr(), buffer.ptr());
      } catch(...){
        return BasicVariant<innerBufferSize>(*this);
      }
      return result;
    }
  }

  template <size_t innerBufferSize>
  template <typename Ty>
  BasicVariant<innerBufferSize> BasicVariant<innerBufferSize>::operator*(const Ty& a_value) const{
    return _mul(a_value);
  }

  template <size_t innerBufferSize>
  BasicVariant<innerBufferSize> BasicVariant<innerBufferSize>::operator*(const char* a_value) const{
    return _mul(a_value);
  }



  template <size_t innerBufferSize>
  BasicVariant<innerBufferSize>& BasicVariant<innerBufferSize>::operator/=(const BasicVariant<innerBufferSize>& a_value){
    if (!_typeInfo) {
      return *this;
    } else if (TypeIndexConverter<>().isConst(typeIndex())){
      throw std::runtime_error("The data in the Variant object is read-only");
    } else if (!a_value._typeInfo) {
      return *this;
    } else if (_typeInfo->dataIndex == a_value._typeInfo->dataIndex) {
      _typeInfo->getSafeSpecificatorCall<DivSpecificator>()(ptr(), ptr(), a_value.ptr());
    } else {
      try {
        Variant buffer(_typeInfo->dataIndex, a_value.ptr(), a_value._typeInfo->dataIndex);
        _typeInfo->getSafeSpecificatorCall<DivSpecificator>()(ptr(), ptr(), buffer.ptr());
      } catch(...){
      }
    }
    return *this;
  }

  template <size_t innerBufferSize>
  template <typename Ty>
  BasicVariant<innerBufferSize>& BasicVariant<innerBufferSize>::operator/=(const Ty& a_value){
    return _divTo(a_value);
  }

  template <size_t innerBufferSize>
  BasicVariant<innerBufferSize>& BasicVariant<innerBufferSize>::operator/=(const char* a_value){
    return _divTo(a_value);
  }


  template <size_t innerBufferSize>
  BasicVariant<innerBufferSize> BasicVariant<innerBufferSize>::operator/(const BasicVariant<innerBufferSize>& a_value) const{
    if (!_typeInfo || !a_value._typeInfo) {
      return BasicVariant<innerBufferSize>(*this);
    } else if (_typeInfo->dataIndex == a_value._typeInfo->dataIndex) {
      BasicVariant<innerBufferSize> result(_typeInfo);
      _typeInfo->getSafeSpecificatorCall<DivSpecificator>()(result.ptr(), ptr(), a_value.ptr());
      return result;
    } else {
      BasicVariant<innerBufferSize> result(_typeInfo);
      try {
        Variant buffer(_typeInfo->dataIndex, a_value.ptr(), a_value._typeInfo->dataIndex);
        _typeInfo->getSafeSpecificatorCall<DivSpecificator>()(result.ptr(), ptr(), buffer.ptr());
      } catch(...){
        return BasicVariant<innerBufferSize>(*this);
      }
      return result;
    }
  }

  template <size_t innerBufferSize>
  template <typename Ty>
  BasicVariant<innerBufferSize> BasicVariant<innerBufferSize>::operator/(const Ty& a_value) const{
    return _div(a_value);
  }

  template <size_t innerBufferSize>
  BasicVariant<innerBufferSize> BasicVariant<innerBufferSize>::operator/(const char* a_value) const{
    return _div(a_value);
  }

  template <size_t innerBufferSize>
  unsigned int BasicVariant<innerBufferSize>::typeIndex() const{
    return _typeInfo ? _typeInfo->index : 0;
  }

  template <size_t innerBufferSize>
  const TypeInfo* BasicVariant<innerBufferSize>::getTypeInfo() const{
    return _typeInfo;
  }

  template <size_t innerBufferSize>
  unsigned int BasicVariant<innerBufferSize>::dataTypeIndex() const{
    return _typeInfo ? _typeInfo->dataIndex : 0;
  }

  template <size_t innerBufferSize>
  void* BasicVariant<innerBufferSize>::ptr(){
    return _ptr;
  }

  template <size_t innerBufferSize>
  const void* BasicVariant<innerBufferSize>::ptr() const{
    return _ptr;
  }

  template <size_t innerBufferSize>
  template <typename TResult>
  typename std::remove_const< typename std::remove_reference<TResult>::type >::type& BasicVariant<innerBufferSize>::as() {
    typedef typename std::remove_const< typename std::remove_reference<TResult>::type >::type result_type;
    if (!_typeInfo) {
      reset(Type<TResult>());
      return *(result_type*)ptr();
    } else if (dataTypeIndex() == Type<TResult>().dataIndex()){
      return *(result_type*)ptr();
    } else {
      result_type result;
      convertRuntimeByDestination(&result, ptr(), dataTypeIndex());
      *this = result;
      return *(result_type*)ptr();
    }
  }

  template <size_t innerBufferSize>
  template <typename TResult>
  typename std::remove_const< typename std::remove_reference<TResult>::type >::type& BasicVariant<innerBufferSize>::get() {
    typedef typename std::remove_const< typename std::remove_reference<TResult>::type >::type result_type;
    if (dataTypeIndex() != Type<TResult>().dataIndex()){
      const TypeInfo* ti = _typeInfo;
      while (ti) {
        ResolveSpecificator::CallType resolveCall = ti->getSpecificatorCall<ResolveSpecificator>();
        if (resolveCall) {
          ResolveData rd = resolveCall(ptr());
          if (rd.data){
            unsigned int dataTypeIndex = TypeIndexConverter<>::getDataIndex(rd.typeIndex);
            if (Type<TResult>().dataIndex() == dataTypeIndex){
              return *(result_type*)rd.data;
            } else {
              ti = ::fcf::getTypeInfo(rd.typeIndex);
              continue;
            }
          }
        }
        ti = 0;
      }
      throw std::runtime_error(std::string() + "The type saved in the variant is not '" + Type<TResult>().name() + "' type");
    } else {
      return *(result_type*)ptr();
    }
  }

  template <size_t innerBufferSize>
  template <typename TResult>
  TResult BasicVariant<innerBufferSize>::cast() const{
    static const unsigned int selfVariantTypeIndex  = Type<BasicVariant>().index();
    static const unsigned int variantTypeIndex      = Type<Variant>().index();
    if (!_typeInfo){
      return TResult();
    } if (dataTypeIndex() == Type<TResult>().dataIndex()){
      return *(TResult*)ptr();
    } else if (_typeInfo->dataIndex == selfVariantTypeIndex) {
      return ((BasicVariant*)ptr())->cast<TResult>();
    } else if (_typeInfo->dataIndex == variantTypeIndex) {
      return ((Variant*)ptr())->cast<TResult>();
    } else {
      TResult result;
      convertRuntimeByDestination(&result, ptr(), dataTypeIndex());
      return result;
    }
  }

  template <size_t innerBufferSize>
  template <typename TResult>
  TResult BasicVariant<innerBufferSize>::strict_cast() const{
    static const unsigned int selfVariantTypeIndex  = Type<BasicVariant>().index();
    static const unsigned int variantTypeIndex      = Type<Variant>().index();
    if (dataTypeIndex() != Type<TResult>().dataIndex()){
      if (_typeInfo->dataIndex == selfVariantTypeIndex) {
        return ((BasicVariant*)ptr())->strict_cast<TResult>();
      } else if (_typeInfo->dataIndex == variantTypeIndex) {
        return ((Variant*)ptr())->strict_cast<TResult>();
      }
      throw std::runtime_error(std::string() + "The type saved in the variant is not '" + Type<TResult>().name() + "' type");
    }
    return *(TResult*)ptr();
  }

  template <size_t innerBufferSize>
  template <typename TType>
  bool BasicVariant<innerBufferSize>::is() const{
    return dataTypeIndex() == Type<TType>().dataIndex();
  }

  template <size_t innerBufferSize>
  template <typename TType>
  bool BasicVariant<innerBufferSize>::strictIs() const{
    return typeIndex() == Type<TType>().index();
  }

  template <size_t innerBufferSize>
  void BasicVariant<innerBufferSize>::_destroy(){
    if (_typeInfo) {
      if (isInnerMemory()){
        ((BaseTypeWrapper*)&_mem[0])->~BaseTypeWrapper();
      } else {
        delete (BaseTypeWrapper*)_getWrapper();
      }
    }
  }

  template <size_t innerBufferSize>
  template <size_t InputInnerBufferSize>
  void BasicVariant<innerBufferSize>::_clone(const BasicVariant<InputInnerBufferSize>& a_variant, DataSetMode a_dataMode) {
    static const unsigned int selfVariantTypeIndex  = Type<BasicVariant>().index();
    static const unsigned int variantTypeIndex      = Type<Variant>().index();
    switch (a_dataMode){
      case WRITE:
      {
        if (TypeIndexConverter<>().isConst(typeIndex())){
          throw std::runtime_error("The data in the Variant object is read-only");
        }
        if (isReference()){
          BaseTypeWrapper* wrp = (BaseTypeWrapper*)_getWrapper();
          if (!a_variant._typeInfo) {
            throw std::runtime_error("Source variant object not set");
          } else if (_typeInfo->dataIndex == a_variant._typeInfo->dataIndex) {
            wrp->set(a_variant.ptr());
          } else if (_typeInfo->dataIndex == selfVariantTypeIndex) {
            *((BasicVariant*)ptr()) = a_variant;
          } else if (_typeInfo->dataIndex == variantTypeIndex) {
            *((Variant*)ptr()) = a_variant;
          } else {
            Variant buffer(_typeInfo->dataIndex, a_variant.ptr(), a_variant._typeInfo->dataIndex);
            wrp->set(buffer.ptr());
          }
        } else {
          _destroy();
          _ptr = 0;
          _typeInfo = 0;
          auto ui = a_variant._getUnref();
          if (ui.typeInfo) {
            if (ui.wrapper->size() <= innerBufferSize){
              _ptr = ui.wrapper->cloneData(&_mem[0])->ptr();
            } else {
              _ptr = ui.wrapper->cloneData()->ptr();
            }
            if (TypeIndexConverter<>::isSingleReference(ui.typeInfo->index)){
              ui.typeInfo = ::fcf::getTypeInfo(TypeIndexConverter<>::getUnreferenceIndex(ui.typeInfo->index));
            }
            _typeInfo = ui.typeInfo;
          }
        }
      }
      break;
      case RESET:
        {
          _destroy();
          _ptr = 0;
          _typeInfo = 0;
          auto ui = a_variant._getUnref();
          if (ui.typeInfo) {
            if (ui.wrapper->size() <= innerBufferSize){
              _ptr = ui.wrapper->clone(&_mem[0])->ptr();
            } else {
              _ptr = ui.wrapper->clone()->ptr();
            }
            _typeInfo = ui.typeInfo;
          }
        }
      break;
      case FORCE_REFERENCE:
      case REFERENCE:
      {
          _destroy();
          _ptr = 0;
          _typeInfo = 0;
          if (a_variant._typeInfo) {
            BaseTypeWrapper* wrp = (BaseTypeWrapper*)a_variant._getWrapper();
            _ptr = wrp->referenceClone(&_mem[0])->ptr();
            _typeInfo = ::fcf::getTypeInfo(TypeIndexConverter<>().getSingleReferenceIndex(a_variant.typeIndex()));
          }
      }
      break;
    }
  }

  template <size_t innerBufferSize>
  template <typename Ty>
  void BasicVariant<innerBufferSize>::_set(const Ty& a_value) {
    typedef typename std::remove_reference< typename Type<Ty, StoredDataTypeSpecificator>::type >::type type;
    _ptr = NDetails::VariantAllocator<type, innerBufferSize>()(&_mem[0], a_value)->ptr();
    _typeInfo = Type<type>().getTypeInfo();
  }

  template <size_t innerBufferSize>
  template <typename Ty>
  void BasicVariant<innerBufferSize>::_set(const Ty& a_value, DataSetMode a_dataMode) {
    switch (a_dataMode){
      case RESET:
      case WRITE:
        {
        typedef typename std::remove_reference< typename Type<Ty, StoredDataTypeSpecificator>::type >::type type;
        _ptr = NDetails::VariantAllocator<type, innerBufferSize>()(&_mem[0], a_value)->ptr();
        _typeInfo = Type<type>().getTypeInfo();
        }
        break;
      case FORCE_REFERENCE:
      case REFERENCE:
        {
          typedef typename std::remove_reference< typename Type<Ty, StoredDataTypeSpecificator>::type >::type& type;
          _ptr = NDetails::VariantAllocator<type, innerBufferSize>()(&_mem[0], a_value)->ptr();
          _typeInfo = Type<type>().getTypeInfo();
        }
        break;
    }
  }

  template <size_t innerBufferSize>
  template <typename Ty>
  void BasicVariant<innerBufferSize>::_reset(const Ty& a_value, DataSetMode a_dataMode) {
    static const unsigned int selfVariantTypeIndex  = Type<BasicVariant>().index();
    static const unsigned int variantTypeIndex      = Type<Variant>().index();
    switch (a_dataMode){
      case WRITE:
        {
          if (TypeIndexConverter<>().isConst(typeIndex())){
            throw std::runtime_error("The data in the Variant object is read-only");
          }
          if (isReference()){
            BaseTypeWrapper* wrp = (BaseTypeWrapper*)_getWrapper();
            if (_typeInfo->dataIndex == Type<Ty>().dataIndex()) {
              wrp->set(&a_value);
            } else if (selfVariantTypeIndex == _typeInfo->dataIndex) {
              ((BasicVariant*)ptr())->_reset(a_value, WRITE);
            } else if (variantTypeIndex == _typeInfo->dataIndex){
              ((Variant*)ptr())->_reset(a_value, WRITE);
            } else {
              Variant buffer(_typeInfo->dataIndex, &a_value, Type<Ty>().index());
              wrp->set(buffer.ptr());
            }
          } else {
            _destroy();
            _ptr = 0;
            _typeInfo = 0;
            typedef typename Type<Ty, StoredDataTypeSpecificator>::type type;
            _ptr = NDetails::VariantAllocator<type, innerBufferSize>()(&_mem[0], a_value)->ptr();
            _typeInfo = Type<type>().getTypeInfo();
          }
        }
        break;
      case RESET:
        {
          typedef typename Type<Ty, StoredDataTypeSpecificator>::type type;
          _destroy();
          _ptr = 0;
          _typeInfo = 0;
          _ptr = NDetails::VariantAllocator<type, innerBufferSize>()(&_mem[0], a_value)->ptr();
          _typeInfo = Type<type>().getTypeInfo();
        }
        break;
      case FORCE_REFERENCE:
      case REFERENCE:
        {
          typedef typename Type<Ty, StoredDataTypeSpecificator>::type& type;
          _destroy();
          _ptr = 0;
          _typeInfo = 0;
          _ptr = NDetails::VariantAllocator<type, innerBufferSize>()(&_mem[0], a_value)->ptr();
          _typeInfo = Type<type>().getTypeInfo();
        }
        break;
    }
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
        _ptr = dt.getTypeInfo()->initializer->clone(a_sourceData)->ptr();
      } else {
        _ptr = dt.getTypeInfo()->initializer->create()->ptr();
      }
    } else {
      if (a_sourceData && !a_sourceTypeIndex && !a_convertFunction) {
        _ptr = dt.getTypeInfo()->initializer->clone(&_mem[0], a_sourceData)->ptr();
      } else {
        _ptr = dt.getTypeInfo()->initializer->create(&_mem[0])->ptr();
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
  BaseTypeWrapper* BasicVariant<innerBufferSize>::_getWrapper() const{
    if (!_typeInfo){
      return 0;
    }
    if (isInnerMemory()) {
      return (BaseTypeWrapper*)&_mem[0];
    } else {
      char* data = (char*)&((const TypeWrapper<int>*)_ptr)->data;
      char* wrp  = (char*)_ptr;
      long  offset  = data - wrp;
      char* address = wrp - offset;
      return (BaseTypeWrapper*)address;
    }
  }

  template <size_t innerBufferSize>
  typename BasicVariant<innerBufferSize>::UnrefInfo BasicVariant<innerBufferSize>::_getUnref() const {
    static const unsigned int selfVariantTypeIndex  = Type<BasicVariant>().index();
    static const unsigned int variantTypeIndex      = Type<Variant>().index();
    if (!_typeInfo){
      return UnrefInfo{0, 0};
    }
    const void* p        = ptr();
    BaseTypeWrapper* wrp = _getWrapper();
    const TypeInfo* ti   = _typeInfo;
    while (ti) {
      if (TypeIndexConverter<>::isSingleReference(ti->index)){
        if (ti->dataIndex == selfVariantTypeIndex){
          p = ((BasicVariant*)p)->ptr();
          wrp = ((BasicVariant*)p)->_getWrapper();
          ti  = ((BasicVariant*)p)->_typeInfo;
          continue;
        } else if (ti->dataIndex == variantTypeIndex){
          p = ((Variant*)p)->ptr();
          wrp = ((Variant*)p)->_getWrapper();
          ti  = ((Variant*)p)->_typeInfo;
          continue;
        }
      }
      break;
    }
    return UnrefInfo{ti, wrp};
  }

  template <size_t innerBufferSize>
  template <typename Ty>
  bool BasicVariant<innerBufferSize>::_less(const Ty& a_value) const{
    if (!_typeInfo) {
      return true;
    }

    typedef typename std::remove_reference<Ty>::type ArgType;

    unsigned int argTypeIndex = Type<ArgType>().index();
    if (_typeInfo->dataIndex == argTypeIndex) {
      return _typeInfo->getSafeSpecificatorCall<LessSpecificator>()(ptr(), &a_value);
    } else {
      try {
        Variant buffer(_typeInfo->index, &a_value, argTypeIndex);
        return _typeInfo->getSafeSpecificatorCall<LessSpecificator>()(ptr(), buffer.ptr());
      } catch(...) {
        return _typeInfo->dataIndex < argTypeIndex;
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
    if (_typeInfo->dataIndex == argTypeIndex) {
      bool res = _typeInfo->getSafeSpecificatorCall<LessSpecificator>()(ptr(), &a_value);
      if (res) {
        return true;
      }
      return _typeInfo->getSafeSpecificatorCall<EqualSpecificator>()(ptr(), &a_value);
    } else {
      try {
        Variant buffer(_typeInfo->dataIndex, &a_value, argTypeIndex);
        bool res = _typeInfo->getSafeSpecificatorCall<LessSpecificator>()(ptr(), buffer.ptr());
        if (res) {
          return true;
        }
        return _typeInfo->getSafeSpecificatorCall<EqualSpecificator>()(ptr(), buffer.ptr());
      } catch(...) {
        return _typeInfo->dataIndex < argTypeIndex;
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
    if (_typeInfo->dataIndex == argTypeIndex) {
      return _typeInfo->getSafeSpecificatorCall<EqualSpecificator>()(ptr(), &a_value);
    }

    try {
      Variant buffer(_typeInfo->dataIndex, &a_value, argTypeIndex);
      return _typeInfo->getSafeSpecificatorCall<EqualSpecificator>()(ptr(), buffer.ptr());
    } catch(...) {
    }

    return false;
  }

  template <size_t innerBufferSize>
  template <typename Ty>
  BasicVariant<innerBufferSize>& BasicVariant<innerBufferSize>::_appendTo(const Ty& a_value){
    if (!_typeInfo) {
      return *this;
    }

    if (TypeIndexConverter<>().isConst(typeIndex())){
      throw std::runtime_error("The data in the Variant object is read-only");
    }

    typedef typename std::remove_reference<Ty>::type ArgType;

    unsigned int argTypeIndex = Type<ArgType>().index();
    if (_typeInfo->dataIndex == argTypeIndex) {
      _typeInfo->getSafeSpecificatorCall<AddSpecificator>()(ptr(), ptr(), &a_value);
      return *this;
    }

    try {
      Variant buffer(_typeInfo->dataIndex, &a_value, argTypeIndex);
      _typeInfo->getSafeSpecificatorCall<AddSpecificator>()(ptr(), ptr(), buffer.ptr());
    } catch(...) {
    }

    return *this;
  }

  template <size_t innerBufferSize>
  template <typename Ty>
  BasicVariant<innerBufferSize> BasicVariant<innerBufferSize>::_append(const Ty& a_value) const{
    if (!_typeInfo) {
      return BasicVariant<innerBufferSize>(*this);
    }

    typedef typename std::remove_reference<Ty>::type ArgType;

    unsigned int argTypeIndex = Type<ArgType>().index();

    BasicVariant<innerBufferSize> result(_typeInfo);

    if (_typeInfo->dataIndex == argTypeIndex) {
      _typeInfo->getSafeSpecificatorCall<AddSpecificator>()(result.ptr(), ptr(), &a_value);
      return result;
    }

    try {
      Variant buffer(_typeInfo->dataIndex, &a_value, argTypeIndex);
      _typeInfo->getSafeSpecificatorCall<AddSpecificator>()(result.ptr(), ptr(), buffer.ptr());
    } catch(...){
      return BasicVariant<innerBufferSize>(*this);
    }

    return result;
  }



  template <size_t innerBufferSize>
  template <typename Ty>
  BasicVariant<innerBufferSize>& BasicVariant<innerBufferSize>::_subTo(const Ty& a_value){
    if (!_typeInfo) {
      return *this;
    }

    if (TypeIndexConverter<>().isConst(typeIndex())){
      throw std::runtime_error("The data in the Variant object is read-only");
    }

    typedef typename std::remove_reference<Ty>::type ArgType;

    unsigned int argTypeIndex = Type<ArgType>().index();
    if (_typeInfo->dataIndex == argTypeIndex) {
      _typeInfo->getSafeSpecificatorCall<SubSpecificator>()(ptr(), ptr(), &a_value);
      return *this;
    }

    try {
      Variant buffer(_typeInfo->dataIndex, &a_value, argTypeIndex);
      _typeInfo->getSafeSpecificatorCall<SubSpecificator>()(ptr(), ptr(), buffer.ptr());
    } catch(...) {
    }

    return *this;
  }

  template <size_t innerBufferSize>
  template <typename Ty>
  BasicVariant<innerBufferSize> BasicVariant<innerBufferSize>::_sub(const Ty& a_value) const {
    if (!_typeInfo) {
      return BasicVariant<innerBufferSize>(*this);
    }

    typedef typename std::remove_reference<Ty>::type ArgType;

    unsigned int argTypeIndex = Type<ArgType>().index();

    BasicVariant<innerBufferSize> result(_typeInfo);

    if (_typeInfo->dataIndex == argTypeIndex) {
      _typeInfo->getSafeSpecificatorCall<SubSpecificator>()(result.ptr(), ptr(), &a_value);
      return result;
    }

    try {
      Variant buffer(_typeInfo->dataIndex, &a_value, argTypeIndex);
      _typeInfo->getSafeSpecificatorCall<SubSpecificator>()(result.ptr(), ptr(), buffer.ptr());
    } catch(...) {
      return BasicVariant<innerBufferSize>(*this);
    }

    return result;
  }

  template <size_t innerBufferSize>
  template <typename Ty>
  BasicVariant<innerBufferSize>& BasicVariant<innerBufferSize>::_mulTo(const Ty& a_value){
    if (!_typeInfo) {
      return *this;
    }

    if (TypeIndexConverter<>().isConst(typeIndex())){
      throw std::runtime_error("The data in the Variant object is read-only");
    }

    typedef typename std::remove_reference<Ty>::type ArgType;

    unsigned int argTypeIndex = Type<ArgType>().index();
    if (_typeInfo->dataIndex == argTypeIndex) {
      _typeInfo->getSafeSpecificatorCall<MulSpecificator>()(ptr(), ptr(), &a_value);
      return *this;
    }

    try {
      Variant buffer(_typeInfo->dataIndex, &a_value, argTypeIndex);
      _typeInfo->getSafeSpecificatorCall<MulSpecificator>()(ptr(), ptr(), buffer.ptr());
    } catch(...) {
    }

    return *this;
  }

  template <size_t innerBufferSize>
  template <typename Ty>
  BasicVariant<innerBufferSize> BasicVariant<innerBufferSize>::_mul(const Ty& a_value) const{
    if (!_typeInfo) {
      return BasicVariant<innerBufferSize>(*this);
    }

    typedef typename std::remove_reference<Ty>::type ArgType;

    unsigned int argTypeIndex = Type<ArgType>().index();

    BasicVariant<innerBufferSize> result(_typeInfo);

    if (_typeInfo->dataIndex == argTypeIndex) {
      _typeInfo->getSafeSpecificatorCall<MulSpecificator>()(result.ptr(), ptr(), &a_value);
      return result;
    }

    try {
      Variant buffer(_typeInfo->dataIndex, &a_value, argTypeIndex);
      _typeInfo->getSafeSpecificatorCall<MulSpecificator>()(result.ptr(), ptr(), buffer.ptr());
    } catch(...){
      return BasicVariant<innerBufferSize>(*this);
    }

    return result;
  }

  template <size_t innerBufferSize>
  template <typename Ty>
  BasicVariant<innerBufferSize>& BasicVariant<innerBufferSize>::_divTo(const Ty& a_value){
    if (!_typeInfo) {
      return *this;
    }

    if (TypeIndexConverter<>().isConst(typeIndex())){
      throw std::runtime_error("The data in the Variant object is read-only");
    }

    typedef typename std::remove_reference<Ty>::type ArgType;

    unsigned int argTypeIndex = Type<ArgType>().index();
    if (_typeInfo->dataIndex == argTypeIndex) {
      _typeInfo->getSafeSpecificatorCall<DivSpecificator>()(ptr(), ptr(), &a_value);
      return *this;
    }

    try {
      Variant buffer(_typeInfo->dataIndex, &a_value, argTypeIndex);
      _typeInfo->getSafeSpecificatorCall<DivSpecificator>()(ptr(), ptr(), buffer.ptr());
    } catch(...) {
    }

    return *this;
  }

  template <size_t innerBufferSize>
  template <typename Ty>
  BasicVariant<innerBufferSize> BasicVariant<innerBufferSize>::_div(const Ty& a_value) const{
    if (!_typeInfo) {
      return BasicVariant<innerBufferSize>(*this);
    }

    typedef typename std::remove_reference<Ty>::type ArgType;

    unsigned int argTypeIndex = Type<ArgType>().index();

    BasicVariant<innerBufferSize> result(_typeInfo);

    if (_typeInfo->dataIndex == argTypeIndex) {
      _typeInfo->getSafeSpecificatorCall<DivSpecificator>()(result.ptr(), ptr(), &a_value);
      return result;
    }

    try {
      Variant buffer(_typeInfo->dataIndex, &a_value, argTypeIndex);
      _typeInfo->getSafeSpecificatorCall<DivSpecificator>()(result.ptr(), ptr(), buffer.ptr());
    } catch(...){
      return BasicVariant<innerBufferSize>(*this);
    }

    return result;
  }

}  // fcf namespace

#include "bits/PartSpecificator/ResolveSpecificator.hpp"

namespace std {
  template <size_t innerBufferSize>
  std::string to_string(const fcf::BasicVariant<innerBufferSize>& a_variant){
    return a_variant.template cast<std::string>();
  }
}

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
