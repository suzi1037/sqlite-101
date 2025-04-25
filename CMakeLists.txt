cmake_minimum_required(VERSION 2.8.4)
project(SQLite_f37dd18e3f C)

set(CMAKE_C_STANDARD 11)

include_directories(build)
include_directories(my/demo1)
include_directories(my/gdbm)
include_directories(my/gdbm2)
include_directories(sqlite/src)
include_directories(sqlite/tool)


add_executable(SQLite_f37dd18e3f
        build/lempar.c
        build/parse.c
        build/parse.h
        build/sqlite.h
        my/demo1/main.c
        my/gdbm/gbdm.h
        my/gdbm/gdbm_example.c
        my/gdbm2/main.c
        sqlite/src/build.c
        sqlite/src/dbbe.c
        sqlite/src/dbbe.h
        sqlite/src/delete.c
        sqlite/src/expr.c
        sqlite/src/insert.c
        sqlite/src/main.c
        sqlite/src/select.c
        sqlite/src/shell.c
        sqlite/src/sqliteInt.h
        sqlite/src/tclsqlite.c
        sqlite/src/tokenize.c
        sqlite/src/update.c
        sqlite/src/util.c
        sqlite/src/vdbe.c
        sqlite/src/vdbe.h
        sqlite/src/where.c
        sqlite/tool/gdbmdump.c
        sqlite/tool/lemon.c
        sqlite/tool/lempar.c)
