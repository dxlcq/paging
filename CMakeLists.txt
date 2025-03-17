cmake_minimum_required(VERSION 3.28)    # 指定 CMake 的最低版本要求
project(paging VERSION 1.0.0.20250317)  # 设置项目名称和版本号

set(CMAKE_CXX_STANDARD 23)              # 指定 C++ 标准版本
set(CMAKE_CXX_STANDARD_REQUIRED True)   # 编译器必须严格遵循指定的 C++ 标准版本

find_package(Qt6 REQUIRED COMPONENTS
    Core
    Widgets
)                                       # 查找 Qt 组件库

add_executable(paging main.cpp)         # 生成可执行文件
target_link_libraries(paging Qt6::Widgets)# 链接 Qt 库到 main