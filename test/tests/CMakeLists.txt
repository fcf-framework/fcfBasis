set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable("basis-test" impl.cpp
                           main.cpp
                           index/deepIndexCallInner.cpp
                           index/deepIndexCallCaller.cpp
                           index/deepIndexCall.cpp
                           index/deepIndexSimpleCall.cpp
                           index/types.cpp
                           variant/variant.cpp
                           iterator/iterator.cpp
                           iterator/dynamicIterator.cpp
                           StaticVector/StaticVector.cpp
                           StaticVector/StaticVectorCopy.cpp
                           StaticVector/StaticVectorException.cpp
                           StaticVector/StaticVectorIterator.cpp
                           StaticVector/StaticVectorPush.cpp
                           StaticVector/StaticVectorNotReduce.cpp
                         )

