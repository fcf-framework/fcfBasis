#ifndef ___FCF_BASIS__BITS__PART_CALL__NDETAILS__CALL_PAIR_ARGUMENT_NODE_HPP___
#define ___FCF_BASIS__BITS__PART_CALL__NDETAILS__CALL_PAIR_ARGUMENT_NODE_HPP___

#include "../../PartType/TypeInfo.hpp"

namespace fcf{
  namespace NDetails{

    struct CallPairArgumentNode {
      unsigned int           index;
      const TypeInfo*        typeInfo;
      void*                  begin;
      void*                  end;
      CallPairArgumentNode*  next;
    };

  } // NDetails namespace
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_CALL__NDETAILS__CALL_PAIR_ARGUMENT_NODE_HPP___
