cmake_minimum_required(VERSION 3.10)
project(use-lib)


set(CMAKE_PREFIX_PATH "/home/hp/code/github/use_cmake/course_07/make_lib/install/lib/cmake")
find_package(my_math)
if(my_math_FOUND)
    message(STATUS "my_math found")
else()
    message(STATUS "my_math not found")
endif()

add_executable(run main.cpp)
target_link_libraries(run math::my_math)
get_target_property(INC math::my_math INTERFACE_INCLUDE_DIRECTORIES)
message(${INC})