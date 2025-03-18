#pragma once
#include <QicsDataModelDefault.h>
#include <QicsTable.h>

#include <QLabel>

#include "get_data.h"

// 一个分页窗口类
class PagingWindow {
   public:
    PagingWindow(std::string conninfo);
    ~PagingWindow();

   private:
    GetData *_pq;  // 数据获取对象
    QicsDataModel *_dm;  // 数据模型
    QicsTable *_table;   // 表格
};