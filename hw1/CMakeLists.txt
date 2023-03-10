add_subdirectory(lib/name_basics)
add_subdirectory(lib/title_akas)
add_subdirectory(lib/title_basics)
add_subdirectory(lib/title_crew)

add_executable(hw1 src/main.cpp)

target_link_libraries(hw1 name_basics title_akas title_basics title_crew)
