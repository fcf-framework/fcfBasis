#ifndef ___FCF_BASIS__BITS__PART_CALL__NDETAILS__CALL_ARGUMENTS_HPP___
#define ___FCF_BASIS__BITS__PART_CALL__NDETAILS__CALL_ARGUMENTS_HPP___

#include <tuple>
#include "../../../PartStaticVector.hpp"
#include "../../../PartType.hpp"
#include "../../../PartForeach.hpp"
#include "../../../PartException.hpp"

namespace fcf{
  namespace NDetails {

    class CallArguments {
      public:
      struct ArgumentInfo {
        unsigned int    typeIndex;
        const TypeInfo* typeInfo;
      };
      private:

      struct ArgumentInfoFull : public ArgumentInfo {
        void* ptr;
      };

      enum { STATIC_BUFFER_SIZE = 8 };

      char                     _mem[sizeof(ArgumentInfoFull) * STATIC_BUFFER_SIZE];
      void*                    _ptr;
      size_t                   _capacity;
      size_t                   _size;

      inline void _init(size_t a_size) {
        if (a_size <= STATIC_BUFFER_SIZE){
          _ptr = &_mem[0];
          _capacity = STATIC_BUFFER_SIZE;
        } else {
          _capacity = STATIC_BUFFER_SIZE << 1;
          while(_capacity < a_size) {
            _capacity <<= 1;
          }
          _ptr = new char[sizeof(ArgumentInfoFull) * _capacity];
        }
      }

      inline void _destroy() {
        if (_ptr != &_mem[0]){
          delete[] (char*)_ptr;
        }
      }

      inline void _realloc(size_t a_size, bool a_copyMode){
        if (a_size <= _capacity){
          return;
        }
        ArgumentInfo* oldInfoPtr =  (ArgumentInfo*)(((void**)_ptr) + _capacity);
        while(_capacity < a_size) {
          _capacity <<= 1;
        }
        void* ptr = new char[sizeof(ArgumentInfoFull) * _capacity];
        if (a_copyMode) {
          ArgumentInfo* infoPtr = (ArgumentInfo*)(((void**)ptr) + _capacity);
          for(size_t i = 0; i < _size; ++i){
            ((void**)ptr)[i] = ((void**)_ptr)[i];
            infoPtr[i] = oldInfoPtr[i];
          }
        }
        if (_ptr != &_mem[0]){
          delete[] (char*)_ptr;
        }
        _ptr = ptr;
      }

    public:
      template <typename ...TArgPack>
      inline CallArguments(Nop /*a_nop*/, const TArgPack&... a_argPack) {
        _init(sizeof...(TArgPack));
        _size = sizeof...(TArgPack);

        std::tuple<TArgPack*...>  tuple{(TArgPack*)&a_argPack...};
        foreach(tuple, ArgFiller(this));
        /*
        ArgumentInfo* infoPtr =  (ArgumentInfo*)(((void**)_ptr) + _capacity);
        _argFill<0>(infoPtr, a_argPack...);
        */
      }

      template <typename ...TArgPack>
      inline CallArguments(std::tuple<TArgPack*...>& a_tuple) {
        _init(sizeof...(TArgPack));
        _size = sizeof...(TArgPack);

        foreach(a_tuple, ArgFiller(this));
      }

      inline CallArguments(size_t a_csize, size_t a_size) {
        _init(a_csize);
        _size = a_size;
      }

      inline CallArguments(const CallArguments& a_source) {
        _init(a_source._capacity);
        _size = a_source._size;
        ArgumentInfo* slfInfoPtr =  (ArgumentInfo*)(((void**)_ptr) + _capacity);
        ArgumentInfo* srcInfoPtr =  (ArgumentInfo*)(((void**)a_source._ptr) + a_source._capacity);
        for(size_t i = 0; i < _size; ++i){
          slfInfoPtr[i] = srcInfoPtr[i];
          ((void**)_ptr)[i] = ((void**)a_source._ptr)[i];
        }
      }

      inline CallArguments& operator=(const CallArguments& a_source) {
        if (_capacity < a_source._capacity){
          _realloc(a_source._capacity, false);
        }
        _size = a_source._size;
        ArgumentInfo* slfInfoPtr =  (ArgumentInfo*)(((void**)_ptr) + _capacity);
        ArgumentInfo* srcInfoPtr =  (ArgumentInfo*)(((void**)a_source._ptr) + a_source._capacity);
        for(size_t i = 0; i < _size; ++i){
          slfInfoPtr[i] = srcInfoPtr[i];
          ((void**)_ptr)[i] = ((void**)a_source._ptr)[i];
        }
        return *this;
      }

      inline size_t size() const{
        return _size;
      }

      inline void resize(size_t a_size) {
        _realloc(a_size, true);
        _size = a_size;
      } 

      inline unsigned int getTypeIndex(size_t a_index) const{
        ArgumentInfo* infoPtr =  (ArgumentInfo*)(((void**)_ptr) + _capacity) + a_index;
        return infoPtr->typeIndex;
      }

      inline void setTypeIndex(size_t a_index, unsigned int a_typeIndex) {
        ArgumentInfo* infoPtr =  (ArgumentInfo*)(((void**)_ptr) + _capacity) + a_index;
        infoPtr->typeIndex = a_typeIndex;
      }

      inline const TypeInfo* getTypeInfo(size_t a_index){
        ArgumentInfo* infoPtr =  (ArgumentInfo*)(((void**)_ptr) + _capacity) + a_index;
        if (infoPtr->typeInfo->index != infoPtr->typeIndex) {
          infoPtr->typeInfo = fcf::getTypeInfo(infoPtr->typeIndex);
        }
        return infoPtr->typeInfo;
      }

      inline ArgumentInfo& getArgumentInfo(size_t a_index){
        ArgumentInfo* infoPtr =  (ArgumentInfo*)(((void**)_ptr) + _capacity) + a_index;
        if (infoPtr->typeInfo->index != infoPtr->typeIndex) {
          infoPtr->typeInfo = fcf::getTypeInfo(infoPtr->typeIndex);
        }
        return *infoPtr;
      }

      inline void setArgumentInfo(size_t a_index, const ArgumentInfo& a_argumentInfo){
        ArgumentInfo* infoPtr =  (ArgumentInfo*)(((void**)_ptr) + _capacity) + a_index;
        *infoPtr = a_argumentInfo;
      }

      inline void* getArgument(size_t a_index){
        return ((void**)_ptr)[a_index];
      }

      inline void setArgument(size_t a_index, void* a_ptr){
        ((void**)_ptr)[a_index] = a_ptr;
      }

      inline void** getArguments(){
        return &((void**)_ptr)[0];
      }

      inline void extend(size_t /*a_index*/){
      }

      inline void prepare(ptrdiff_t /*a_index*/, bool a_forceCopy = false){
        (void)a_forceCopy;
      }

      inline void prepare(){
      }

      inline void prepareForceCopy() {
      }

      inline CallArguments& getCallArguments(){
        return *this;
      }

      inline CallArguments& getSourceCallArguments(){
        return *this;
      }

      inline std::string getStringRepresentationTypes(){
        std::string result;
        for(size_t i = 0; i < size(); ++i){
          if (i){
            result += ", ";
          }
          result += getTypeInfo(i)->name;
        }
        return result;
      }

    protected:
      FCF_FOREACH_METHOD_WRAPPER(ArgFiller, CallArguments, _argFiller);
      template <typename TTuple, typename TArg>
      void _argFiller(const TTuple&, size_t a_index, TArg* a_arg) {
        ((void**)_ptr)[a_index] = (void*)a_arg;
        ArgumentInfo* infoPtr =  (ArgumentInfo*)(((void**)_ptr) + _capacity) + a_index;
        infoPtr->typeInfo = Type<TArg>().getTypeInfo();
        infoPtr->typeIndex = infoPtr->typeInfo->index;
      }

      /*
      template <size_t Index, typename ArgumentInfo, typename TArg, typename ... TPackArg>
      inline void _argFill(ArgumentInfo* a_infoPtr, const TArg& a_arg, TPackArg&... a_packArg) {
        ((void**)_ptr)[Index] = (void*)&a_arg;
        ArgumentInfo* infoPtr = a_infoPtr + Index;
        infoPtr->typeInfo = Type<TArg>().getTypeInfo();
        infoPtr->typeIndex = infoPtr->typeInfo->index;
        _argFill<Index+1>(a_infoPtr, a_packArg...);
      }

      template <size_t Index, typename ArgumentInfo>
      inline void _argFill(ArgumentInfo*) {
      }
      */

    };


    class CallArgumentsExtended {
      CallArguments& _source;
      CallArguments  _buffer;
      CallArguments* _current;
      unsigned int   _extendCounter;

      public:
        inline CallArgumentsExtended(CallArguments& a_source)
          : _source(a_source)
          , _buffer(0, 0)
          , _current(&_source)
          , _extendCounter(0) {
        }

        inline CallArguments& getCallArguments(){
          return *_current;
        }

        inline CallArguments& getSourceCallArguments(){
          return _source;
        }

        inline void extend(size_t a_index){
          _current = &_buffer;
          if (a_index) {
            prepare((ptrdiff_t)a_index-1);
          }
          if (a_index < _buffer.size()) {
            throw CallArgumentBufferOverflowException(__FILE__, __LINE__, _source.getStringRepresentationTypes());
          }
          _buffer.resize(a_index+1);
          _buffer.setArgumentInfo(a_index, CallArguments::ArgumentInfo{ Type<void>().index(), Type<void>().getTypeInfo() });
          ++_extendCounter;
        }

        inline void prepare(){
          prepare(_extendCounter + _source.size() - 1);
        }

        inline void prepareForceCopy() {
          prepare(_extendCounter + _source.size() - 1, true);
        }

        inline void prepare(ptrdiff_t a_index, bool a_forceCopy = false){
          if (!a_forceCopy) {
            if (_current != &_buffer){
              return;
            }
          } else {
              if (_current != &_buffer) {
                _current = &_buffer;
              }
          }
          if (a_index < (ptrdiff_t)_buffer.size()) {
            return;
          }
          size_t lastIndex = _buffer.size();
          _buffer.resize(a_index+1);
          while(lastIndex <= (size_t)a_index){
            _buffer.setArgumentInfo(lastIndex, _source.getArgumentInfo(lastIndex - _extendCounter));
            _buffer.setArgument(lastIndex, _source.getArgument(lastIndex - _extendCounter));
            ++lastIndex;
          }
        }

        inline size_t size() const{
          return _current->size();
        }

        inline void resize(size_t a_size) {
          prepare((ptrdiff_t)a_size - 1);
          _current->resize(a_size);
        } 

        inline unsigned int getTypeIndex(size_t a_index) const{
          return _current->getTypeIndex(a_index);
        }

        inline void setTypeIndex(size_t a_index, unsigned int a_typeIndex){
          _current->setTypeIndex(a_index, a_typeIndex);
        }


        inline const TypeInfo* getTypeInfo(size_t a_index){
          return _current->getTypeInfo(a_index);
        }

        inline CallArguments::ArgumentInfo& getArgumentInfo(size_t a_index){
          return _current->getArgumentInfo(a_index);
        }

        inline void setArgumentInfo(size_t a_index, const CallArguments::ArgumentInfo& a_argumentInfo){
          _current->setArgumentInfo(a_index, a_argumentInfo);
        }

        inline void* getArgument(size_t a_index){
          return _current->getArgument(a_index);
        }

        inline void setArgument(size_t a_index, void* a_ptr){
          _current->setArgument(a_index, a_ptr);
        }

        inline void** getArguments() {
          return _current->getArguments();
        }

    };
  } // NDetails namespace
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_CALL__NDETAILS__CALL_ARGUMENTS_HPP___
