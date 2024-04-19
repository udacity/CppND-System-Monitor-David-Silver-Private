cmake_minimum_required(VERSION 2.6)
project(monitor)

# Set the C++ standard we will use
set(CMAKE_CXX_STANDARD 17)

# Add the path of the cmake files to the CMAKE_MODULE_PATH
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

set(CURSES_NEED_NCURSES TRUE)
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIRS})

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(include)
file(GLOB SOURCES "src/*.cpp")

add_executable(monitor ${SOURCES})

set_property(TARGET monitor PROPERTY CXX_STANDARD 17)
target_link_libraries(monitor ${CURSES_LIBRARIES})
# TODO: Run -Werror in CI.
target_compile_options(monitor PRIVATE -Wall -Wextra)

enable_testing()
add_executable(
        monitor_test
        src/format.cpp
        src/linux_parser.cpp
        src/linux_system.cpp
        src/system_memory.cpp
        test/format_test.cpp
        test/linux_parser_test.cpp
        test/system_memory_test.cpp
)
target_link_libraries(
        monitor_test
        GTest::gtest_main
)
add_test(monitor_test ${PROJECT_BINARY_DIR})
set_tests_properties(monitor_test PROPERTIES WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test)

include(GoogleTest)
gtest_discover_tests(monitor_test)