cmake_minimum_required(VERSION 3.10)

# Set your project name
project(cs50_final_project)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add executable target and list all source files
add_executable(my_project
    button.cpp
    camera.cpp
    led.cpp
    main.cpp
)

# Include directories for header files
target_include_directories(my_project PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Link libraries
target_link_libraries(my_project wiringPi)
