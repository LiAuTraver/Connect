## **《程序设计课程实践》**综合项目实验报告

### 项目名称:

团队成员：213180209 吕逸尘

# 项目实验报告

## 系统功能设计



## 4.项目创建

### 4.1系统开发环境要求

本项目的开发及运行环境要求：

操作系统：，在`Windows 11`上开发，在`WSL2`中测试：*无所谓，我使用的Qt是跨平台的 :P*

开发工具：

* `JetBrains Clion Nova` (主要使用的IDE)

* `Neovim`, (次要使用的IDE (`nvim` 应该只算文本编辑器，不算IDE))

* `Qt Creator 13.0.2 (Enterprise), Qt 6.6.3 (MSVC 2019, x86_64)`,  (用来看Qt 6 的文档，虽然它也是个IDE)

*  `Qt Designer 6.7.2 (MSVC 2019)`, (辅助`Qt Gui`设计工具)

*  ~~`Qt Design Studio 4.5.1(Professional),Qt 6.5.5 (MSVC 2019, x86_64)` (`QML`设计工具，可能交作业的时候还没用到)~~
* `vcpkg` (包管理工具)
* `clangd`, `clang-tidy`, `clazy` (Qt/C++辅助工具)

开发语言：

* C++ (程序开发语言) 
* CMake (Build system)
* Python (辅助资源管理)
* ~~QML/C++ (程序开发语言)~~

### 项目创建过程

#### Prerequisites 

* Qt Widget 6.6
* `nlohmann json` `fmt` `magic_enum` `abseil library`
* C++ 20 编译器
* CMake
* ninja

#### Build from source

```bash
# 先 configure cmake
Cmake 
	-DCMAKE_BUILD_TYPE=Debug | Release
	-DVCPKG_CMAKE_PATH=${vcpkg_dir}
	-DCMAKE_PREFIX_PATH=${Qt_dir}
	-DCMAKE_MAKE_PROGRAM=ninja 
	-DCMAKE_TOOLCHAIN_FILE= ${vcpkg_dir}\scripts\buildsystems\vcpkg.cmake 
	-G Ninja
	-S ${project dir} 
	-B ${project dir}\build

# build app
Cmake --build ${project dir}\build --target Connect -j 10

# 程序可能无法运行，需要qt的dll.
# 若图片无法导入，这是因为resources.json / records.json是程序需要的，需要将这两个文件放在同一文件夹之下。
```



## 预处理模块设计

###  文件

```bash
# 源代码在 https://github.com/LiAuTraver/Connect
.
├── CMake # 一个CMakeList太多了，分成多文件了
│   ├── Qt-import-dlls.cmake # Qt相关文件
│   ├── files.cmake # 源代码文件
│   └── unit_test.cmake # 测试程序
├── CMakeLists.txt # 主CMakeList
├── generate_qrc.py # QRC需要手动输入，懒人我就直接拿python parse
|									# 在Resources文件夹下的音频和图片了
├── Helpers
│   ├── ButtonComparator.hpp # 核心部分，还没弄完，就是符合得分的逻辑
│   ├── RecordSerializer.hpp # 读写游戏记录
│   └── ResourcesSerializer.hpp # 读写QRC资源
├── include
│   ├── config.hpp # 一些宏
│   └── details.hpp # 一些枚举
├── main.cpp # 主程序入口
├── Models
│   ├── BlockButton.hpp # 
│   ├── Point.hpp # 简单的xy坐标
│   └── Record.hpp # 游戏记录（单个）
├── pch	# 由于Qt库太大，用 Precompiled header 来减少编译时间
│   ├── absl.log.hh
│   ├── absl.status.hh
│   ├── fmt.hh
│   ├── nlohmann.json.hh
│   ├── qt.core.hh
│   ├── qt.gui.hh
│   ├── qt.multimedia.hh
│   ├── qt.widgets.hh
│   ├── std.algorithm.hh
│   ├── std.concurrency.hh
│   ├── std.container.hh
│   ├── std.dynamic.hh
│   ├── std.error.hh
│   ├── std.io.hh
│   ├── std.string.hh
│   ├── std.time.hh
│   └── std.utils.hh
├── records.json # 游戏记录的json
├── Resources
│   ├── audios # 音频，来自 Plants vs Zombies :P
│   ├── hard  # 以下均是图片，来自 Minecraft :P
│   ├── images
│   └── ordinary
├── resources.json # 程序用于读取QRC资源的json列表
├── resources.qrc # 列有 static linked的资源，也就是上面的Resources文件夹
├── Services
│   ├── Animation.hpp # 按钮动画
│   ├── Blocks.cpp # 按钮们
│   ├── Blocks.hpp 
│   ├── Records.cpp # 游戏记录
│   ├── Records.hpp
│   ├── Sound.cpp # 音频和声音
│   └── Sound.hpp
├── test # unit test, 请忽略
│   ├── test.cpp
│   ├── textedit.cpp
│   ├── textedit.hpp
│   └── textedit.ui
├── ViewModels
│   ├── addrecorddialog.cpp # 对话框（加游戏记录）
│   ├── addrecorddialog.hpp
│   ├── addrecorddialog.ui
│   ├── blockswidget.cpp # 按钮显示的地方
│   ├── blockswidget.hpp
│   ├── blockswidget.ui
│   ├── pastgamewidget.cpp # 游戏结束页面
│   ├── pastgamewidget.hpp
│   ├── pastgamewidget.ui
│   ├── statuswidget.cpp # 得分、时间、暂停按钮 状态栏
│   ├── statuswidget.hpp
│   └── statuswidget.ui
└── Views
    ├── about.cpp # 关于界面
    ├── about.hpp
    ├── about.ui
    ├── game.cpp # 游戏界面
    ├── game.hpp
    ├── game.ui
    ├── leaderboard.cpp # 游戏记录界面
    ├── leaderboard.hpp
    ├── leaderboard.ui
    ├── mainwindow.cpp # 主窗口 （整个程序只有这一个窗口，但有四个界面，
    |								# 界面里面又有单独的组件和Layout
    ├── mainwindow.hpp
    ├── mainwindow.ui
    ├── menu.cpp # 菜单界面
    ├── menu.hpp
    └── menu.ui
```



### 宏定义

C++不推荐使用宏。我的宏全部都在`<include/config.hpp>`里。这些宏没有实际意义，大多只是个人习惯和为了测试。只解释一个宏定义:

```c#
#define CONNECT_OPT_1 1
#define CONNECT_OPT_2 0
#define CONNECT_NAMESPACE_DETAILS_INLINE 1

#if CONNECT_OPT_1 == 1 && CONNECT_OPT_2 == 0
#define CONNECT_OPT_1_NAMESPACE_BEGIN inline namespace opt1 {
#define CONNECT_OPT_1_NAMESPACE_END }
#define CONNECT_OPT_2_NAMESPACE_BEGIN namespace opt2 {
#define CONNECT_OPT_2_NAMESPACE_END }
#elif CONNECT_OPT_1 == 0 && CONNECT_OPT_2 == 1
#define CONNECT_OPT_1_NAMESPACE_BEGIN namespace opt1 {
#define CONNECT_OPT_1_NAMESPACE_END }
#define CONNECT_OPT_2_NAMESPACE_BEGIN inline namespace opt2 {
#define CONNECT_OPT_2_NAMESPACE_END }
#else
#error "Choose one opt namespace to apply."
#endif
```

该宏定义只是用来测试代码，我在Google的`abseil` , `MSVC std`以及`fmt`库中都发现了类似写法。我把失效的代码放到 `namespace opt2`里面去，再在`namespace opt1`里面重新写，使用`inline namespace`来减少使用处不需要更改代码，更换`opt`的宏定义即可。

### 定义全局变量

只有一个（包括命名空间里面的，只有以下这个)

```c++
static const absl::Status initialization = <lambda-expression>() 
```

原因和用途见`main.cpp`代码里面的`deoxygen`注释。

### 类的声明

![Qt6Class](C:\Users\LiAu\Desktop\《程序设计课程实践》综合项目实验报告.assets\Qt6Class.png)

黑色方框内是我继承/创建的class,图中列出的Qt class都是程序中用到的，没时间介绍啦~！

## 游戏主窗体设计

`MainWindow class(inherits QMainWindow (inherits QWidget(inherits QObject))`

四个不同页面`menu,about,leaderboard,game`

不同页面之间、及平行类之间用`Qt's signal & slots`进行沟通，具体是由`Qt's Auto Metaobject Compilation`实现。（比较麻烦，学起来也比较费力！:(

## 开始游戏

视频单独上传，这个pdf很可能播放不出来

exe 文件请自行编译 :)

<video src="C:\Users\LiAu\Videos\Screen Recordings\Recording 2024-07-05 231415.mp4"></video>



## 项目运行效果

消去方块的逻辑并没有完全实现，来不及了~

其余效果尚可

## 项目创新点

*其实什么也没有~*

* 随机背景音乐
* 导入/导出成绩记录,`json`格式
* 排行榜表格

## 收获和建议

Qt本身是用来做应用的而非游戏的，游戏`ui`目前流行的是`imgui x opengl`，所以界面显得着实比较简陋 :( 

尝试Qt只是为了学习它， Qt在产业中貌似还是占主要地位。

