#ifndef ___FCF_BASIS__BITS__PART_VARIANT__VARIANT_HPP___
#define ___FCF_BASIS__BITS__PART_VARIANT__VARIANT_HPP___


#include "../../PartType.hpp"
#include "../../bits/registry.hpp"
#include "../../bits/PartType/DynamicType.hpp"
#include "../../bits/PartConvert/convertRuntime.hpp"
#include "../../bits/PartSpecifier/StoredDataTypeSpecifier.hpp"
#include "../../bits/PartSpecifier/LessSpecifier.hpp"
#include "../../bits/PartSpecifier/EqualSpecifier.hpp"
#include "../../bits/PartSpecifier/AddSpecifier.hpp"
#include "../../bits/PartSpecifier/SubSpecifier.hpp"
#include "../../bits/PartSpecifier/MulSpecifier.hpp"
#include "../../bits/PartSpecifier/DivSpecifier.hpp"
#include "../../bits/PartSpecifier/BoolSpecifier.hpp"
#include "../../bits/PartSpecifier/ContainerAccessSpecifier.hpp"
#include "../../bits/PartVariant/NDetails/VariantAllocator.hpp"
#include "../../bits/PartContainerAccess/VariantCursor.hpp"
#include "../../PartException.hpp"

#include "VariantDefinition.hpp"

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
    _clone<BasicVariant<InputInnerBufferSize>, const BasicVariant<InputInnerBufferSize> >(std::false_type(), a_variant, RESET);
  }

  template <size_t innerBufferSize>
  template <size_t InputInnerBufferSize>
  BasicVariant<innerBufferSize>::BasicVariant(BasicVariant<InputInnerBufferSize>& a_variant)
    : _typeInfo(0) {
    _clone<BasicVariant<InputInnerBufferSize>, BasicVariant<InputInnerBufferSize> >(std::false_type(), a_variant, RESET);
  }

  template <size_t innerBufferSize>
  template <size_t InputInnerBufferSize>
  BasicVariant<innerBufferSize>::BasicVariant(const BasicVariant<InputInnerBufferSize>& a_variant, DataSetMode a_dataMode)
    : _typeInfo(0) {
    _clone<BasicVariant<InputInnerBufferSize>, const BasicVariant<InputInnerBufferSize> >(std::false_type(), a_variant, a_dataMode);
  }

  template <size_t innerBufferSize>
  template <size_t InputInnerBufferSize>
  BasicVariant<innerBufferSize>::BasicVariant(BasicVariant<InputInnerBufferSize>& a_variant, DataSetMode a_dataMode)
    : _typeInfo(0) {
    _clone<BasicVariant<InputInnerBufferSize>, BasicVariant<InputInnerBufferSize> >(std::false_type(), a_variant, a_dataMode);
  }

  template <size_t innerBufferSize>
  BasicVariant<innerBufferSize>::BasicVariant(const BasicVariant& a_variant)
    : _typeInfo(0) {
    _clone<BasicVariant, const BasicVariant >(std::false_type(), a_variant, RESET);
  }

  template <size_t innerBufferSize>
  BasicVariant<innerBufferSize>::BasicVariant(const BasicVariant& a_variant, DataSetMode a_dataMode)
    : _typeInfo(0) {
    _clone<BasicVariant, const BasicVariant >(std::false_type(), a_variant, a_dataMode);
  }

  template <size_t innerBufferSize>
  BasicVariant<innerBufferSize>::BasicVariant(BasicVariant& a_variant, DataSetMode a_dataMode)
    : _typeInfo(0) {
    _clone<BasicVariant, BasicVariant>(std::false_type(), a_variant, a_dataMode);
  }

  template <size_t innerBufferSize>
  template <typename Ty>
  BasicVariant<innerBufferSize>::BasicVariant(const Ty& a_value)
    : _typeInfo(0) {
    _init<Ty, Ty>(std::false_type(), a_value, RESET);
  }

  template <size_t innerBufferSize>
  template <typename Ty>
  BasicVariant<innerBufferSize>::BasicVariant(const Ty& a_value, DataSetMode a_dataMode)
    : _typeInfo(0) {
    _init<Ty, const Ty>(std::false_type(), a_value, a_dataMode);
  }

  template <size_t innerBufferSize>
  template <typename Ty>
  BasicVariant<innerBufferSize>::BasicVariant(Ty& a_value, DataSetMode a_dataMode)
    : _typeInfo(0) {
    _init<Ty, Ty>(std::false_type(), a_value, a_dataMode);
  }


  template <size_t innerBufferSize>
  template <typename Ty, typename TSource>
  BasicVariant<innerBufferSize>::BasicVariant(const Type<Ty>& /*a_type*/, TSource& a_value, DataSetMode a_dataMode)
    : _typeInfo(0) {
    typedef typename std::remove_reference< typename std::remove_const<Ty>::type >::type      ResType;
    typedef typename std::remove_reference< typename std::remove_const<TSource>::type >::type SrcType;
    _init<Ty, Ty>(typename MetaTypeBoolean< !std::is_same<ResType, SrcType>::value >::Type(), a_value, a_dataMode);
  }

  template <size_t innerBufferSize>
  template <typename Ty, typename TSource>
  BasicVariant<innerBufferSize>::BasicVariant(const Type<Ty>& /*a_type*/, const TSource& a_value, DataSetMode a_dataMode)
    : _typeInfo(0) {
    typedef typename std::remove_reference< typename std::remove_const<Ty>::type >::type      ResType;
    typedef typename std::remove_reference< typename std::remove_const<TSource>::type >::type SrcType;
    _init<Ty, Ty>(typename MetaTypeBoolean< !std::is_same<ResType, SrcType>::value >::Type(), a_value, a_dataMode);
  }

  template <size_t innerBufferSize>
  template <typename Ty, size_t InputInnerBufferSize>
  BasicVariant<innerBufferSize>::BasicVariant(const Type<Ty>& /*a_type*/, BasicVariant<InputInnerBufferSize>& a_value, DataSetMode a_dataMode)
    : _typeInfo(0) {
    typedef typename std::remove_reference< typename std::remove_const<Ty>::type >::type      ResType;
    _clone<Ty, Ty>(typename MetaTypeBoolean< !std::is_same<ResType, BasicVariant<InputInnerBufferSize> >::value >::Type(), a_value, a_dataMode);
  }

  template <size_t innerBufferSize>
  template <typename Ty, size_t InputInnerBufferSize>
  BasicVariant<innerBufferSize>::BasicVariant(const Type<Ty>& /*a_type*/, const BasicVariant<InputInnerBufferSize>& a_value, DataSetMode a_dataMode)
    : _typeInfo(0) {
    typedef typename std::remove_reference< typename std::remove_const<Ty>::type >::type      ResType;
    _clone<Ty, Ty>(typename MetaTypeBoolean< !std::is_same<ResType, BasicVariant<InputInnerBufferSize> >::value >::Type(), a_value, a_dataMode);
  }

  template <size_t innerBufferSize>
  BasicVariant<innerBufferSize>::BasicVariant(const char* a_value)
    : _typeInfo(0) {
    _init<const char*, const char*>(std::false_type(), a_value, RESET);
  }

  template <size_t innerBufferSize>
  BasicVariant<innerBufferSize>::BasicVariant(const char* a_value, DataSetMode a_dataMode)
    : _typeInfo(0) {
    _init<const char*, const char*>(std::false_type(), a_value, a_dataMode);
  }

  template <size_t innerBufferSize>
  template <typename Ty>
  BasicVariant<innerBufferSize>::BasicVariant(Type<Ty, Nop> a_type){
    _ptr = a_type.typeInfo()->initializer->create(_size(a_type.typeInfo()) <= innerBufferSize ? (void*)&_mem[0] : (void*)0);
    _typeInfo = a_type.typeInfo();
  }

  template <size_t innerBufferSize>
  BasicVariant<innerBufferSize>::BasicVariant(DynamicType a_dynamicType){
    const unsigned int index = a_dynamicType.index();
    if (!index){
      _typeInfo = 0;
      _ptr = 0;
      return;
    }
    size_t dataSize = _size(a_dynamicType.getTypeInfo());
    _ptr = a_dynamicType.getTypeInfo()->initializer->create( dataSize <= innerBufferSize ? &_mem[0] : 0 );
    _typeInfo = a_dynamicType.getTypeInfo();
  }

  template <size_t innerBufferSize>
  BasicVariant<innerBufferSize>::BasicVariant(const TypeInfo* a_typeInfo) {
    if (!a_typeInfo) {
      _typeInfo = 0;
      _ptr = 0;
      return;
    }
    size_t dataSize = _size(a_typeInfo);
    _ptr = a_typeInfo->initializer->create(dataSize <= innerBufferSize ? &_mem[0] : 0);
    _typeInfo = a_typeInfo;
  }

  template <size_t innerBufferSize>
  BasicVariant<innerBufferSize>::~BasicVariant(){
    _destroy();
  }

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

    size_t dataSize = _size(a_dynamicType.getTypeInfo());
    _ptr = a_dynamicType.getTypeInfo()->initializer->create( dataSize <= innerBufferSize ? &_mem[0] : 0 );
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

    size_t dataSize = _size(a_typeInfo);
    _ptr = a_typeInfo->initializer->create( dataSize <= innerBufferSize ? &_mem[0] : 0 );
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

    _ptr = a_type.typeInfo()->initializer->create(_size(a_type.typeInfo()) <= innerBufferSize ? (void*)&_mem[0] : (void*)0);
    _typeInfo = a_type.typeInfo();
  }

  template <size_t innerBufferSize>
  BasicVariant<innerBufferSize>& BasicVariant<innerBufferSize>::operator=(const BasicVariant<innerBufferSize>& a_variant)
  {
    _clone<BasicVariant<innerBufferSize>, const BasicVariant<innerBufferSize> >(std::false_type(), a_variant, WRITE);
    return *this;
  }

  template <size_t innerBufferSize>
  template <size_t InputInnerBufferSize>
  BasicVariant<innerBufferSize>& BasicVariant<innerBufferSize>::operator=(const BasicVariant<InputInnerBufferSize>& a_variant)
  {
    _clone<BasicVariant<InputInnerBufferSize>, const BasicVariant<InputInnerBufferSize> >(std::false_type(), a_variant, WRITE);
    return *this;
  }

  template <size_t innerBufferSize>
  template <typename Ty>
  BasicVariant<innerBufferSize>& BasicVariant<innerBufferSize>::operator=(const Ty& a_value)
  {
    _reset<Ty, Ty>(a_value, WRITE);
    return *this;
  }

  template <size_t innerBufferSize>
  BasicVariant<innerBufferSize>& BasicVariant<innerBufferSize>::operator=(const char* a_value)
  {
    _reset<const char*, const char*>(a_value, WRITE);
    return *this;
  }

  template <size_t innerBufferSize>
  void BasicVariant<innerBufferSize>::set(const BasicVariant<innerBufferSize>& a_variant)
  {
    _clone<BasicVariant<innerBufferSize>, const BasicVariant<innerBufferSize> >(std::false_type(), a_variant, WRITE);
  }

  template <size_t innerBufferSize>
  void BasicVariant<innerBufferSize>::set(const BasicVariant<innerBufferSize>& a_variant, DataSetMode a_dataMode)
  {
    _clone<BasicVariant<innerBufferSize>, const BasicVariant<innerBufferSize> >(std::false_type(), a_variant, a_dataMode);
  }

  template <size_t innerBufferSize>
  void BasicVariant<innerBufferSize>::set(BasicVariant<innerBufferSize>& a_variant, DataSetMode a_dataMode)
  {
    _clone<BasicVariant<innerBufferSize>, BasicVariant<innerBufferSize> >(std::false_type(), a_variant, a_dataMode);
  }

  template <size_t innerBufferSize>
  template <typename Ty>
  void BasicVariant<innerBufferSize>::set(const Ty& a_value)
  {
    _reset<Ty, Ty>(a_value, WRITE);
  }

  template <size_t innerBufferSize>
  template <typename Ty>
  void BasicVariant<innerBufferSize>::set(Ty& a_value, DataSetMode a_dataMode)
  {
    _reset<Ty, Ty>(a_value, a_dataMode);
  }

  template <size_t innerBufferSize>
  template <typename Ty>
  void BasicVariant<innerBufferSize>::set(const Ty& a_value, DataSetMode a_dataMode)
  {
    _reset<Ty, const Ty>(a_value, a_dataMode);
  }

  template <size_t innerBufferSize>
  void BasicVariant<innerBufferSize>::set(const char* a_value)
  {
    _reset<const char*, const char*>(a_value, WRITE);
  }

  template <size_t innerBufferSize>
  void BasicVariant<innerBufferSize>::set(const char* a_value, DataSetMode a_dataMode)
  {
    _reset<const char*, const char*>(a_value, a_dataMode);
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
  size_t BasicVariant<innerBufferSize>::containerSize() const{
    if (!_typeInfo){
      return 0;
    }
    UniversalCall call = _typeInfo->specifierUniversalCall<ContainerAccessSpecifier>(0);
    if (!call) {
      return 0;
    }

    Variant vdca = call((void*)ptr(), 0, 0);
    DynamicContainerAccessBase* pdca = (DynamicContainerAccessBase*)vdca.ptr();
    return pdca->getContainerSize();
  }

  template <size_t innerBufferSize>
  bool BasicVariant<innerBufferSize>::isContainer() const {
    if (!_typeInfo){
      return false;
    }
    UniversalCall call = _typeInfo->specifierUniversalCall<ContainerAccessSpecifier>(0);
    return !!call;
  }


  template <size_t innerBufferSize>
  void BasicVariant<innerBufferSize>::erase(const BasicVariant& a_key){
    if (!_typeInfo){
      return;
    }
    UniversalCall call = _typeInfo->specifierUniversalCall<ContainerAccessSpecifier>(0);
    if (!call) {
      return;
    }
    Variant vdca = call(ptr(), 0, 0);
    DynamicContainerAccessBase* pdca = (DynamicContainerAccessBase*)vdca.ptr();
    pdca->setPosition(a_key, false);
    if (pdca->isEnd()){
      return;
    }
    Variant vdcaEnd(vdca);
    DynamicContainerAccessBase* pdcaEnd = (DynamicContainerAccessBase*)vdcaEnd.ptr();
    pdcaEnd->inc();
    pdca->erase(*pdcaEnd);
  }

  template <size_t innerBufferSize>
  void BasicVariant<innerBufferSize>::erase(const iterator& a_iterator){
    if (!_typeInfo){
      return;
    }
    UniversalCall call = _typeInfo->specifierUniversalCall<ContainerAccessSpecifier>(0);
    if (!call) {
      return;
    }
    DynamicContainerAccessBase* pdca = (DynamicContainerAccessBase*)a_iterator.cursor.iterator.ptr();
    Variant vdcaEnd(a_iterator.cursor.iterator);
    DynamicContainerAccessBase* pdcaEnd = (DynamicContainerAccessBase*)vdcaEnd.ptr();
    pdcaEnd->inc();

    pdca->erase(*pdcaEnd);
  }

  template <size_t innerBufferSize>
  void BasicVariant<innerBufferSize>::erase(const iterator& a_begin, const iterator& a_end){
    if (!_typeInfo){
      return;
    }
    UniversalCall call = _typeInfo->specifierUniversalCall<ContainerAccessSpecifier>(0);
    if (!call) {
      return;
    }
    DynamicContainerAccessBase* pdca = (DynamicContainerAccessBase*)a_begin.cursor.iterator.ptr();
    DynamicContainerAccessBase* pdcaEnd = (DynamicContainerAccessBase*)a_end.cursor.iterator.ptr();
    pdca->erase(*pdcaEnd);
  }

  template <size_t innerBufferSize>
  Variant BasicVariant<innerBufferSize>::operator[](const Variant& a_key){
    UniversalCall call = _typeInfo->specifierUniversalCall<ContainerAccessSpecifier>(0);
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
    if (!p) {
      return false;
    }
    BoolSpecifier::CallType c = _typeInfo->specifierCall<BoolSpecifier>(0);
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
    const unsigned int selfDataIndex = TypeIndexConverter<>::getDataIndex(selfUnref.typeInfo->index);
    const unsigned int argDataIndex = TypeIndexConverter<>::getDataIndex(argUnref.typeInfo->index);
    try {
      if (selfDataIndex == argDataIndex) {
        return selfUnref.typeInfo->template specifierCall<LessSpecifier>()(selfUnref.ptr, argUnref.ptr);
      } else {
        Variant buffer(selfDataIndex, argUnref.ptr, argDataIndex);
        return selfUnref.typeInfo->template specifierCall<LessSpecifier>()(selfUnref.ptr, buffer.ptr());
      }
    } catch(...) {
      return selfDataIndex < argDataIndex;
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
    const unsigned int selfDataIndex = TypeIndexConverter<>::getDataIndex(selfUnref.typeInfo->index);
    const unsigned int argDataIndex = TypeIndexConverter<>::getDataIndex(argUnref.typeInfo->index);
    try {
      if (selfDataIndex == argDataIndex) {
        bool res = selfUnref.typeInfo->template specifierCall<LessSpecifier>()(selfUnref.ptr, argUnref.ptr);
        if (res){
          return true;
        }
        return selfUnref.typeInfo->template specifierCall<EqualSpecifier>()(selfUnref.ptr, argUnref.ptr);
      } else {
        Variant buffer(selfDataIndex, argUnref.ptr, argDataIndex);
        bool res = selfUnref.typeInfo->template specifierCall<LessSpecifier>()(selfUnref.ptr, buffer.ptr());
        if (res) {
          return true;
        }
        return selfUnref.typeInfo->template specifierCall<EqualSpecifier>()(selfUnref.ptr, buffer.ptr());
      }
    } catch(...){
      return selfDataIndex < argDataIndex;
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
    const unsigned int selfDataIndex = TypeIndexConverter<>::getDataIndex(selfUnref.typeInfo->index);
    const unsigned int argDataIndex = TypeIndexConverter<>::getDataIndex(argUnref.typeInfo->index);
    try {
      if (selfDataIndex == argDataIndex) {
        return selfUnref.typeInfo->template specifierCall<EqualSpecifier>()(selfUnref.ptr, argUnref.ptr);
      } else {
        Variant buffer(selfDataIndex, argUnref.ptr, argDataIndex);
        return selfUnref.typeInfo->template specifierCall<EqualSpecifier>()(selfUnref.ptr, buffer.ptr());
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
    return _selfCalcTo<AddSpecifier>(a_value);
  }

  template <size_t innerBufferSize>
  template <typename Ty>
  BasicVariant<innerBufferSize>& BasicVariant<innerBufferSize>::operator+=(const Ty& a_value){
    return _calcTo<AddSpecifier>(a_value);
  }

  template <size_t innerBufferSize>
  BasicVariant<innerBufferSize>& BasicVariant<innerBufferSize>::operator+=(const char* a_value){
    return _calcTo<AddSpecifier>(a_value);
  }

  template <size_t innerBufferSize>
  BasicVariant<innerBufferSize> BasicVariant<innerBufferSize>::operator+(const BasicVariant<innerBufferSize>& a_value) const{
    return _selfCalc<AddSpecifier>(a_value);
  }

  template <size_t innerBufferSize>
  template <typename Ty>
  BasicVariant<innerBufferSize> BasicVariant<innerBufferSize>::operator+(const Ty& a_value) const {
    return _calc<AddSpecifier>(a_value);
  }

  template <size_t innerBufferSize>
  BasicVariant<innerBufferSize> BasicVariant<innerBufferSize>::operator+(const char* a_value) const {
    return _calc<AddSpecifier>(a_value);
  }

  template <size_t innerBufferSize>
  BasicVariant<innerBufferSize>& BasicVariant<innerBufferSize>::operator-=(const BasicVariant<innerBufferSize>& a_value){
    return _selfCalcTo<SubSpecifier>(a_value);
  }

  template <size_t innerBufferSize>
  template <typename Ty>
  BasicVariant<innerBufferSize>& BasicVariant<innerBufferSize>::operator-=(const Ty& a_value){
    return _calcTo<SubSpecifier>(a_value);
  }

  template <size_t innerBufferSize>
  BasicVariant<innerBufferSize>& BasicVariant<innerBufferSize>::operator-=(const char* a_value){
    return _calcTo<SubSpecifier>(a_value);
  }

  template <size_t innerBufferSize>
  BasicVariant<innerBufferSize> BasicVariant<innerBufferSize>::operator-(const BasicVariant<innerBufferSize>& a_value) const{
    return _selfCalc<SubSpecifier>(a_value);
  }

  template <size_t innerBufferSize>
  template <typename Ty>
  BasicVariant<innerBufferSize> BasicVariant<innerBufferSize>::operator-(const Ty& a_value) const{
    return _calc<SubSpecifier>(a_value);
  }

  template <size_t innerBufferSize>
  BasicVariant<innerBufferSize> BasicVariant<innerBufferSize>::operator-(const char* a_value) const{
    return _calc<SubSpecifier>(a_value);
  }

  template <size_t innerBufferSize>
  BasicVariant<innerBufferSize>& BasicVariant<innerBufferSize>::operator*=(const BasicVariant<innerBufferSize>& a_value){
    return _selfCalcTo<MulSpecifier>(a_value);
  }

  template <size_t innerBufferSize>
  template <typename Ty>
  BasicVariant<innerBufferSize>& BasicVariant<innerBufferSize>::operator*=(const Ty& a_value){
    return _calcTo<MulSpecifier>(a_value);
  }

  template <size_t innerBufferSize>
  BasicVariant<innerBufferSize>& BasicVariant<innerBufferSize>::operator*=(const char* a_value){
    return _calcTo<MulSpecifier>(a_value);
  }


  template <size_t innerBufferSize>
  BasicVariant<innerBufferSize> BasicVariant<innerBufferSize>::operator*(const BasicVariant<innerBufferSize>& a_value) const{
    return _selfCalc<MulSpecifier>(a_value);
  }

  template <size_t innerBufferSize>
  template <typename Ty>
  BasicVariant<innerBufferSize> BasicVariant<innerBufferSize>::operator*(const Ty& a_value) const{
    return _calc<MulSpecifier>(a_value);
  }

  template <size_t innerBufferSize>
  BasicVariant<innerBufferSize> BasicVariant<innerBufferSize>::operator*(const char* a_value) const{
    return _calc<MulSpecifier>(a_value);
  }

  template <size_t innerBufferSize>
  BasicVariant<innerBufferSize>& BasicVariant<innerBufferSize>::operator/=(const BasicVariant<innerBufferSize>& a_value){
    return _selfCalcTo<DivSpecifier>(a_value);
  }

  template <size_t innerBufferSize>
  template <typename Ty>
  BasicVariant<innerBufferSize>& BasicVariant<innerBufferSize>::operator/=(const Ty& a_value){
    return _calcTo<DivSpecifier>(a_value);
  }

  template <size_t innerBufferSize>
  BasicVariant<innerBufferSize>& BasicVariant<innerBufferSize>::operator/=(const char* a_value){
    return _calcTo<DivSpecifier>(a_value);
  }


  template <size_t innerBufferSize>
  BasicVariant<innerBufferSize> BasicVariant<innerBufferSize>::operator/(const BasicVariant<innerBufferSize>& a_value) const{
    return _selfCalc<DivSpecifier>(a_value);
  }

  template <size_t innerBufferSize>
  template <typename Ty>
  BasicVariant<innerBufferSize> BasicVariant<innerBufferSize>::operator/(const Ty& a_value) const{
    return _calc<DivSpecifier>(a_value);
  }

  template <size_t innerBufferSize>
  BasicVariant<innerBufferSize> BasicVariant<innerBufferSize>::operator/(const char* a_value) const{
    return _calc<DivSpecifier>(a_value);
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
    return _typeInfo ? TypeIndexConverter<>::getDataIndex(_typeInfo->index) : 0;
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
        ResolveSpecifier::CallType resolveCall = ti->specifierCall<ResolveSpecifier>(0);
        if (resolveCall) {
          ResolveData rd = resolveCall(ptr());
          if (rd.data){
            unsigned int resultDataIndex = TypeIndexConverter<>::getDataIndex(Type<TResult>().index());
            unsigned int dataDataIndex   = TypeIndexConverter<>::getDataIndex(rd.typeIndex);
            if (resultDataIndex == dataDataIndex){
              return *(result_type*)rd.data;
            } else {
              ti = ::fcf::getTypeInfo(rd.typeIndex);
              continue;
            }
          }
        }
        ti = 0;
      }
      throw VariantTypeMismatchExeption(__FILE__, __LINE__, (_typeInfo ? _typeInfo->name.c_str() : "undefined"), Type<TResult>().name());
    } else {
      return *(result_type*)ptr();
    }
  }

  template <size_t innerBufferSize>
  template <typename TResult>
  TResult BasicVariant<innerBufferSize>::cast() const{
    typedef typename std::remove_const<TResult>::type ResultType;

    static const unsigned int selfVariantTypeIndex  = Type<BasicVariant>().index();
    static const unsigned int variantTypeIndex      = Type<Variant>().index();
    const unsigned int selfDataIndex = getDataTypeIndex();
    if (!_typeInfo){
      return ResultType();
    } if (selfDataIndex == Type<ResultType>().dataIndex()){
      return *(ResultType*)ptr();
    } else if (selfDataIndex == selfVariantTypeIndex) {
      return ((BasicVariant*)ptr())->cast<ResultType>();
    } else if (selfDataIndex == variantTypeIndex) {
      return ((Variant*)ptr())->cast<ResultType>();
    } else {
      ResultType result;
      convertRuntimeByDestination(&result, ptr(), getDataTypeIndex());
      return result;
    }
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
      _typeInfo->initializer->destroy(_ptr);
      if (!isInnerMemory()){
        TypeFactoryBase::deallocate(_ptr);
      }
    }
  }

  template <size_t innerBufferSize>
  template <typename DataType, typename ReferenceType, size_t InputInnerBufferSize>
  void BasicVariant<innerBufferSize>::_clone(std::true_type /*a_enableConvert*/, const BasicVariant<InputInnerBufferSize>& a_variant, DataSetMode a_dataMode) {
    if (a_dataMode & FORCE_REFERENCE) {
      throw VariantSetReferenceTypeException(__FILE__, __LINE__, (a_variant._typeInfo ? a_variant._typeInfo->name.c_str() : "undefined"), Type<Variant>().name()+"&");
    }
    if (a_dataMode & REFERENCE) {
      if (a_variant._typeInfo && TypeIndexConverter<>::getDataIndex(a_variant._typeInfo->index) == Type<ReferenceType>().dataIndex() ){
        if (TypeIndexConverter<>::isConst(Type<ReferenceType>().index())) {
          _clone< const BasicVariant<InputInnerBufferSize>, const BasicVariant<InputInnerBufferSize> >(std::false_type(), a_variant, a_dataMode);
        } else {
          _clone< BasicVariant<InputInnerBufferSize>, BasicVariant<InputInnerBufferSize> >(std::false_type(), a_variant, a_dataMode);
        }
        return;
      } else {
        throw VariantSetReferenceTypeException(__FILE__, __LINE__, (a_variant._typeInfo ? a_variant._typeInfo->name.c_str() : "undefined"), Type<ReferenceType&>().name() );
      }
    }
    DataType source = a_variant.template cast<DataType>();
    _reset<DataType, DataType>(source, a_dataMode);
  }

  template <size_t innerBufferSize>
  template <typename DataType, typename ReferenceType, size_t InputInnerBufferSize>
  void BasicVariant<innerBufferSize>::_clone(std::false_type /*a_enableConvert*/, const BasicVariant<InputInnerBufferSize>& a_variant, DataSetMode a_dataMode) {
    switch (a_dataMode){
      case WRITE:
      {
        VariantEndpoint                                             selfEndpoint   = _variantEndpoint();
        typename BasicVariant<InputInnerBufferSize>::DataEndpointEx sourceEndpoint = ((BasicVariant<InputInnerBufferSize>&)a_variant)._dataEndpointEx();

        if (selfEndpoint.isConst){
          throw VariantReadOnlyException(__FILE__, __LINE__);
        }
        BasicVariant* curVariant =  (BasicVariant*)selfEndpoint.variant;
        if (curVariant->_typeInfo && 
            !(curVariant->_typeInfo->flags & TIF_VARIANT)  && 
            TypeIndexConverter<>::isReference(curVariant->_typeInfo->index)) {
          if (TypeIndexConverter<>::isConst(curVariant->_typeInfo->index)){
            throw VariantReadOnlyException(__FILE__, __LINE__);
          }
          if (sourceEndpoint.typeInfo) {
            const unsigned int curVariantDataIndex = TypeIndexConverter<>::getDataIndex(curVariant->_typeInfo->index);
            const unsigned int sourceDataIndex     = TypeIndexConverter<>::getDataIndex(sourceEndpoint.typeInfo->index);
            if (curVariantDataIndex == sourceDataIndex) {
              curVariant->_typeInfo->initializer->set(curVariant->_ptr, sourceEndpoint.ptr);
            } else {
              Variant buffer(curVariantDataIndex, sourceEndpoint.ptr, sourceEndpoint.typeInfo->index);
              curVariant->_typeInfo->initializer->set( curVariant->_ptr, buffer.ptr());
            }
          } else {
            throw VariantEmptyToReferenceException(__FILE__, __LINE__);
          }
        } else {
          if (curVariant->_typeInfo){
            if (TypeIndexConverter<>::isConst(curVariant->_typeInfo->index)){
              throw VariantReadOnlyException(__FILE__, __LINE__);
            }
            curVariant->_typeInfo->initializer->destroy( curVariant->_ptr );
            if (_size(curVariant->_typeInfo) > selfEndpoint.innerSize ){
              TypeFactoryBase::deallocate(curVariant->_ptr);
            }
            curVariant->_ptr = 0;
            curVariant->_typeInfo = 0;
          }
          const TypeInfo* newTypeInfo        = sourceEndpoint.typeInfo;
          const unsigned int sourceDataIndex = TypeIndexConverter<>::getDataIndex(sourceEndpoint.typeInfo->index);
          if (sourceEndpoint.typeInfo->index != sourceDataIndex){
            newTypeInfo = ::fcf::getTypeInfo(sourceDataIndex) ;
          } else {
            newTypeInfo = sourceEndpoint.typeInfo;
          }
          if (sourceEndpoint.typeInfo){
            curVariant->_ptr = newTypeInfo->initializer->clone(
                                     (_size(newTypeInfo) <= selfEndpoint.innerSize)
                                        ? (void*)&curVariant->_mem[0]
                                        : (void*)0,
                                     sourceEndpoint.ptr
                                    );
            curVariant->_typeInfo = newTypeInfo;
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
            _ptr = ui.typeInfo->initializer->clone((_size(ui.typeInfo) <= innerBufferSize) 
                                                      ? (void*)&_mem[0]
                                                      : (void*)0,
                                                    ui.ptr
                                                  );
            const unsigned int uiDataIndex = TypeIndexConverter<>::getDataIndex(ui.typeInfo->index);
            if (ui.typeInfo->index != uiDataIndex){
              ui.typeInfo = ::fcf::getTypeInfo(uiDataIndex);
            }
            _typeInfo = ui.typeInfo;
          }
        }
      break;
      case FORCE_REFERENCE:
      {
        if (this == (void*)&a_variant){
          return;
        }
        _destroy();
        _ptr = 0;
        _typeInfo = 0;
        typedef typename std::remove_reference< ReferenceType >::type& EndpointType;
        *(void**)(&_mem[0]) = (void*)&a_variant;
        _ptr = (void*)&a_variant;
        _typeInfo = Type<EndpointType>().typeInfo();
      }
      break;
      case REFERENCE:
      {
        if (this == (void*)&a_variant){
          return;
        }
        _destroy();
        _ptr = 0;
        _typeInfo = 0;
        if (a_variant._typeInfo) {
          unsigned int index = std::is_const<ReferenceType>::value 
                    ? TypeIndexConverter<>::getConstSingleReferenceIndex( a_variant._typeInfo->index )
                    : TypeIndexConverter<>::getSingleReferenceIndex( a_variant._typeInfo->index );
          const TypeInfo* refTypeInfo = ::fcf::getTypeInfo(index);
          *(void**)(&_mem[0]) = (void*)a_variant._ptr;
          _ptr = (void*)a_variant._ptr;
          _typeInfo = refTypeInfo;
        }
      }
      break;
    }
  }

  template <size_t innerBufferSize>
  template <typename DataType, typename ReferenceType, typename ArgTy>
  void BasicVariant<innerBufferSize>::_init(std::false_type /*a_enableConvert*/, ArgTy& a_value, DataSetMode a_dataMode) {
    switch (a_dataMode){
      case RESET:
      case WRITE:
        {
          typedef typename std::remove_reference< typename Type<DataType, StoredDataTypeSpecifier>::type >::type StoredType;
          _ptr = (void*)NDetails::VariantAllocator<StoredType, innerBufferSize>()(&_mem[0], a_value);
          _typeInfo = Type<StoredType>().typeInfo();
        }
        break;
      case FORCE_REFERENCE:
      case REFERENCE:
        {
          if (!std::is_const<ReferenceType>::value && std::is_const<ArgTy>::value){
            throw VariantAssignConstDataException(__FILE__, __LINE__);
          }
          typedef typename std::remove_reference< ReferenceType >::type EndpointType;
          typedef EndpointType& RefEndpointType;
          _ptr = *(void**)NDetails::VariantAllocator<EndpointType*, innerBufferSize>()(&_mem[0], (EndpointType*)&a_value);
          _typeInfo = Type<RefEndpointType>().typeInfo();
        }
        break;
    }
  }

  template <size_t innerBufferSize>
  template <typename DataType, typename ReferenceType, typename ArgTy>
  void BasicVariant<innerBufferSize>::_init(std::true_type /*a_enableConvert*/, ArgTy& a_value, DataSetMode a_dataMode) {
    if (a_dataMode & (REFERENCE|FORCE_REFERENCE)) {
      throw VariantSetReferenceTypeException(__FILE__, __LINE__, Type<ArgTy>().name()+"&", Type<Variant>().name()+"&");
    }
    Variant buffer(Type<DataType>().index(), &a_value, Type<ArgTy>().index());
    _init<DataType, DataType>(std::false_type(), *(DataType*)buffer.ptr(), a_dataMode);
  }

  template <size_t innerBufferSize>
  template <typename DataType, typename ReferenceType, typename Ty>
  void BasicVariant<innerBufferSize>::_reset(const Ty& a_value, DataSetMode a_dataMode) {
    switch (a_dataMode){
      case WRITE:
        {
          VariantEndpoint ve = _variantEndpoint();
          if (ve.isConst){
            throw VariantReadOnlyException(__FILE__, __LINE__);
          }
          BasicVariant* curVariant =  (BasicVariant*)ve.variant;
          if (curVariant->_typeInfo &&
              !(curVariant->_typeInfo->flags & TIF_VARIANT) &&
              TypeIndexConverter<>::isReference(curVariant->_typeInfo->index)) {
            if (TypeIndexConverter<>::isConst(curVariant->_typeInfo->index)){
              throw VariantReadOnlyException(__FILE__, __LINE__);
            }
            const unsigned int curVariantDataIndex = TypeIndexConverter<>::getDataIndex(curVariant->_typeInfo->index);
            if (curVariantDataIndex == Type<DataType>().dataIndex()) {
              curVariant->_typeInfo->initializer->set(curVariant->_ptr, &a_value);
            } else {
              Variant buffer(curVariantDataIndex, &a_value, Type<DataType>().dataIndex());
              curVariant->_typeInfo->initializer->set(curVariant->_ptr, buffer.ptr());
            }
          } else {
            if (curVariant->_typeInfo){
              if (TypeIndexConverter<>::isConst(curVariant->_typeInfo->index)){
                throw VariantReadOnlyException(__FILE__, __LINE__);
              }
              curVariant->_destroy();
              curVariant->_ptr = 0;
              curVariant->_typeInfo = 0;
            }
            typedef typename Type<DataType, StoredDataTypeSpecifier>::type StroredType;
            if (Type<StroredType>().dataIndex() == Type<DataType>().dataIndex()){
              const TypeInfo* ti = Type<StroredType>().typeInfo();
              curVariant->_ptr = ti->initializer->clone(_size(ti) <= ve.innerSize ? (void*)&curVariant->_mem[0] : 0, &a_value);
              curVariant->_typeInfo = ti;
            } else {
              const TypeInfo* storedTypeInfo    = Type<StroredType>().typeInfo();
              Variant buffer(storedTypeInfo->index, &a_value, Type<DataType>().dataIndex());
              curVariant->_ptr      = storedTypeInfo->initializer->clone(_size(storedTypeInfo) <= ve.innerSize ? (void*)&curVariant->_mem[0] : 0, buffer.ptr());
              curVariant->_typeInfo = storedTypeInfo;
            }
          }
          break;
        }
        break;
      case RESET:
        {
          typedef typename std::remove_reference< typename Type<DataType, StoredDataTypeSpecifier>::type >::type type;
          _destroy();
          _ptr = 0;
          _typeInfo = 0;
          _ptr = NDetails::VariantAllocator<type, innerBufferSize>()(&_mem[0], a_value);
          _typeInfo = Type<type>().typeInfo();
        }
        break;
      case FORCE_REFERENCE:
      case REFERENCE:
        {
          typedef typename std::remove_reference< typename Type<ReferenceType, StoredDataTypeSpecifier>::type >::type type;
          _destroy();
          _ptr = 0;
          _typeInfo = 0;
          *(void**)&_mem[0] = (void*)&a_value;
          _ptr = (void*)&a_value;
          _typeInfo = Type<type&>().typeInfo();
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
    if (a_sourceData && !a_sourceTypeIndex && !a_convertFunction) {
      _ptr = dt.getTypeInfo()->initializer->clone(_size(ti) <= innerBufferSize ? (void*)&_mem[0] : (void*)0, a_sourceData);
    } else {
      _ptr = dt.getTypeInfo()->initializer->create(_size(ti) <= innerBufferSize ? (void*)&_mem[0] : (void*)0);
    }

    _typeInfo = ti;

    if (a_sourceTypeIndex && !a_convertFunction) {
      convertRuntime(ptr(), a_typeIndex, a_sourceData, a_sourceTypeIndex, a_convertOptions);
    } else if (a_convertFunction) {
      a_convertFunction(ptr(), a_sourceData, a_convertOptions);
    }
  }


  template <size_t innerBufferSize>
  typename BasicVariant<innerBufferSize>::VariantEndpoint BasicVariant<innerBufferSize>::_variantEndpoint(){
    VariantEndpoint result{this, false, innerBufferSize};
    while((((BasicVariant*)result.variant)->_typeInfo) && (((BasicVariant*)result.variant)->_typeInfo->flags & TIF_VARIANT_REF)){
      result.innerSize = ((BasicVariant*)result.variant)->_typeInfo->variantInnerSize;
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
    size_t rcounter      = FCF_BASIS_VARIANT_MAX_REF_NESTING;
    while (ti && ti->flags & TIF_VARIANT) {
      ti = ((BasicVariant*)p)->getTypeInfo();
      p = ((BasicVariant*)p)->ptr();
      --rcounter;
      if (!rcounter){
        throw VariantMaxRefNesting(__FILE__, __LINE__);
      }
    }
    return DataEndpoint{ti, p};
  }

  template <size_t innerBufferSize>
  typename BasicVariant<innerBufferSize>::ConstDataEndpoint BasicVariant<innerBufferSize>::_constDataEndpoint() {
    if (!_typeInfo){
      return ConstDataEndpoint{0, 0, false};
    }
    ConstDataEndpoint result{_typeInfo, ptr(), false};

    while (result.typeInfo) {
      result.isConst |= TypeIndexConverter<>::isConst(result.typeInfo->index);
      if (result.typeInfo->flags & TIF_VARIANT) {
        result.typeInfo = ((BasicVariant*)result.ptr)->getTypeInfo();
        result.ptr = ((BasicVariant*)result.ptr)->ptr();
      } else {
        break;
      }
    }

    return result;
  }

  template <size_t innerBufferSize>
  typename BasicVariant<innerBufferSize>::DataEndpointEx BasicVariant<innerBufferSize>::_dataEndpointEx() {
    if (!_typeInfo){
      return DataEndpointEx{0, 0};
    }
    void* p              = ptr();
    const TypeInfo* ti   = _typeInfo;
    size_t rcounter       = FCF_BASIS_VARIANT_MAX_REF_NESTING;
    while (ti && ti->flags & TIF_VARIANT) {
      ti = ((BasicVariant*)p)->getTypeInfo();
      p = ((BasicVariant*)p)->ptr();
      --rcounter;
      if (!rcounter){
        throw VariantMaxRefNesting(__FILE__, __LINE__);
      }
    }
    return DataEndpointEx{ti, p};
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
    const unsigned int selfDataIndex = TypeIndexConverter<>::getDataIndex(selfUnref.typeInfo->index);
    if (selfDataIndex == argTypeIndex) {
      return selfUnref.typeInfo->template specifierCall<LessSpecifier>()(selfUnref.ptr, &a_value);
    } else {
      try {
        Variant buffer(selfUnref.typeInfo->index, &a_value, argTypeIndex);
        return selfUnref.typeInfo->template specifierCall<LessSpecifier>()(selfUnref.ptr, buffer.ptr());
      } catch(...) {
        return selfDataIndex < argTypeIndex;
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
    const unsigned int selfDataIndex = TypeIndexConverter<>::getDataIndex(selfUnref.typeInfo->index);
    if (selfDataIndex == argTypeIndex) {
      bool res = selfUnref.typeInfo->template specifierCall<LessSpecifier>()(selfUnref.ptr, &a_value);
      if (res) {
        return true;
      }
      return selfUnref.typeInfo->template specifierCall<EqualSpecifier>()(selfUnref.ptr, &a_value);
    } else {
      try {
        Variant buffer(selfDataIndex, &a_value, argTypeIndex);
        bool res = selfUnref.typeInfo->template specifierCall<LessSpecifier>()(selfUnref.ptr, buffer.ptr());
        if (res) {
          return true;
        }
        return selfUnref.typeInfo->template specifierCall<EqualSpecifier>()(selfUnref.ptr, buffer.ptr());
      } catch(...) {
        return selfDataIndex < argTypeIndex;
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

    const unsigned int argTypeIndex = Type<ArgType>().index();
    const unsigned int selfDataIndex = TypeIndexConverter<>::getDataIndex(selfUnref.typeInfo->index);
    if (selfDataIndex == argTypeIndex) {
      return selfUnref.typeInfo->template specifierCall<EqualSpecifier>()(selfUnref.ptr, &a_value);
    }

    try {
      Variant buffer(selfDataIndex, &a_value, argTypeIndex);
      return selfUnref.typeInfo->template specifierCall<EqualSpecifier>()(selfUnref.ptr, buffer.ptr());
    } catch(...) {
    }

    return false;
  }

  template <size_t innerBufferSize>
  template <typename TSpecifier, size_t InputInnerBufferSize>
  BasicVariant<innerBufferSize>& BasicVariant<innerBufferSize>::_selfCalcTo(const BasicVariant<InputInnerBufferSize>& a_value){
    ConstDataEndpoint                                         dde = _constDataEndpoint();
    typename BasicVariant<InputInnerBufferSize>::DataEndpoint sde = ((BasicVariant<InputInnerBufferSize>&)a_value)._dataEndpoint();
    if (!dde.typeInfo) {
      return *this;
    } else if (dde.isConst){
      throw VariantReadOnlyException(__FILE__, __LINE__);
    } else if (!sde.typeInfo) {
      return *this;
    } else if (TypeIndexConverter<>::getDataIndex(dde.typeInfo->index) == TypeIndexConverter<>::getDataIndex(sde.typeInfo->index)) {
      dde.typeInfo->template specifierCall<TSpecifier>()(dde.ptr, dde.ptr, sde.ptr);
    } else {
      try {
        BasicVariant<innerBufferSize> buffer(TypeIndexConverter<>::getDataIndex(dde.typeInfo->index), sde.ptr, TypeIndexConverter<>::getDataIndex(sde.typeInfo->index));
        dde.typeInfo->template specifierCall<TSpecifier>()(dde.ptr, dde.ptr, buffer.ptr());
      } catch(...){
      }
    }
    return *this;
  }

  template <size_t innerBufferSize>
  template <typename TSpecifier, size_t InputInnerBufferSize>
  BasicVariant<innerBufferSize> BasicVariant<innerBufferSize>::_selfCalc(const BasicVariant<InputInnerBufferSize>& a_value) const{
    DataEndpoint                                              dde = ((BasicVariant<innerBufferSize>*)this)->_dataEndpoint();
    typename BasicVariant<InputInnerBufferSize>::DataEndpoint sde = ((BasicVariant<InputInnerBufferSize>&)a_value)._dataEndpoint();
    const unsigned int selfDataIndex = TypeIndexConverter<>::getDataIndex(dde.typeInfo->index);
    const unsigned int sourceDataIndex = TypeIndexConverter<>::getDataIndex(sde.typeInfo->index);
    if (!dde.typeInfo || !sde.typeInfo) {
      return BasicVariant<innerBufferSize>(*this);
    } else if (selfDataIndex == sourceDataIndex) {
      BasicVariant<innerBufferSize> result(::fcf::getTypeInfo(selfDataIndex));
      _typeInfo->specifierCall<TSpecifier>()(result.ptr(), dde.ptr, sde.ptr);
      return result;
    } else {
      BasicVariant<innerBufferSize> result(::fcf::getTypeInfo(selfDataIndex));
      try {
        BasicVariant<innerBufferSize> buffer(selfDataIndex, sde.ptr, sourceDataIndex);
        _typeInfo->specifierCall<TSpecifier>()(result.ptr(), dde.ptr, buffer.ptr());
      } catch(...){
        return BasicVariant<innerBufferSize>(*this);
      }
      return result;
    }
  }


  template <size_t innerBufferSize>
  template <typename TSpecifier, typename Ty>
  BasicVariant<innerBufferSize>& BasicVariant<innerBufferSize>::_calcTo(const Ty& a_value){
    ConstDataEndpoint dde = ((BasicVariant<innerBufferSize>*)this)->_constDataEndpoint();
    if (!dde.typeInfo) {
      return *this;
    }

    if (dde.isConst){
      throw VariantReadOnlyException(__FILE__, __LINE__);
    }

    typedef typename std::remove_reference<Ty>::type ArgType;

    unsigned int argTypeIndex = Type<ArgType>().index();
    unsigned int selfDataIndex = TypeIndexConverter<>::getDataIndex(dde.typeInfo->index);
    if (selfDataIndex == argTypeIndex) {
      dde.typeInfo->template specifierCall<TSpecifier>()(dde.ptr, dde.ptr, &a_value);
      return *this;
    }

    try {
      Variant buffer(selfDataIndex, &a_value, argTypeIndex);
      dde.typeInfo->template specifierCall<TSpecifier>()(dde.ptr, dde.ptr, buffer.ptr());
    } catch(...) {
    }

    return *this;
  }

  template <size_t innerBufferSize>
  template <typename TSpecifier, typename Ty>
  BasicVariant<innerBufferSize> BasicVariant<innerBufferSize>::_calc(const Ty& a_value) const{
    DataEndpoint dde = ((BasicVariant<innerBufferSize>*)this)->_dataEndpoint();
    if (!dde.typeInfo) {
      return BasicVariant<innerBufferSize>(*this);
    }

    typedef typename std::remove_reference<Ty>::type ArgType;

    unsigned int argTypeIndex = Type<ArgType>().index();

    BasicVariant<innerBufferSize> result(_typeInfo);

    const unsigned int selfDataIndex = TypeIndexConverter<>::getDataIndex(dde.typeInfo->index);

    if (selfDataIndex == argTypeIndex) {
      dde.typeInfo->template specifierCall<TSpecifier>()(result.ptr(), dde.ptr, &a_value);
      return result;
    }

    try {
      Variant buffer(selfDataIndex, &a_value, argTypeIndex);
      dde.typeInfo->template specifierCall<TSpecifier>()(result.ptr(), dde.ptr, buffer.ptr());
    } catch(...){
      return BasicVariant<innerBufferSize>(*this);
    }

    return result;
  }

}  // fcf namespace

#include "../../bits/PartSpecifier/ResolveSpecifier.hpp"

namespace std {
  template <size_t innerBufferSize>
  std::string to_string(const fcf::BasicVariant<innerBufferSize>& a_variant){
    return a_variant.template cast<std::string>();
  }
}

namespace fcf {

  template <size_t innerBufferSize>
  struct Type<BasicVariant<innerBufferSize>, ResolveSpecifier> : public TypeImpl<BasicVariant<innerBufferSize>, ResolveSpecifier>{

    enum { invariantValue = true };

    inline void operator()(BasicVariant<innerBufferSize>* a_object, void** a_dstData, unsigned int* a_dstTypeIndex){
      *a_dstData = a_object->ptr();
      *a_dstTypeIndex = a_object->getTypeIndex();
    }
  };


} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_VARIANT__VARIANT_HPP___
