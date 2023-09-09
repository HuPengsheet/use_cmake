# 第一节：初识CMake

## 编写我们的第一个CMakeLists.txt

参考代码在：https://github.com/HuPengsheet/use_cmake/tree/master/course_01

项目的目录结构
.
├── CMakeLists.txt
└── main.cpp

```c++
//main.cpp
#include<iostream>

using namespace std;

int main(){

    cout<<"Hello World"<<endl;
    return 0;
}
```

```cmake
#CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(course_01 VERSION 0.0.1)
add_executable(run main.cpp)
```

接下来对CMakeLists.txt中的内容进行解释

`cmake_minimum_required(VERSION 3.10):`设置cmake的最低版本，这里是不低于3.10，我们可以通过终端cmake --version查看本机的cmake版本

`project(course_01 VERSION 0.0.1)`: 设置项目的名称和版本号（0.0.1），上面两行代码可以省略，但cmake会报一个警告，建议保留。

`add_executable(run main.cpp)`：添加可执行文件run，其源文件是main.cpp

**注意：run在这里是cmake的目标（target），目标是现代cmake的概念，也就是cmake3.x版本的东西。目前我们只需要记住，run是一个CMake目标，详细的知识会在后面进行介绍。**

​	之后，我们在终端中执行如下指令

```shell
mkdir build
cd build
cmake ..
make
./run

#此时会输出Hello World
```

​	创建一个build目录并进入是因为，在执行cmake的过程中，会产生许多中间文件。为了避免产生的中间文件，污染我们的工作目录，就让CMake在build中执行。

​	执行`cmake ..`就是根据上层目录编写的CMakeLists.txt，进行执行，最总生成Makefile文件，再执行`make`命令，自动编译代码，生成可执行文件run。

## 设置c++标准

```cmake
#CMakeLists.txt

cmake_minimum_required(VERSION 3.10)
project(course_01 VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 11)  # 将 C++ 标准设置为 C++ 11
set(CMAKE_CXX_STANDARD_REQUIRED ON)  # C++ 11 是强制要求，不会衰退至低版本
set(CMAKE_CXX_EXTENSIONS OFF)  # 禁止使用编译器特有扩展

add_executable(run main.cpp)

```

​	我们在上一节的基础上，加上c++标准的代码，这里将c++标准设置为c++11。

​	`set(CMAKE_CXX_EXTENSIONS OFF）`：是取消编译器的特有扩展，比如linux下的gcc编译器与windows下的msvc编译器有一些不同的特性，为了跨平台的需要，就将这个变量设置为OFF。