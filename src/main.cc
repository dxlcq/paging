#include "paging_window.h"

int32_t main(int argc, char* argv[]) {
    auto app = new QApplication(argc, argv);
    auto window = new PagingWindow();
    window->data_source = std::make_unique<GetData>();
    window->UPDATE();
    window->show();
    return app->exec();
}