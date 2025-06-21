cmake_minimum_required(VERSION 3.14)
cmake_policy(SET CMP0079 NEW)
project(filament_rendering LANGUAGES CXX)

find_package(SDL2 REQUIRED)

# imnodes
set(IMNODES_IMGUI_TARGET_NAME ImGui)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(spdlog_DIR ThirdParty/spdlog)
set(imgui_DIR ThirdParty/imgui)
set(imnodes_DIR ThirdParty/imnodes)
set(imguizmo_DIR ThirdParty/ImGuizmo)
set(glfw_DIR ThirdParty/glfw)
set(glad_DIR ThirdParty/glad)
set(glm_DIR ThirdParty/glm)
set(entt_DIR ThirdParty/entt)
set(stbimage_DIR ThirdParty/stbimage)
set(assimp_DIR ThirdParty/assimp)
set(filament_DIR ThirdParty/filament)

add_subdirectory(${spdlog_DIR})
add_subdirectory(${imgui_DIR})
add_subdirectory(${imguizmo_DIR})
add_subdirectory(${imnodes_DIR})
add_subdirectory(${glfw_DIR})
add_subdirectory(${glad_DIR})
add_subdirectory(${glm_DIR})
add_subdirectory(${filament_DIR})

add_executable(renderer
        cocoa_helper.h
        cocoa_helper.mm
        main.cpp
)

target_include_directories(renderer
        PUBLIC
        ${spdlog_DIR}/include
        ${glfw_DIR}/include
        ${glad_DIR}/include
        ${glm_DIR}
        ${filament_DIR}/include
)

target_link_libraries(renderer
        PUBLIC
        spdlog
        ImGui
        ImGuizmo
        imnodes
        glm
        glad
        glfw
        filament
        SDL2::SDL2
        SDL2::SDL2main
)

if(APPLE)
    target_link_libraries(renderer PUBLIC
            "-framework Cocoa"
            "-framework QuartzCore"
            "-framework Metal"
    )
endif()

# ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
# ┃            IMGUI CONSUMER CONFIGURATION                 ┃
# ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
target_include_directories(ImGui PUBLIC
        ${glad_DIR}/include
        ${glfw_DIR}/include
)
target_link_libraries(ImGui PUBLIC
        glfw
        glad
        ${OPENGL_LIBRARIES}
        ${CMAKE_DL_LIBS}
)

# ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
# ┃            IMGUIZMO CONSUMER CONFIGURATION              ┃
# ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
target_include_directories(ImGuizmo PUBLIC
        ${imgui_DIR}
        ${glad_DIR}/include
        ${glfw_DIR}/include
)
target_link_libraries(ImGuizmo PUBLIC
        glfw
        glad
        ImGui
        ${OPENGL_LIBRARIES}
        ${CMAKE_DL_LIBS}
)

# ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
# ┃            IMNODES CONSUMER CONFIGURATION              ┃
# ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
target_include_directories(imnodes PUBLIC
        ${imgui_DIR}
        ${glad_DIR}/include
        ${glfw_DIR}/include
)
target_link_libraries(imnodes PUBLIC
        glfw
        glad
        ImGui
        ${OPENGL_LIBRARIES}
        ${CMAKE_DL_LIBS}
)

add_custom_command(TARGET renderer POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Assets
        $<TARGET_FILE_DIR:renderer>/Assets
)