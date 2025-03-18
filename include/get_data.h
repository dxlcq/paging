#pragma once

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

#include "libpq-fe.h"

class GetData {
   public:
    // 连接固定数据库中固定的表
    GetData(std::string conninfo);
    ~GetData();
    uint32_t get_row() { return _row_all; };
    uint32_t get_col() { return _col_all; };
    // 每页显示 one_page_num 条数据，显示第 show_page_no 页的数据
    std::vector<std::vector<std::string>> FetchData(uint32_t one_page_num,
                                                    uint32_t show_page_no);

   private:
    PGconn *_conn;      // 数据库连接对象
    PGresult *_res;     // 查询结果集
    uint32_t _row_all;  // 结果行数
    uint32_t _col_all;  // 结果列数
};