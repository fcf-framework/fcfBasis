#ifndef ___FCF_BASIS__BITS__PART_STATIC_VECTOR__STATIC_VECTOR_HPP___
#define ___FCF_BASIS__BITS__PART_STATIC_VECTOR__STATIC_VECTOR_HPP___

#include "StaticVectorDefinition.hpp"

namespace fcf{

  template<typename Ty, unsigned int StaticSize=16, unsigned int OffsetSize=2, unsigned int StepSize=2, unsigned int StepModuleInt=2, unsigned int StepModuleFrac=0, unsigned int MaxPow=/*16*2*4096/sizeof(Ty)*/ 0 >
  class StaticVector;


  template<typename Ty, unsigned int StaticSize, unsigned int OffsetSize, unsigned int StepSize, unsigned int StepModuleInt, unsigned int StepModuleFrac, unsigned int MaxPow>
  struct Cursor< StaticVector<Ty, StaticSize, OffsetSize, StepSize, StepModuleInt, StepModuleFrac, MaxPow> > : public FlatCursor<
                                  StaticVector<Ty, StaticSize, OffsetSize, StepSize, StepModuleInt, StepModuleFrac, MaxPow>
                                >{
    typedef FlatCursor< StaticVector<Ty, StaticSize, OffsetSize, StepSize, StepModuleInt, StepModuleFrac, MaxPow>
                       > BaseType;
    using FlatCursor< StaticVector<Ty, StaticSize, OffsetSize, StepSize, StepModuleInt, StepModuleFrac, MaxPow> >::FlatCursor;
  };

  template<typename Ty, unsigned int StaticSize, unsigned int OffsetSize, unsigned int StepSize, unsigned int StepModuleInt, unsigned int StepModuleFrac, unsigned int MaxPow >
  StaticVector<Ty, StaticSize, OffsetSize, StepSize, StepModuleInt, StepModuleFrac, MaxPow >::StaticVector()
    : _pdata((Ty*)&_adata[0])
    , _sdata(0)
    , _cdata(StaticSize) {
  }

  template<typename Ty, unsigned int StaticSize, unsigned int OffsetSize, unsigned int StepSize, unsigned int StepModuleInt, unsigned int StepModuleFrac, unsigned int MaxPow >
  StaticVector<Ty, StaticSize, OffsetSize, StepSize, StepModuleInt, StepModuleFrac, MaxPow >::~StaticVector() {
    _destroyMem(_pdata, _sdata);
  }

  template<typename Ty, unsigned int StaticSize, unsigned int OffsetSize, unsigned int StepSize, unsigned int StepModuleInt, unsigned int StepModuleFrac, unsigned int MaxPow >
  StaticVector<Ty, StaticSize, OffsetSize, StepSize, StepModuleInt, StepModuleFrac, MaxPow >::StaticVector(size_t a_size)
    : _pdata((Ty*)&_adata[0])
    , _sdata(0)
    , _cdata(StaticSize){
    _realloc(_getBufferSize(a_size), a_size);
  }

  template<typename Ty, unsigned int StaticSize, unsigned int OffsetSize, unsigned int StepSize, unsigned int StepModuleInt, unsigned int StepModuleFrac, unsigned int MaxPow >
  StaticVector<Ty, StaticSize, OffsetSize, StepSize, StepModuleInt, StepModuleFrac, MaxPow >::StaticVector(const StaticVector& a_source)
    : _pdata((Ty*)&_adata[0])
    , _sdata(0)
    , _cdata(StaticSize) {
    _forceRealloc(_getBufferSize(a_source.size()));
    _copyMem(_pdata, a_source.size(), a_source, _sdata);
  }

  template<typename Ty, unsigned int StaticSize, unsigned int OffsetSize, unsigned int StepSize, unsigned int StepModuleInt, unsigned int StepModuleFrac, unsigned int MaxPow >
  StaticVector<Ty, StaticSize, OffsetSize, StepSize, StepModuleInt, StepModuleFrac, MaxPow >::StaticVector(std::initializer_list<Ty> a_list)
    : _pdata((Ty*)&_adata[0])
    , _sdata(0)
    , _cdata(StaticSize) {
    _forceRealloc(_getBufferSize(a_list.size()));
    for(auto it = a_list.begin(); it != a_list.end(); ++it){
      new (&_pdata[_sdata]) Ty(*it);
      ++_sdata;
    }
  }

  template<typename Ty, unsigned int StaticSize, unsigned int OffsetSize, unsigned int StepSize, unsigned int StepModuleInt, unsigned int StepModuleFrac, unsigned int MaxPow >
  StaticVector<Ty, StaticSize, OffsetSize, StepSize, StepModuleInt, StepModuleFrac, MaxPow >::StaticVector(const Ty* a_begin, size_t a_size)
    : _pdata((Ty*)&_adata[0])
    , _sdata(0)
    , _cdata(StaticSize) {
    _forceRealloc(_getBufferSize(a_size));
    for(size_t i = 0; i != a_size; ++i){
      new (&_pdata[_sdata]) Ty(a_begin[i]);
      ++_sdata;
    }
  }

  template<typename Ty, unsigned int StaticSize, unsigned int OffsetSize, unsigned int StepSize, unsigned int StepModuleInt, unsigned int StepModuleFrac, unsigned int MaxPow >
  StaticVector<Ty, StaticSize, OffsetSize, StepSize, StepModuleInt, StepModuleFrac, MaxPow >::StaticVector(size_t a_size, const Ty& a_fill)
    : _pdata((Ty*)&_adata[0])
    , _sdata(0)
    , _cdata(StaticSize) {
    _forceRealloc(_getBufferSize(a_size));
    for(; _sdata < a_size; ++_sdata){
      new (&_pdata[_sdata]) Ty(a_fill);
    }
  }

  template<typename Ty, unsigned int StaticSize, unsigned int OffsetSize, unsigned int StepSize, unsigned int StepModuleInt, unsigned int StepModuleFrac, unsigned int MaxPow >
  StaticVector<Ty, StaticSize, OffsetSize, StepSize, StepModuleInt, StepModuleFrac, MaxPow >& StaticVector<Ty, StaticSize, OffsetSize, StepSize, StepModuleInt, StepModuleFrac, MaxPow >::operator=(const StaticVector& a_source){
    _forceRealloc(_getBufferSize(a_source.size()));
    _copyMem(_pdata, a_source.size(), a_source, _sdata);
    return *this;
  }

  template<typename Ty, unsigned int StaticSize, unsigned int OffsetSize, unsigned int StepSize, unsigned int StepModuleInt, unsigned int StepModuleFrac, unsigned int MaxPow >
  typename StaticVector<Ty, StaticSize, OffsetSize, StepSize, StepModuleInt, StepModuleFrac, MaxPow >::iterator StaticVector<Ty, StaticSize, OffsetSize, StepSize, StepModuleInt, StepModuleFrac, MaxPow >::begin(){
    return iterator(*this, 0, false);
  }

  template<typename Ty, unsigned int StaticSize, unsigned int OffsetSize, unsigned int StepSize, unsigned int StepModuleInt, unsigned int StepModuleFrac, unsigned int MaxPow >
  typename StaticVector<Ty, StaticSize, OffsetSize, StepSize, StepModuleInt, StepModuleFrac, MaxPow >::const_iterator StaticVector<Ty, StaticSize, OffsetSize, StepSize, StepModuleInt, StepModuleFrac, MaxPow >::begin() const{
    return const_iterator(*this, 0);
  }

  template<typename Ty, unsigned int StaticSize, unsigned int OffsetSize, unsigned int StepSize, unsigned int StepModuleInt, unsigned int StepModuleFrac, unsigned int MaxPow >
  typename StaticVector<Ty, StaticSize, OffsetSize, StepSize, StepModuleInt, StepModuleFrac, MaxPow >::const_iterator StaticVector<Ty, StaticSize, OffsetSize, StepSize, StepModuleInt, StepModuleFrac, MaxPow >::cbegin() const{
    return const_iterator(*this, 0);
  }

  template<typename Ty, unsigned int StaticSize, unsigned int OffsetSize, unsigned int StepSize, unsigned int StepModuleInt, unsigned int StepModuleFrac, unsigned int MaxPow >
  typename StaticVector<Ty, StaticSize, OffsetSize, StepSize, StepModuleInt, StepModuleFrac, MaxPow >::iterator StaticVector<Ty, StaticSize, OffsetSize, StepSize, StepModuleInt, StepModuleFrac, MaxPow >::end(){
    return iterator(*this, _sdata, false);
  }

  template<typename Ty, unsigned int StaticSize, unsigned int OffsetSize, unsigned int StepSize, unsigned int StepModuleInt, unsigned int StepModuleFrac, unsigned int MaxPow >
  typename StaticVector<Ty, StaticSize, OffsetSize, StepSize, StepModuleInt, StepModuleFrac, MaxPow >::const_iterator StaticVector<Ty, StaticSize, OffsetSize, StepSize, StepModuleInt, StepModuleFrac, MaxPow >::end() const{
    return const_iterator(*this, _sdata);
  }

  template<typename Ty, unsigned int StaticSize, unsigned int OffsetSize, unsigned int StepSize, unsigned int StepModuleInt, unsigned int StepModuleFrac, unsigned int MaxPow >
  typename StaticVector<Ty, StaticSize, OffsetSize, StepSize, StepModuleInt, StepModuleFrac, MaxPow >::const_iterator StaticVector<Ty, StaticSize, OffsetSize, StepSize, StepModuleInt, StepModuleFrac, MaxPow >::cend() const{
    return const_iterator(*this, _sdata);
  }

  template<typename Ty, unsigned int StaticSize, unsigned int OffsetSize, unsigned int StepSize, unsigned int StepModuleInt, unsigned int StepModuleFrac, unsigned int MaxPow >
  Ty& StaticVector<Ty, StaticSize, OffsetSize, StepSize, StepModuleInt, StepModuleFrac, MaxPow >::operator[](size_t a_index){
    return _pdata[a_index];
  }

  template<typename Ty, unsigned int StaticSize, unsigned int OffsetSize, unsigned int StepSize, unsigned int StepModuleInt, unsigned int StepModuleFrac, unsigned int MaxPow >
  const Ty& StaticVector<Ty, StaticSize, OffsetSize, StepSize, StepModuleInt, StepModuleFrac, MaxPow >::operator[](size_t a_index) const{
    return _pdata[a_index];
  }

  template<typename Ty, unsigned int StaticSize, unsigned int OffsetSize, unsigned int StepSize, unsigned int StepModuleInt, unsigned int StepModuleFrac, unsigned int MaxPow >
  size_t StaticVector<Ty, StaticSize, OffsetSize, StepSize, StepModuleInt, StepModuleFrac, MaxPow >::size() const{
    return _sdata;
  }

  template<typename Ty, unsigned int StaticSize, unsigned int OffsetSize, unsigned int StepSize, unsigned int StepModuleInt, unsigned int StepModuleFrac, unsigned int MaxPow >
  size_t StaticVector<Ty, StaticSize, OffsetSize, StepSize, StepModuleInt, StepModuleFrac, MaxPow >::capacity() const{
    return _cdata;
  }

  template<typename Ty, unsigned int StaticSize, unsigned int OffsetSize, unsigned int StepSize, unsigned int StepModuleInt, unsigned int StepModuleFrac, unsigned int MaxPow >
  bool StaticVector<Ty, StaticSize, OffsetSize, StepSize, StepModuleInt, StepModuleFrac, MaxPow >::empty() const{
    return !_sdata;
  }

  template<typename Ty, unsigned int StaticSize, unsigned int OffsetSize, unsigned int StepSize, unsigned int StepModuleInt, unsigned int StepModuleFrac, unsigned int MaxPow >
  void StaticVector<Ty, StaticSize, OffsetSize, StepSize, StepModuleInt, StepModuleFrac, MaxPow >::clear(bool a_notReduce){
    if (a_notReduce) {
      _destroyMem(_pdata, _sdata, _sdata);
    } else {
      _realloc(0, 0);
    }
  }

  template<typename Ty, unsigned int StaticSize, unsigned int OffsetSize, unsigned int StepSize, unsigned int StepModuleInt, unsigned int StepModuleFrac, unsigned int MaxPow >
  Ty& StaticVector<Ty, StaticSize, OffsetSize, StepSize, StepModuleInt, StepModuleFrac, MaxPow >::back(){
    return _pdata[_sdata-1];
  }

  template<typename Ty, unsigned int StaticSize, unsigned int OffsetSize, unsigned int StepSize, unsigned int StepModuleInt, unsigned int StepModuleFrac, unsigned int MaxPow >
  const Ty& StaticVector<Ty, StaticSize, OffsetSize, StepSize, StepModuleInt, StepModuleFrac, MaxPow >::back() const{
    return _pdata[_sdata-1];
  }

  template<typename Ty, unsigned int StaticSize, unsigned int OffsetSize, unsigned int StepSize, unsigned int StepModuleInt, unsigned int StepModuleFrac, unsigned int MaxPow >
  Ty& StaticVector<Ty, StaticSize, OffsetSize, StepSize, StepModuleInt, StepModuleFrac, MaxPow >::front(){
    return _pdata[0];
  }

  template<typename Ty, unsigned int StaticSize, unsigned int OffsetSize, unsigned int StepSize, unsigned int StepModuleInt, unsigned int StepModuleFrac, unsigned int MaxPow >
  const Ty& StaticVector<Ty, StaticSize, OffsetSize, StepSize, StepModuleInt, StepModuleFrac, MaxPow >::front() const{
    return _pdata[0];
  }

  template<typename Ty, unsigned int StaticSize, unsigned int OffsetSize, unsigned int StepSize, unsigned int StepModuleInt, unsigned int StepModuleFrac, unsigned int MaxPow >
  void StaticVector<Ty, StaticSize, OffsetSize, StepSize, StepModuleInt, StepModuleFrac, MaxPow >::push_back(const Ty& a_value){
    if (_cdata <= _sdata){
      _realloc(_getNextSize(_cdata), _sdata);
    }
    new (&_pdata[_sdata]) Ty(a_value);
    ++_sdata;
  }

  template<typename Ty, unsigned int StaticSize, unsigned int OffsetSize, unsigned int StepSize, unsigned int StepModuleInt, unsigned int StepModuleFrac, unsigned int MaxPow >
  void StaticVector<Ty, StaticSize, OffsetSize, StepSize, StepModuleInt, StepModuleFrac, MaxPow >::pop_back(bool a_notReduce){
    if (_sdata) {
      if (!a_notReduce) {
        size_t prev = _getPreviousSize(capacity());
        if (prev >= _sdata - 1){
          _realloc(prev, _sdata-1);
        } else {
          --_sdata;
          _pdata[_sdata].~Ty();
        }
      } else {
        --_sdata;
        _pdata[_sdata].~Ty();
      }
    }
  }

  template<typename Ty, unsigned int StaticSize, unsigned int OffsetSize, unsigned int StepSize, unsigned int StepModuleInt, unsigned int StepModuleFrac, unsigned int MaxPow >
  void StaticVector<Ty, StaticSize, OffsetSize, StepSize, StepModuleInt, StepModuleFrac, MaxPow >::reserve(size_t a_size) {
    size_t newBufferSize = _getBufferSize(a_size);
    _realloc(newBufferSize, a_size < _sdata ? a_size : _sdata);
  }

  template<typename Ty, unsigned int StaticSize, unsigned int OffsetSize, unsigned int StepSize, unsigned int StepModuleInt, unsigned int StepModuleFrac, unsigned int MaxPow >
  void StaticVector<Ty, StaticSize, OffsetSize, StepSize, StepModuleInt, StepModuleFrac, MaxPow >::resize(size_t a_size, bool a_notReduce) {
    size_t newBufferSize = _getBufferSize(a_size);
    if (a_notReduce && newBufferSize < _cdata) {
      newBufferSize = _cdata;
    }
    _realloc(newBufferSize, a_size);
  }

  template<typename Ty, unsigned int StaticSize, unsigned int OffsetSize, unsigned int StepSize, unsigned int StepModuleInt, unsigned int StepModuleFrac, unsigned int MaxPow >
  typename  StaticVector<Ty, StaticSize, OffsetSize, StepSize, StepModuleInt, StepModuleFrac, MaxPow >::iterator StaticVector<Ty, StaticSize, OffsetSize, StepSize, StepModuleInt, StepModuleFrac, MaxPow >::insert(iterator a_iterator, const Ty& a_value){
    size_t nextSize;
    if (_cdata <= _sdata){
      nextSize = _getNextSize(_cdata);
    } else {
      nextSize = _cdata;
    }
    _insert(nextSize, a_iterator.key(), &a_value, 1);
    return iterator(*this, a_iterator.key(), false);
  }

  template<typename Ty, unsigned int StaticSize, unsigned int OffsetSize, unsigned int StepSize, unsigned int StepModuleInt, unsigned int StepModuleFrac, unsigned int MaxPow >
  template <typename TInsertIterator>
  typename StaticVector<Ty, StaticSize, OffsetSize, StepSize, StepModuleInt, StepModuleFrac, MaxPow >::iterator StaticVector<Ty, StaticSize, OffsetSize, StepSize, StepModuleInt, StepModuleFrac, MaxPow >::insert(iterator a_iterator, TInsertIterator a_begin, TInsertIterator a_end){
    size_t insertSize = std::distance(a_begin, a_end);
    size_t nextSize;
    if (!insertSize)  {
      return iterator(*this, a_iterator.key(), false);
    } else if (insertSize == 1) {
      nextSize = _getNextSize(_cdata);
    } else {
      nextSize = _getBufferSize(_sdata + insertSize);
    }
    _insert(nextSize, a_iterator.key(), a_begin, std::distance(a_begin, a_end));
    return iterator(*this, a_iterator.key(), false);
  }

  template<typename Ty, unsigned int StaticSize, unsigned int OffsetSize, unsigned int StepSize, unsigned int StepModuleInt, unsigned int StepModuleFrac, unsigned int MaxPow >
  typename StaticVector<Ty, StaticSize, OffsetSize, StepSize, StepModuleInt, StepModuleFrac, MaxPow >::iterator StaticVector<Ty, StaticSize, OffsetSize, StepSize, StepModuleInt, StepModuleFrac, MaxPow >::erase(iterator a_iterator, bool a_notReduce){
    if (a_iterator.key() >= _sdata){
      return iterator(*this, 0, false);
    }
    size_t newBufferSize;
    if (a_notReduce) {
      newBufferSize = _cdata;
    } else {
      size_t prev = _getPreviousSize(capacity());
      if (prev >= _sdata - 1) {
        newBufferSize = prev;
      } else {
        newBufferSize = _cdata;
      }
    }
    _erase(newBufferSize, a_iterator.key(), 1);
    return iterator(*this, a_iterator.key(), false);
  }

  template<typename Ty, unsigned int StaticSize, unsigned int OffsetSize, unsigned int StepSize, unsigned int StepModuleInt, unsigned int StepModuleFrac, unsigned int MaxPow >
  typename StaticVector<Ty, StaticSize, OffsetSize, StepSize, StepModuleInt, StepModuleFrac, MaxPow >::iterator StaticVector<Ty, StaticSize, OffsetSize, StepSize, StepModuleInt, StepModuleFrac, MaxPow >::erase(iterator a_begin, iterator a_end, bool a_notReduce){
    if (a_begin.key() >= _sdata){
      return iterator(*this, 0, false);
    }
    if (a_end.key() > _sdata){
      a_end.cursor.key = _sdata;
    }
    size_t eraseSize = a_begin.distance(a_end);
    size_t newBufferSize;
    if (a_notReduce) {
      newBufferSize = _cdata;
    } else {
      newBufferSize= _getBufferSize(_sdata - eraseSize);
    }
    _erase(newBufferSize, a_begin.key(), eraseSize);
    return iterator(*this, a_begin.key(), false);
  }


  template<typename Ty, unsigned int StaticSize, unsigned int OffsetSize, unsigned int StepSize, unsigned int StepModuleInt, unsigned int StepModuleFrac, unsigned int MaxPow >
  void StaticVector<Ty, StaticSize, OffsetSize, StepSize, StepModuleInt, StepModuleFrac, MaxPow >::_initMem(Ty* a_mem, size_t a_size, size_t& a_sdata) {
    new (&a_mem[0]) Ty[a_size]();
    a_sdata += a_size;
  }

  template<typename Ty, unsigned int StaticSize, unsigned int OffsetSize, unsigned int StepSize, unsigned int StepModuleInt, unsigned int StepModuleFrac, unsigned int MaxPow >
  void StaticVector<Ty, StaticSize, OffsetSize, StepSize, StepModuleInt, StepModuleFrac, MaxPow >::_destroyMem(Ty* a_mem, size_t a_size, size_t& a_sdata) {
    a_sdata -= a_size;
    while (a_size) {
      --a_size;
      a_mem[a_size].~Ty();
    }
  }

  template<typename Ty, unsigned int StaticSize, unsigned int OffsetSize, unsigned int StepSize, unsigned int StepModuleInt, unsigned int StepModuleFrac, unsigned int MaxPow >
  void StaticVector<Ty, StaticSize, OffsetSize, StepSize, StepModuleInt, StepModuleFrac, MaxPow >::_destroyMem(Ty* a_mem, size_t a_size) {
    while (a_size) {
      --a_size;
      a_mem[a_size].~Ty();
    }
  }

  template<typename Ty, unsigned int StaticSize, unsigned int OffsetSize, unsigned int StepSize, unsigned int StepModuleInt, unsigned int StepModuleFrac, unsigned int MaxPow >
  template <typename TContainer>
  void StaticVector<Ty, StaticSize, OffsetSize, StepSize, StepModuleInt, StepModuleFrac, MaxPow >::_copyMem(Ty* a_mem, size_t a_size, TContainer& a_container, size_t& a_sdata) {
    for(size_t i = 0; i < a_size; ++i) {
      new (&a_mem[i]) Ty(a_container[i]);
      ++a_sdata;
    }
  }


  template<typename Ty, unsigned int StaticSize, unsigned int OffsetSize, unsigned int StepSize, unsigned int StepModuleInt, unsigned int StepModuleFrac, unsigned int MaxPow >
  template <typename TIterator>
  void StaticVector<Ty, StaticSize, OffsetSize, StepSize, StepModuleInt, StepModuleFrac, MaxPow >::_iteratorCopy(Ty* a_mem, TIterator& a_iterator, size_t a_size, size_t& a_sdata) {
    for(size_t i = 0; i < a_size; ++i) {
      new (&a_mem[i]) Ty(*a_iterator);
      ++a_sdata;
      ++a_iterator;
    }
  }

  template<typename Ty, unsigned int StaticSize, unsigned int OffsetSize, unsigned int StepSize, unsigned int StepModuleInt, unsigned int StepModuleFrac, unsigned int MaxPow >
  void StaticVector<Ty, StaticSize, OffsetSize, StepSize, StepModuleInt, StepModuleFrac, MaxPow >::_memRightMove(Ty* a_mem, size_t a_memSize, Ty* a_destMem) {
    Ty* mem = a_mem + a_memSize - 1;
    Ty* endMem = a_mem - 1;
    Ty* destMem = a_destMem + a_memSize - 1;
    while(mem != endMem) {
      new (destMem) Ty(*mem);
      mem->~Ty();
      --mem;
      --destMem;
    }
  }

  template<typename Ty, unsigned int StaticSize, unsigned int OffsetSize, unsigned int StepSize, unsigned int StepModuleInt, unsigned int StepModuleFrac, unsigned int MaxPow >
  void StaticVector<Ty, StaticSize, OffsetSize, StepSize, StepModuleInt, StepModuleFrac, MaxPow >::_memLeftMove(Ty* a_mem, size_t a_memSize, Ty* a_destMem) {
    Ty* endMem = a_mem + a_memSize;
    while(a_mem != endMem) {
      new (a_destMem) Ty(*a_mem);
      a_mem->~Ty();
      ++a_mem;
      ++a_destMem;
    }
  }

  template<typename Ty, unsigned int StaticSize, unsigned int OffsetSize, unsigned int StepSize, unsigned int StepModuleInt, unsigned int StepModuleFrac, unsigned int MaxPow >
  void StaticVector<Ty, StaticSize, OffsetSize, StepSize, StepModuleInt, StepModuleFrac, MaxPow >::_forceRealloc(size_t a_size){
    const size_t oldCapacity = capacity();

    _destroyMem(_pdata, _sdata);

    if ((char*)_pdata != &_adata[0] && oldCapacity != a_size){
      _mdata.reset();
    }

    _sdata = 0;

    if (a_size <= StaticSize) {
      _pdata = (Ty*)&_adata[0];
      _cdata = StaticSize;
    } else if (oldCapacity != a_size){
      size_t bufferSize = sizeof(Ty)*a_size;
      _mdata.reset(new char[bufferSize]);
      _pdata = (Ty*)_mdata.get();
      _cdata = a_size;
    }
  }

  template<typename Ty, unsigned int StaticSize, unsigned int OffsetSize, unsigned int StepSize, unsigned int StepModuleInt, unsigned int StepModuleFrac, unsigned int MaxPow >
  void StaticVector<Ty, StaticSize, OffsetSize, StepSize, StepModuleInt, StepModuleFrac, MaxPow >::_erase(size_t a_newBufferSize, size_t a_position, size_t a_size) {
    if (a_newBufferSize <= StaticSize || capacity() == a_newBufferSize) {
      const Ty* destroyPtr =  _pdata + a_position;
      const Ty* endDestroyPtr = _pdata + a_position + a_size;
      while(destroyPtr != endDestroyPtr) {
        destroyPtr->~Ty();
        ++destroyPtr;
      }
      _memLeftMove(&_pdata[a_position + a_size], _sdata - a_position - a_size, &_pdata[a_position]);
      _sdata -= a_size;
      _cdata = a_newBufferSize;
    } else {
      size_t bufferSize = sizeof(Ty)*a_newBufferSize;
      std::unique_ptr<char[]> uptr(new char[bufferSize]);
      Ty* newPtr                    = (Ty*)uptr.get();
      Ty* oldPtr                    = _pdata;

      size_t copyCounter = 0;
      try {
        _copyMem(newPtr, a_position, oldPtr, copyCounter);
      } catch(...){
        _destroyMem(newPtr, copyCounter);
        throw;
      }
      try {
        oldPtr += a_position + a_size;
        _copyMem(&newPtr[a_position], _sdata - a_position - a_size, oldPtr, copyCounter);
      } catch(...){
        _destroyMem(newPtr, copyCounter);
        throw;
      }
      _destroyMem(_pdata, _sdata);
      _mdata.swap(uptr);
      _sdata = copyCounter;
      _pdata = newPtr;
      _cdata = a_newBufferSize;
    }
  }

  template<typename Ty, unsigned int StaticSize, unsigned int OffsetSize, unsigned int StepSize, unsigned int StepModuleInt, unsigned int StepModuleFrac, unsigned int MaxPow >
  template <typename TIterator>
  void StaticVector<Ty, StaticSize, OffsetSize, StepSize, StepModuleInt, StepModuleFrac, MaxPow >::_insert(size_t a_newBufferSize, size_t a_position, TIterator a_iterator, size_t a_insertSize) {
    if (a_newBufferSize <= StaticSize) {
      _memRightMove((Ty*)_adata + a_position, _sdata - a_position, (Ty*)_adata + a_position + a_insertSize);
      _iteratorCopy((Ty*)_adata + a_position, a_iterator, a_insertSize, _sdata);
    } else if (capacity() == a_newBufferSize) {
      _memRightMove(&_pdata[a_position], _sdata - a_position, &_pdata[a_position + a_insertSize]);
      _iteratorCopy(&_pdata[a_position], a_iterator, a_insertSize, _sdata);
    } else {
      size_t bufferSize = sizeof(Ty)*a_newBufferSize;
      std::unique_ptr<char[]> uptr(new char[bufferSize]);
      Ty* newPtr                    = (Ty*)uptr.get();
      Ty* oldPtr                    = _pdata;

      size_t copyCounter = 0;
      try {
        _copyMem(newPtr, a_position, oldPtr, copyCounter);
      } catch(...) {
        _destroyMem(newPtr, copyCounter);
        throw;
      }
      try {
        _iteratorCopy(&newPtr[a_position], a_iterator, a_insertSize, copyCounter);
      } catch(...) {
        _destroyMem(newPtr, copyCounter);
        throw;
      }
      try {
        oldPtr += a_position;
        _copyMem(&newPtr[a_position + a_insertSize], _sdata - a_position, oldPtr, copyCounter);
      } catch(...) {
        _destroyMem(newPtr, copyCounter);
        throw;
      }
      _destroyMem(_pdata, _sdata);
      _mdata.swap(uptr);
      _sdata = copyCounter;
      _pdata = newPtr;
      _cdata = a_newBufferSize;
    }
  }

  template<typename Ty, unsigned int StaticSize, unsigned int OffsetSize, unsigned int StepSize, unsigned int StepModuleInt, unsigned int StepModuleFrac, unsigned int MaxPow >
  void StaticVector<Ty, StaticSize, OffsetSize, StepSize, StepModuleInt, StepModuleFrac, MaxPow >::_realloc(size_t a_size, size_t a_initSize) {
    if (a_size <= StaticSize) { // if the a_size fits in the internall buffer
      if ((char*)_pdata == &_adata[0]) { // if the current data is in the internal buffer
        if (_sdata > a_initSize) {
          _destroyMem(&_pdata[a_initSize], _sdata - a_initSize, _sdata);
        } else if (a_initSize > _sdata) {
          _initMem(&_pdata[_sdata], a_initSize - _sdata, _sdata);
        }
      } else {
        size_t copyCounter = 0;
        try {
          _copyMem((Ty*)&_adata[0], a_initSize, _pdata, copyCounter);
        } catch(...){
          _destroyMem((Ty*)&_adata[0], copyCounter);
          throw;
        }
        _destroyMem(_pdata, _sdata);
        _pdata = (Ty*)&_adata[0];
        _mdata.reset();
        _sdata = a_initSize;
        _cdata = StaticSize;
      }
    } else {
      if (capacity() == a_size) {
        if (_sdata > a_initSize) {
          _destroyMem(&_pdata[a_initSize], _sdata - a_initSize, _sdata);
        } else if (_sdata < a_initSize) {
          _initMem(&_pdata[_sdata], a_initSize - _sdata, _sdata);
        }
      } else {
        size_t bufferSize = sizeof(Ty)*a_size;
        std::unique_ptr<char[]> uptr(new char[bufferSize]);
        Ty* newPtr                    = (Ty*)uptr.get();
        Ty* oldPtr                    = _pdata;
        size_t oldSize                = _sdata;

        size_t copyCounter = 0;
        try {
          _copyMem(newPtr, std::min(oldSize, a_initSize), oldPtr, copyCounter);
        } catch(...){
          _destroyMem(newPtr, copyCounter);
          throw;
        }
        if (a_initSize > _sdata) {
          try {
            _initMem(&newPtr[oldSize], a_initSize - oldSize, copyCounter);
          } catch(...){
            _destroyMem(newPtr, copyCounter);
            throw;
          }
        }
        _destroyMem(_pdata, oldSize);
        _mdata.swap(uptr);
        _sdata = copyCounter;
        _pdata = newPtr;
        _cdata = a_size;
      }
    }
  }

  template<typename Ty, unsigned int StaticSize, unsigned int OffsetSize, unsigned int StepSize, unsigned int StepModuleInt, unsigned int StepModuleFrac, unsigned int MaxPow >
  size_t StaticVector<Ty, StaticSize, OffsetSize, StepSize, StepModuleInt, StepModuleFrac, MaxPow >::_getBufferSize(size_t a_size) {
    const size_t maxPow(_getMaxPow());
    size_t bufferSize;
    if (a_size <= StaticSize) {
      bufferSize = StaticSize;
    } else if (maxPow != 0 && a_size >= maxPow) {
      bufferSize = _getOwerPowSize(a_size);
    } else {
      bufferSize = _getPowSize(a_size);
      if (maxPow != 0 && bufferSize >= maxPow) {
        bufferSize = maxPow;
      }
    }
    return bufferSize;
  }

  template<typename Ty, unsigned int StaticSize, unsigned int OffsetSize, unsigned int StepSize, unsigned int StepModuleInt, unsigned int StepModuleFrac, unsigned int MaxPow >
  size_t StaticVector<Ty, StaticSize, OffsetSize, StepSize, StepModuleInt, StepModuleFrac, MaxPow >::_getPreviousSize(size_t a_size, bool a_forcePowMode) {
    const size_t maxPow(_getMaxPow());
    if (maxPow == 0 || a_size < maxPow || a_forcePowMode) {
      if (a_size >= OffsetSize) {
        a_size -= OffsetSize;
      }
      if (StepModuleFrac) {
        const long double stepMode(_getStepMode());
        return std::max((size_t)StaticSize, (size_t)((long double)(a_size > StepSize ? a_size - StepSize : 0) / stepMode) + (size_t)OffsetSize);
      } else {
        return std::max((size_t)StaticSize, (a_size > StepSize ? a_size - StepSize : 0) / (size_t)(StepModuleInt ? StepModuleInt : 1) + (size_t)OffsetSize);
      }
    } else {
      const size_t maxPowStep(_getMaxPowStep());
      size_t step = _getOwerPowStep(a_size);
      if (!step) {
        return _getPowSize(a_size - 1, 0);
      }
      return maxPow + (step - 1) * maxPowStep;
    }
  }

  template<typename Ty, unsigned int StaticSize, unsigned int OffsetSize, unsigned int StepSize, unsigned int StepModuleInt, unsigned int StepModuleFrac, unsigned int MaxPow >
  size_t StaticVector<Ty, StaticSize, OffsetSize, StepSize, StepModuleInt, StepModuleFrac, MaxPow >::_getNextSize(size_t a_size) {
    const size_t maxPow(_getMaxPow());
    if (maxPow == 0 || a_size < maxPow) {
      size_t result;
      if (a_size >= OffsetSize) {
      a_size -= OffsetSize;
      }
      if (!StepModuleFrac) {
        result = a_size * StepModuleInt + StepSize + OffsetSize;
      } else {
        const long double stepMode(_getStepMode());
        result = (size_t)((long double)a_size * stepMode + StepSize + OffsetSize);
      }
      return (maxPow == 0 || result <= maxPow) ? result : _getBufferSize(a_size+1);
    } else {
      return _getBufferSize(a_size+1);
    }
  }

  template<typename Ty, unsigned int StaticSize, unsigned int OffsetSize, unsigned int StepSize, unsigned int StepModuleInt, unsigned int StepModuleFrac, unsigned int MaxPow >
  size_t StaticVector<Ty, StaticSize, OffsetSize, StepSize, StepModuleInt, StepModuleFrac, MaxPow >::_getMaxPowImpl() {
    return MaxPow ? _getPowSize(MaxPow) : 0;
  }

  template<typename Ty, unsigned int StaticSize, unsigned int OffsetSize, unsigned int StepSize, unsigned int StepModuleInt, unsigned int StepModuleFrac, unsigned int MaxPow >
  size_t StaticVector<Ty, StaticSize, OffsetSize, StepSize, StepModuleInt, StepModuleFrac, MaxPow >::_getMaxPow() {
    static const size_t result(_getMaxPowImpl());
    return result;
  }

  template<typename Ty, unsigned int StaticSize, unsigned int OffsetSize, unsigned int StepSize, unsigned int StepModuleInt, unsigned int StepModuleFrac, unsigned int MaxPow >
  double StaticVector<Ty, StaticSize, OffsetSize, StepSize, StepModuleInt, StepModuleFrac, MaxPow >::_getStepModeImpl() {
    double pow = std::pow((double)StepModuleFrac, -std::ceil(std::log10((double)StepModuleFrac)));
    return (double)StepModuleInt + (double)StepModuleFrac * pow;
  }

  template<typename Ty, unsigned int StaticSize, unsigned int OffsetSize, unsigned int StepSize, unsigned int StepModuleInt, unsigned int StepModuleFrac, unsigned int MaxPow >
  double StaticVector<Ty, StaticSize, OffsetSize, StepSize, StepModuleInt, StepModuleFrac, MaxPow >::_getStepMode() {
    static const double result(_getStepModeImpl());
    return result;
  }

  template<typename Ty, unsigned int StaticSize, unsigned int OffsetSize, unsigned int StepSize, unsigned int StepModuleInt, unsigned int StepModuleFrac, unsigned int MaxPow >
  size_t StaticVector<Ty, StaticSize, OffsetSize, StepSize, StepModuleInt, StepModuleFrac, MaxPow >::_getMaxPowStepImpl() {
    const size_t maxPow(_getMaxPow());
    size_t curSize = _getPowSize(maxPow);
    size_t prevSize = _getPreviousSize(curSize, true);
    return curSize - prevSize;
  }

  template<typename Ty, unsigned int StaticSize, unsigned int OffsetSize, unsigned int StepSize, unsigned int StepModuleInt, unsigned int StepModuleFrac, unsigned int MaxPow >
  size_t StaticVector<Ty, StaticSize, OffsetSize, StepSize, StepModuleInt, StepModuleFrac, MaxPow >::_getMaxPowStep() {
    static const size_t result(_getMaxPowStepImpl());
    return result;
  }

  template<typename Ty, unsigned int StaticSize, unsigned int OffsetSize, unsigned int StepSize, unsigned int StepModuleInt, unsigned int StepModuleFrac, unsigned int MaxPow >
  size_t StaticVector<Ty, StaticSize, OffsetSize, StepSize, StepModuleInt, StepModuleFrac, MaxPow >::_getPowSize(size_t a_size, size_t a_powInc) {
    if (StepModuleInt == 1 && StepModuleFrac == 0) {
      if (a_size >= OffsetSize){
        a_size -= OffsetSize;
      }
      size_t step = a_size / StepSize;
      if (a_size % StepSize){
        ++step;
      }
      if (step && a_powInc == 0){
        step -= 1;
      }
      return step * StepSize + OffsetSize;
    } else {
      if (a_powInc) {
        if (_pps.is(a_size)) {
          return _pps.get(a_size);
        }
      } else  {
        if (_pps.isp(a_size)) {
          return _pps.getp(a_size);
        }
      }
      if (a_size >= OffsetSize){
        a_size -= OffsetSize;
      }
      const long double stepMode(_getStepMode());
      long double val = ( (long double)a_size * stepMode + (long double)StepSize - (long double)a_size ) / (long double)StepSize;
      long double log = std::log(val) / std::log(stepMode);
      long double pow = std::ceil(log - 1);
      long double powStepMode = std::pow(stepMode, pow + a_powInc);
      long double bufferSize = (long double)(StepSize * (powStepMode - 1) ) / (long double)(stepMode - 1);
      return (size_t)bufferSize + OffsetSize;
    }
  }

  template<typename Ty, unsigned int StaticSize, unsigned int OffsetSize, unsigned int StepSize, unsigned int StepModuleInt, unsigned int StepModuleFrac, unsigned int MaxPow >
  size_t StaticVector<Ty, StaticSize, OffsetSize, StepSize, StepModuleInt, StepModuleFrac, MaxPow >::_getOwerPowStep(size_t a_size){
    const size_t maxPow(_getMaxPow());
    const size_t maxPowStep(_getMaxPowStep());
    size_t diff = a_size - maxPow;
    size_t step = diff / maxPowStep;
    if (diff % maxPowStep) {
      ++step;
    }
    return step;
  }

  template<typename Ty, unsigned int StaticSize, unsigned int OffsetSize, unsigned int StepSize, unsigned int StepModuleInt, unsigned int StepModuleFrac, unsigned int MaxPow >
  size_t StaticVector<Ty, StaticSize, OffsetSize, StepSize, StepModuleInt, StepModuleFrac, MaxPow >::_getOwerPowSize(size_t a_size){
    const size_t maxPow(_getMaxPow());
    const size_t maxPowStep(_getMaxPowStep());
    size_t step = _getOwerPowStep(a_size);
    return maxPow + step * maxPowStep;
  }


  template<typename Ty, unsigned int StaticSize, unsigned int OffsetSize, unsigned int StepSize, unsigned int StepModuleInt, unsigned int StepModuleFrac, unsigned int MaxPow>
  typename StaticVector<Ty, StaticSize, OffsetSize, StepSize, StepModuleInt, StepModuleFrac, MaxPow>::PrebuildPowSizes StaticVector<Ty, StaticSize, OffsetSize, StepSize, StepModuleInt, StepModuleFrac, MaxPow>::_pps;

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_STATIC_VECTOR__STATIC_VECTOR_HPP___
