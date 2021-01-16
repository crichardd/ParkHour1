cmake_minimum_required(VERSION 3.17)
project(ParkHour C)

set(CMAKE_C_STANDARD 11)

add_executable(ParkHour sources/main.c sources/function.c)

find_package(PkgConfig REQUIRED)

pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories(includes)
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})

add_definitions(${GTK3_CFLAGS_OTHER})

target_link_libraries(ParkHour ${GTK3_LIBRARIES} mariadb)