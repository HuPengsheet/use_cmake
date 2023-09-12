# 第六节：find_package包含第三方库

​	在我们编写代码的时候，我们常常会用到一些开源库，比如opencv，Glog，googletest，protobuf等。我们可以使用

```cmake
find_package(ncnn)
find_package(OpenCV)
find_package(Protobuf)
```

​	来帮助我们快速在我们的项目中，使用这个第三方库。

本节示例代码结构与上一节一样只修改CMakeLists.txt，代码在https://github.com/HuPengsheet/use_cmake/tree/master/course_06

## find_package的**Module**模式

​	例如`find_package(OpenCV)`，在不添加其他参数下默认就是Module模式，在`Module`模式下，其实是在找FindOpenCV.cmake文件，查找路径是`/usr/share/cmake-3.25/Modules`。Find<LibaryName>.cmake文件是CMake官方给我们提供的，它只支持一些特别常见的库。下面是里面/usr/share/cmake-3.25/Modules的部分内容，里面有许多CMake提供的Find<LibaryName>.cmake文件。

![cmkaemodul](../image/cmkaemodul.png)

​	在这些文件里，都会给我们提供一些变量

```cmake
<LibaryName>_FOUND
<LibaryName>_INCLUDE_DIR 
<LibaryName>_INCLUDES` `
<LibaryName>_LIBRARY
<LibaryName>_LIBRARIES
```

<LibaryName>_FOUND就是告诉我们，这个库是否找到，所以我们常常会有这种写法,如果没有找到对应的包，则报一个警告或者直接报错。

```cmake
find_package(Protobuf)

if(Protobuf_FOUND)
	message(STATUS "Protobuf found")
else()
	message(WARNING "Protobuf not  found")
endif()

```

进一步的，我们可以使用message打印这些变量，

```cmake
cmake_minimum_required(VERSION 3.10)
project(course_05)


find_package(Protobuf)

if(Protobuf_FOUND)
	message(STATUS "Protobuf found")
    message(STATUS ${Protobuf_FOUND})
    message(STATUS ${Protobuf_INCLUDE_DIR})
    message(STATUS ${Protobuf_INCLUDES})
    message(STATUS ${Protobuf_LIBRARY})
    message(STATUS ${Protobuf_LIBRARIES})
else()
	message(WARNING "Protobuf not  found")
endif(）

```

![](../image/Protobuf.png)

根据这些变量，可以设置对应头文件和库，来链接到自己的项目里。

## find_package的**Config**模式

​	其实大部分情况下，如果这些第三方库，我们是自己安装的话，更推荐使用Config模式。有两个原因，一是CMake不一定Find<LibaryName>.cmake这个文件。二是，Find<LibaryName>.cmake的内容不一定跟的是第三方库的演变，往往是滞后的，所以很有可能即使找到了	其实大部分情况下，如果这些第三方库，我们是自己安装的话，更推荐使用Config模式。有两个原因，一是CMake不一定Find<LibaryName>.cmake，也会有一些莫名奇妙的错误。

```cmake
find_package(ncnn CONFIG)
find_package(OpenCV CONFIG)
find_package(Protobuf CONFIG)
```

​	使用`CONFIG`显示的指定，find_package为CONFIG模式。（**注：`Module`下如果没有找到Find<LibaryName>.cmake文件，则再执行Config模式**）。`CONFIG`模式实际是在/usr/local/lib/cmake下查找对应的<LibaryName>config.cmake文件。以Protobuf为例：

![](../image/cmake.png)

在找到这个库文件后，我们就可以直接链接到这个库，如下：

```cmake
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
```

​	有两个需要注意的地方：

1.我们并没有设置protobuf::libprotobuf这个库的头文件在哪，以及对应的的编译选项。那为什么在编译的时候，run目标可以找到它的头文件呢？我们看protobuf-config.cmake里面有这么一串代码（实际上是在protobuf-targets.cmake里，但protobuf-config.cmake包含了protobuf-targets.cmake）

```cmake
add_library(protobuf::libprotobuf STATIC IMPORTED)

set_target_properties(protobuf::libprotobuf PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_std_14"
  INTERFACE_INCLUDE_DIRECTORIES "${_IMPORT_PREFIX}/include"
  INTERFACE_LINK_LIBRARIES "\$<LINK_ONLY:-lpthread>;\$<LINK_ONLY:ZLIB::ZLIB>;absl::absl_check;absl::absl_log;absl::algorithm;absl::base;absl::bind_front;absl::bits;absl::btree;absl::cleanup;absl::cord;absl::core_headers;absl::debugging;absl::die_if_null;absl::dynamic_annotations;absl::flags;absl::flat_hash_map;absl::flat_hash_set;absl::function_ref;absl::hash;absl::layout;absl::log_initialize;absl::log_severity;absl::memory;absl::node_hash_map;absl::node_hash_set;absl::optional;absl::span;absl::status;absl::statusor;absl::strings;absl::synchronization;absl::time;absl::type_traits;absl::utility;absl::variant;\$<LINK_ONLY:utf8_range::utf8_validity>"
)
```

​	它为protobuf::libprotobuf设置了`INTERFACE_COMPILE_FEATURES`，`INTERFACE_INCLUDE_DIRECTORIES`，`INTERFACE_LINK_LIBRARIES`[这三个属性我们在第四节提到过](#INTERFACE、PUBLIC和PRIVATE)。它是给外部目标来链接使用的。

2.protobuf::libprotobuf这个名字是什么意思？我们使用find_package命令的时候写的是protobuf，为什么链接的时候写protobuf::libprotobuf。首先protobuf::libprotobuf表示libprotobuf是protobuf库的一个模块，protobuf里面还有其他的模块。其次我们怎么确定我们该用哪个名字。这里作者提供这么几个方法，第一就是我们直接去protobuf-targets.cmake里看，看他导出的是什么名字。第二就是去这个库的github看作者提供的CMake demo ，看看它的示例里怎么写的。



