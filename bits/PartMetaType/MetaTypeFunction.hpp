#ifndef ___FCF_BASIS__BITS__PART_META_TYPE__META_TYPE_FUNCTION_HPP___
#define ___FCF_BASIS__BITS__PART_META_TYPE__META_TYPE_FUNCTION_HPP___

namespace fcf{

  template <typename Ty>
  struct MetaTypeFunction;

  template <typename TResult, typename ...TPack>
  struct MetaTypeFunction<TResult(*)(TPack...)>{
    enum { argCount = sizeof...(TPack) };
    typedef TResult(*Type)(TPack...);
    typedef TResult               ResultType;
    typedef std::tuple<TPack...>  ArgumentsType;
    typedef TResult(*FunctionType)(TPack...);
  };

  template <typename TResult, typename ...TPack>
  struct MetaTypeFunction<TResult(TPack...)>{
    enum { argCount = sizeof...(TPack) };
    typedef TResult(*Type)(TPack...);
    typedef TResult               ResultType;
    typedef std::tuple<TPack...>  ArgumentsType;
    typedef TResult(*FunctionType)(TPack...);
  };

  template <typename TResult, typename TClass, typename ...TPack>
  struct MetaTypeFunction<TResult(TClass::*)(TPack...)>{
    enum { argCount = sizeof...(TPack) };
    typedef TResult(TClass::*Type)(TPack...);
    typedef TResult                         ResultType;
    typedef std::tuple<TPack...>            ArgumentsType;
    typedef TResult(*FunctionType)(TPack...);
    typedef TResult(TClass::*MethodType)(TPack...);
  };

  template <typename TResult, typename TClass, typename ...TPack>
  struct MetaTypeFunction<TResult(TClass::*)(TPack...) const>{
    enum { argCount = sizeof...(TPack) };
    typedef TResult(TClass::*Type)(TPack...);
    typedef TResult                         ResultType;
    typedef std::tuple<TPack...>            ArgumentsType;
    typedef TResult(*FunctionType)(TPack...);
    typedef TResult(TClass::*MethodType)(TPack...);
  };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_META_TYPE__META_TYPE_FUNCTION_HPP___
