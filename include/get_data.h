#pragma once

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

#include "libpq-fe.h"

class GetData {
   public:
    // 连接固定数据库中固定的表
    GetData(const std::string conninfo =
                "host=localhost port=5432 dbname = qicstabledata user=postgres "
                "password=postgres");
    ~GetData();

    // 返回值: 查询结果的二维数组，每行代表一条记录，每列代表一个字段
    // one_page_num: 每页显示的行数
    // show_page_no: 当前显示的页码
    // table_name: 表名
    const std::vector<std::vector<std::string>>& FetchData(
        const uint32_t one_page_num,
        const uint32_t show_page_no,
        const std::string& table_name);

    // 返回值: 表的总体大小，需要在 FetchData 之后调用
    const std::pair<uint32_t, uint32_t>& GetTableRC() const {
        return _table_rc;
    }

   private:
    void errif(bool) const;

    PGconn* _conn;                                     // 数据库连接对象
    PGresult* _res;                                    // 查询结果集
    std::vector<std::vector<std::string>> _res_table;  // 存储查询结果的二维数组
    std::pair<uint32_t, uint32_t> _table_rc;           // 表的大小
};