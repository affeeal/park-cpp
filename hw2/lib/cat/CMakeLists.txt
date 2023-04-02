add_library(cat src/cat.cpp)

target_include_directories(cat PUBLIC include)

target_link_libraries(cat ioperation)
