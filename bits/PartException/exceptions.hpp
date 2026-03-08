#ifndef ___FCF_BASIS__BITS__PART_EXCEPTION__EXCEPTIONS_HPP___
#define ___FCF_BASIS__BITS__PART_EXCEPTION__EXCEPTIONS_HPP___

#include "ExceptionDefinition.hpp"

namespace fcf {

 FCF_EXCEPTION_DECLARE(LogicException, "FCF_LOGIC", "Logic error: ${{1}}$", 1);

  FCF_EXCEPTION_DECLARE(FunctionNotFoundException, "FCF_FUNCTION_NOT_FOUND", "Function '${{1}}$' function not'", 1);

  FCF_EXCEPTION_DECLARE(CallNotFoundException, "FCF_CALL_NOT_FOUND", "Call '${{1}}$' function not found with signature '${{2}}$'", 2);
  FCF_EXCEPTION_DECLARE(CallIterableNotFoundException, "FCF_CALL_ITERABLE_NOT_FOUND", "Call iterable '${{1}}$' function not found (Arguments: ${{2}}$)'", 2);
  FCF_EXCEPTION_DECLARE(CallIterationConversionBufferOverflowException, "FCF_CALL_ITERATION_CONVERSION_BUFFER_OWERFLOW", " Iteration conversion buffer overflow (Function: ${{1}}$; Arguments: ${{2}}$)'", 2);
  FCF_EXCEPTION_DECLARE(CallArgumentBufferOverflowException, "FCF_CALL_ARGUMENT_BUFFER_OVERFLOW", "Argument buffer overflow in dynamic call (Arguments: ${{1}}$)", 1);
  FCF_EXCEPTION_DECLARE(CallArgumentBufferOverflowExException, "FCF_CALL_ARGUMENT_BUFFER_OVERFLOW", "Argument buffer overflow in dynamic call (Function: ${{1}}$; Arguments: ${{2}}$)", 2);
  FCF_EXCEPTION_DECLARE(CallSpecificatorArgumentCountException, "FCF_CALL_SPECIFICATOR_COUNT_ARGUMENTS", "The specificator returned an insufficient number of arguments (Argument: ${{1}}$; Call: ${{2}}$, Arguments: ${{3}}$)", 3);
  FCF_EXCEPTION_DECLARE(CallIteratorGettingException, "FCF_CALL_ITERATOR_GETTING", "Unable to get an iterator from argument ${{1}}$ for function call '${{2}}$' (Arguments: ${{3}}$)", 3);
  FCF_EXCEPTION_DECLARE(CallPlaceholderBufferOverflowException, "FCF_CALL_PLACEHOLDER_BUFFER_OVERFLOW", "Argument placeholder buffer overflow for function call '${{1}}$' (Signature: ${{2}}$)", 2);

  FCF_EXCEPTION_DECLARE(VariantTypeMismatchExeption, "FCF_VARIANT_TYPE_MISMATCH", "The stored data type '${{1}}$' in the Variant object is not of type '${{2}}$'", 2);
  FCF_EXCEPTION_DECLARE(VariantSetReferenceTypeException, "FCF_VARIANT_SET_REFERENCE_TYPE", "Cannot set a reference of type ${{1}}$ to data type '${{2}}$'", 2);
  FCF_EXCEPTION_DECLARE(VariantReadOnlyException, "FCF_VARIANT_READ_ONLY", "The Variant object is read-only", 0);
  FCF_EXCEPTION_DECLARE(VariantEmptyToReferenceException, "FCF_VARIANT_EMPTY_TO_REFERENCE", "Setting an empty value for a variant reference", 0);
  FCF_EXCEPTION_DECLARE(VariantAssignConstDataException, "FCF_VARIANT_ASSIGN_CONST_DATA", "It is impossible to establish a non-constant reference to constant data", 0);

  FCF_EXCEPTION_DECLARE(MathArumentCountException, "FCF_MATH_ARGUMENT_COUNT", "Error in the mathematical operation '${{1}}$'. Incorrent number of arguments", 1);
  FCF_EXCEPTION_DECLARE(MathEmptyResultPointerException, "FCF_MATH_EMPTY_RESULT_POINTER", "Error in the mathematical operation '${{1}}$'. The pointer to the result variable is not set", 1);
  FCF_EXCEPTION_DECLARE(MathEmptyArgumentException, "FCF_MATH_EMPTY_ARGUMENT", "Error in the mathematical operation '${{1}}$'. Argument number ${{2}}$ is empty/null", 2);

  FCF_EXCEPTION_DECLARE(ConversionNotFoundException, "FCF_CONVERSION_NOT_FOUND", "No conversion function found for types ${{2}}$ to ${{1}}$", 2);
  
  FCF_EXCEPTION_DECLARE(TypeIndexNotRegisteredException, "FCF_TYPE_INDEX_NOT_REGISTERED", "The requested type index (${{1}}$) is not registered", 1);

  // Новые исключения для конвертеров
  FCF_EXCEPTION_DECLARE(ConvertFormatException, "FCF_PARSING_FORMAT_ERROR", "Argument '${{1}}$' is not a valid format for type ${{2}}$", 2);
  FCF_EXCEPTION_DECLARE(ConvertRangeExceededException, "FCF_CONVERSION_RANGE_EXCEEDED", "Value '${{1}}$' exceeds the range of type ${{2}}$", 2);

 // Новые исключения для контейнеров
 FCF_EXCEPTION_DECLARE(ContainerReadOnlyException, "FCF_CONTAINER_READ_ONLY", "The container '{{1}}' does not support the recording of the value", 1);
 FCF_EXCEPTION_DECLARE(ContainerIterationTypeMismatchException, "FCF_CONTAINER_ITERATION_TYPE_MISMATCH", "The transferred virtual type does not correspond to the required type '${{1}}$'", 1);

} // fcf namespace

#include "Exception.hpp"

#endif // #ifndef ___FCF_BASIS__BITS__PART_EXCEPTION__EXCEPTIONS_HPP___


