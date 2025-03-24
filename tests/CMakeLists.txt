SET(TEST_NAME paging_test)

set(TEST_SOURCES
    test_get_data.cc
    ../include/get_data.h
    ../src/get_data.cc
)

add_executable(${TEST_NAME} 
    ${TEST_SOURCES}
)

# 添加 include 目录
target_include_directories(${TEST_NAME} PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    /usr/include/postgresql
)

# 链接库
target_link_libraries(${TEST_NAME} PRIVATE
    pq
)