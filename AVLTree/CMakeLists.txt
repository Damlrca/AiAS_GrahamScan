add_library(AVLTree STATIC AVLtree.h AVLtree.cpp)

target_include_directories(AVLTree PUBLIC ../Utils)
target_link_libraries(AVLTree PUBLIC Utils)
