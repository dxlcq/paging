#include "get_data.h"

#include <stdio.h>
#include <stdlib.h>

void GetData::errif(bool condition) const {
    if (condition) {
        std::cerr << PQerrorMessage(_conn) << std::endl;
        PQclear(_res);
        PQfinish(_conn);
        exit(1);
    }
}

GetData::GetData(std::string conninfo) {
    _conn = PQconnectdb(conninfo.c_str());
    // 连接
    if (CONNECTION_OK != PQstatus(_conn)) {
        std::cerr << PQerrorMessage(_conn) << std::endl;
        PQfinish(_conn);
        exit(1);
    }

    // 安全
    _res =
        PQexec(_conn, "SELECT pg_catalog.set_config('search_path', '', false)");
    errif(PGRES_TUPLES_OK != PQresultStatus(_res));
    PQclear(_res);
}

GetData::~GetData() {
    // 断开连接
    PQfinish(_conn);
};

const std::vector<std::vector<std::string>>& GetData::FetchData(
    const uint32_t one_page_num,
    const uint32_t show_page_no,
    const std::string& table_name) {
    // 开始事务块
    _res = PQexec(_conn, "BEGIN");
    errif(PGRES_COMMAND_OK != PQresultStatus(_res));
    PQclear(_res);

    // 查询
    std::string query =
        "DECLARE myportal CURSOR FOR SELECT count(*) FROM public." + table_name;
    _res = PQexec(_conn, query.c_str());
    errif(PGRES_COMMAND_OK != PQresultStatus(_res));
    PQclear(_res);

    // 获取游标中的所有数据
    _res = PQexec(_conn, "FETCH ALL IN myportal");
    errif(PGRES_TUPLES_OK != PQresultStatus(_res));
    _table_rc.first = std::stoi(PQgetvalue(_res, 0, 0));  // 表的行数
    PQclear(_res);

    // 关闭游标
    _res = PQexec(_conn, "CLOSE myportal");
    PQclear(_res);

    // 查询
    query = "DECLARE myportal CURSOR FOR SELECT * FROM public." + table_name +
            " LIMIT " + std::to_string(one_page_num) +
            " OFFSET " + std::to_string((show_page_no - 1) * one_page_num);
    // 上面的 query 存在借位！！
    _res = PQexec(_conn, query.c_str());
    errif(PGRES_COMMAND_OK != PQresultStatus(_res));
    PQclear(_res);

    // 获取游标中的所有数据
    _res = PQexec(_conn, "FETCH ALL IN myportal");
    errif(PGRES_TUPLES_OK != PQresultStatus(_res));

    _table_rc.second = PQnfields(_res);  // 表的列数
    // 重置结果集大小
    _res_table.resize(PQntuples(_res) + 1);  // 行
    for (auto& c : _res_table)
        c.resize(PQnfields(_res));  // 列

    // 获取列名
    for (auto j = 0; j < _table_rc.second; ++j)
        _res_table[0][j] = std::string(PQfname(_res, j));

    // 获取数据
    for (auto i = 0; i + 1 < _res_table.size(); ++i) {
        for (auto j = 0; j < _res_table[i].size(); ++j)
            _res_table[i + 1][j] = std::string(PQgetvalue(_res, i, j));
    }
    PQclear(_res);

    // 关闭游标
    _res = PQexec(_conn, "CLOSE myportal");
    PQclear(_res);

    // 事物块结束
    _res = PQexec(_conn, "END");
    PQclear(_res);

    return _res_table;
}