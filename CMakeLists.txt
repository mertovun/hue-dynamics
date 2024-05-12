cmake_minimum_required(VERSION 3.10)
project(hue-dynamics)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)  # Important

include_directories(include)
add_executable(hue-dynamics src/main.cpp src/Particle.cpp src/Util.cpp src/Config.cpp)

target_link_libraries(hue-dynamics sfml-graphics sfml-window sfml-system)

add_custom_command(
    TARGET hue-dynamics POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/fonts
            $<TARGET_FILE_DIR:hue-dynamics>/fonts
)
