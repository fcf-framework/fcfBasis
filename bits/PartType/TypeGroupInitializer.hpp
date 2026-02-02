#ifndef ___FCF_BASIS__BITS__PART_TYPE__TYPE_GROUP_INITIALIZER_HPP___
#define ___FCF_BASIS__BITS__PART_TYPE__TYPE_GROUP_INITIALIZER_HPP___

#include <type_traits>
#include "TypeTrialInitializer.hpp"

namespace fcf{

  template <typename Ty>
  struct TypeGroupInitializer{
    typedef typename std::remove_const<
              typename std::remove_reference<
                typename std::remove_pointer<
                  typename std::remove_const<
                    typename std::remove_reference<
                      typename std::remove_pointer<
                        typename std::remove_const<
                          Ty
                        >::type
                      >::type
                    >::type
                  >::type
                >::type
              >::type
            >::type raw_type;
    TypeGroupInitializer(){
      { fcf::TypeTrialInitializer<Ty, raw_type> var; }
      { fcf::TypeTrialInitializer<Ty, raw_type*> var; }
      { fcf::TypeTrialInitializer<Ty, raw_type**> var; }
      { fcf::TypeTrialInitializer<Ty, raw_type&> var; }
      { fcf::TypeTrialInitializer<Ty, raw_type&&> var; }
      { fcf::TypeTrialInitializer<Ty, const raw_type*> var; }
      { fcf::TypeTrialInitializer<Ty, const raw_type*&> var; }
      { fcf::TypeTrialInitializer<Ty, const raw_type**> var; }
      { fcf::TypeTrialInitializer<Ty, const raw_type**&> var; }
      { fcf::TypeTrialInitializer<Ty, const raw_type&> var; }
      { fcf::TypeTrialInitializer<Ty, const raw_type&&> var; }
    }

  };

  template <>
  struct TypeGroupInitializer<void>{
    TypeGroupInitializer(){
    }
  };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_TYPE__TYPE_GROUP_INITIALIZER_HPP___
