#ifndef ___FCF__BASIS__BITS__PART_CONTAINER_ACCESS__CONTAINER_ACCESS_INFO_HPP___
#define ___FCF__BASIS__BITS__PART_CONTAINER_ACCESS__CONTAINER_ACCESS_INFO_HPP___

namespace fcf {

  template <typename TContainer>
  class ContainerAccessInfo;

  template <typename TContainer>
  class ContainerAccessInfo<const TContainer>: public ContainerAccessInfo<TContainer>{
  };

} // fcf namespace

#endif // #ifndef ___FCF__BASIS__BITS__PART_CONTAINER_ACCESS__CONTAINER_ACCESS_INFO_HPP___

