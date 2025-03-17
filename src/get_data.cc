#include <stdio.h>
#include <stdlib.h>

#include "libpq-fe.h"

#include "get_data.h"

// 只做连接
GetData::GetData() {
};

GetData::~GetData() {};

/*
int main(int argc, char **argv) {
    const char *conninfo;  // 连接信息
    PGconn *conn;          // 用于数据库连接
    PGresult *res;         // 用于查询结果

    if (argc > 1)
        conninfo = argv[1];
    else
        conninfo =
            "host=localhost port=5432 dbname = qicstabledata user=postgres "
            "password=postgres";

    /* 建立一个到数据库的连接 */
    conn = PQconnectdb(conninfo);

    /* 如果连接失败，输出错误信息并退出程序 */
    if (PQstatus(conn) != CONNECTION_OK) {
        fprintf(stderr, "%s", PQerrorMessage(conn));
        exit_nicely(conn);
    }

    /* 设置总是安全的搜索路径，因此恶意用户无法控制 */
    res =
        PQexec(conn, "SELECT pg_catalog.set_config('search_path', '', false)");
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        fprintf(stderr, "SET failed: %s", PQerrorMessage(conn));
        PQclear(res);
        exit_nicely(conn);
    }

    /* 当使用完 PGresult 后，应该调用 PQclear 以避免内存泄漏 */
    PQclear(res);

    /* 开始一个事务块 */
    res = PQexec(conn, "BEGIN");
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        fprintf(stderr, "BEGIN command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        exit_nicely(conn);
    }
    PQclear(res);

    /*
     * 搞一个游标 myportal  出来
     */
    res = PQexec(conn, "DECLARE myportal CURSOR FOR select * from public.events");
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        fprintf(stderr, "DECLARE CURSOR failed: %s", PQerrorMessage(conn));
        PQclear(res);
        exit_nicely(conn);
    }
    PQclear(res);

    /*
     * 从游标中获取数据
     */
    res = PQexec(conn, "FETCH ALL in myportal");
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        fprintf(stderr, "FETCH ALL failed: %s", PQerrorMessage(conn));
        PQclear(res);
        exit_nicely(conn);
    }

    /*
     ******************************************** 暂时只需要关注这里
     */

    int nCols = PQnfields(res);     // 列数
    int nRows = PQntuples(res);     // 行数
    
    for (int i = 0; i < nCols; i++) printf("%-15s", PQfname(res, i));
    printf("\n");
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++)
            printf("%-30s ", PQgetvalue(res, i, j));
        printf("\n");
    }
    PQclear(res);

    /*
     ********************************************
     */

    /* 关闭游标 ... 不关心错误检查？ ... */
    res = PQexec(conn, "CLOSE myportal");
    PQclear(res);

    /* 结束一个事务块 */
    res = PQexec(conn, "END");
    PQclear(res);

    /* 关闭数据库 */
    PQfinish(conn);

    return 0;
}
*/