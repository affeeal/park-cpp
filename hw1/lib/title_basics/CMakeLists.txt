add_library(title_basics src/title_basics.cpp)

target_include_directories(title_basics PUBLIC include)

target_link_libraries(title_basics dataset)
