#ifndef ___FCF_BASIS__BITS__PART_EXCEPTION__EXCEPTIONS_HPP___
#define ___FCF_BASIS__BITS__PART_EXCEPTION__EXCEPTIONS_HPP___

#include "Exception.hpp"
namespace fcf {

  FCF_EXCEPTION_DECLARE(LogicException, "FCF_LOGIC", "Logic error: ${{1}}$", 1);
 
  FCF_EXCEPTION_DECLARE(CallNotFoundException, "FCF_CALL_NOT_FOUND", "Call '${{1}}$' function not found with signature '${{2}}$'", 2);
  FCF_EXCEPTION_DECLARE(CallIterableNotFoundException, "FCF_CALL_ITERABLE_NOT_FOUND", "Call iterable '${{1}}$' function not found (Arguments: ${{2}}$)'", 2);
  FCF_EXCEPTION_DECLARE(CallIterationConversionBufferOverflowException, "FCF_CALL_ITERATION_CONVERSION_BUFFER_OWERFLOW", " Iteration conversion buffer overflow (Function: ${{1}}$; Arguments: ${{2}}$)'", 2);
  FCF_EXCEPTION_DECLARE(CallArgumentBufferOverflowException, "FCF_CALL_ARGUMENT_BUFFER_OVERFLOW", "Argument buffer overflow in dynamic call (Arguments: ${{1}}$)", 1);
  FCF_EXCEPTION_DECLARE(CallArgumentBufferOverflowExException, "FCF_CALL_ARGUMENT_BUFFER_OVERFLOW", "Argument buffer overflow in dynamic call (Function: ${{1}}$; Arguments: ${{2}}$)", 2);
  FCF_EXCEPTION_DECLARE(CallSpecificatorArgumentCountException, "FCF_CALL_SPECIFICATOR_COUNT_ARGUMENTS", "The specificator returned an insufficient number of arguments (Argument: ${{1}}$; Call: ${{2}}$, Arguments: ${{3}}$)", 3);
  FCF_EXCEPTION_DECLARE(CallIteratorGettingException, "FCF_CALL_ITERATOR_GETTING", "Unable to get an iterator from argument ${{1}}$ for function call '${{2}}$' (Arguments: ${{3}}$)", 3);
  FCF_EXCEPTION_DECLARE(CallPlaceholderBufferOverflowException, "FCF_CALL_PLACEHOLDER_BUFFER_OVERFLOW", "Argument placeholder buffer overflow for function call '${{1}}$' (Signature: ${{2}}$)", 2);

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_EXCEPTION__EXCEPTIONS_HPP___
