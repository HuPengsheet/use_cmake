cmake_minimum_required(VERSION 3.10)
project(course_07)


set(INCLUDE "include")
#set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_LIST_DIR}/install)

add_library(add)
target_sources(add PRIVATE src/add.cpp)
target_include_directories(add  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include/math>)  # <prefix>/include/mylib)

add_library(sub)
target_sources(sub PRIVATE src/sub.cpp)
target_include_directories(sub  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include/math> ) # <prefix>/include/mylib)


add_executable(run test/main.cpp)
target_include_directories(run PRIVATE ${INCLUDE})
target_link_libraries(run sub add)




install(TARGETS 
            run add sub
            EXPORT mathTarget
            RUNTIME DESTINATION bin
            LIBRARY DESTINATION lib)

install(FILES 
            include/math.hpp DESTINATION include/math)

install(
      EXPORT
        mathTarget
      NAMESPACE  "math::"
      DESTINATION  lib/cmake/math
)

include(CMakePackageConfigHelpers)
configure_package_config_file(
        ${PROJECT_SOURCE_DIR}/cmake/mathConfig.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/mathConfig.cmake
        INSTALL_DESTINATION lib/cmake
        )

install(FILES 
    ${CMAKE_CURRENT_BINARY_DIR}/mathConfig.cmake DESTINATION lib/cmake/math)