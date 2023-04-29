cmake_minimum_required(VERSION 3.22)
include(FindPkgConfig)
project(my_sh)

pkg_search_module(GLIB REQUIRED glib-2.0)
pkg_search_module(READLINE REQUIRED readline)

set(CMAKE_C_STANDARD 17)
include_directories(${PROJECT_SOURCE_DIR})
add_executable(my_sh src/main.c src/utils.c src/command.c src/parser.c src/execute.c src/help.c)
target_include_directories(my_sh SYSTEM PUBLIC src/ ${GLIB_INCLUDE_DIRS} ${READLINE_INCLUDE_DIRS})
target_link_libraries(my_sh ${GLIB_LIBRARIES} ${READLINE_LIBRARIES})
