#ifndef ___FCF_BASIS__DETAILS__SPECIFICATOR__REGISTRATOR_HPP___
#define ___FCF_BASIS__DETAILS__SPECIFICATOR__REGISTRATOR_HPP___

#include "../../Type.hpp"
#include "Storage.hpp"

namespace fcf {
  namespace Details {
    namespace Specificator {

      template <typename TSpecificator>
      class Registrator {
        public:
          Registrator() {
            std::pair<unsigned int, SpecificatorInfo> itm;
            itm.first = Type<TSpecificator>::index();
            itm.second.asize = TSpecificator::argc;
            getStorage().specificators->insert(itm);
          }
      };
    } // Specificator namespace
  } // Details namepsace
} // fcf namespace


#endif // #ifndef ___FCF_BASIS__DETAILS__SPECIFICATOR__REGISTRATOR_HPP___
