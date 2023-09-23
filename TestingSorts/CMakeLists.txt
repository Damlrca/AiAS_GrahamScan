add_executable(TestingSorts main.cpp)

target_include_directories(TestingSorts PUBLIC ../AVLTree)
target_link_libraries(TestingSorts PUBLIC AVLTree)

target_include_directories(TestingSorts PUBLIC ../QuickSort)
target_link_libraries(TestingSorts PUBLIC QuickSort)
