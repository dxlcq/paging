#include <QApplication>

#include "paging_window.h"

// 启动 Qt 应用程序并显示 PagingWindow 窗口
int32_t main(int argc, char *argv[]) {
    auto app = QApplication(argc, argv);
    auto window = PagingWindow();
    return app.exec();
}