CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

PROJECT(QtCefCMakeDemo LANGUAGES CXX)
SET(CMAKE_BUILD_TYPE DEBUG)
SET(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_INCLUDE_CURRENT_DIR ON)

# 【QT】CMAKE_PREFIX_PATH 实际值为本地安装的QT中的对应编译环境的目录
SET(CMAKE_PREFIX_PATH "D:\\Programs\\Qt\\Qt5.14.2\\5.14.2\\msvc2017_64")
# 配置了上述后，可以通过find_package来查找QT相关的cmake文件

# 【QT】UIC、MOC、RCC启用
# 引入的QT模块则会对.ui文件、.qtc文件以及QT中的元信息机制自动进行处理
SET(CMAKE_AUTOUIC ON)
SET(CMAKE_AUTOMOC ON)
SET(CMAKE_AUTORCC ON)

# 【QT】通过FIND_PACKAGE，CMake会查找QT相关模块cmake文件，
# 这些cmake文件自动处理了头文件的查找等，
# 不需要像配置CEF的头文件查找一样来配置QT的头文件引入
FIND_PACKAGE(Qt5 COMPONENTS Widgets REQUIRED)
# 【CEF】CEF相关头文件的引入
INCLUDE_DIRECTORIES("${CMAKE_SOURCE_DIR}/CefFiles")
INCLUDE_DIRECTORIES("${CMAKE_SOURCE_DIR}/CefFiles/include")

# 添加项目所有的文件：
# 头文件、源文件、ui文件、qrc资源文件
# 特别的，在Windows下VS下，还需要manifest文件，并且该文件在cmake3.4以后就能够自动是被并被引入
ADD_EXECUTABLE(qt-cef
        WIN32
        src/qtcefwindow.h
        src/simple_app.h
        src/simple_handler.h
        src/main.cpp
        src/qtcefwindow.cpp
        src/simple_app.cpp
        src/simple_handler.cpp
        src/qtcefwindow.ui
        src/qtcefwindow.qrc
        src/app.manifest
        )

# QT库链接
TARGET_LINK_LIBRARIES(qt-cef
        PRIVATE
        # 【QT】QT库链接
        Qt5::Widgets
        # 【CEF】cef相关库链接
        "${CMAKE_SOURCE_DIR}/CefFiles/bin/Debug/libcef.lib"
        "${CMAKE_SOURCE_DIR}/CefFiles/bin/Debug/libcef_dll_wrapper.lib"
        )