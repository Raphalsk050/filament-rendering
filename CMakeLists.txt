cmake_minimum_required(VERSION 3.2)
project(filament_rendering LANGUAGES CXX)

set(CMAKE_CXX_STANDARD          20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS       OFF)

add_subdirectory(ThirdParty/filament)

add_executable(renderer 
    main.cpp
)

target_include_directories(renderer 
    PUBLIC
        ThirdParty/filament/include
)

target_link_libraries(renderer 
    PUBLIC
        filament
)

target_link_libraries(renderer PRIVATE
        "-framework Cocoa"
        "-framework CoreFoundation"
        "-framework CoreVideo"
        "-framework CoreMedia"
        "-framework QuartzCore"
        "-framework Metal"
        "-framework MetalKit"
        "-framework IOSurface"
)