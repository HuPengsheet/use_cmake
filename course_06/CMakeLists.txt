cmake_minimum_required(VERSION 3.10)
project(course_06)


find_package(protobuf CONFIG)

aux_source_directory(src SRC)
set(INCLUDE "include")
add_library(my_math)
target_sources(my_math PRIVATE ${SRC})
target_include_directories(my_math PUBLIC ${INCLUDE})


add_executable(run test/main.cpp)
target_link_libraries(run my_math protobuf::libprotobuf)





