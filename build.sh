#!/bin/bash

CMAKE_TOOLCHAIN_DIR=cmake-build-debug/build/Debug/generators

# Script to install Conan dependencies
install_dependencies() {
    conan install . -of cmake-build-debug -s build_type=Debug -b missing -c tools.system.package_manager:mode=install
}

# Script to configure the project with CMake
configure_project() {
    cmake -S . -B cmake-build-debug \
        -DCONAN_USER_HOME=cmake-build-debug/conan_cache \
        -DCMAKE_BUILD_TYPE=Debug \
        -DCMAKE_TOOLCHAIN_FILE=$CMAKE_TOOLCHAIN_DIR/conan_toolchain.cmake \
        -G Ninja
}

# Script to build the project
build_project() {
    cmake --build cmake-build-debug --config Debug
}

build_project_debug() {
    cmake --build cmake-build-debug
}

# Script to build the project
build_wasm() {
    cmake --build cmake-build-debug --target build_wasm
}

# Script to build the project
clean() {
    cmake --build cmake-build-debug --target clean
}


# Script to run the project
run_project() {
    project_name=$(grep -oP 'project\(\K[^)]+' CMakeLists.txt)
   exec "cmake-build-debug/$project_name"
}

run_project_wasm() {
    project_name=$(grep -oP 'project\(\K[^)]+' CMakeLists.txt)
    npx http-server cmake-build-debug 
}




# Display help
display_help() {
    echo "Usage: $0 [command]"
    echo "Available commands:"
    echo "  install     - Install Conan dependencies"
    echo "  configure   - Configure the project with CMake"
    echo "  build       - Build the project"
    echo "  build_debug - Build in Debug mode the project"
    echo "  run         - Run the project"
    echo "  all         - Execute all tasks (install, configure, build, run)"
}

# Check the number of arguments
if [ "$#" -eq 0 ]; then
    display_help
    exit 1
fi

# Execute the appropriate task
case "$1" in
    "clean") clean ;;
    "install") install_dependencies ;;
    "configure") configure_project ;;
    "build") build_project ;;
    "build_debug") build_project_debug ;;
    "build_wasm") build_wasm ;;
    "run") run_project ;;
	"run_wasm") run_project_wasm ;;
    "all"|"")  # Default to "all" if no task is provided
        install_dependencies
        configure_project
        build_project
        run_project
        ;;
	"all_wasm"|"")  # Default to "all" if no task is provided
        install_dependencies
        configure_project
        build_project_wasm
        run_project_wasm
        ;;
    *)
        echo "Invalid command: $1"
         display_help
        exit 1
        ;;
esac
