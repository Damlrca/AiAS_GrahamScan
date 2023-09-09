add_library(GrahamScan STATIC GrahamScan.h GrahamScan.cpp)

target_include_directories(GrahamScan PRIVATE ../AVLTree)
target_link_libraries(GrahamScan PRIVATE AVLTree)

target_include_directories(GrahamScan PRIVATE ../QuickSort)
target_link_libraries(GrahamScan PRIVATE QuickSort)
