add_library(title_crew src/title_crew.cpp)

target_include_directories(title_crew PUBLIC include)

target_link_libraries(title_crew dataset)
