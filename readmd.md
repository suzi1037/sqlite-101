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