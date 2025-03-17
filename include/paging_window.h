#pragma once
#include "get_data.h"

// 一个分页窗口类
class PagingWindow {
   public:
    PagingWindow();
    ~PagingWindow();
   private:
    GetData *pq;    // 数据获取对象
};