#ifndef ___FCF_BASIS__DETAILS__TYPE_INDEX_HPP___
#define ___FCF_BASIS__DETAILS__TYPE_INDEX_HPP___

namespace fcf {
  namespace Details {

    template <typename Ty = Nop>
    class TypeIndex {
      public:
        static unsigned int index(){
          return Type<Ty>::index();
        }
    };

    template <>
    class TypeIndex<Nop> {
      public:
        static unsigned int index(){
          return 0;
        }
    };

  } // Details namespace
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__DETAILS__TYPE_INDEX_HPP___
