add_library(Utils STATIC Utils.h Utils.cpp)

add_library(Utils_IO STATIC Utils_IO.h Utils_IO.cpp)
target_link_libraries(Utils_IO PUBLIC Utils)

add_library(Utils_TestGen STATIC Utils_TestGen.h Utils_TestGen.cpp)
target_link_libraries(Utils_TestGen PUBLIC Utils)
