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
      _ptr = a_type.getTypeInfo()->initializer->create(&_mem[0])->rootPtr();
    } else {
      _ptr = a_type.getTypeInfo()->initializer->create()->rootPtr();
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
      _ptr = a_dynamicType.getTypeInfo()->initializer->create(&_mem[0])->rootPtr();
    } else {
      _ptr = a_dynamicType.getTypeInfo()->initializer->create()->rootPtr();
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
      _ptr = a_typeInfo->initializer->create(&_mem[0])->rootPtr();
    } else {
      _ptr = a_typeInfo->initializer->create()->rootPtr();
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
      _ptr = a_dynamicType.getTypeInfo()->initializer->create(&_mem[0])->rootPtr();
    } else {
      _ptr = a_dynamicType.getTypeInfo()->initializer->create()->rootPtr();
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
      _ptr = a_typeInfo->initializer->create(&_mem[0])->rootPtr();
    } else {
      _ptr = a_typeInfo->initializer->create()->rootPtr();
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
      _ptr = a_type.getTypeInfo()->initializer->create(&_mem[0])->rootPtr();
    } else {
      _ptr = a_type.getTypeInfo()->initializer->create()->rootPtr();
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
    auto selfUnref = ((BasicVariant*)this)->_dataEndpoint();
    auto argUnref  = ((BasicVariant<innerBufferSize>&)a_value)._dataEndpoint();
    if (!argUnref.typeInfo) {
      return false;
    } else if (!selfUnref.typeInfo) {
      return true;
    }
    try {
      if (selfUnref.typeInfo->dataIndex == argUnref.typeInfo->dataIndex) {
        return selfUnref.typeInfo->template getSafeSpecificatorCall<LessSpecificator>()(selfUnref.ptr, argUnref.ptr);
      } else {
        Variant buffer(selfUnref.typeInfo->dataIndex, argUnref.ptr, argUnref.typeInfo->dataIndex);
        return selfUnref.typeInfo->template getSafeSpecificatorCall<LessSpecificator>()(selfUnref.ptr, buffer.ptr());
      }
    } catch(...) {
      return selfUnref.typeInfo->dataIndex < argUnref.typeInfo->dataIndex;
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
    auto selfUnref = ((BasicVariant*)this)->_dataEndpoint();
    auto argUnref  = ((BasicVariant<innerBufferSize>&)a_value)._dataEndpoint();
    if (!selfUnref.typeInfo) {
      return true;
    } else if (!argUnref.typeInfo) {
      return false;
    }
    try {
      if (selfUnref.typeInfo->dataIndex == argUnref.typeInfo->dataIndex) {
        bool res = selfUnref.typeInfo->template getSafeSpecificatorCall<LessSpecificator>()(selfUnref.ptr, argUnref.ptr);
        if (res){
          return true;
        }
        return selfUnref.typeInfo->template getSafeSpecificatorCall<EqualSpecificator>()(selfUnref.ptr, argUnref.ptr);
      } else {
        Variant buffer(selfUnref.typeInfo->dataIndex, argUnref.ptr, argUnref.typeInfo->dataIndex);
        bool res = selfUnref.typeInfo->template getSafeSpecificatorCall<LessSpecificator>()(selfUnref.ptr, buffer.ptr());
        if (res) {
          return true;
        }
        return selfUnref.typeInfo->template getSafeSpecificatorCall<EqualSpecificator>()(selfUnref.ptr, buffer.ptr());
      }
    } catch(...){
      return selfUnref.typeInfo->dataIndex < argUnref.typeInfo->dataIndex;
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
    auto selfUnref = ((BasicVariant*)this)->_dataEndpoint();
    auto argUnref  = ((BasicVariant<innerBufferSize>&)a_value)._dataEndpoint();
    if (!argUnref.typeInfo) {
      return !selfUnref.typeInfo;
    } else if (!selfUnref.typeInfo) {
      return false;
    }
    try {
      if (selfUnref.typeInfo->dataIndex == argUnref.typeInfo->dataIndex) {
        return selfUnref.typeInfo->template getSafeSpecificatorCall<EqualSpecificator>()(selfUnref.ptr, argUnref.ptr);
      } else {
        Variant buffer(selfUnref.typeInfo->dataIndex, argUnref.ptr, argUnref.typeInfo->dataIndex);
        return selfUnref.typeInfo->template getSafeSpecificatorCall<EqualSpecificator>()(selfUnref.ptr, buffer.ptr());
      }
    } catch(...) {
      return false;
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
    } else if (TypeIndexConverter<>().isConst(getTypeIndex())){
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
    } else if (TypeIndexConverter<>().isConst(getTypeIndex())){
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
    } else if (TypeIndexConverter<>().isConst(getTypeIndex())){
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
    } else if (TypeIndexConverter<>().isConst(getTypeIndex())){
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
  unsigned int BasicVariant<innerBufferSize>::getTypeIndex() const{
    return _typeInfo ? _typeInfo->index : 0;
  }

  template <size_t innerBufferSize>
  const TypeInfo* BasicVariant<innerBufferSize>::getTypeInfo() const{
    return _typeInfo;
  }

  template <size_t innerBufferSize>
  unsigned int BasicVariant<innerBufferSize>::getDataTypeIndex() const{
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
    } else if (getDataTypeIndex() == Type<TResult>().dataIndex()){
      return *(result_type*)ptr();
    } else {
      result_type result;
      convertRuntimeByDestination(&result, ptr(), getDataTypeIndex());
      *this = result;
      return *(result_type*)ptr();
    }
  }

  template <size_t innerBufferSize>
  template <typename TResult>
  typename std::remove_const< typename std::remove_reference<TResult>::type >::type& BasicVariant<innerBufferSize>::get() {
    typedef typename std::remove_const< typename std::remove_reference<TResult>::type >::type result_type;
    if (getDataTypeIndex() != Type<TResult>().dataIndex()){
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
    } if (getDataTypeIndex() == Type<TResult>().dataIndex()){
      return *(TResult*)ptr();
    } else if (_typeInfo->dataIndex == selfVariantTypeIndex) {
      return ((BasicVariant*)ptr())->cast<TResult>();
    } else if (_typeInfo->dataIndex == variantTypeIndex) {
      return ((Variant*)ptr())->cast<TResult>();
    } else {
      TResult result;
      convertRuntimeByDestination(&result, ptr(), getDataTypeIndex());
      return result;
    }
  }

  template <size_t innerBufferSize>
  template <typename TResult>
  TResult BasicVariant<innerBufferSize>::strict_cast() const{
    static const unsigned int selfVariantTypeIndex  = Type<BasicVariant>().index();
    static const unsigned int variantTypeIndex      = Type<Variant>().index();
    if (getDataTypeIndex() != Type<TResult>().dataIndex()){
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
    return getDataTypeIndex() == Type<TType>().dataIndex();
  }

  template <size_t innerBufferSize>
  template <typename TType>
  bool BasicVariant<innerBufferSize>::strictIs() const{
    return getTypeIndex() == Type<TType>().index();
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
    switch (a_dataMode){
      case WRITE:
      {
        VariantEndpoint                                             selfEndpoint   = _variantEndpoint();
        typename BasicVariant<InputInnerBufferSize>::DataEndpointEx sourceEndpoint = ((BasicVariant<InputInnerBufferSize>&)a_variant)._dataEndpointEx();
 
        if (selfEndpoint.isConst){
          throw std::runtime_error("The data in the Variant object is read-only");
        }
        BasicVariant* curVariant =  (BasicVariant*)selfEndpoint.variant;
        if (curVariant->_typeInfo && 
            !curVariant->_typeInfo->isVariant && 
            TypeIndexConverter<>::isReference(curVariant->_typeInfo->index)) {
          if (TypeIndexConverter<>::isConst(curVariant->_typeInfo->index)){
            throw std::runtime_error("The data in the Variant object is read-only");
          }
          if (sourceEndpoint.typeInfo) {
            if (curVariant->_typeInfo->dataIndex == sourceEndpoint.typeInfo->dataIndex) {
              BaseTypeWrapper* wrp = curVariant->_getWrapper();
              wrp->set(sourceEndpoint.ptr);
            } else {
              Variant buffer(curVariant->_typeInfo->dataIndex, sourceEndpoint.ptr, sourceEndpoint.typeInfo->index);
              BaseTypeWrapper* wrp = curVariant->_getWrapper();
              wrp->set(buffer.ptr());
            }
          } else {
            throw std::runtime_error("Set empty value for variant reference");
          }
        } else {
          if (curVariant->_typeInfo){
            if (TypeIndexConverter<>::isConst(curVariant->_typeInfo->index)){
              throw std::runtime_error("The data in the Variant object is read-only");
            }
            if (curVariant->_typeInfo->initializer->size() <= selfEndpoint.innerSize ){
              ((BaseTypeWrapper*)&curVariant->_mem[0])->~BaseTypeWrapper();
            } else {
              delete (BaseTypeWrapper*)curVariant->_getWrapper();
            }
            curVariant->_ptr = 0;
            curVariant->_typeInfo = 0;
          }
          if (sourceEndpoint.typeInfo){
            if ( sourceEndpoint.typeInfo->initializer->size() <= selfEndpoint.innerSize ){
              char* innerBuffer = (char*)&curVariant->_mem[0];
              curVariant->_ptr = sourceEndpoint.wrapper->cloneData(innerBuffer)->rootPtr();
            } else {
              curVariant->_ptr = sourceEndpoint.wrapper->cloneData()->rootPtr();
            }
            if (TypeIndexConverter<>::isSingleReference(sourceEndpoint.typeInfo->index)){
              curVariant->_typeInfo = ::fcf::getTypeInfo(TypeIndexConverter<>::getUnreferenceIndex(sourceEndpoint.typeInfo->index));
            } else {
              curVariant->_typeInfo = sourceEndpoint.typeInfo;
            }
          }
        }
        break;
      }
      case RESET:
        {
          _destroy();
          _ptr = 0;
          _typeInfo = 0;
          auto ui = ((BasicVariant<InputInnerBufferSize>&)a_variant)._dataEndpointEx();
          if (ui.typeInfo) {
            if (ui.wrapper->size() <= innerBufferSize){
              _ptr = ui.wrapper->cloneData(&_mem[0])->rootPtr();
            } else {
              _ptr = ui.wrapper->cloneData()->rootPtr();
            }
            if (ui.typeInfo->index != ui.typeInfo->dataIndex){
              ui.typeInfo = ::fcf::getTypeInfo(TypeIndexConverter<>::getUnreferenceIndex(ui.typeInfo->dataIndex));
            }
            _typeInfo = ui.typeInfo;
          }
        }
      break;
      case FORCE_REFERENCE:
      case REFERENCE:
      {
        if (this == (void*)&a_variant){
          return;
        }
        _destroy();
        _ptr = 0;
        _typeInfo = 0;
        if (a_variant._typeInfo) {
          BaseTypeWrapper* wrp = (BaseTypeWrapper*)a_variant._getWrapper();
          _ptr = wrp->referenceClone(&_mem[0])->rootPtr();
          _typeInfo = ::fcf::getTypeInfo(TypeIndexConverter<>().getSingleReferenceIndex(a_variant.getTypeIndex()));
        }
      }
      break;
    }
  }

  template <size_t innerBufferSize>
  template <typename Ty>
  void BasicVariant<innerBufferSize>::_set(const Ty& a_value, DataSetMode a_dataMode) {
    switch (a_dataMode){
      case RESET:
      case WRITE:
        {
          typedef typename std::remove_reference< typename Type<Ty, StoredDataTypeSpecificator>::type >::type type;
          _ptr = NDetails::VariantAllocator<type, innerBufferSize>()(&_mem[0], a_value)->rootPtr();
          _typeInfo = Type<type>().getTypeInfo();
        }
        break;
      case FORCE_REFERENCE:
      case REFERENCE:
        {
          typedef typename std::remove_reference< typename Type<Ty, StoredDataTypeSpecificator>::type >::type& type;
          _ptr = NDetails::VariantAllocator<type, innerBufferSize>()(&_mem[0], a_value)->rootPtr();
          _typeInfo = Type<type>().getTypeInfo();
        }
        break;
    }
  }

  template <size_t innerBufferSize>
  template <typename Ty>
  void BasicVariant<innerBufferSize>::_reset(const Ty& a_value, DataSetMode a_dataMode) {
    switch (a_dataMode){
      case WRITE:
        {
          VariantEndpoint ve = _variantEndpoint();
          if (ve.isConst){
            throw std::runtime_error("The data in the Variant object is read-only");
          }
          BasicVariant* curVariant =  (BasicVariant*)ve.variant;
          if (curVariant->_typeInfo && 
              !curVariant->_typeInfo->isVariant && 
              TypeIndexConverter<>::isReference(curVariant->_typeInfo->index)) {
            if (TypeIndexConverter<>::isConst(curVariant->_typeInfo->index)){
              throw std::runtime_error("The data in the Variant object is read-only");
            }
            if (curVariant->_typeInfo->dataIndex == Type<Ty>().dataIndex()) {
              BaseTypeWrapper* wrp = curVariant->_getWrapper();
              wrp->set(&a_value);
            } else {
              Variant buffer(curVariant->_typeInfo->dataIndex, &a_value, Type<Ty>().index());
              BaseTypeWrapper* wrp = curVariant->_getWrapper();
              wrp->set(buffer.ptr());
            }
          } else {
            if (curVariant->_typeInfo){
              if (TypeIndexConverter<>::isConst(curVariant->_typeInfo->index)){
                throw std::runtime_error("The data in the Variant object is read-only");
              }
              if ( curVariant->_typeInfo->initializer->size() <= ve.innerSize ){
                ((BaseTypeWrapper*)&curVariant->_mem[0])->~BaseTypeWrapper();
              } else {
                delete (BaseTypeWrapper*)curVariant->_getWrapper();
              }
              curVariant->_ptr = 0;
              curVariant->_typeInfo = 0;
            }
            typedef typename Type<Ty, StoredDataTypeSpecificator>::type type;
            if ( sizeof(TypeWrapper<type>) <= ve.innerSize ){
              void* innerBuffer = &curVariant->_mem[0];
              curVariant->_ptr = (new (innerBuffer) TypeWrapper<type>(a_value))->rootPtr();
            } else {
              curVariant->_ptr = (new TypeWrapper<type>(a_value))->rootPtr();
            }
            curVariant->_typeInfo = Type<type>().getTypeInfo();
          }
          break;
        }
        break;
      case RESET:
        {
          typedef typename Type<Ty, StoredDataTypeSpecificator>::type type;
          _destroy();
          _ptr = 0;
          _typeInfo = 0;
          _ptr = NDetails::VariantAllocator<type, innerBufferSize>()(&_mem[0], a_value)->rootPtr();
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
          _ptr = NDetails::VariantAllocator<type, innerBufferSize>()(&_mem[0], a_value)->rootPtr();
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
        _ptr = dt.getTypeInfo()->initializer->clone(a_sourceData)->rootPtr();
      } else {
        _ptr = dt.getTypeInfo()->initializer->create()->rootPtr();
      }
    } else {
      if (a_sourceData && !a_sourceTypeIndex && !a_convertFunction) {
        _ptr = dt.getTypeInfo()->initializer->clone(&_mem[0], a_sourceData)->rootPtr();
      } else {
        _ptr = dt.getTypeInfo()->initializer->create(&_mem[0])->rootPtr();
      }
    }
    _typeInfo = ti;

    if (a_sourceTypeIndex && !a_convertFunction) {
      convertRuntime(ptr(), a_typeIndex, a_sourceData, a_sourceTypeIndex, a_convertOptions);
    } else if (a_convertFunction) {
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
  typename BasicVariant<innerBufferSize>::UnrefInfo BasicVariant<innerBufferSize>::_getUnref() {
    if (!_typeInfo){
      return UnrefInfo{0, 0, 0, false};
    }
    void* p              = ptr();
    BaseTypeWrapper* wrp = _getWrapper();
    const TypeInfo* ti   = _typeInfo;
    bool isConst         = ti ? TypeIndexConverter<>::isConst(ti->index) : false;
    if (!ti || !ti->isVariantRef) {
      return UnrefInfo{ti, wrp, p, isConst};
    }
    while (true) {
      const TypeInfo* nextTypeInfo = ((BasicVariant*)p)->getTypeInfo();
      if (nextTypeInfo && TypeIndexConverter<>::isReference(nextTypeInfo->index)) {
        ti = nextTypeInfo;
        wrp = ((BasicVariant*)p)->_getWrapper();
        p = ((BasicVariant*)p)->ptr();
        isConst |= TypeIndexConverter<>::isConst(ti->index);
        if (ti->isVariantRef) {
          continue;
        }
      }
      break;
    }
    return UnrefInfo{ti, wrp, p, isConst};
  }

  template <size_t innerBufferSize>
  typename BasicVariant<innerBufferSize>::VariantEndpoint BasicVariant<innerBufferSize>::_variantEndpoint(){
    VariantEndpoint result{this, false, innerBufferSize};
    while((((BasicVariant*)result.variant)->_typeInfo) && (((BasicVariant*)result.variant)->_typeInfo->isVariantRef)){
      result.innerSize = ((BasicVariant*)result.variant)->_typeInfo->innerSize;
      result.isConst |= TypeIndexConverter<>::isConst( ((BasicVariant*)result.variant)->_typeInfo->index );
      result.variant  = ((BasicVariant*)result.variant)->ptr();
    }
    return result;
  }

  template <size_t innerBufferSize>
  typename BasicVariant<innerBufferSize>::DataEndpoint BasicVariant<innerBufferSize>::_dataEndpoint() {
    if (!_typeInfo){
      return DataEndpoint{0, 0};
    }
    void* p              = ptr();
    const TypeInfo* ti   = _typeInfo;
    while (ti && ti->isVariant) {
      ti = ((BasicVariant*)p)->getTypeInfo();
      p = ((BasicVariant*)p)->ptr();
    }
    return DataEndpoint{ti, p};
  }

  template <size_t innerBufferSize>
  typename BasicVariant<innerBufferSize>::DataEndpointEx BasicVariant<innerBufferSize>::_dataEndpointEx() {
    if (!_typeInfo){
      return DataEndpointEx{0, 0, 0};
    }
    void* p              = ptr();
    const TypeInfo* ti   = _typeInfo;
    BaseTypeWrapper* wrp = (BaseTypeWrapper*)_getWrapper();
    while (ti && ti->isVariant) {
      ti = ((BasicVariant*)p)->getTypeInfo();
      wrp = ((BasicVariant*)p)->_getWrapper();
      p = ((BasicVariant*)p)->ptr();
    }
    return DataEndpointEx{ti, p, wrp};
  }

  template <size_t innerBufferSize>
  template <typename Ty>
  bool BasicVariant<innerBufferSize>::_less(const Ty& a_value) const{
    auto selfUnref = ((BasicVariant*)this)->_dataEndpoint();
    if (!selfUnref.typeInfo) {
      return true;
    }

    typedef typename std::remove_reference<Ty>::type ArgType;

    unsigned int argTypeIndex = Type<ArgType>().index();
    if (selfUnref.typeInfo->dataIndex == argTypeIndex) {
      return selfUnref.typeInfo->template getSafeSpecificatorCall<LessSpecificator>()(selfUnref.ptr, &a_value);
    } else {
      try {
        Variant buffer(selfUnref.typeInfo->index, &a_value, argTypeIndex);
        return selfUnref.typeInfo->template getSafeSpecificatorCall<LessSpecificator>()(selfUnref.ptr, buffer.ptr());
      } catch(...) {
        return selfUnref.typeInfo->dataIndex < argTypeIndex;
      }
    }
  }

  template <size_t innerBufferSize>
  template <typename Ty>
  bool BasicVariant<innerBufferSize>::_lessEqual(const Ty& a_value) const {
    auto selfUnref = ((BasicVariant*)this)->_dataEndpoint();
    if (!selfUnref.typeInfo) {
      return true;
    }

    typedef typename std::remove_reference<Ty>::type ArgType;

    unsigned int argTypeIndex = Type<ArgType>().index();
    if (selfUnref.typeInfo->dataIndex == argTypeIndex) {
      bool res = selfUnref.typeInfo->template getSafeSpecificatorCall<LessSpecificator>()(selfUnref.ptr, &a_value);
      if (res) {
        return true;
      }
      return selfUnref.typeInfo->template getSafeSpecificatorCall<EqualSpecificator>()(selfUnref.ptr, &a_value);
    } else {
      try {
        Variant buffer(selfUnref.typeInfo->dataIndex, &a_value, argTypeIndex);
        bool res = selfUnref.typeInfo->template getSafeSpecificatorCall<LessSpecificator>()(selfUnref.ptr, buffer.ptr());
        if (res) {
          return true;
        }
        return selfUnref.typeInfo->template getSafeSpecificatorCall<EqualSpecificator>()(selfUnref.ptr, buffer.ptr());
      } catch(...) {
        return selfUnref.typeInfo->dataIndex < argTypeIndex;
      }
    }
  }

  template <size_t innerBufferSize>
  template <typename Ty>
  bool BasicVariant<innerBufferSize>::_equal(const Ty& a_value) const {
    auto selfUnref = ((BasicVariant*)this)->_dataEndpoint();
    if (!selfUnref.typeInfo) {
      return false;
    }

    typedef typename std::remove_reference<Ty>::type ArgType;

    unsigned int argTypeIndex = Type<ArgType>().index();
    if (selfUnref.typeInfo->dataIndex == argTypeIndex) {
      return selfUnref.typeInfo->template getSafeSpecificatorCall<EqualSpecificator>()(selfUnref.ptr, &a_value);
    }

    try {
      Variant buffer(selfUnref.typeInfo->dataIndex, &a_value, argTypeIndex);
      return selfUnref.typeInfo->template getSafeSpecificatorCall<EqualSpecificator>()(selfUnref.ptr, buffer.ptr());
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

    if (TypeIndexConverter<>().isConst(getTypeIndex())){
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

    if (TypeIndexConverter<>().isConst(getTypeIndex())){
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

    if (TypeIndexConverter<>().isConst(getTypeIndex())){
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

    if (TypeIndexConverter<>().isConst(getTypeIndex())){
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
        return ResolveData{a_object->ptr(), a_object->getTypeIndex(), true};
      } else {
        return ResolveData{0, 0, true};
      }
    }
  };


} // fcf namespace


#endif // #ifndef ___FCF_BASIS__VARIANT_HPP___
