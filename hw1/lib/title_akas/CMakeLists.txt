add_library(title_akas INTERFACE)

target_include_directories(title_akas INTERFACE include)

target_link_libraries(title_akas INTERFACE dataset)
