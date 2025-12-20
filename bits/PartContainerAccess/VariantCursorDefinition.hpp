#ifndef ___FCF_BASIS__BITS__PART_CONTAINER_ACCESS__VARIANT_CURSOR_DEFINITION_HPP___
#define ___FCF_BASIS__BITS__PART_CONTAINER_ACCESS__VARIANT_CURSOR_DEFINITION_HPP___

#include "../../Nop.hpp"
#include "../../bits/PartVariant/VariantPredefinition.hpp"

namespace fcf{

  template <typename TContainer>
  struct VariantCursor {
    typedef VariantCursor                 self_type;
    typedef TContainer                    container_type;
    typedef TContainer                    key_type;
    typedef TContainer                    value_type;
    typedef TContainer                    stored_value_type;
    typedef TContainer                    resolve_value_type;
    typedef TContainer                    resolve_stored_value_type;
    enum { is_flat = false };

    VariantCursor();

    VariantCursor(TContainer& a_variant);

    inline void setPosition(const key_type& a_position, bool a_create = false);

    inline void addPosition(size_t a_position);

    inline void decPosition(size_t a_position);

    inline void decPosition();

    inline void incPosition();

    inline void setBeginPosition();

    inline void setEndPosition();

    inline size_t getDistance(const self_type& a_cursor) const;

    inline key_type getKey() const;

    inline resolve_value_type getValue();

    inline void* getValuePtr();

    inline resolve_stored_value_type getStoredValue();

    inline size_t getContainerSize() const;

    inline bool isEnd() const;

    inline bool equal(const self_type& a_cursor) const;

    TContainer iterator;
  };


} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_CONTAINER_ACCESS__VARIANT_CURSOR_DEFINITION_HPP___
