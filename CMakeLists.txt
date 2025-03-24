cmake_minimum_required(VERSION 3.28)
project(paging VERSION 1.0.0.20250319)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)

# 查找 Qt6 组件
# 自动导入头文件路径和库路径
find_package(Qt6 REQUIRED COMPONENTS
    Core
    PrintSupport
    Xml
)

# 定义源文件和头文件列表，便于管理
set(SOURCES
    src/main.cc
    src/paging_window.cc
    src/get_data.cc
)
set(HEADERS
    include/paging_window.h
)

# 生成可执行文件
add_executable(paging
    ${SOURCES}
    ${HEADERS}
)

# 头文件路径
target_include_directories(paging PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    /usr/include/postgresql                     # apt 管理
    /home/jiao/Desktop/qicstable-master/include # 第三方库
)

# 动态库路径
target_link_directories(paging PRIVATE
    /home/jiao/Desktop/qicstable-master/lib     # 第三方库需要指定路径
)

# 链接库
target_link_libraries(paging PRIVATE
    Qt6::Core
    Qt6::PrintSupport
    Qt6::Xml
    pq
    qicstable.so.3
)

# 启用测试
#enable_testing()
#add_subdirectory(tests)