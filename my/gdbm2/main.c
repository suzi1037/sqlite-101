//
// Created by xiaoxinguo on 2025/4/25.
//
#include <stdio.h>
#include <string.h>
#include <gdbm.h>

int main() {
    GDBM_FILE db;
    char *name = "1.db";
    db = gdbm_open(name, 0, GDBM_WRCREAT, 0666, NULL);
    if (db == NULL) {
        fprintf(stderr, "无法打开数据库: %s\n", gdbm_strerror(gdbm_errno));
        return 1;
    }
    return 0;
}