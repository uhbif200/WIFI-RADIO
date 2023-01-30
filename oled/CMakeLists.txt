cmake_minimum_required(VERSION 3.16.3)

message(Toolchain="${CMAKE_TOOLCHAIN_FILE}")

project(wifi-radio)

find_package(Threads REQUIRED)

include_directories(src)

file(GLOB SOURCES "src/*.cpp")

add_executable(wifi-radio ${SOURCES})

target_link_libraries(wifi-radio Threads::Threads)
