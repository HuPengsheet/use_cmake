

​	如果我们需要将自己的库安装，供别人使用且支持find_package()命令，那我们需要完成这些东西。

​	本节中，我们以安装自己编写的math静态库为例来讲解。要想支持find_package()命令，我们相关的文件在linux进行安装后，应该遵循如下布局：

安装目录（默认情况是/usr/local）

```
.
├── bin
│   └── run
├── include
│   └── math
│       └── my_math.hpp
└── lib
    ├── cmake
    │   └── math
    │       ├── mathConfig.cmake
    │       ├── mathTarget.cmake
    │       └── mathTarget-noconfig.cmake
    ├── libadd.a
    └── libsub.a

```

​	即bin目录下安装可执行文件，include/math 放对外提供的头文件，lib里面是库文件，lib/cmake/math 下放cmake文件

​	项目的源代码可以在https://github.com/HuPengsheet/use_cmake/tree/master/course_07中进行获取。

## 生成和安装库	

下面对源代码的结构进行简单介绍

```
.
├── make_lib
│   ├── cmake
│   │   └── mathConfig.cmake.in
│   ├── CMakeLists.txt
│   ├── include
│   │   └── math.hpp
│   ├── src
│   │   ├── add.cpp
│   │   └── sub.cpp
│   └── test
│       └── main.cpp
└── use_lib
    ├── CMakeLists.txt
    └── main.cpp
```

​	代码分成两个文件夹，make_lib用来生成库文件并安装，use_lib下用来使用find_package()命令来调佣我们自己安装的math包。

```c++
//math.hpp
#ifndef MY_MATH_HPP
#define MY_MATH_HPP

int add(int a,int b);
int sub(int a,int b);

#endif

//add.cpp
#include"math.hpp"

int  add(int a,int b){
    return a+b;
}

//sub.cpp
#include"math.hpp"

int sub(int a,int b){
    return a-b;
}

//main.cpp
#include<iostream>
#include<my_math.hpp>
using namespace std;
int main(){
    cout<<"3+2="<<add(2,3)<<endl;
    cout<<"3-2="<<sub(3,2)<<endl;
}
```

​	简单来说就是math.hpp里定义了加法函数和减法函数，main.cpp里调用了这两个函数进行测试。

我们主要看CMakeLists.txt的内容：

```cmake
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
            include/math.hpp 
            DESTINATION include/math)
install(EXPORT
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
```

​	下面对CMakeLists.txt中的内容进行分析：

```cmake
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
```

本例中将，add和sub分别编译成静态库，以add为例

`add_library(add)`：指明一个add静态库目标

`target_sources(add PRIVATE src/add.cpp)`：指明库的源文件为src/add.cpp下的add.cpp且，为私有属性，因为源文件是库内部使用的。

```cmake
target_include_directories(add  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include/math>)  # <prefix>/include/mylib)
```

​	在设置目标的包含路径时，使用了生成器，可以参考https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#target-dependent-queries

​	这里简单解释一下作用，`$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>`是指在构建目标的时候，属性设置为`${CMAKE_CURRENT_SOURCE_DIR}/include`。相对的 `$<INSTALL_INTERFACE:include/math>`表示属性设置为include/math（**注：这其实是一个相对路径，它会自动与CMAKE_INSTALL_PREFIX进行拼接，CMAKE_INSTALL_PREFIX默认值为/usr/local，所以在导出目标的时候头文件路径实际是/usr/local/include/math/**）。使用生成器的原因是，我们在编译库的时候，头文件是放在我们的项目目录里的，别人在用我们库的时候，找头文件显然不可能在我们编译的目录里找，肯定是在系统目录下找，所以我们根据是在构建还是安装设定两个路径。

​	接下来是生成一个测试文件run，链接两个库。

```cmake
add_executable(run test/main.cpp)
target_include_directories(run PRIVATE ${INCLUDE})
target_link_libraries(run sub add)
```

后面是安装的相关代码

```cmake
install(TARGETS 
            run add sub
            EXPORT mathTarget
            RUNTIME DESTINATION bin
            LIBRARY DESTINATION lib)
```

​	将run,add,sub目标进行安装，将可执行文件安装在bin目录下，库安装在lib目录下（注：**这里也都是相对路径，会与CMAKE_INSTALL_PREFIX进行拼接**），

EXPORT mathTarget表示这些目标要进行导出，导出名字为mathTarget。

```cmake
install(FILES 
            include/math.hpp 
            DESTINATION include/math
```

​	文件安装，将库的头文件math.hpp 安装在include/math下

```cmake
install(EXPORT
      mathTarget
      NAMESPACE  "math::"
      DESTINATION  lib/cmake/math
)
```

​	导出mathTarget目标，命名空间为math::，也就是我们的目标会变成math::add,math::sub这种。这条指令会生成mathTarget.cmake文件，里面定义了导出的目标及相关的信息。

​	接下来我们要生成mathConfig.cmake文件,并安装在lib/cmake/math

```cmake
include(CMakePackageConfigHelpers)

configure_package_config_file(
        ${PROJECT_SOURCE_DIR}/cmake/mathConfig.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/mathConfig.cmake
        INSTALL_DESTINATION lib/cmake
        )

install(FILES 
    ${CMAKE_CURRENT_BINARY_DIR}/mathConfig.cmake DESTINATION lib/cmake/math)
```

configure_package_config_file就是帮我们完成一些宏替换，变量的定义，下面是/cmake/mathConfig.cmake.in的内容

```cmake
@PACKAGE_INIT@

include("${CMAKE_CURRENT_LIST_DIR}/mathTarget.cmake")
```

@PACKAGE_INIT@会被替换为其他的东西，其他就是包含了我们导出目标的mathTarget.cmake文件，这样就可以被其他人使用。

最后安装/mathConfig.cmake文件

```cmake
install(FILES 
    ${CMAKE_CURRENT_BINARY_DIR}/mathConfig.cmake DESTINATION lib/cmake/math)
```



## find_packange()使用库

```c++
#include<iostream>
#include"math.hpp"

using namespace std;


int main(){


    cout<<"10+1="<<add(10,1)<<endl;
    return 0;
}
```

```cmake
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
```

很简单的代码，查找math库，并判断是否查找到，然后把库与run进行链接。