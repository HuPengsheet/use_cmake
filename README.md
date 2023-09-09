***项目链接在：https://github.com/HuPengsheet/use_cmake***欢迎大家多多star

​	CMake是一个跨平台的构建工具，用于自动化软件构建过程，其实也就是作为一个工具帮助我们，完成代码的编译、安装与发布。我们知道，在window平台下有诸如VS2017，VS2019的集成化工具，我们只需要鼠标轻轻点一下，代码就可以完成编译和运行。但在linux系统下，我们没有像VS一样完善的集成化工具，我们自然需要采取其他的办法来完成这个工作。

​	在linux平台下，假如我们有一个main.cpp的源文件，那我们可以直接在终端中通过gcc的命令来编译代码

```shell
g++ -o run main.cpp
./run
```

​	通过运行指令，我们就可以生成名为run的可执行文件，然后通过./run就可以执行。

​	但是当我们项目代码复杂起来，包含很多个源文件和头文件，甚至是第三方库的时候，我们再采取g++的命令行编译，就不再合适了。解决的方法有两种。

1. 编写Makefile，也就是编译脚本，但是编写Makefile费事费力，难度大，不建议新手采取这种方式。
2. 编写CMake文件，通过CMake生成Makefile，来完成编译。CMake支持跨平台，可以很好的包含第三方库，新手上手容易，大部分开源项目，也都是使用CMake编译，学会CMake就可以无阻碍的编译和学习那些开源的源代码。

​	本教程的特点在于其实用性。我们将重点介绍CMake的核心概念、基本用法和常见技巧，帮助您快速上手并开始构建您自己的项目。无论您是开发桌面应用程序、嵌入式系统还是服务器端软件，CMake都能为您提供灵活且可扩展的解决方案。

教程大纲：

1. [第一节：初识CMake](https://github.com/HuPengsheet/use_cmake/tree/master/course_01)
2. [第二节：CMake变量与打印变量信息](https://github.com/HuPengsheet/use_cmake/tree/master/course_02)
3. [第三节：多个源文件与头文件](https://github.com/HuPengsheet/use_cmake/tree/master/course_03)
4. [第四节：CMake目标与目标属性](https://github.com/HuPengsheet/use_cmake/tree/master/course_04)
5. [第五节：安装项目](https://github.com/HuPengsheet/use_cmake/tree/master/course_05)
6. [第六节：find_package包含第三方库](https://github.com/HuPengsheet/use_cmake/tree/master/course_06)

​	未完待续...
