add_executable(Program1 main.cpp)

target_include_directories(Program1 PUBLIC ../GrahamScan)
target_link_libraries(Program1 PUBLIC GrahamScan)

target_include_directories(Program1 PUBLIC ../Utils)
target_link_libraries(Program1 PUBLIC Utils_IO)
