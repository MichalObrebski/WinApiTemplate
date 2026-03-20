cmake_minimum_required(VERSION 3.20)

project(app_template)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(app_template WIN32
    main.cpp
    app.cpp
    board.cpp
    Resource.rc
)

target_link_libraries(app_template
    user32
    gdi32
    dwmapi
)