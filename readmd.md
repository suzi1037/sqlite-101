#

https://stackoverflow.com/questions/55791432/how-to-compile-sqlite-1-0-1-which-released-18-years-ago

```text
docker pull fedora:36
docker run -dt --name f36 --cap-add=SYS_PTRACE --security-opt seccomp=unconfined fedora:36
docker exec -it f36 bash
dnf update -y
dnf install -y ncurses git hostname clang diffutils readline-devel tcl-devel gdbm-devel
mkdir ~/src && cd ~/src
git clone https://github.com/ruomeng0x/sqlite.git
cd ~/src/sqlite
git checkout badcc1d968fdb7cf0ff5d89468248468b8329f4e
mkdir ../build && cd ../build
CC=clang CFLAGS="-std=c89" bash ../sqlite/configure
make
```

# 

https://xie.infoq.cn/article/0582eb62e5de75a4e54a92be6

SQLite 的作者 D. Richard Hipp 失业在家，凭借着之前构建编译器的经验，实现了一个不需要服务器的数据库引擎。这就是 SQLite 的第一版。

GDBM 衍生自 DBM，而 DBM（DataBase Manager 的缩写）是来自 Unix 的键值数据库（key-value database），支持通过主键快速访问数据，最初由计算机界的大佬
Ken Thompson 编写。

## SQLite 第一版的架构

如下图所示，SQLite 采用了典型的分层架构，一条 SQL 语句依次经过

用户接口（UI）层 →

词法分析器（Tokenizer）层 →

语法解析器（Parser）层 →

字节码生成器（Code Generator）层 →

虚拟机（虚拟数据库引擎〔Virtual DataBase Engine〕）层 →

数据库后端（DataBase BackEnd〔DBBE〕）层

最终到达 GDBM 数据库层，变为对 GDBM 数据库的 CRUD（通过调用 GDBM 提供的 API）。