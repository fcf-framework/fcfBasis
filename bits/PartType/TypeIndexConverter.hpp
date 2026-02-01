#ifndef ___FCF_BASIS__BITS__PART_TYPE__TYPE_INDEX_CONVERTER_HPP___
#define ___FCF_BASIS__BITS__PART_TYPE__TYPE_INDEX_CONVERTER_HPP___

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

    inline static bool isDoublePointer(unsigned int a_typeIndex) {
      return a_typeIndex & ( 16 << (24 + 1) );
    }

    inline static bool isSinglePointer(unsigned int a_typeIndex) {
      return a_typeIndex & ( 8 << (24 + 1) );
    }

    inline static bool isPointer(unsigned int a_typeIndex) {
      return isSinglePointer(a_typeIndex) || isDoublePointer(a_typeIndex);
    }

    inline static bool isSingleReference(unsigned int a_typeIndex) {
      return a_typeIndex & ( 1 << (24 + 1) );
    }

    inline static bool isDoubleReference(unsigned int a_typeIndex) {
      return a_typeIndex & ( 2 << (24 + 1) );
    }

    inline static bool isReference(unsigned int a_typeIndex) {
      return isSingleReference(a_typeIndex) || isDoubleReference(a_typeIndex);
    }

    inline static bool isConst(unsigned int a_typeIndex) {
      return a_typeIndex & ( 4 << (24 + 1) );
    }

    inline static unsigned int getRawIndex(unsigned int a_typeIndex){
      return a_typeIndex & ~( 0x1f << (24 + 1) );
    }

    inline static unsigned int getDataIndex(unsigned int a_typeIndex){
      return a_typeIndex & ~( (1|2|4) << (24 + 1) );
    }

    inline static unsigned int getUnreferenceIndex(unsigned int a_typeIndex){
      return a_typeIndex & ~( (1|2) << (24 + 1) );
    }

    inline static unsigned int getUnpointerIndex(unsigned int a_typeIndex){
      return a_typeIndex & ~( (8|16) << (24 + 1) );
    }

    inline static unsigned int getUnpointerSingleIndex(unsigned int a_typeIndex){
      return a_typeIndex & ~( 8 << (24 + 1) );
    }

    inline static unsigned int getSinglePointerIndex(unsigned int a_typeIndex){
      return (a_typeIndex & ~( 16 << (24 + 1) ) ) | ( (8) << (24 + 1) );
    }

    inline static unsigned int getSingleReferenceIndex(unsigned int a_typeIndex){
      return (a_typeIndex & ~( (2) << (24 + 1) ) ) | ( (1) << (24 + 1) );
    }

    inline static unsigned int getConstSingleReferenceIndex(unsigned int a_typeIndex){
      return (a_typeIndex & ~( (2) << (24 + 1) ) ) | ( (1) << (24 + 1) ) | ( (4) << (24 + 1) );
    }

    inline static unsigned int getConstIndex(unsigned int a_typeIndex){
      return a_typeIndex | ( (4) << (24 + 1) );
    }

  };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_TYPE__TYPE_INDEX_CONVERTER_HPP___
