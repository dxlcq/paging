#include "get_data.h"

#include <stdio.h>
#include <stdlib.h>

GetData::GetData(std::string conninfo) {
    _conn = PQconnectdb(conninfo.c_str());
    // 连接
    if (CONNECTION_OK != PQstatus(_conn)) {
        std::cerr << PQerrorMessage(_conn) << std::endl;
        PQfinish(_conn);
        exit(1);
    }

    _res =
        PQexec(_conn, "SELECT pg_catalog.set_config('search_path', '', false)");
    // 安全
    if (PGRES_TUPLES_OK != PQresultStatus(_res)) {
        std::cerr << PQerrorMessage(_conn) << std::endl;
        PQclear(_res);
        PQfinish(_conn);
        exit(1);
    }
    PQclear(_res);
}

GetData::~GetData() {
    // 断开连接
    PQfinish(_conn);
};

std::vector<std::vector<std::string>> GetData::FetchData(
    const uint32_t one_page_num, const uint32_t show_page_no) {
    _res = PQexec(_conn, "BEGIN");
    // 事物块开始
    if (PGRES_COMMAND_OK != PQresultStatus(_res)) {
        std::cerr << PQerrorMessage(_conn) << std::endl;
        PQclear(_res);
        PQfinish(_conn);
        exit(1);
    }
    PQclear(_res);

    _res = PQexec(_conn,
                  "DECLARE myportal CURSOR FOR select * from public.events");
    // 使用 myportal 游标来查询 public.events 表中的所有数据
    if (PGRES_COMMAND_OK != PQresultStatus(_res)) {
        std::cerr << PQerrorMessage(_conn) << std::endl;
        PQclear(_res);
        PQfinish(_conn);
        exit(1);
    };
    PQclear(_res);

    _res = PQexec(_conn, "FETCH ALL IN myportal");
    // 获取游标中的所有数据
    if (PGRES_TUPLES_OK != PQresultStatus(_res)) {
        std::cerr << PQerrorMessage(_conn) << std::endl;
        PQclear(_res);
        PQfinish(_conn);
        exit(1);
    };

    _col_all = PQnfields(_res);
    _row_all = PQntuples(_res);

    // * * * * * * * * * * * * * * * * * * * * *

    std::vector<std::vector<std::string>> res_table;

    // one_page_num 每页，第 show_page_no 页
    for (u_int32_t row_index = (show_page_no - 1) * one_page_num, i = 0;
         row_index < _row_all && i < one_page_num; row_index++, i++) {
        std::vector<std::string> row_data;
        for (uint32_t col_index = 0; col_index < _col_all; col_index++)
            row_data.push_back(PQgetvalue(_res, row_index, col_index));
        res_table.push_back(row_data);
    }

    // * * * * * * * * * * * * * * * * * * * * *

    _res = PQexec(_conn, "CLOSE myportal");
    // 关闭游标
    PQclear(_res);

    _res = PQexec(_conn, "END");
    // 事物块结束
    PQclear(_res);

    return res_table;
}