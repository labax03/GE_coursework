cmake_minimum_required(VERSION 3.11)
project(GE_coursework)

# Require modern C++
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Main output directory
set(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})

# External Dependencies
add_subdirectory("lib/SFML")
add_subdirectory("lib/tmxlite-master/tmxlite")

set(SFML_INCS "lib/SFML/include")

link_directories("${CMAKE_BINARY_DIR}/lib/SFML/lib")

# Copy resources
add_custom_target(copy_resources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${PROJECT_SOURCE_DIR}/resources"
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIGURATION>/res
)

# Main executable
add_executable(GE_coursework
    main.cpp
    game_system.cpp
     "Parameters.cpp" "NPC.cpp")

target_include_directories(GE_coursework PRIVATE
    ${SFML_INCS}
)

target_link_libraries(
    GE_coursework
    sfml-graphics
    tmxlite
)

set_target_properties(
    GE_coursework
    PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration)
)

add_dependencies(GE_coursework copy_resources)