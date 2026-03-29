#ifndef ___FCF__BASIS__BITS__CALL_STORAGE__CALL_STORAGE_FUNCTION_INDEXES_HPP___
#define ___FCF__BASIS__BITS__CALL_STORAGE__CALL_STORAGE_FUNCTION_INDEXES_HPP___

#include <string>
#include <map>
#include "../../bits/PartCall/FunctionSignature.hpp"

namespace fcf {

  typedef std::map< BaseFunctionSignature, std::map<std::string, unsigned int>  > CallStorageFunctionIndexes;

} // fcf namespace

#endif // #ifndef ___FCF__BASIS__BITS__CALL_STORAGE__CALL_STORAGE_FUNCTION_INDEXES_HPP___
