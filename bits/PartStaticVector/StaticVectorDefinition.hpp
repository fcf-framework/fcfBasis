#ifndef ___FCF_BASIS__BITS__PART_STATIC_VECTOR__STATIC_VECTOR_DEFINITION_HPP___
#define ___FCF_BASIS__BITS__PART_STATIC_VECTOR__STATIC_VECTOR_DEFINITION_HPP___

#include <memory>
#include <cmath>
#include "../../bits/PartContainerAccess/ContainerAccessDefinition.hpp"

namespace FcfTest {
  namespace BasisTest {

    void staticVectorTest();
    void staticVectorPushTest();

  } // BasisTest namespace
} // FcfTest namespace

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

  ///
  /// @class StaticVector<typename Ty, unsigned int StaticSize=16, unsigned int OffsetSize=2, unsigned int StepSize=2, unsigned int StepModuleInt=2, unsigned int StepModuleFrac=0, unsigned int MaxPow=2*4096/sizeof(Ty)>
  /// @brief A class that stores data in internal data fields and, if necessary, allocates memory from the heap when there is insufficient memory
  /// @detail Data storage algorithm
  ///           - If the buffer size (StaticSize) is sufficient to store the data, then the data is stored in internal fields.
  ///             BufferSizeFunction()=StaticVector::capacity() == StaticSize
  ///           - If the internal buffer size is not sufficient, the data will be stored on the heap.
  ///           The buffer size is determined by the closest value of the following formula \n
  ///             StaticVector::capacity() == OffsetSize + SUM(from{0}, to{n}, StepSize * StepModule^{n})\n
  ///             That is, for n==3:\n
  ///               StaticVector::capacity() == OffsetSize + StepSize + StepSize*StepModule + StepSize*StepModule^2 + StepSize*StepModule^3\n
  ///           - If the MaxPow parameter is not equal to 0, then if the buffer size is greater than the MaxPow value, then the calculation
  ///           of subsequent values ​​of the buffer size is performed by adding the difference between the previous (n-1)
  ///           and the previous (n-2) buffer size.
  ///
  ///         Description of template parameters
  ///           - typename Ty - Type of stored elements
  ///           - unsigned int StaticSize - Maximum number of elements stored in the internal buffer
  ///           - unsigned int OffsetSize - The offset size used in the calculation function
  ///           - unsigned int StepSize - The step size used in the calculation function
  ///           - unsigned int StepModuleInt - The integer part of the StepModule parameter used in the calculation function
  ///           - unsigned int StepModuleFrac - Fractional part of the StepModule parameter number used in the calculation function
  ///           - unsigned int MaxPow - The limit value after which the buffer size calculation goes into linear form and a simple increment is performed.
  ///                                   If the value is 0, but this functionality is not used
  ///
  template<typename Ty, unsigned int StaticSize, unsigned int OffsetSize, unsigned int StepSize, unsigned int StepModuleInt, unsigned int StepModuleFrac, unsigned int MaxPow >
  class StaticVector {
    friend void ::FcfTest::BasisTest::staticVectorTest();
    friend void ::FcfTest::BasisTest::staticVectorPushTest();

    public:
      typedef StaticVector                                             self_type;
      typedef Ty                                                       value_type;
      typedef size_t                                                   size_type;
      typedef ContainerAccess<self_type>                               iterator;
      typedef ContainerAccess<const self_type>                         const_iterator;

      enum {
        static_capacity_value = StaticSize
      };

      StaticVector();

      ~StaticVector();

      StaticVector(size_t a_size);

      StaticVector(const StaticVector& a_source);

      StaticVector(std::initializer_list<Ty> a_list);

      StaticVector(const Ty* a_begin, size_t a_size);

      StaticVector(size_t a_size, const Ty& a_fill);

      StaticVector& operator=(const StaticVector& a_source);

      iterator begin();

      const_iterator begin() const;

      const_iterator cbegin() const;

      iterator end();

      const_iterator end() const;

      const_iterator cend() const;

      Ty& operator[](size_t a_index);

      const Ty& operator[](size_t a_index) const;

      size_t size() const;

      size_t capacity() const;

      bool empty() const;

      void clear(bool a_notReduce = false);

      Ty& back();

      const Ty& back() const;

      Ty& front();

      const Ty& front() const;

      void push_back(const Ty& a_value);

      void pop_back(bool a_notReduce = false);

      void reserve(size_t a_size);

      void resize(size_t a_size, bool a_notReduce = false);

      iterator insert(iterator a_iterator, const Ty& a_value);

      template <typename TInsertIterator>
      iterator insert(iterator a_iterator, TInsertIterator a_begin, TInsertIterator a_end);

      iterator erase(iterator a_iterator, bool a_notReduce = false);

      iterator erase(iterator a_begin, iterator a_end, bool a_notReduce = false);

    protected:
      struct PrebuildPowSizes {
        PrebuildPowSizes() {
          size_t lastValue = StaticSize + 1;
          size_t m = 0;
          for(size_t i = 0; i < sizeof(values) / sizeof(values[0]); ++i){
            m = _getPowSize(lastValue);
            values[i] = m;
            lastValue = m + 1;
          }
          max = m;
        }

        bool isp(size_t a_size){
          return max >= a_size;
        }

        bool is(size_t a_size){
          return max >= a_size;
        }

        size_t get(size_t a_size) {
          for(size_t i = 0; i < sizeof(values) / sizeof(values[0]); ++i){
            if (values[i] >= a_size) {
              return values[i];
            }
          }
          return _getPowSize(a_size);
        }

        size_t getp(size_t a_size) {
          size_t last = StaticSize;
          for(size_t i = 0; i < sizeof(values) / sizeof(values[0]); ++i){
            if (values[i] >= a_size) {
              return last;
            }
            last = values[i];
          }
          return _getPowSize(a_size, 0);
        }

        size_t max;
        size_t values[10];
      };

      static void _initMem(Ty* a_mem, size_t a_size, size_t& a_sdata);

      static void _destroyMem(Ty* a_mem, size_t a_size, size_t& a_sdata);

      static void _destroyMem(Ty* a_mem, size_t a_size);

      template <typename TContainer>
      static void _copyMem(Ty* a_mem, size_t a_size, TContainer& a_container, size_t& a_sdata);

      template <typename TIterator>
      static void _iteratorCopy(Ty* a_mem, TIterator& a_iterator, size_t a_size, size_t& a_sdata);

      static void _memRightMove(Ty* a_mem, size_t a_memSize, Ty* a_destMem);

      static void _memLeftMove(Ty* a_mem, size_t a_memSize, Ty* a_destMem);

      void _forceRealloc(size_t a_size);

      void _erase(size_t a_newBufferSize, size_t a_position, size_t a_size);

      template <typename TIterator>
      void _insert(size_t a_newBufferSize, size_t a_position, TIterator a_iterator, size_t a_insertSize);

      void _realloc(size_t a_size, size_t a_initSize);

      static size_t _getBufferSize(size_t a_size);

      static size_t _getPreviousSize(size_t a_size, bool a_forcePowMode = false);

      static size_t _getNextSize(size_t a_size);

      static size_t _getMaxPowImpl();

      static size_t _getMaxPow();

      static double _getStepModeImpl();

      static double _getStepMode();

      static size_t _getMaxPowStepImpl();

      static size_t _getMaxPowStep();

      static size_t _getPowSize(size_t a_size, size_t a_powInc = 1);

      static size_t _getOwerPowStep(size_t a_size);

      static size_t _getOwerPowSize(size_t a_size);

      char                    _adata[StaticSize * sizeof(Ty)];
      Ty*                     _pdata;
      std::unique_ptr<char[]> _mdata;
      size_t                  _sdata;
      size_t                  _cdata;
      static PrebuildPowSizes _pps;
  };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_STATIC_VECTOR__STATIC_VECTOR_DEFINITION_HPP___
