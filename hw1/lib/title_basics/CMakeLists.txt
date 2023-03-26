add_library(title_basics INTERFACE) 

target_include_directories(title_basics INTERFACE include)

target_link_libraries(title_basics INTERFACE dataset)
