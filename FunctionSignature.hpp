#ifndef ___FCF_BASIS__FUNCTION_SIGNATURE_HPP___
#define ___FCF_BASIS__FUNCTION_SIGNATURE_HPP___
#include <cstring>
#include <vector>
#include "Type.hpp"

#ifndef FCF_FUNCTION_SIGNATURE_CLASS_MEM_STORAGE_SIZE
  #define FCF_FUNCTION_SIGNATURE_CLASS_MEM_STORAGE_SIZE 10
#endif // #ifndef FCF_FUNCTION_SIGNATURE_CLASS_MEM_STORAGE_SIZE

namespace fcf {

      namespace Details { 
        namespace FunctionSignature { 
          template <size_t Index, size_t IndexEnd, typename... TPack>
          struct TypeInitializer {
            void operator()(unsigned int* a_codes){
            }
          };

          template <size_t Index, size_t IndexEnd, typename Ty, typename... TPack>
          struct TypeInitializer<Index, IndexEnd, Ty, TPack...> {
            void operator()(unsigned int* a_codes){
              a_codes[Index] = Type<Ty>::index();
              TypeInitializer<Index+1, IndexEnd, TPack...>()(a_codes);
            }
          };

          template <size_t IndexEnd, typename Ty>
          struct TypeInitializer<IndexEnd-1, IndexEnd, Ty> {
            void operator()(unsigned int* a_codes){
              a_codes[IndexEnd-1] = Type<Ty>::index();
            }
          };
        }
      }

      struct BaseFunctionSignature{

        BaseFunctionSignature() 
          : asize(0)
          , pacodes(&aacodes[0]) {
        }

        BaseFunctionSignature(size_t a_asize)
          : asize(a_asize)
          , pacodes(&aacodes[0]) {
          if (asize > (sizeof(aacodes)/sizeof(aacodes[0]))) {
            vacodes.resize(asize);
            pacodes = &vacodes[0];
          }
        }

        BaseFunctionSignature(const BaseFunctionSignature& a_value){
          operator=(a_value);
        }

        BaseFunctionSignature& operator=(const BaseFunctionSignature& a_value) {
          asize = a_value.asize;
          rcode = a_value.rcode;
          if (a_value.pacodes == &a_value.aacodes[0]){
            memcpy(&aacodes[0], &a_value.aacodes[0], sizeof(aacodes));
            pacodes = &aacodes[0];
          } else {
            vacodes = a_value.vacodes;
            pacodes = &vacodes[0];
          }
          return *this;
        }

        bool operator<(const BaseFunctionSignature& a_value) const{
          if (rcode != a_value.rcode) {
            return rcode < a_value.rcode;
          }
          if (asize != a_value.asize){
            return asize < a_value.asize;
          }
          return memcmp(pacodes, a_value.pacodes, asize * sizeof(unsigned int) ) < 0;
        }

        bool operator==(const BaseFunctionSignature& a_value) const{
          if (rcode != a_value.rcode) {
            return false;
          }
          if (asize != a_value.asize){
            return false;
          }
          return memcmp(pacodes, a_value.pacodes, asize * sizeof(unsigned int)) == 0;
        }

        unsigned int              asize;
        unsigned int              rcode;
        unsigned int*             pacodes;
        unsigned int              aacodes[FCF_FUNCTION_SIGNATURE_CLASS_MEM_STORAGE_SIZE];
        std::vector<unsigned int> vacodes;
      };

      template <typename TFunction>
      struct FunctionSignature;

      template <typename TResult, typename... TArgs>
      struct FunctionSignature<TResult (TArgs...)> : public BaseFunctionSignature{
        typedef TResult(*value_type)(TArgs...);
        FunctionSignature()
          : BaseFunctionSignature(sizeof...( TArgs) ) {
          rcode = Type<TResult>::index();
          Details::FunctionSignature::TypeInitializer<0, sizeof...(TArgs), TArgs...>()(pacodes);
        }
      };

      template <typename TResult, typename... TArgs>
      struct FunctionSignature<TResult (*)(TArgs...)> : public BaseFunctionSignature{
        typedef TResult(*value_type)(TArgs...);
        FunctionSignature()
          : BaseFunctionSignature(sizeof...( TArgs) ) {
          rcode = Type<TResult>::index();
          Details::FunctionSignature::TypeInitializer<0, sizeof...(TArgs), TArgs...>()(pacodes);
        }
      };

} // fcf namespace

#endif // #ifndef ___FCF_SIGNATURE__FUNCTION_SIGNATURE_HPP___
