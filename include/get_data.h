#pragma once

#include "libpq-fe.h"

class GetData {
   public:
    GetData();
    ~GetData();
    void fetchData();

   private:
    void exit_nicely(){
        PQfinish(_conn);
        exit(1);
    }

    const char *_conninfo;  // 数据库连接信息
    PGconn *_conn;          // 数据库连接对象
    PGresult *_res;         // 查询结果集
};