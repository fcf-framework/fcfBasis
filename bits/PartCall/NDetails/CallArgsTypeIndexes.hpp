#ifndef ___FCF_BASIS__BITS__PART_CALL__NDETAILS__CALL_ARGS_TYPE_INDEXES_HPP___
#define ___FCF_BASIS__BITS__PART_CALL__NDETAILS__CALL_ARGS_TYPE_INDEXES_HPP___

#include "../../../foreach.hpp"

namespace fcf { 
  namespace NDetails {

    /**
     * @class CallArgsTypeIndexes
     * @brief Classes are used to preserve type indices
     **/
    template <typename... TArgPack>
    struct CallArgsTypeIndexes {

      CallArgsTypeIndexes(){
        typedef std::tuple< TArgPack*... > tuple_type;
        tuple_type tuple;
        foreach(tuple, *this);
      }

      template <typename TTuple, typename TItem>
      void operator()(const TTuple& /*a_tuple*/, size_t a_index, const TItem* /*a_item*/){
        indexes[a_index] = Type<TItem>().index();
      }

      unsigned int indexes[sizeof...(TArgPack)];
    };

  } // NDetails namespace
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_CALL__NDETAILS__CALL_ARGS_TYPE_INDEXES_HPP___
