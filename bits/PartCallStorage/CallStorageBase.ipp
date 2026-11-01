#ifndef _FCF_BASIS__BITS__PART_CALL_STORAGE__CALL_STORAGE_BASE_IPP___
#define _FCF_BASIS__BITS__PART_CALL_STORAGE__CALL_STORAGE_BASE_IPP___

namespace fcf{

  #ifdef FCF_BASIS_IMPLEMENTATION
    void CallStorageBase::_add(std::string a_name,
                               const std::string& a_space,
                               const std::string& a_sourceName,
                               const BaseFunctionSignature& a_functionSignature,
                               const BaseFunctionSignature& a_simpleCallSignature,
                               void* a_function,
                               unsigned int a_argc,
                               std::string a_sourceCode,
                               void (*a_wrapper)(void*, void**),
                               Variant (*a_rwrapper)(void*, void**),
                               unsigned int& a_dstIndex,
                               CallStorageSelectionFunctionGroups::iterator& a_dstGroupIterator
                              ){
      a_name = _rtrim(a_name);
      CallStorageFunctionIndexes::iterator it = indexes.find(a_functionSignature);
      if (it == indexes.end()) {
        CallStorageFunctionIndexes::value_type newItem(a_functionSignature, CallStorageFunctionIndexes::value_type::second_type());
        it = indexes.insert(newItem).first;
      }
      CallStorageFunctionIndexes::value_type::second_type::iterator indexIt = it->second.find(a_name);

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
          if (str == "*" || str == "cpu") {
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
        a_dstIndex = (unsigned int)functions.size();

        CallStorageFunctionInfo sfi;
        sfi.name       = a_name;
        sfi.signature  = a_functionSignature;
        sfi.sourceName = a_function && weight ? a_sourceName : std::string();
        sfi.function   = a_function && weight ? (void*)a_function : (void*)0;

        CallStorageSpace sfs;
        sfs.sourceName = a_sourceName;
        sfs.function   = (void*)a_function;
        sfs.spaces     = spaces;
        sfs.code       = a_sourceCode;
        sfi.spaces.push_back(sfs);

        functions.push_back(sfi);

        it->second[a_name] = a_dstIndex;
      } else {
        a_dstIndex = indexIt->second;

        CallStorageFunctionInfo& sfi = functions[indexIt->second];

        if (!sfi.function && a_function && weight){
          sfi.function = (void*)a_function;
          sfi.sourceName = a_sourceName;
        }

        CallStorageSpace sfs;
        sfs.sourceName = a_sourceName;
        sfs.function   = (void*)a_function;
        sfs.spaces     = spaces;
        sfs.code       = a_sourceCode;
        sfi.spaces.push_back(sfs);
      }

      a_dstGroupIterator = groups.find(a_name);
      if (a_dstGroupIterator == groups.end()) {
        std::pair<std::string, CallStorageSelectionFunctionGroup> item;
        item.first = a_name;
        a_dstGroupIterator = groups.insert(item).first;
      }

      a_dstGroupIterator->second.maxArgumentCount = std::max(a_dstGroupIterator->second.maxArgumentCount, a_argc);

      BaseFunctionSignature sscs = a_simpleCallSignature;
      sscs.rcode = Type<void>().index();
      a_dstGroupIterator->second.callers.insert({
          sscs,
          CallStorageSelectionFunctionInfo{
            a_simpleCallSignature,
            a_dstIndex,
            a_wrapper,
            a_rwrapper,
            CallStorageSelectionFunctionInfo::PlaceHolderType()
          }
        });
      CallStorageSelectionFunctionsByArgNumber::iterator itTree = a_dstGroupIterator->second.callersTree.find(a_simpleCallSignature.asize);
      if (itTree == a_dstGroupIterator->second.callersTree.end()) {
        itTree = a_dstGroupIterator->second.callersTree.insert({a_simpleCallSignature.asize, {}});
      }
      itTree->second.insert({
                  sscs,
                  CallStorageSelectionFunctionInfo{
                    a_simpleCallSignature,
                    a_dstIndex,
                    a_wrapper,
                    a_rwrapper,
                    CallStorageSelectionFunctionInfo::PlaceHolderType()
                  }
                });

    }
  #endif

  #ifdef FCF_BASIS_IMPLEMENTATION
    std::string CallStorageBase::_rtrim(std::string a_str) {
      size_t len = a_str.length(), i = len;
      for(; i && a_str[i-1] == ':'; --i);
      a_str.erase(i, len);
      return a_str;
    }
  #endif



} // fcf namespace

#endif // #ifndef _FCF_BASIS__BITS__PART_CALL_STORAGE__CALL_STORAGE_BASE_IPP___

