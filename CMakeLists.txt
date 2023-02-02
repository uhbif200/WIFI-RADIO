cmake_minimum_required(VERSION 3.16.3)

message(Toolchain="${CMAKE_TOOLCHAIN_FILE}")

project(wifi-radio)

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

include_directories(src)

file(GLOB SOURCES "src/*.cpp")

add_executable(wifi-radio ${SOURCES})

target_link_libraries(wifi-radio Threads::Threads)
