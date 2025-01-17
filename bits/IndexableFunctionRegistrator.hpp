#ifndef ___FCF_BASIS__INDEXABLE_FUNCTION_REGISTRATOR_HPP___
#define ___FCF_BASIS__INDEXABLE_FUNCTION_REGISTRATOR_HPP___

#include "./IndexableFunctionSpace.hpp"
#include "./IndexableFunctionInfo.hpp"
#include "../Details/IndexableFunction/Storage.hpp"

namespace fcf {

    struct IndexableFunctionRegistrator {
      template <typename TFunctionResult, typename... TArgPack>
      IndexableFunctionRegistrator(const std::string& a_name, const std::string& a_space, const std::string& a_sourceName, TFunctionResult (*a_function)(TArgPack...), std::string a_sourceCode = std::string()){
        FunctionSignature<TFunctionResult (TArgPack...)> fs;
        Details::IndexableFunction::Indexes::iterator it = Details::IndexableFunction::getStorage().indexes.find(fs);
        if (it == Details::IndexableFunction::getStorage().indexes.end()) {
          Details::IndexableFunction::Indexes::value_type newItem(fs, Details::IndexableFunction::Indexes::value_type::second_type());
          it = Details::IndexableFunction::getStorage().indexes.insert(newItem).first;
        }
        Details::IndexableFunction::Indexes::value_type::second_type::iterator indexIt = it->second.find(a_name);

        int weight = 0;
        std::set<std::string> spaces;
        size_t bspace = 0;
        size_t cspace = 0;
        size_t lspace = a_space.length();
        while(true) {
          bool isCh = cspace != lspace &&
                      (
                        ((unsigned char)a_space[cspace] >= (unsigned char)'a' && (unsigned char)a_space[cspace] <= (unsigned char)'z') ||
                        ((unsigned char)a_space[cspace] >= (unsigned char)'A' && (unsigned char)a_space[cspace] <= (unsigned char)'Z') ||
                        ((unsigned char)a_space[cspace] >= (unsigned char)'0' && (unsigned char)a_space[cspace] <= (unsigned char)'9') ||
                        a_space[bspace] >= '_' ||
                        a_space[bspace] >= '*'
                      );
          if (bspace != cspace && !isCh) {
            std::string str(&a_space[bspace], &a_space[cspace]);
            if (str == "*") {
              weight = 1;
            }
            spaces.insert(str);
          }
          if (cspace == lspace){
            break;
          }
          ++cspace;
          if (!isCh) {
            bspace = cspace;
          }
        }

        if (indexIt == it->second.end()) {
          unsigned int index = Details::IndexableFunction::getStorage().functions.size();

          IndexableFunctionInfo sfi;
          sfi.name       = a_name;
          sfi.signature  = fs;
          sfi.sourceName = a_function && weight ? a_sourceName : std::string();
          sfi.function   = a_function && weight ? (void*)a_function : (void*)0;

          IndexableFunctionSpace sfs;
          sfs.sourceName = a_sourceName;
          sfs.function   = (void*)a_function;
          sfs.spaces     = spaces;
          sfs.code       = a_sourceCode;
          sfi.spaces.push_back(sfs);

          Details::IndexableFunction::getStorage().functions.push_back(sfi);

          it->second[a_name] = index;
        } else {
          IndexableFunctionInfo& sfi = Details::IndexableFunction::getStorage().functions[indexIt->second];

          if (!sfi.function && a_function && weight){
            sfi.function = (void*)a_function;
            sfi.sourceName = a_sourceName;
          }

          IndexableFunctionSpace sfs;
          sfs.sourceName = a_sourceName;
          sfs.function   = (void*)a_function;
          sfs.spaces     = spaces;
          sfs.code       = a_sourceCode;
          sfi.spaces.push_back(sfs);
        }
      }

      template <typename TFunction>
      static unsigned int getIndex(const std::string& a_name){
        FunctionSignature<TFunction> fs;
          Details::IndexableFunction::Indexes::iterator it = Details::IndexableFunction::getStorage().indexes.find(fs);
        if (it == Details::IndexableFunction::getStorage().indexes.end()) {
          throw std::runtime_error(std::string() + "Function \"" + a_name + "\" not found");
        }
        Details::IndexableFunction::Indexes::value_type::second_type::iterator itFunc = it->second.find(a_name);
        if (itFunc == it->second.end()) {
          throw std::runtime_error(std::string() + "Function \"" + a_name + "\" not found");
        }
        return itFunc->second;
      }

      static unsigned int getSize(){
        return (unsigned int)Details::IndexableFunction::getStorage().functions.size();
      }

      static const IndexableFunctionInfo& getFunctionInfo(unsigned int a_index){
        return Details::IndexableFunction::getStorage().functions[a_index];
      }
    };
  
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__INDEXABLE_FUNCTION_REGISTRATOR_HPP___
