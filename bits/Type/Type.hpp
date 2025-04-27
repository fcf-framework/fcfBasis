#ifndef ___FCF__BASIS__BITS__TYPE__TYPE_HPP___
#define ___FCF__BASIS__BITS__TYPE__TYPE_HPP___

#include <list>
#include <set>
#include <vector>
#include "../../Nop.hpp"
#include "../Specificator/specificators.hpp"
#include "../BaseType.hpp"
#include "../BaseContainerType.hpp"

namespace fcf {

  template <typename Ty, typename TInfoMode = Nop>
  struct Type : public BaseType<Ty> {
    enum { container = false };

    typedef Ty data_type;
  };

  template <>
  struct Type<void> : public BaseType<void> {
    enum { container = false };

    typedef void data_type;
  };

  template <typename Ty>
  struct Type< Ty* > : public BaseContainerType< Ty*, true > {

    typedef Ty* owner_type;

    typedef typename Type<Ty>::data_type data_type;

    typedef Ty value_type;

  };


  template <typename Ty>
  struct Type< Ty** > : public BaseContainerType< Ty**, true > {

    typedef Ty** owner_type;

    typedef typename Type<Ty>::data_type data_type;

    typedef Ty* value_type;
  };


  template <typename Ty>
  struct Type< std::vector<Ty> > : public BaseContainerType< std::vector<Ty>, true > {

    typedef std::vector<Ty> owner_type;

    typedef typename Type<Ty>::data_type data_type;

    typedef Ty value_type;

  };


  template <typename Ty, size_t Size>
  struct Type< Ty[Size] > : public BaseContainerType< Ty[Size], true > {

    typedef Ty owner_type[Size];

    typedef typename Type<Ty>::data_type data_type;

    typedef Ty value_type;
  };

  template <typename Ty>
  struct Type< std::list<Ty> > : public BaseContainerType< std::list<Ty>, false > {

    typedef std::list<Ty> owner_type;

    typedef typename Type<Ty>::data_type data_type;

    typedef Ty value_type;
  };

  template <typename Ty>
  struct Type< std::set<Ty> > : public BaseContainerType< std::set<Ty>, false > {

    typedef std::set<Ty> owner_type;

    typedef typename Type<Ty>::data_type data_type;

    typedef Ty value_type;
  };

} // fcf namespace

namespace fcf {

  template <typename Ty>
  struct Type<Ty, IteratorContainerSpecificator> {
    auto begin(Ty a_iterator) -> decltype(std::begin(*a_iterator)){
      return std::begin(*a_iterator);
    }
    auto end(Ty a_iterator) -> decltype(std::end(*a_iterator)) {
      return std::end(*a_iterator);
    }
  };

  template <typename Ty>
  struct Type<Ty, IteratorSpecificator> {
    typedef typename Ty::value_type value_type;
  };

  template <typename Ty>
  struct Type<Ty*, IteratorSpecificator> {
    typedef Ty value_type;
  };

  template <typename Ty>
  struct Type<Ty, ValueSpecificator> {
    enum { enable = false };
  };

  template <typename Ty>
  struct Type<Ty, RawDataSpecificator> {
    enum { enable = false };
    void* operator()(const void* a_value = 0, unsigned int* a_type = 0, bool* a_invariantType = 0, bool* a_mayBeUnintialized = 0){
      if (a_type){
        *a_type = 0;
      }
      if (a_invariantType){
        *a_invariantType = 0;
      }
      if (a_mayBeUnintialized){
        *a_mayBeUnintialized = 0;
      }
      return 0;
    }
  };

  template <typename Ty>
  struct Type<Ty, MinMaxSpecificator> {
    enum { enable = false };
  };

  template <typename Ty>
  struct Type<Ty, MemoryTypeSpecificator> {
    typedef Ty type;
  };

  template <>
  struct Type<const char*, MemoryTypeSpecificator> {
    typedef std::string type;
  };

  template <>
  struct Type<char*, MemoryTypeSpecificator> {
    typedef std::string type;
  };

  template <size_t Size>
  struct Type<char[Size], MemoryTypeSpecificator> {
    typedef std::string type;
  };

  template <size_t Size>
  struct Type<const char[Size], MemoryTypeSpecificator> {
    typedef std::string type;
  };

} // fcf namespace

#endif // #ifndef ___FCF__BASIS__BITS__TYPE__TYPE_HPP___
