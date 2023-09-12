add_executable(Program2 main.cpp)

target_include_directories(Program2 PUBLIC ../GrahamScan)
target_link_libraries(Program2 PUBLIC GrahamScan)

target_include_directories(Program2 PUBLIC ../Utils)
target_link_libraries(Program2 PUBLIC Utils_IO)
target_link_libraries(Program2 PUBLIC Utils_TestGen)
