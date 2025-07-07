#ifndef ___FCF_BASIS__BITS__STATIC_VECTOR__STATIC_VECTOR_HPP___
#define ___FCF_BASIS__BITS__STATIC_VECTOR__STATIC_VECTOR_HPP___

#include <memory>
#include <cmath>
#include "../../bits/iterator/IndexIterator.hpp"

void staticVectorTest();
void staticVectorPushTest();

namespace fcf {

  ///
  /// @class StaticVector<typename Ty, unsigned int StaticSize=1, unsigned int StepSize=1, unsigned int StepModuleInt=1, unsigned int StepModuleFrac=0, unsigned int MaxPow=0>
  /// @brief A class that stores data in internal data fields and, if necessary, allocates memory from the heap when there is insufficient memory
  /// @detail Data storage algorithm
  ///           - If the buffer size (StaticSize) is sufficient to store the data, then the data is stored in internal fields.
  ///             BufferSizeFunction()=StaticVector::capacity() == StaticSize
  ///           - If the internal buffer size is not sufficient, the data will be stored on the heap.
  ///           The buffer size is determined by the closest value of the following formula \n
  ///             StaticVector::capacity() == SUM(from{0}, to{n}, StepSize * StepModule^{n})\n
  ///             That is, for n==3:\n
  ///               StaticVector::capacity() == StepSize + StepSize*StepModule + StepSize*StepModule^2 + StepSize*StepModule^3\n
  ///           - If the MaxPow parameter is not equal to 0, then if the buffer size is greater than the MaxPow value, then the calculation
  ///           of subsequent values ​​of the buffer size is performed by adding the difference between the previous (n-1)
  ///           and the previous (n-2) buffer size.
  ///
  ///         Description of template parameters
  ///           - typename Ty - Type of stored elements
  ///           - unsigned int StaticSize - Maximum number of elements stored in the internal buffer
  ///           - unsigned int StepSize - The step size used in the calculation function
  ///           - unsigned int StepModuleInt - The integer part of the StepModule parameter used in the calculation function
  ///           - unsigned int StepModuleFrac - Fractional part of the StepModule parameter number used in the calculation function
  ///           - unsigned int MaxPow - The limit value after which the buffer size calculation goes into linear form and a simple increment is performed.
  ///                                   If the value is 0, but this functionality is not used
  ///
  template<typename Ty, unsigned int StaticSize=1, unsigned int StepSize=1, unsigned int StepModuleInt=1, unsigned int StepModuleFrac=0, unsigned int MaxPow=0>
  class StaticVector {
    friend void ::staticVectorTest();
    friend void ::staticVectorPushTest();

    public:
      typedef IndexIterator<StaticVector&, Ty&>             iterator;
      typedef IndexIterator<const StaticVector&, const Ty&> const_iterator;

      StaticVector()
        : _pdata((Ty*)&_adata[0])
        , _sdata(0) {
      }

      ~StaticVector() {
        if ((char*)_pdata == &_adata[0]) { // if the current data is in the internal buffer
          _destroyMem(_pdata, _sdata);
        }
      }

      StaticVector(size_t a_size)
        : _pdata((Ty*)&_adata[0])
        , _sdata(0) {
        _realloc(_getBufferSize(a_size), a_size);
      }

      StaticVector(const StaticVector& a_source)
        : _pdata((Ty*)&_adata[0])
        , _sdata(0) {
        _forceRealloc(_getBufferSize(a_source.size()));
        _copyMem(_pdata, a_source.size(), a_source, _sdata);
      }

      StaticVector(std::initializer_list<Ty> a_list)
        : _pdata((Ty*)&_adata[0])
        , _sdata(0) {
        _forceRealloc(_getBufferSize(a_list.size()));
        for(auto it = a_list.begin(); it != a_list.end(); ++it){
          new (&_pdata[_sdata]) Ty(*it);
          ++_sdata;
        }
      }

      StaticVector(size_t a_size, const Ty& a_fill)
        : _pdata((Ty*)&_adata[0])
        , _sdata(0) {
        _forceRealloc(_getBufferSize(a_size));
        for(; _sdata < a_size; ++_sdata){
          new (&_pdata[_sdata]) Ty(a_fill);
        }
      }

      StaticVector& operator=(const StaticVector& a_source){
        _forceRealloc(_getBufferSize(a_source.size()));
        _copyMem(_pdata, a_source.size(), a_source, _sdata);
        return *this;
      }

      iterator begin(){
        return iterator(*this, 0);
      }

      const_iterator cbegin() const{
        return const_iterator(*this, 0);
      }

      iterator end(){
        return iterator(*this, _sdata);
      }

      const_iterator cend() const{
        return const_iterator(*this, _sdata);
      }

      Ty& operator[](size_t a_index){
        return _pdata[a_index];
      }

      const Ty& operator[](size_t a_index) const{
        return _pdata[a_index];
      }

      size_t size() const{
        return _sdata;
      }

      size_t capacity(){
        return _pdata == (Ty*)&_adata[0] ? StaticSize : *(size_t*)_mdata.get();
      }

      bool empty() const{
        return !_sdata;
      }

      void clear(){
        _realloc(0);
      }

      void push_back(const Ty& a_value){
        if (capacity() < _sdata + 1){
          _realloc(_getNextSize(capacity()), _sdata);
        }
        new (&_pdata[_sdata]) Ty(a_value);
        ++_sdata;
      }

      void pop_back(){
        size_t prev = _getPreviousSize(capacity());
        if (prev >= _sdata - 1){
          _realloc(prev, _sdata-1);
        } else {
          --_sdata;
          _pdata[_sdata-1].~Ty();
        }
      }

      void resize(size_t a_size) {
        _realloc(_getBufferSize(a_size), a_size);
      }

    protected:
      static void _initMem(Ty* a_mem, size_t a_size, size_t& a_sdata) {
        for(size_t i = 0; i < a_size; ++i) {
          new (&a_mem[i]) Ty();
          ++a_sdata;
        }
      }

      static void _destroyMem(Ty* a_mem, size_t a_size, size_t& a_sdata) {
        while (a_size) {
          --a_sdata;
          --a_size;
          a_mem[a_size].~Ty();
        }
      }

      static void _destroyMem(Ty* a_mem, size_t a_size) {
        while (a_size) {
          --a_size;
          a_mem[a_size].~Ty();
        }
      }

      template <typename TContainer>
      static void _copyMem(Ty* a_mem, size_t a_size, TContainer& a_container, size_t& a_sdata) {
        for(size_t i = 0; i < a_size; ++i) {
          new (&a_mem[i]) Ty(a_container[i]);
          ++a_sdata;
        }
      }


      void _forceRealloc(size_t a_size){
        const size_t oldCapacity = capacity();
        if ((char*)_pdata == &_adata[0]) { // if the current data is in the internal buffer
          _destroyMem(&_pdata[0], _sdata);
        } else if (oldCapacity != a_size){
          _mdata.reset();
        } else {
          _destroyMem(&_pdata[0], _sdata);
        }

        _sdata = 0;

        if (a_size <= StaticSize) {
          _pdata = (Ty*)&_adata[0];
        } else if (oldCapacity != a_size){
            //                    buffer size  |     data
            size_t bufferSize = sizeof(size_t) + sizeof(Ty)*a_size;
            std::shared_ptr<char> sptr(
                                      new char[bufferSize],
                                      [this](char* a_mem) {
                                        _releaseSharedBuffer(a_mem, this);
                                      }
                                    );
            *(size_t*)sptr.get() = a_size;
            Ty* newBuffer = (Ty*)((size_t*)sptr.get() + 1);
            _mdata = sptr;
            _pdata = newBuffer;
        }
      }

      void _realloc(size_t a_size, size_t a_initSize) {
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
            _pdata = (Ty*)&_adata[0];
            _mdata.reset();
            _sdata = a_initSize;
          }
        } else {
          if (capacity() == a_size) {
            if (_sdata > a_initSize) {
              _destroyMem(&_pdata[a_initSize], _sdata - a_initSize, _sdata);
            } else if (_sdata < a_initSize) {
              _initMem(&_pdata[_sdata], a_initSize - _sdata, _sdata);
            }
          } else {
            //                    buffer size  |     data
            size_t bufferSize = sizeof(size_t) + sizeof(Ty)*a_size;
            std::shared_ptr<char> sptr(
                                      new char[bufferSize],
                                      [this](char* a_mem) {
                                        _releaseSharedBuffer(a_mem, this);
                                      }
                                    );
            *(size_t*)sptr.get() = a_size;
            Ty* newPtr                    = (Ty*)((size_t*)sptr.get() + 1);
            Ty* oldPtr                    = _pdata;
            size_t oldSize                = _sdata;

            size_t copyCounter = 0;
            try {
              _copyMem(newPtr, std::min(oldSize, a_initSize), oldPtr, copyCounter);
            } catch(...){
              _sdata = copyCounter;
              sptr.reset();
              _sdata = oldSize;
              throw;
            }
            if (a_initSize > _sdata) {
              try {
                _initMem(&newPtr[oldSize], a_initSize - oldSize, copyCounter);
              } catch(...){
                _sdata = copyCounter;
                sptr.reset();
                _sdata = oldSize;
                throw;
              }
            }
            _mdata = sptr;
            _sdata = copyCounter;
            _pdata = newPtr;

            if (oldPtr == (Ty*)&_adata[0]) { // if the current data is in the internal buffer
              _destroyMem(oldPtr, oldSize);
            }
          }
        }
      }

      static void _releaseSharedBuffer(char* a_mem, StaticVector* a_pthis){
        Ty* ptr = (Ty*)((size_t*)a_mem + 1);
        _destroyMem(ptr, a_pthis->_sdata);
        delete [] a_mem;
      }

      static size_t _getBufferSize(size_t a_size) {
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

      static size_t _getPreviousSize(size_t a_size, bool a_forcePowMode = false) {
        const size_t maxPow(_getMaxPow());
        if (maxPow == 0 || a_size < maxPow || a_forcePowMode) {
          if (StepModuleFrac) {
            const long double stepMode(_getStepMode());
            return std::max((size_t)StaticSize, (size_t)((long double)(a_size > StepSize ? a_size - StepSize : 0) / stepMode));
          } else {
            return std::max((size_t)StaticSize, (a_size > StepSize ? a_size - StepSize : 0) / (size_t)StepModuleInt);
          }
        } else {
          const size_t maxPowStep(_getMaxPowStep());
          size_t step = _getOwerPowStep(a_size);
          if (!step) {
            return _getPowSize(a_size-1, 0);
          }
          return maxPow + (step - 1) * maxPowStep;
        }
      }

      static size_t _getNextSize(size_t a_size) {
        const size_t maxPow(_getMaxPow());
        if (maxPow == 0 || a_size < maxPow) {
          size_t result;
          if (!StepModuleFrac) {
            result = a_size * StepModuleInt + StepSize;
          } else {
            const long double stepMode(_getStepMode());
            result = (long double)a_size * stepMode + StepSize;
          }
          return (maxPow == 0 || result <= maxPow) ? result : _getBufferSize(a_size+1);
        } else {
          return _getBufferSize(a_size+1);
        }
      }

      static size_t _getMaxPowImpl() {
        return MaxPow ? _getPowSize(MaxPow) : 0;
      }

      static size_t _getMaxPow() {
        static const size_t result(_getMaxPowImpl());
        return result;
      }

      static double _getStepModeImpl() {
        double pow = std::pow((double)StepModuleFrac, -std::ceil(std::log10((double)StepModuleFrac)));
        return (double)StepModuleInt + (double)StepModuleFrac * pow;
      }

      static double _getStepMode() {
        static const size_t result(_getStepModeImpl());
        return result;
      }

      static size_t _getMaxPowStepImpl() {
        const size_t maxPow(_getMaxPow());
        size_t curSize = _getPowSize(maxPow);
        size_t prevSize = _getPreviousSize(curSize, true);
        return curSize - prevSize;
      }

      static size_t _getMaxPowStep() {
        static const size_t result(_getMaxPowStepImpl());
        return result;
      }

      static size_t _getPowSize(size_t a_size, size_t a_powInc = 1) {
        if (StepModuleInt == 1 && StepModuleFrac == 0) {
          size_t step = a_size / StepSize;
          if (a_size % StepSize){
            ++step;
          }
          if (step && a_powInc == 0){
            step -= 1;
          }
          return step * StepSize;
        } else {
          const long double stepMode(_getStepMode());
          long double val = ( (long double)a_size * stepMode + (long double)StepSize - (long double)a_size ) / (long double)StepSize;
          long double log = std::log(val) / std::log(stepMode);
          long double pow = std::ceil(log - 1);
          long double powStepMode = std::pow(stepMode, pow + a_powInc);
          long double bufferSize = (long double)(StepSize * (powStepMode - 1) ) / (long double)(stepMode - 1);
          return (size_t)bufferSize;
        }
      }

      static size_t _getOwerPowStep(size_t a_size){
        const size_t maxPow(_getMaxPow());
        const size_t maxPowStep(_getMaxPowStep());
        size_t diff = a_size - maxPow;
        size_t step = diff / maxPowStep;
        if (diff % maxPowStep) {
          ++step;
        }
        return step;
      }

      static size_t _getOwerPowSize(size_t a_size){
        const size_t maxPow(_getMaxPow());
        const size_t maxPowStep(_getMaxPowStep());
        size_t step = _getOwerPowStep(a_size);
        return maxPow + step * maxPowStep;
      }

      char                  _adata[StaticSize * sizeof(Ty)];
      Ty*                   _pdata;
      std::shared_ptr<char> _mdata;
      size_t                _sdata;
  };

} // fcf namespace


#endif // #ifndef ___FCF_BASIS__BITS__STATIC_VECTOR__STATIC_VECTOR_HPP___
