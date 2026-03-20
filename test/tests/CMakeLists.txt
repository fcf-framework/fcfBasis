set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable("basis-test"
                           impl.cpp
                           main.cpp
                           PartStaticVector/StaticVector.cpp
                           PartStaticVector/StaticVectorCopy.cpp
                           PartStaticVector/StaticVectorErase.cpp
                           PartStaticVector/StaticVectorException.cpp
                           PartStaticVector/StaticVectorIterator.cpp
                           PartStaticVector/StaticVectorInsert.cpp
                           PartStaticVector/StaticVectorNotReduce.cpp
                           PartStaticVector/StaticVectorPush.cpp
                           PartCall/Call.cpp
                           PartCall/CallSpeed.cpp
                           PartCall/CallDeclare.cpp
                           PartCall/CallInvariantArguments.cpp
                           PartCall/CallPlaceHolder.cpp
                           PartCall/CallQuietOptions.cpp
                           PartCall/CallResult.cpp
                           PartCall/CallSpeed.cpp
                           PartCall/CallWithIterations.cpp
                           PartCall/CallZeroIterations.cpp
                           PartContainerAccess/ContainerAccess.cpp
                           PartContainerAccess/DynamicContainerAccess.cpp
                           PartException/Exception.cpp
                           PartForeach/foreach.cpp
                           PartMetaType/MetaTypeModifyTuple.cpp
                           PartMetaType/MetaTypeSequence.cpp
                           PartSpecificator/ArithmeticSpecificators.cpp
                           PartSpecificator/MinMaxSpecificator.cpp
                           PartType/TypeIndex.cpp
                           PartVariant/Variant.cpp
                           PartVariant/VariantArithmeticTest.cpp
                           PartVariant/VariantAssignmentTest.cpp
                           PartVariant/VariantCmpTest.cpp
                           PartVariant/VariantConstructor.cpp
                           PartVariant/VariantConstTest.cpp
                           PartVariant/VariantContainerTest.cpp
                           PartVariant/VariantEraseTest.cpp
                           PartVariant/VariantPtrTest.cpp
                           PartVariant/VariantRefTest.cpp
                         )

