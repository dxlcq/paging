set(TEST_NAME_1 test_get_data)

set(TEST_1_SOURCES
    test_get_data.cc
    ../include/get_data.h
    ../src/get_data.cc
)

add_executable(${TEST_NAME_1} 
    ${TEST_1_SOURCES}
)

target_include_directories(${TEST_NAME_1} PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    /usr/include/postgresql
)

target_link_libraries(${TEST_NAME_1} PRIVATE
    pq
)