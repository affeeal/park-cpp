add_library(head src/head.cpp)

target_include_directories(head PUBLIC include)

target_link_libraries(head ioperation)
