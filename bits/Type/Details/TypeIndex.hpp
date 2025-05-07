#ifndef ___FCF_BASIS__BITS__TYPE__DETAILS__TYPE_INDEX_HPP___
#define ___FCF_BASIS__BITS__TYPE__DETAILS__TYPE_INDEX_HPP___

#include "../Type.hpp"

namespace fcf {
  namespace Details {
    namespace Basis {
      namespace Type {

        template <typename Ty = Nop>
        class TypeIndex {
          public:
            static unsigned int index(){
              return ::fcf::Type<Ty>().index();
            }
        };

        template <>
        class TypeIndex<Nop> {
          public:
            static unsigned int index(){
              return 0;
            }
        };

      } // Type namespace
    } // Basis namespace
  } // Details namespace
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__TYPE__DETAILS__TYPE_INDEX_HPP___
