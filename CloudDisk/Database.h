#pragma once
#include <mysql/mysql.h>

typedef struct {
    MYSQL* conn;
    int is_connected;
} Database;

// 初始化数据库连接
int db_init(Database* db, const char* host, const char* user, const char* passwd, const char* db_name, unsigned int port);

// 关闭数据库连接
void db_close(Database* db);

// 执行查询，返回结果集 (需调用 db_free_result 释放)
MYSQL_RES* db_query(Database* db, const char* sql);

// 执行非查询语句 (INSERT, UPDATE, DELETE)
int db_execute(Database* db, const char* sql);

// 释放结果集
void db_free_result(MYSQL_RES* result);

// 获取错误信息
const char* db_error(Database* db);
