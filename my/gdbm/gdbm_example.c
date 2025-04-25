#include <stdio.h>
#include <string.h>
#include "gdbm.h"

int main() {
    GDBM_FILE db;
    datum key, value;
    char *db_file = "example.db";

    // 打开或创建数据库（读写模式，若不存在则创建）
    db = gdbm_open(db_file, 0, GDBM_WRCREAT, 0666, NULL);
    if (db == NULL) {
        fprintf(stderr, "无法打开数据库: %s\n", gdbm_strerror(gdbm_errno));
        return 1;
    }

    // 存储键值对
    key.dptr = "name";
    key.dsize = strlen(key.dptr) + 1;
    value.dptr = "Alice";
    value.dsize = strlen(value.dptr) + 1;

    if (gdbm_store(db, key, value, GDBM_REPLACE) != 0) {
        fprintf(stderr, "存储失败: %s\n", gdbm_strerror(gdbm_errno));
    } else {
        printf("存储成功: %s -> %s\n", key.dptr, value.dptr);
    }

    // 检索键值对
    key.dptr = "name";
    key.dsize = strlen(key.dptr) + 1;
    value = gdbm_fetch(db, key);

    if (value.dptr != NULL) {
        printf("检索到: %s -> %s\n", key.dptr, value.dptr);
        free(value.dptr); // 释放检索到的值
    } else {
        printf("键 %s 未找到\n", key.dptr);
    }

    // 删除键值对
    if (gdbm_delete(db, key) == 0) {
        printf("成功删除键: %s\n", key.dptr);
    } else {
        printf("删除失败: %s\n", gdbm_strerror(gdbm_errno));
    }

    // 关闭数据库
    gdbm_close(db);
    return 0;
}