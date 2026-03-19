
add_library(basis-shared-library SHARED shared.cpp)


#set_target_properties(basis-shared-library PROPERTIES
#      POSITION_INDEPENDENT_CODE ON
#      )


add_executable(basis-shared-app main.cpp)
target_link_libraries(basis-shared-app PUBLIC basis-shared-library)



