add_library(title_akas src/title_akas.cpp)

target_include_directories(title_akas PUBLIC include)

target_link_libraries(title_akas dataset)
