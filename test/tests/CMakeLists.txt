set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable("basis-test" impl.cpp
                           main.cpp
                           Template/Sequence.cpp
                           index/deepIndexCallInner.cpp
                           index/deepIndexCallCaller.cpp
                           index/deepIndexCall.cpp
                           index/deepIndexSimpleCall.cpp
                           index/types.cpp
                           call/placeHolderCall.cpp
                           call/declareCall.cpp
                           variant/variant.cpp
                           iterator/iterator.cpp
                           iterator/dynamicIterator.cpp
                           StaticVector/StaticVector.cpp
                           StaticVector/StaticVectorCopy.cpp
                           StaticVector/StaticVectorException.cpp
                           StaticVector/StaticVectorIterator.cpp
                           StaticVector/StaticVectorInsert.cpp
                           StaticVector/StaticVectorPush.cpp
                           StaticVector/StaticVectorNotReduce.cpp
                         )

