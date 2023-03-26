add_library(name_basics INTERFACE)

target_include_directories(name_basics INTERFACE include)

target_link_libraries(name_basics INTERFACE dataset)
