cmake_minimum_required(VERSION 3.16)
project(filament_sdl)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)

# Filament subdirectory
add_subdirectory(${CMAKE_SOURCE_DIR}/../third_party/filament ${CMAKE_BINARY_DIR}/filament-build)

set(SRC
        main.cpp
        window.cpp
        input.cpp
        renderer.cpp
        camera_controller.cpp
        native_window_helper_cocoa.mm
)

add_executable(filament_sdl ${SRC})

target_include_directories(filament_sdl PRIVATE
        ${SDL2_INCLUDE_DIRS}
        ${CMAKE_SOURCE_DIR}/../third_party/filament/include
)

target_link_libraries(filament_sdl PRIVATE
        SDL2::SDL2
        filament
)

# Material compilation
set(MATERIAL_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/materials)
file(MAKE_DIRECTORY ${MATERIAL_OUTPUT_DIR})
add_custom_command(
        OUTPUT ${MATERIAL_OUTPUT_DIR}/lit_color.filamat
        COMMAND ${CMAKE_SOURCE_DIR}/../third_party/filament/bin/matc -o ${MATERIAL_OUTPUT_DIR}/lit_color.filamat
        ${CMAKE_CURRENT_SOURCE_DIR}/materials/lit_color.mat
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/materials/lit_color.mat
        COMMENT "Compiling Filament material"
)
add_custom_target(materials ALL DEPENDS ${MATERIAL_OUTPUT_DIR}/lit_color.filamat)
add_dependencies(filament_sdl materials)