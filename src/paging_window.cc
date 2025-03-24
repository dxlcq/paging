#include "paging_window.h"

PagingWindow::PagingWindow(QWidget* parent) : QMainWindow(parent) {
    _dm = std::make_unique<QicsDataModelDefault>();
    _table = std::make_unique<QicsTable>(_dm.get(), this);

    // 布局
    this->setCentralWidget(&_center_widget);
    _center_widget.setLayout(&_v_layout);
    _v_layout.addWidget(_table.get());
    _v_layout.addLayout(&_h_layout);
    _h_layout.addWidget(&_table_name);
    _h_layout.addWidget(&_one_page);
    _h_layout.addWidget(&_first);
    _h_layout.addWidget(&_prev);
    _h_layout.addWidget(&_current);
    _h_layout.addWidget(&_total);
    _h_layout.addWidget(&_next);
    _h_layout.addWidget(&_last);

    // 初始化按钮状态
    _table_name.setText("events");
    _one_page.setText("10");
    _one_page_num = 10;
    _first.setText("首页");
    _prev.setText("上一页");
    _current.setText("1");
    _current_num = 1;
    _total.setText("0");
    _total_num = 0;
    _next.setText("下一页");
    _last.setText("尾页");

    connect(&_one_page, &QLineEdit::textChanged, this,
            &PagingWindow::_set_one_page);
    connect(&_current, &QLineEdit::textChanged, this,
            &PagingWindow::_set_current);
    connect(&_first, &QPushButton::clicked, this, &PagingWindow::_set_first);
    connect(&_prev, &QPushButton::clicked, this, &PagingWindow::_set_prev);
    connect(&_next, &QPushButton::clicked, this, &PagingWindow::_set_next);
    connect(&_last, &QPushButton::clicked, this, &PagingWindow::_set_last);
}

PagingWindow::~PagingWindow() {}

void PagingWindow::_update_table() {
    _data = data_source->FetchData(_one_page_num, _current_num,
                                   _table_name.text().toStdString());
    // 更新总的页数
    _total_num =
        (data_source->GetTableRC().first + _one_page_num - 1) / _one_page_num;
    _total.setText(QString::fromStdString(std::to_string(_total_num)));

    // 更新当前页码
    if (_current_num < 1) {
        _current_num = 1;
    } else if (_current_num > _total_num) {
        _current_num = _total_num;
    }
    _current.setText(QString::fromStdString(std::to_string(_current_num)));

    _data = data_source->FetchData(_one_page_num, _current_num,
        _table_name.text().toStdString());

    // dm 更新大小
    if (_dm->numRows() < _data.size())
        _dm->addRows(_data.size() - _dm->numRows());
    else if (_dm->numRows() > _data.size())
        _dm->deleteRows(_dm->numRows() - _data.size(), _data.size());

    if (_dm->numColumns() < _data[0].size())
        _dm->addColumns(_data[0].size() - _dm->numColumns());
    else if (_dm->numColumns() > _data[0].size())
        _dm->deleteColumns(_dm->numColumns() - _data[0].size(),
                           _data[0].size());

    for (size_t i = 0; i < _data.size(); ++i) {
        for (size_t j = 0; j < _data[i].size(); ++j) {
            _dm->setItem(i, j,
                         QicsDataString(QString::fromStdString(_data[i][j])));
        }
    }

    // table 更新数据
    _table->setWindowTitle("🥳 Paging 🎉");
    _table->setVisibleRows(_data.size());
    _table->setVisibleColumns(_data[0].size());
    _table->show();
}

// 设置每页显示的数量，不得 < 1
void PagingWindow::_set_one_page() {
    _one_page_num = _one_page.text().toInt();
    _update_table();
}

// 首页
void PagingWindow::_set_first() {
    _current.setText("1");
    _update_table();
}

// 上一页
void PagingWindow::_set_prev() {
    _current_num--;
    _update_table();
}

// 跳转到指定页码
void PagingWindow::_set_current() {
    _current_num = _current.text().toInt();
    _update_table();
}

// 下一页
void PagingWindow::_set_next() {
    _current_num++;
    _update_table();
}

// 尾页
void PagingWindow::_set_last() {
    _current_num =
        (data_source->GetTableRC().first + _one_page_num - 1) / _one_page_num;
    _update_table();
}

/*
PagingWindow::PagingWindow(QWidget* parent) : QMainWindow(parent) {
    _dm = new QicsDataModelDefault();
    _table = new QicsTable(_dm, this);

    // 更新一手
    _update_table_data();

    _center_widget = new QWidget();        // 中心部件
    _v_layout = new QVBoxLayout();         // 垂直布局
    _h_layout = new QHBoxLayout();         // 水平布局
    _center_widget->setLayout(_v_layout);  // 设置中心部件的布局

    _v_layout->addWidget(_table);     // 将表格添加到布局中
    _v_layout->addLayout(_h_layout);  // 将水平布局添加到垂直布局中

    // 向水平布局中添加按钮
    _first_button = new QPushButton(QObject::tr("首页"));
    _prev_button = new QPushButton(QObject::tr("上一页"));
    _next_button = new QPushButton(QObject::tr("下一页"));
    _last_button = new QPushButton(QObject::tr("尾页"));
    _now_page_edit = new QLineEdit(QObject::tr("1"));
    _now_page_edit->setReadOnly(false);  // 设置为可编辑状态

    _h_layout->addWidget(_first_button);
    _h_layout->addWidget(_prev_button);
    _h_layout->addWidget(_now_page_edit);
    _h_layout->addWidget(_next_button);
    _h_layout->addWidget(_last_button);

    // 槽函数连接
    connect(_first_button, &QPushButton::clicked, this,
            &PagingWindow::_first_page);
    connect(_last_button, &QPushButton::clicked, this,
            &PagingWindow::_last_page);
    connect(_prev_button, &QPushButton::clicked, this,
            &PagingWindow::_prev_page);
    connect(_next_button, &QPushButton::clicked, this,
            &PagingWindow::_next_page);
    connect(_now_page_edit, &QLineEdit::returnPressed, this,
            &PagingWindow::_go_page);

    _center_widget->show();  // 显示中心部件
}

PagingWindow::~PagingWindow() {
    delete _table;
    delete _dm;
}

void PagingWindow::_update_table_data() {
    // auto res = _pq->FetchData(_page_size, _page);  // 获取第一页的数据

    //_now_page_edit->setText(QString::number(_page));  //
    // 设置当前页码输入框的文本

    std::cout << _page << "\n";
    // 无语，这好像是列名
    //_dm->setColumnItems(0, new QicsDataString("ID"));
    //_dm->setColumnItems(1, new QicsDataString("Name"));

    // 貌似只能一个一个加，如果有时间写成函数吧，不然太呆了
    // 行
    /*
    if (_dm->numRows() < res.size()) {
        _dm->addRows(res.size() - _dm->numRows());  // 添加行
    } else if (_dm->numRows() > res.size()) {
        _dm->deleteRows(_dm->numRows() - res.size(), _dm->numRows());  //
删除行
    }
    // 列
    if (_dm->numColumns() < res[0].size()) {
        _dm->addColumns(res[0].size() - _dm->numColumns());  // 添加列
    } else if (_dm->numColumns() > res[0].size()) {
        _dm->deleteColumns(_dm->numColumns() - res[0].size(),
                           _dm->numColumns());  // 删除列
    }

    // 塞数据
    for (uint32_t row = 0; row < res.size(); row++)
        for (uint32_t col = 0; col < res[row].size(); col++)
            _dm->setItem(row, col,
                         QicsDataString(QString::fromStdString(res[row][col])));

    // 创建表
    _table->setWindowTitle(QObject::tr("paging 🥳"));
    _table->setVisibleRows(res.size());
    _table->setVisibleColumns(res[0].size());
    _table->show();
    */
//}

/*
void PagingWindow::_first_page() {
    _page = 1;
    _update_table_data();  // 更新表格数据
}

void PagingWindow::_last_page() {}

void PagingWindow::_go_page() {
    // 获取当前页码输入框的值并更新页码
    _page = stoi(_now_page_edit->text().toStdString());
    // 记得检查！！！

    _update_table_data();  // 更新表格数据
}

void PagingWindow::_prev_page() {
    _page = std::max(int32_t(_page - 1), 1);  // 确保页码不小于1
    _update_table_data();                     // 更新表格数据
}

void PagingWindow::_next_page() {

    _page += 1;
    _update_table_data();  // 更新表格数据
}



*/