#ifndef ___FCF_BASIS__BITS__PART_TYPE__NDETAILS__ASSIGMENT_WRAPPER_HPP___
#define ___FCF_BASIS__BITS__PART_TYPE__NDETAILS__ASSIGMENT_WRAPPER_HPP___

namespace fcf{

  namespace NDetails {
    template <typename Ty, typename = void>
    struct AssigmentWrapper{
      void operator()(void* a_dst, const void* a_src){
        ((Ty*)a_dst)->~Ty();
        new (a_dst)Ty(*(const Ty*)a_src);
      }
    };

    template <typename Ty>
    struct AssigmentWrapper<Ty, decltype((void)*((Ty*)0) = *((Ty*)0xff))>{
      void operator()(void* a_dst, const void* a_src){
        typedef typename std::remove_const<Ty>::type UnconstType;
        *(UnconstType*)a_dst = *(const UnconstType*)a_src;
      }
    };
  }

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_TYPE__NDETAILS__ASSIGMENT_WRAPPER_HPP___
