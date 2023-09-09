add_executable(Program2 main.cpp)

target_include_directories(Program2 PRIVATE ../GrahamScan)
target_link_libraries(Program2 PRIVATE GrahamScan)

target_include_directories(Program2 PRIVATE ../Utils)
target_link_libraries(Program2 PRIVATE Utils)
