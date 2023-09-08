cmake_minimum_required(VERSION 3.10)
project(course_04)

set(CMAKE_CXX_STANDARD 11)  # 将 C++ 标准设置为 C++ 11
set(CMAKE_CXX_STANDARD_REQUIRED ON)  # C++ 11 是强制要求，不会衰退至低版本
set(CMAKE_CXX_EXTENSIONS OFF)  # 禁止使用编译器特有扩展

if(NOT CMAKE_BUILD_TYPE)
	message(WARNING "NOT SET CMAKE_BUILD_TYPE")
    set(CMAKE_BUILD_TYPE "Release")
endif()

aux_source_directory(src SRC)
set(INCLUDE "include")
add_library(my_math)
target_sources(my_math PRIVATE ${SRC})
target_include_directories(my_math PUBLIC ${INCLUDE})


add_executable(run test/main.cpp)
target_link_libraries(run my_math)
