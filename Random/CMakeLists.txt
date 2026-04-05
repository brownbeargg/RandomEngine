cmake_minimum_required(VERSION 3.20)
project(Random)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Random/*.cpp
)

if (WIN32)
    file(GLOB_RECURSE PLATFORM_SRC_FILES CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Platform/Windows/*.cpp
    ) 
else ()
    message(FATAL_ERROR "Hazel doesn't support this platform")
endif ()

add_library(${PROJECT_NAME} SHARED
    ${SRC_FILES}
    ${PLATFORM_SRC_FILES}
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/GLFW)

target_link_libraries(${PROJECT_NAME} PRIVATE
    glfw
    glad
)

add_library(glad ${CMAKE_CURRENT_SOURCE_DIR}/vendor/GLAD/src/glad.c)
target_include_directories(glad PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/GLAD/include
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/GLFW/include
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/spdlog/include
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
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Random/RandomPch.hpp
)
