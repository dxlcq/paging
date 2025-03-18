#pragma once
#include <QicsDataModelDefault.h>
#include <QicsTable.h>

#include <QApplication>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QObject>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

#include "get_data.h"

// 一个分页窗口类
class PagingWindow : public QMainWindow {
    Q_OBJECT
   public:
    PagingWindow(QWidget *parent = nullptr);
    ~PagingWindow();

   private:
    void _update_table_data();  // 更新表格数据

    void _first_page();
    void _last_page();
    void _go_page();
    void _prev_page();
    void _next_page();

    uint32_t _page = 1;        // 当前页码
    uint32_t _page_size = 10;  // 每页显示的记录数

    GetData *_pq;        // 数据获取对象
    QicsDataModel *_dm;  // 数据模型
    QicsTable *_table;   // 表格

    QWidget *_center_widget;  // 中心部件
    QVBoxLayout *_v_layout;   // 垂直布局
    QHBoxLayout *_h_layout;   // 水平布局

    QPushButton *_prev_button;   // 上一页按钮
    QPushButton *_next_button;   // 下一页按钮
    QLineEdit *_now_page_edit;   // 页码输入框
    QPushButton *_first_button;  // 首页按钮
    QPushButton *_last_button;   // 尾页按钮
};