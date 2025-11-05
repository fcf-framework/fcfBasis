#ifndef ___FCF_BASIS__BITS__PART_TYPE__TYPE_INDEX_CONVERTER_HPP___
#define ___FCF_BASIS__BITS__PART_TYPE__TYPE_INDEX_CONVERTER_HPP___

namespace fcf{

  template <unsigned int Index=0>
  struct TypeIndexConverter{

    enum { index = Index };

    enum { rawIndexType = Index & ~( 0x1f << (24 + 1) ) };

    enum { isSinglePointerValue = Index & ( 8 << (24 + 1) ) ? 1 : 0 };

    enum { isDoublePointerValue = Index & ( 16 << (24 + 1) ) ? 1 : 0 };

    enum { isPointerValue = isSinglePointerValue || isDoublePointerValue ? 1 : 0 };


    inline static bool isDoublePointer(unsigned int a_typeIndex) {
      return a_typeIndex & ( 16 << (24 + 1) );
    }

    inline static bool isSinglePointer(unsigned int a_typeIndex) {
      return a_typeIndex & ( 8 << (24 + 1) );
    }

    inline static bool isPointer(unsigned int a_typeIndex) {
      return isSinglePointer(a_typeIndex) || isDoublePointer(a_typeIndex);
    }

    inline static unsigned int getRawIndex(unsigned int a_typeIndex){
      return a_typeIndex & ~( 0x1f << (24 + 1) );
    }

  };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_TYPE__TYPE_INDEX_CONVERTER_HPP___
