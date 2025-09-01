#ifndef ___FCF_BASIS__BITS__TYPE_INDEX_FUNCTIONS_HPP___
#define ___FCF_BASIS__BITS__TYPE_INDEX_FUNCTIONS_HPP___

namespace fcf {

  inline bool typeIndexIsDoublePointer(unsigned int a_typeIndex) {
    return a_typeIndex & (16 << (24 + 1) );
  }

  inline bool typeIndexIsSinglePointer(unsigned int a_typeIndex) {
    return a_typeIndex & (8 << (24 + 1) );
  }

  inline bool typeIndexIsPointer(unsigned int a_typeIndex) {
    return typeIndexIsSinglePointer(a_typeIndex) || typeIndexIsDoublePointer(a_typeIndex);
  }

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__TYPE_INDEX_FUNCTIONS_HPP___
