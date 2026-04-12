cmake_minimum_required(VERSION 3.20)
project(Random)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Random/*.cpp
)

if (WIN32)
    file(GLOB_RECURSE PLATFORM_SRC_FILES CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Platform/Windows/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Platform/OpenGL/*.cpp
    ) 
else ()
    message(FATAL_ERROR "Hazel doesn't support this platform")
endif ()

add_library(${PROJECT_NAME} SHARED
    ${SRC_FILES}
    ${PLATFORM_SRC_FILES}
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/GLFW)

add_library(glad ${CMAKE_CURRENT_SOURCE_DIR}/vendor/GLAD/src/glad.c)
target_include_directories(glad PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/GLAD/include
)

file(GLOB IMGUI_SRC
    vendor/imgui/*.cpp
)
add_library(imgui STATIC ${IMGUI_SRC})
target_include_directories(imgui PUBLIC
    vendor/GLAD/include
    vendor/GLFW/include
    vendor/imgui
    vendor/imgui/backends
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    glfw
    glad
    imgui
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/GLFW/include
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/spdlog/include
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui
)

if (WIN32)
    target_compile_definitions(${PROJECT_NAME} PUBLIC
        RAND_PLATFORM_WINDOWS
    )
endif ()

target_compile_definitions(${PROJECT_NAME} PRIVATE
    RAND_BUILD_DLL
    GLFW_INCLUDE_NONE
)

target_precompile_headers(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Random/RandomPch.hpp
)
