#ifndef ___FCF_BASIS__BITS__PART_TYPE__TYPE_INDEX_CONVERTER_HPP___
#define ___FCF_BASIS__BITS__PART_TYPE__TYPE_INDEX_CONVERTER_HPP___

#include "TypeIndex.hpp"

namespace fcf{

  template <unsigned int Index=0>
  struct TypeIndexConverter{

    enum { index = Index };

    enum { rawTypeIndex = Index & ~( 0x1f << (24 + 1) ) };

    enum { dataTypeIndex = Index & ~( (1|2|4) << (24 + 1) ) };

    enum { singleReferenceTypeIndex = (Index & ~( (2) << (24 + 1) )) | ( (1) << (24 + 1) ) };

    enum { constSingleReferenceTypeIndex = (Index & ~( (2) << (24 + 1) )) | ( (1) << (24 + 1) ) | ( (4) << (24 + 1) ) };

    enum { constTypeIndex = (Index | ( (4) << (24 + 1) )) };

    enum { unreferenceTypeIndex = (Index & ~( (1|2) << (24 + 1) )) };

    enum { unpointerTypeIndex = Index & ~( (8|16) << (24 + 1) ) };

    enum { unpointerTypeSingleIndex = Index & ~( 8 << (24 + 1) ) };

    enum { singlePointerTypeIndex = (Index & ~( 16 << (24 + 1) ) ) | ( (8) << (24 + 1) ) };

    enum { isSinglePointerValue = Index & ( 8 << (24 + 1) ) ? 1 : 0 };

    enum { isDoublePointerValue = Index & ( 16 << (24 + 1) ) ? 1 : 0 };

    enum { isPointerValue = isSinglePointerValue || isDoublePointerValue ? 1 : 0 };

    enum { isSingleReferenceValue = Index & ( 1 << (24 + 1) ) };

    enum { isDoubleReferenceValue = Index & ( 2 << (24 + 1) ) };

    enum { isReferenceValue = isSingleReferenceValue || isDoubleReferenceValue };

    enum { isConstValue = Index & ( 4 << (24 + 1) ) };

    inline static bool isDoublePointer(TypeIndex a_typeIndex) {
      return a_typeIndex & ( 16 << (24 + 1) );
    }

    inline static bool isSinglePointer(TypeIndex a_typeIndex) {
      return a_typeIndex & ( 8 << (24 + 1) );
    }

    inline static bool isPointer(TypeIndex a_typeIndex) {
      return isSinglePointer(a_typeIndex) || isDoublePointer(a_typeIndex);
    }

    inline static bool isSingleReference(TypeIndex a_typeIndex) {
      return a_typeIndex & ( 1 << (24 + 1) );
    }

    inline static bool isDoubleReference(TypeIndex a_typeIndex) {
      return a_typeIndex & ( 2 << (24 + 1) );
    }

    inline static bool isReference(TypeIndex a_typeIndex) {
      return isSingleReference(a_typeIndex) || isDoubleReference(a_typeIndex);
    }

    inline static bool isConst(TypeIndex a_typeIndex) {
      return a_typeIndex & ( 4 << (24 + 1) );
    }

    inline static TypeIndex getRawIndex(TypeIndex a_typeIndex){
      return a_typeIndex & ~( 0x1f << (24 + 1) );
    }

    inline static TypeIndex getDataIndex(TypeIndex a_typeIndex){
      return a_typeIndex & ~( (1|2|4) << (24 + 1) );
    }

    inline static TypeIndex getUnreferenceIndex(TypeIndex a_typeIndex){
      return a_typeIndex & ~( (1|2) << (24 + 1) );
    }

    inline static TypeIndex getUnpointerIndex(TypeIndex a_typeIndex){
      return a_typeIndex & ~( (8|16) << (24 + 1) );
    }

    inline static TypeIndex getUnpointerSingleIndex(TypeIndex a_typeIndex){
      return a_typeIndex & ~( 8 << (24 + 1) );
    }

    inline static TypeIndex removeLevelPointer(TypeIndex a_typeIndex){
      if ( a_typeIndex & (16 << (24 + 1) ) ){
        return (a_typeIndex & (~( 16 << (24 + 1) ))) | ( 8 << (24 + 1) );
      } else {
        return a_typeIndex & (~( (16|8) << (24 + 1) ));
      }
    }

    inline static TypeIndex addLevelPointer(TypeIndex a_typeIndex){
      if ( a_typeIndex & (8 << (24 + 1) ) ){
        return (a_typeIndex & (~( 8 << (24 + 1) ))) | ( 16 << (24 + 1) );
      } else {
        return a_typeIndex | ( 8 << (24 + 1) );
      }
    }

    inline static TypeIndex getSinglePointerIndex(TypeIndex a_typeIndex){
      return (a_typeIndex & ~( 16 << (24 + 1) ) ) | ( (8) << (24 + 1) );
    }

    inline static TypeIndex getSingleReferenceIndex(TypeIndex a_typeIndex){
      return (a_typeIndex & ~( (2) << (24 + 1) ) ) | ( (1) << (24 + 1) );
    }

    inline static TypeIndex getConstSingleReferenceIndex(TypeIndex a_typeIndex){
      return (a_typeIndex & ~( (2) << (24 + 1) ) ) | ( (1) << (24 + 1) ) | ( (4) << (24 + 1) );
    }

    inline static TypeIndex getConstIndex(TypeIndex a_typeIndex){
      return a_typeIndex | ( (4) << (24 + 1) );
    }

  };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_TYPE__TYPE_INDEX_CONVERTER_HPP___
