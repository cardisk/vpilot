cmake_minimum_required(VERSION 3.10)
project(vpilot C)
set(CMAKE_C_STANDARD 99)

if (RENDERER MATCHES "raylib")
    include(FetchContent)
    set(FETCHCONTENT_QUIET FALSE)
    
    FetchContent_Declare(
        raylib
        GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
        GIT_TAG "master"
        GIT_PROGRESS TRUE
        GIT_SHALLOW TRUE
    )
    
    FetchContent_MakeAvailable(raylib)

    add_compile_definitions(RENDERER_RAYLIB)
endif()

file(GLOB SOURCES CONFIGURE_DEPENDS src/*.h src/*.c)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC .)

if (RENDERER MATCHES "raylib")
    target_link_libraries(${PROJECT_NAME} PUBLIC raylib)
endif()
