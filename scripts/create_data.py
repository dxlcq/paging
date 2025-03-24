from datetime import datetime, timedelta
import random
import psycopg2

# 连接数据库（postgres）
conn_params = {
    'dbname': 'postgres',  # 默认数据库
    'user': 'postgres',
    'password': 'postgres',
    'host': 'localhost',
    'port': 5432
}

try:
    # 连接到默认数据库
    conn = psycopg2.connect(**conn_params)
    conn.autocommit = True  # 自动提交事务
    cursor = conn.cursor()  # 创建一个游标对象

    # 创建数据库
    cursor.execute("CREATE DATABASE qicstabledata;")
    print("数据库 'qicstabledata' 创建成功。")

    # 连接到新创建的数据库
    conn_params['dbname'] = 'qicstabledata'
    conn = psycopg2.connect(**conn_params)
    cursor = conn.cursor()

    # 创建表结构
    temp = '''
    CREATE TABLE events (
        "编号" SERIAL PRIMARY KEY,
        "时间" TIMESTAMP,
        "地点" CIDR,
        "人物" TEXT,
        "事件" TEXT
    );
    '''
    cursor.execute(temp)
    conn.commit()
    print("表 'events' 创建成功。")

    # 随机生成数据并插入表中
    for _ in range(100):
        time = datetime.now() + timedelta(days=random.randint(-365, 0))
        place = f'192.168.{random.randint(0, 255)}.{random.randint(0, 255)}/32'
        person = random.choice(['林丹', '李宗伟', '石宇奇', '安赛龙', '桃田贤斗'])
        event = random.choice(['打羽毛球', '跑步', '游泳', '健身', '学习'])

        temp = '''
        INSERT INTO events ("时间", "地点", "人物", "事件")
        VALUES (%s, %s, %s, %s);
        '''
        cursor.execute(temp, (time, place, person, event))
        conn.commit()
    print("100 条数据插入成功。")

except psycopg2.Error as e:
    print(f"错误！生成数据时：{e}")
finally:
    if cursor:  # 关闭游标
        cursor.close()
    if conn:    # 关闭连接
        conn.close()