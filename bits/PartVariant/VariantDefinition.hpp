#ifndef ___FCF_BASIS__BITS__PART_VARIANT__VARIANT_DEFINITION_HPP___
#define ___FCF_BASIS__BITS__PART_VARIANT__VARIANT_DEFINITION_HPP___

#include <string>
#include <map>
#include <stdexcept>
#include "../../macro.hpp"
#include "../../bits/PartVariant/VariantPredefinition.hpp"
#include "../../bits/PartType/DynamicType.hpp"
#include "../../bits/PartType/TypeIndexConverter.hpp"

namespace fcf {

  template <size_t innerBufferSize>
  class BasicVariant {
    public:

      enum DataSetMode {
        WRITE = 0,
        RESET = 1,
        REFERENCE = 2,
        FORCE_REFERENCE = 4,
      };

      template <size_t InputInnerBufferSize>
      friend class BasicVariant;

      typedef void (*convert_function_type)(void*, const void*);

      BasicVariant();

      BasicVariant(const BasicVariant& a_variant);

      BasicVariant(const BasicVariant& a_variant, DataSetMode a_dataMode);

      BasicVariant(BasicVariant& a_variant, DataSetMode a_dataMode);

      template <typename Ty>
      BasicVariant(const Ty& a_value);

      template <typename Ty, typename TSource>
      BasicVariant(const Type<Ty>& a_type, const TSource& a_value);

      template <typename Ty, typename TSource>
      BasicVariant(const Type<Ty>& a_type, TSource& a_value, DataSetMode a_dataMode);

      template <typename Ty, typename TSource>
      BasicVariant(const Type<Ty>& a_type, const TSource& a_value, DataSetMode a_dataMode);

      template <typename TSource>
      BasicVariant(const TSource& a_value, DataSetMode a_dataMode);

      template <typename TSource>
      BasicVariant(TSource& a_value, DataSetMode a_dataMode);

      BasicVariant(const char* a_value);

      BasicVariant(const char* a_value, DataSetMode a_dataMode);

      template <size_t InputInnerBufferSize>
      BasicVariant(const BasicVariant<InputInnerBufferSize>& a_variant);

      template <size_t InputInnerBufferSize>
      BasicVariant(BasicVariant<InputInnerBufferSize>& a_variant);

      template <size_t InputInnerBufferSize>
      BasicVariant(const BasicVariant<InputInnerBufferSize>& a_variant, DataSetMode a_dataMode);

      template <size_t InputInnerBufferSize>
      BasicVariant(BasicVariant<InputInnerBufferSize>& a_variant, DataSetMode a_dataMode);

      template <typename Ty>
      BasicVariant(Type<Ty, Nop> a_type);

      BasicVariant(DynamicType a_dynamicType);

      BasicVariant(const TypeInfo* a_typeInfo);

      BasicVariant(unsigned int a_typeIndex, const void* a_sourceData, unsigned int a_sourceTypeIndex = 0, ConvertOptions* a_options = 0, ConvertFunction a_convertFunction = 0);

      ~BasicVariant();

      void reset(DynamicType a_dynamicType);

      void reset(const TypeInfo* a_typeInfo);

      template <typename Ty>
      void reset(Type<Ty, Nop> a_dynamicType);

      BasicVariant& operator=(const BasicVariant& a_variant);

      template <size_t InputInnerBufferSize>
      BasicVariant& operator=(const BasicVariant<InputInnerBufferSize>& a_variant);

      template <typename Ty>
      BasicVariant& operator=(const Ty& a_value);

      BasicVariant& operator=(const char* a_value);

      void set(const BasicVariant& a_variant);

      void set(const BasicVariant& a_variant, DataSetMode a_dataMode);

      template <typename Ty>
      void set(const Ty& a_value);

      template <typename Ty>
      void set(Ty& a_value, DataSetMode a_dataMode);

      template <typename Ty>
      void set(const Ty& a_value, DataSetMode a_dataMode);

      void set(const char* a_value);

      void set(const char* a_value, DataSetMode a_dataMode);

      void set(unsigned int a_typeIndex, const void* a_sourceData, unsigned int a_sourceTypeIndex = 0, ConvertOptions* a_options = 0, ConvertFunction a_convertFunction = 0);

      void clear();

      Variant operator[](const Variant& a_key);

      template <typename Ty>
      Variant operator[](const Ty& a_key);

      Variant operator[](const char* a_key);

      operator bool() const;


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
      BasicVariant& operator+=(const Ty& a_value);

      BasicVariant& operator+=(const char* a_value);



      BasicVariant operator+(const BasicVariant& a_value) const;

      template <typename Ty>
      BasicVariant operator+(const Ty& a_value) const;

      BasicVariant operator+(const char* a_value) const;



      BasicVariant& operator-=(const BasicVariant& a_value);

      template <typename Ty>
      BasicVariant& operator-=(const Ty& a_value);

      BasicVariant& operator-=(const char* a_value);



      BasicVariant operator-(const BasicVariant& a_value) const;

      template <typename Ty>
      BasicVariant operator-(const Ty& a_value) const;

      BasicVariant operator-(const char* a_value) const;



      BasicVariant& operator*=(const BasicVariant& a_value);

      template <typename Ty>
      BasicVariant& operator*=(const Ty& a_value);

      BasicVariant& operator*=(const char* a_value);



      BasicVariant operator*(const BasicVariant& a_value) const;

      template <typename Ty>
      BasicVariant operator*(const Ty& a_value) const;

      BasicVariant operator*(const char* a_value) const;



      BasicVariant& operator/=(const BasicVariant& a_value);

      template <typename Ty>
      BasicVariant& operator/=(const Ty& a_value);

      BasicVariant& operator/=(const char* a_value);



      BasicVariant operator/(const BasicVariant& a_value) const;

      template <typename Ty>
      BasicVariant operator/(const Ty& a_value) const;

      BasicVariant operator/(const char* a_value) const;

      unsigned int getDataTypeIndex() const;

      unsigned int getTypeIndex() const;

      const TypeInfo* getTypeInfo() const;

      void* ptr();

      const void* ptr() const;

      inline bool empty() const { return _typeInfo == 0; }

      inline bool isReference() const { return _typeInfo ? TypeIndexConverter<>::isSingleReference(_typeInfo->index) : false; }

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

      template <typename TType>
      bool strictIs() const;

      bool isInnerMemory() const{
        if (!_typeInfo){
          return true;
        }
        return _typeInfo->initializer->size() <= innerBufferSize;
      }

    private:
      struct DataEndpoint {
        const TypeInfo*  typeInfo;
        void*            ptr;
      };
      struct ConstDataEndpoint {
        const TypeInfo*  typeInfo;
        void*            ptr;
        bool             isConst;
      };

      struct DataEndpointEx {
        const TypeInfo*  typeInfo;
        void*            ptr;
        BaseTypeWrapper* wrapper;
      };

      struct VariantEndpoint{
        void* variant;
        bool  isConst;
        size_t innerSize;
      };

      void _destroy();

      template <size_t InputInnerBufferSize>
      void _clone(const BasicVariant<InputInnerBufferSize>& a_variant, DataSetMode a_mode);

      template <typename DataType, typename ReferenceType, typename Ty>
      void _reset(const Ty& a_value, DataSetMode a_dataMode);

      template <typename Ty>
      void _assigment(const Ty& a_value);

      template <typename DataType, typename ReferenceType, typename ArgTy>
      void _init(const ArgTy& a_value, DataSetMode a_dataMode);

      void _set(unsigned int a_typeIndex, const void* a_sourceData, unsigned int a_sourceTypeIndex = 0, ConvertOptions* a_options = 0, ConvertFunction a_convertFunction = 0);

      BaseTypeWrapper* _getWrapper() const;

      inline VariantEndpoint _variantEndpoint();

      inline DataEndpoint _dataEndpoint();

      inline ConstDataEndpoint _constDataEndpoint();

      inline DataEndpointEx _dataEndpointEx();

      template <typename Ty>
      bool _less(const Ty& a_value) const;

      template <typename Ty>
      bool _lessEqual(const Ty& a_value) const;

      template <typename Ty>
      bool _equal(const Ty& a_value) const;

      template <typename TSpecificator, size_t InputInnerBufferSize>
      inline BasicVariant& _selfCalcTo(const BasicVariant<InputInnerBufferSize>& a_value);

      template <typename TSpecificator, size_t InputInnerBufferSize>
      inline BasicVariant _selfCalc(const BasicVariant<InputInnerBufferSize>& a_value) const;

      template <typename TSpecificator, typename Ty>
      inline BasicVariant& _calcTo(const Ty& a_value);

      template <typename TSpecificator, typename Ty>
      inline BasicVariant _calc(const Ty& a_value) const;


      const TypeInfo* _typeInfo;
      void*           _ptr;
      char            _mem[innerBufferSize];
  };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_VARIANT__VARIANT_DEFINITION_HPP___
