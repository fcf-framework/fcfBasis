#ifndef ___FCF_BASIS__TEST__SHARED__HEADER_HPP___
#define ___FCF_BASIS__TEST__SHARED__HEADER_HPP___


struct Storage {
  int inc(){
    static int counter = 0;
    return ++counter;
  }
};


#endif // #ifndef ___FCF_BASIS__TEST__SHARED__HEADER_HPP___
