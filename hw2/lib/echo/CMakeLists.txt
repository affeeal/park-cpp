add_library(echo src/echo.cpp)

target_include_directories(echo PUBLIC include)

target_link_libraries(echo ioperation)
