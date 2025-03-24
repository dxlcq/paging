#include "get_data.h"

int32_t main(int argc, char **argv) {
    auto get_data = new GetData();
    auto s = get_data->FetchData(6, 6, "events");
    auto table_rc = get_data->GetTableRC();
    std::cout << table_rc.first << " " << table_rc.second << std::endl; // 输出表的行数和列数
    // 打印查询结果
    for (auto &i : s) {
        for(auto &j : i){
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}