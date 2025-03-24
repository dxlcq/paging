#include <gtest/gtest.h>

#include "paging_window.h"

int32_t main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    std::unique_ptr<GetDataService> get_data_service(new GetDataService());

    std::unique_ptr<PagingWindow> paging_window(
        new PagingWindow(get_data_service));

    return RUN_ALL_TESTS();
}