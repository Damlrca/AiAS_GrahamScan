add_library(GrahamScan STATIC GrahamScan.h GrahamScan.cpp)

target_include_directories(GrahamScan PUBLIC ../AVLTree)
target_link_libraries(GrahamScan PUBLIC AVLTree)

target_include_directories(GrahamScan PUBLIC ../QuickSort)
target_link_libraries(GrahamScan PUBLIC QuickSort)
