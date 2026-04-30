#ifndef ___FCF_BASIS__TEST__SHARED__HEADER_HPP___
#define ___FCF_BASIS__TEST__SHARED__HEADER_HPP___

#ifdef _WIN32
  #ifdef basis_shared_library_EXPORTS
    #define MY_API __declspec(dllexport)
  #else
    #define MY_API __declspec(dllimport)
  #endif
#else
  #define MY_API
#endif

MY_API int incCounter();

struct MY_API Storage {
  int inc(){
    static int counter = 0;
    return ++counter;
  }
};


#endif // #ifndef ___FCF_BASIS__TEST__SHARED__HEADER_HPP___
