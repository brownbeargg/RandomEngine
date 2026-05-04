project(Sandbox)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    src/*.cpp
)

add_executable(Sandbox ${SRC_FILES})

target_include_directories(Sandbox PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(Sandbox PRIVATE Random)

add_custom_command(TARGET Sandbox POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy -t $<TARGET_FILE_DIR:Sandbox> $<TARGET_RUNTIME_DLLS:Sandbox>
    COMMAND_EXPAND_LISTS
)
