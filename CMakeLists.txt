cmake_minimum_required(VERSION 3.25)

set(CMAKE_C_COMPILER gcc)

project(raylib_celeste_clone C)

find_package(raylib REQUIRED)
find_package(cJSON REQUIRED)

set(CMAKE_C_STANDARD 17)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(GAMEBASE_DIR ${INCLUDE_DIR})

include(FetchContent)

function(add_git_dependency libName gitURL gitTag)
    FetchContent_Declare(${libName}
        GIT_REPOSITORY ${gitURL}
        GIT_TAG ${gitTag}
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
    )
    FetchContent_MakeAvailable(${libName})
    target_compile_options(${libName} PRIVATE "-w")
endfunction()

# boilerplate to download cmake-conan
if(NOT EXISTS "${CMAKE_PROJECT_TOP_LEVEL_INCLUDES}")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/develop2/conan_provider.cmake"
        "${CMAKE_PROJECT_TOP_LEVEL_INCLUDES}"

        # EXPECTED_HASH SHA256=ebcac264a8e25662b5292900c9131c7bd5f838175996b4b1545f99cbb749fa88
        TLS_VERIFY ON)
endif()

# Adicione todos os arquivos-fonte do diretório src
file(GLOB SOURCES ${SOURCE_DIR}/*.c)

file(GLOB_RECURSE SOURCES
    ${SOURCE_DIR}/*.c
    ${INCLUDE_DIR}/*.c
)
file(GLOB_RECURSE HEADER_FILES
    ${INCLUDE_DIR}/*.h
    ${SOURCE_DIR}/*.h
    ${GAMEBASE_DIR}/*.h    
)

add_executable(raylib_celeste_clone ${SOURCES} ${HEADER_FILES}
)

#create symbolic link do resources folder
if(LINUX OR WINDOWS)
    add_custom_command(
        TARGET ${CMAKE_PROJECT_NAME}
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E
        create_symlink ${CMAKE_CURRENT_SOURCE_DIR}/Resources $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>/resources)
endif()

#target_precompile_headers(raylib_celeste_clone PRIVATE ${GAMEBASE_DIR})

if(CMAKE_HOST_SYSTEM MATCHES Linux)
    target_link_libraries(raylib_celeste_clone PRIVATE
        ${CONAN_LIBS}
        X11
        GL
        pthread
        png
        stdc++fs
        raylib
        glfw
        cjson::cjson
    )
endif()

add_custom_target(build_wasm
    COMMAND em++ -std=c++17 -O2 -s ALLOW_MEMORY_GROWTH=1 -s MAX_WEBGL_VERSION=2 -s MIN_WEBGL_VERSION=2 -s USE_LIBPNG=1 ${SOURCES} -o ${CMAKE_PROJECT_NAME}.html

    # COMMAND em++ ${SOURCES} -o raylib_celeste_clone.js -std=c++17 -s WASM=1
)

add_dependencies(build_wasm raylib_celeste_clone)
