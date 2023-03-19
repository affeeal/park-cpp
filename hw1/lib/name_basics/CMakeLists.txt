add_library(name_basics src/name_basics.cpp)

target_include_directories(name_basics PUBLIC include)

target_link_libraries(name_basics dataset)
