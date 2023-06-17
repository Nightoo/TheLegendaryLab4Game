cmake_minimum_required(VERSION 3.24)
project(game_lab)

set(ARTIFACT legame)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc")
set(SFML_STATIC_LIBRARIES TRUE)

set(SFML_DIR "C:/Users/s/CLionProjects/lib/sfml/GCC 7.3.0 MinGW (SEH) - 64-bit/SFML-2.5.1/lib/cmake/SFML")

include_directories("src")
file(GLOB_RECURSE SRC CONFIGURE_DEPENDS src/*.hpp src/*.cpp)
add_executable(${ARTIFACT} ${SRC} src/Game/Object/Map.cpp)
target_link_libraries(${ARTIFACT} sfml-graphics)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML 2.5 REQUIRED graphics network audio window system)


