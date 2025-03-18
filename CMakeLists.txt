cmake_minimum_required(VERSION 3.28)    # 指定 CMake 的最低版本要求
project(paging VERSION 1.0.0.20250317)  # 设置项目名称和版本号

set(CMAKE_CXX_STANDARD 23)              # 指定 C++ 标准版本
set(CMAKE_CXX_STANDARD_REQUIRED True)   # 编译器必须严格遵循指定的 C++ 标准版本

set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS    # 查找 Qt 组件库
    Core
    PrintSupport
    Xml
)

include_directories(                    # 添加包含目录
    ${CMAKE_SOURCE_DIR}/include
    /home/jiao/Desktop/qicstable-master/include
    /usr/include/postgresql
)

add_executable(paging                   # 生成可执行文件
    src/main.cc
    include/paging_window.h
    src/paging_window.cc
    src/get_data.cc
)

target_link_libraries(paging            # 链接 Qt 库到 main
    Qt6::PrintSupport
    Qt6::Xml
    /home/jiao/Desktop/qicstable-master/lib/libqicstable.so.3
    pq
)