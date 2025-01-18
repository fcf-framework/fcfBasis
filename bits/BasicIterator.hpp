#ifndef ___FCF_BASIS__BITS__BASIC_ITERATOR_HPP___
#define ___FCF_BASIS__BITS__BASIC_ITERATOR_HPP___

namespace fcf {
    template <typename TBaseIterator>
    class BasicIterator : public TBaseIterator {
      public:
        using TBaseIterator::TBaseIterator;
        typename TBaseIterator::value_type& operator*(){
          return *TBaseIterator::operator->();
        }
        bool operator!=(const BasicIterator& a_it) const{
          return !TBaseIterator::operator==(a_it);
        }
        BasicIterator& operator++(){
          return (BasicIterator&)TBaseIterator::operator++();
        }
        BasicIterator operator++(int){
          BasicIterator it(*this);
          TBaseIterator::operator++();
          return it;
        }
    };
} // fcf namespace

#endif // #ifndef ___FCF_MATH__BITS__BASIC_ITERATOR_HPP___
