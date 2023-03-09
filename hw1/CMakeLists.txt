add_subdirectory(lib/name_basics)

add_executable(hw1 src/main.cpp)

target_link_libraries(hw1 name_basics)
