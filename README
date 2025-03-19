**分页**

前端使用 Qt(with qicstable)，后端使用 PostgreSQL

1. 示例数据

    **数据库名称**: `qicstabledata`

    **表结构**: `events`

    | 字段名   | 数据类型   |
    |:-:|:-:|
    | 时间     | `timestamp` |
    | 地点     | `cidr`     |
    | 人物     | `text`     |
    | 事件     | `text`     |

    **示例数据**:

    | 时间                | 地点           | 人物   | 事件       |
    |:-:|:-:|:-:|:-:|
    | 2025-03-17 09:49:17 | 192.168.1.1/32 | 林丹   | 打羽毛球   |
    | 2025-03-01 10:00:00 | 192.168.1.2/32 | 李宗伟 | 打羽毛球   |


2. postgreSQL

    ```bash
    sudo docker run --rm -e POSTGRES_PASSWORD=postgres -d -p 5432:5432 postgres
    ```

3. 通过 `CreateData.py` 随机生成数据

    ```bash
    # 需要安装 psycopg2 库
    python3 tools/CreateData.py
    ```

4. 运行 `paging` 程序