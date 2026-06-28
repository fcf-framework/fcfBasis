#ifndef ___FCF_BASIS__BITS__PART_TYPE__TYPE_INDEX_HPP___
#define ___FCF_BASIS__BITS__PART_TYPE__TYPE_INDEX_HPP___

namespace fcf{

  /**
   * @brief Unique identifier for a registered type.
   *
   * This integer type is used throughout the framework to represent and
   * distinguish between different types in the runtime type system.
   * It can also encode additional information such as constness,
   * reference qualifiers, and pointer levels.
   */
  typedef unsigned int TypeIndex;

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_TYPE__TYPE_INDEX_HPP___
