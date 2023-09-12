cmake_minimum_required(VERSION 3.10)
project(course_07)


#设置头文件和和源文件相关路径
aux_source_directory(src SRC)
set(INCLUDE "include")

set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/install)

#生成静态库目标
add_library(my_math)
target_sources(my_math PRIVATE ${SRC})
target_include_directories(my_math PUBLIC ${INCLUDE})


add_executable(run test/main.cpp)
target_include_directories(run PRIVATE ${INCLUDE})
target_link_libraries(run my_math)


include(CMakePackageConfigHelpers)

install(TARGETS 
            run my_math
            EXPORT my_math_target
            RUNTIME DESTINATION bin
            LIBRARY DESTINATION lib)

install(FILES 
            include/my_math.hpp DESTINATION include/my_math)

install(
      EXPORT
        my_math_target
      NAMESPACE
          "math::"
      DESTINATION
          lib/cmake
      )

configure_package_config_file(
        ${PROJECT_SOURCE_DIR}/cmake/my_mathConfig.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/my_mathConfig.cmake
        INSTALL_DESTINATION lib/cmake
        )

install(FILES 
    ${CMAKE_CURRENT_BINARY_DIR}/my_mathConfig.cmake DESTINATION lib/cmake)