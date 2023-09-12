cmake_minimum_required(VERSION 3.10)
project(use-lib)


#set(CMAKE_PREFIX_PATH "/home/hupeng/code_c/github/use_cmake/course_07/make_lib/install")
find_package(math)
if(math_FOUND)
    message(STATUS "my_math found")
else()
    message(STATUS "my_math not found")
endif()

add_executable(run main.cpp)
target_link_libraries(run math::add math::sub)
get_target_property(INC math::add INTERFACE_INCLUDE_DIRECTORIES)
message(${INC})