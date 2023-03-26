add_library(title_crew INTERFACE)

target_include_directories(title_crew INTERFACE include)

target_link_libraries(title_crew INTERFACE dataset)
