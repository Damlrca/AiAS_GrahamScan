add_library(QuickSort STATIC QuickSort.h QuickSort.cpp)

target_include_directories(QuickSort PUBLIC ../Utils)
target_link_libraries(QuickSort PUBLIC Utils)
