#include "paging_window.h"

#include <QString>
PagingWindow::PagingWindow(std::string conninfo) {
    _pq = new GetData(conninfo);
    auto res = _pq->FetchData(5, 3);

    // 数据模型
    _dm = new QicsDataModelDefault(res.size(), res[0].size());

    // 塞数据
    for (uint32_t row = 0; row < res.size(); row++)
        for (uint32_t col = 0; col < res[row].size(); col++)
            _dm->setItem(row, col,
                         QicsDataString(QString::fromStdString(res[row][col])));

    // 使用数据模型创建表
    _table = new QicsTable(_dm, 0);
    _table->setWindowTitle(QObject::tr("paging 🥳"));

    // 表格大小匹配数据模型
    _table->setVisibleRows(res.size());
    _table->setVisibleColumns(res[0].size());

    // Add a title widget to the top of the table
    // QLabel *label = new QLabel(QObject::tr("Hello World, Table"), _table);
    // label->setAlignment(Qt::AlignCenter);
    //_table->setTopTitleWidget(label);

    _table->activateWindow();
    _table->show();
}
PagingWindow::~PagingWindow() {
    delete _table;
    delete _dm;
}