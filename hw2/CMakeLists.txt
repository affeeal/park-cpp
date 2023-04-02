add_subdirectory(lib/ioperation)
add_subdirectory(lib/cat)
add_subdirectory(lib/echo)
add_subdirectory(lib/head)
add_subdirectory(lib/utils)

add_executable(hw2 src/main.cpp)

target_link_libraries(hw2 cat echo head utils)
