#ifndef ___FCF_BASIS__TYPE_HPP___
#define ___FCF_BASIS__TYPE_HPP___

#include <list>
#include <set>
#include <vector>
#include "Nop.hpp"
#include "specificators.hpp"
#include "./bits/BaseType.hpp"
#include "./bits/BaseContainerType.hpp"

namespace fcf {

  template <typename Ty, typename TInfoMode = Nop>
  struct Type : public BaseType<Ty> {
    enum { container = false };

    typedef Ty data_type;
  };


  template <typename Ty>
  struct Type<Ty, IterativeSpecificator> {
    typedef typename Ty::value_type value_type;
  };

  template <typename Ty>
  struct Type<Ty*, IterativeSpecificator> {
    typedef Ty value_type;
  };

  template <typename Ty>
  struct Type<Ty, ValueSpecificator> {
    enum { enable = false };
  };


  template <typename Ty>
  struct Type< Ty* > : public BaseContainerType< Ty* > {

    typedef Ty* owner_type;

    typedef typename Type<Ty>::data_type data_type;

    typedef Ty value_type;

  };


  template <typename Ty>
  struct Type< Ty** > : public BaseContainerType< Ty** > {

    typedef Ty** owner_type;

    typedef typename Type<Ty>::data_type data_type;

    typedef Ty* value_type;
  };


  template <typename Ty>
  struct Type< std::vector<Ty> > : public BaseContainerType< std::vector<Ty> > {

    typedef std::vector<Ty> owner_type;

    typedef typename Type<Ty>::data_type data_type;

    typedef Ty value_type;

  };


  template <typename Ty, size_t Size>
  struct Type< Ty[Size] > : public BaseContainerType< Ty[Size] > {

    typedef Ty owner_type[Size];

    typedef typename Type<Ty>::data_type data_type;

    typedef Ty value_type;
  };

  template <typename Ty>
  struct Type< std::list<Ty> > : public BaseContainerType< std::list<Ty> > {

    typedef std::list<Ty> owner_type;

    typedef typename Type<Ty>::data_type data_type;

    typedef Ty value_type;
  };

  template <typename Ty>
  struct Type< std::set<Ty> > : public BaseContainerType< std::set<Ty> > {

    typedef std::set<Ty> owner_type;

    typedef typename Type<Ty>::data_type data_type;

    typedef Ty value_type;
  };

} // fcf namespace

#include "bits/registry.hpp"

#endif // #ifndef ___FCF_BASIS__TYPE_HPP___
