add_executable(Program1 main.cpp)

target_include_directories(Program1 PRIVATE ../GrahamScan)
target_link_libraries(Program1 PRIVATE GrahamScan)

target_include_directories(Program1 PRIVATE ../Utils)
target_link_libraries(Program1 PRIVATE Utils)
