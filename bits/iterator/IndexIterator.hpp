#ifndef ___FCF_BASIS__BITS__ITERATOR__INDEX_ITERATOR_HPP___
#define ___FCF_BASIS__BITS__ITERATOR__INDEX_ITERATOR_HPP___

namespace fcf {

  template <typename TRefContainer, typename TRefItem>
  class IndexIterator {
      IndexIterator();
    public:
      typedef typename std::remove_reference<TRefItem>::type* ptr_type;
      typedef TRefItem ref_type;

      inline IndexIterator(TRefContainer a_container, size_t a_index)
        : _c(a_container)
        , _i(a_index) {
      }

      inline bool operator!=(const IndexIterator& a_source) const {
        return _i != a_source._i;
      }

      inline bool operator==(const IndexIterator& a_source) const {
        return _i == a_source._i;
      }

      inline bool operator<(const IndexIterator& a_source) const {
        return _i < a_source._i;
      }

      inline bool operator<=(const IndexIterator& a_source) const {
        return _i <= a_source._i;
      }

      inline bool operator>(const IndexIterator& a_source) const {
        return _i > a_source._i;
      }

      inline bool operator>=(const IndexIterator& a_source) const {
        return _i >= a_source._i;
      }

      inline IndexIterator& operator++() {
        ++_i;
        return *this;
      }

      inline IndexIterator operator++(int) {
        IndexIterator it(*this);
        ++_i;
        return it;
      }

      inline IndexIterator& operator--() {
        --_i;
        return *this;
      }

      inline IndexIterator operator--(int) {
        IndexIterator it(*this);
        --_i;
        return it;
      }

      inline ref_type operator*() {
        return _c[_i];
      }

      inline ptr_type operator->() {
        return &_c[_i];
      }

      inline IndexIterator operator+(size_t a_diff) {
        IndexIterator it(*this);
        it._i += a_diff;
        return it;
      }

      inline IndexIterator operator-(size_t a_diff) {
        IndexIterator it(*this);
        it._i -= a_diff;
        return it;
      }

    protected:
      TRefContainer _c;
      size_t        _i;
  };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__ITERATOR__INDEX_ITERATOR_HPP___

