# 	第五节：安装项目

​	许多情况下，我们我们要将代码发布出去，这时我们就需要在CMakeList中编写安装项目的相关代码。把生成的库和相关的头文件，安装到对应的系统目录下，去供别人使用。本节项目代码和第四季一样，只修改CMakeList.txt里的内容。

相关代码在：https://github.com/HuPengsheet/use_cmake/tree/master/course_05

## 使用install安装目标

```cmake
install(TARGETS targets... [EXPORT <export-name>]
        [RUNTIME_DEPENDENCIES args...|RUNTIME_DEPENDENCY_SET <set-name>]
        [[ARCHIVE|LIBRARY|RUNTIME|OBJECTS|FRAMEWORK|BUNDLE|
          PRIVATE_HEADER|PUBLIC_HEADER|RESOURCE|FILE_SET <set-name>|CXX_MODULES_BMI]
         [DESTINATION <dir>]
         [PERMISSIONS permissions...]
         [CONFIGURATIONS [Debug|Release|...]]
         [COMPONENT <component>]
         [NAMELINK_COMPONENT <component>]
         [OPTIONAL] [EXCLUDE_FROM_ALL]
         [NAMELINK_ONLY|NAMELINK_SKIP]
        ] [...]
        [INCLUDES DESTINATION [<dir> ...]]
        )
```

 乍一看参数有很多，我们直接看例子,知道怎么使用就好了

```cmake
install(TARGETS 
            run my_math
            RUNTIME DESTINATION bin
            LIBRARY DESTINATION lib)
```

​	安装run和my_math这两个目标，RUNTIME表示可执行目标文件会被安装到bin目录下，LIBRARY表示静态库会被安装在lib下。这里的目标都是相对路径，相对于`CMAKE_INSTALL_PREFIX`这个宏，也就是实际安装在`${CMAKE_INSTALL_PREFIX}/bin`和`${CMAKE_INSTALL_PREFIX}/lib`下

## 使用install安装文件

```cmake
install(<FILES|PROGRAMS> files...
        TYPE <type> | DESTINATION <dir>
        [PERMISSIONS permissions...]
        [CONFIGURATIONS [Debug|Release|...]]
        [COMPONENT <component>]
        [RENAME <name>] [OPTIONAL] [EXCLUDE_FROM_ALL])
```

​	类似的，我们之间看怎么用就好了，用install安装头文件

```cmake
 install(FILES 
                include/my_math.hpp DESTINATION my_math/include)
```

也就是将`my_math.hpp`安装到`${CMAKE_INSTALL_PREFIX}/my_math/include`下去

下面是完整的CMakeLists.txt

```cmake
cmake_minimum_required(VERSION 3.10)
project(course_05)

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



set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/install/)
install(TARGETS 
            run my_math
            RUNTIME DESTINATION bin
            LIBRARY DESTINATION lib)

 install(FILES 
                include/my_math.hpp DESTINATION my_math/include)

```

在`make`后，执行`sudo make install`命令可以看到有如下安装路径

```shell
├── build
├── CMakeLists.txt
├── include
│   └── my_math.hpp
├── install
│   ├── bin
│   │   └── run
│   ├── lib
│   │   └── libmy_math.a
│   └── my_math
│       └── include
│           └── my_math.hpp
├── src
│   ├── add.cpp
│   └── sub.cpp
└── test
    └── main.cpp
```

