#ifndef ___FCF_BASIS__DETAILS__CONVERT__CONVERT_INDEX_HPP___
#define ___FCF_BASIS__DETAILS__CONVERT__CONVERT_INDEX_HPP___

namespace fcf {
  namespace Details {
    namespace Basis {
      namespace Convert {
        struct ConvertIndex {
          unsigned int source;
          unsigned int destination;
          bool operator<(const ConvertIndex& a_itm) const {
            return *(unsigned long long*)this < *(unsigned long long*)&a_itm;
          }
        };
      } // Convert namespace
    } // Basis namespace
  } // Details namespace
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__DETAILS__CONVERT__CONVERT_INDEX_HPP___
