cmake_minimum_required(VERSION 3.10)

# Set your project name
cs50_final(final_project)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add executable target and list all source files
add_executable(my_project
    button.cpp
    camera.cpp
    dotstar_led.cpp
    led.cpp
    main.cpp
)

