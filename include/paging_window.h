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
#include <iostream>
#include <memory>
#include "get_data.h"

// 一个分页窗口类
class PagingWindow : public QMainWindow {
    Q_OBJECT
   public:
    PagingWindow(QWidget* parent = nullptr);
    ~PagingWindow();

    // 数据源
    std::unique_ptr<GetData> data_source;
    void UPDATE() {
        _update_table();  // 丑陋
    };

   private:
    QWidget _center_widget;  // 中心部件
    QVBoxLayout _v_layout;   // 垂直布局
    QHBoxLayout _h_layout;   // 水平布局

    std::vector<std::vector<std::string>> _data;  // 数据
    std::unique_ptr<QicsDataModelDefault> _dm;    // 数据模型
    std::unique_ptr<QicsTable> _table;            // 表格

    QLineEdit _table_name;  // 表格名称输入框
    QLineEdit _one_page;    // 设置每页显示的行数
    uint32_t _one_page_num;
    QPushButton _first;     // 首页按钮
    QPushButton _prev;      // 上一页按钮
    QLineEdit _current;     // 当前页码
    uint32_t _current_num;
    QLabel _total;          // 总页数标签
    uint32_t _total_num;
    QPushButton _next;      // 下一页按钮
    QPushButton _last;      // 尾页按钮

    void _update_table();    // 更新表格数据
    void _set_table_name();  // 设置表格名称
    void _set_one_page();    // 设置每页显示的行数
    void _set_first();       // 首页
    void _set_prev();        // 上一页
    void _set_current();     // 跳转到指定页码
    void _set_next();        // 下一页
    void _set_last();        // 尾页
};