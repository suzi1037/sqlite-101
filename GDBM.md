# GDBM

## 管理我的数据之GDBM

He YiJun – storysnail<at>hotmail.com

前言:

GDBM（GNU database
manager）是一套简单的资料管理程序。在大部分的UNIX和Linux系统中已经默认提供，如果没有提供，也可以到官方主http://www.gnu.org.ua/software/gdbm/gdbm.html下载来安装。如果想在windows下使用GDBM，目前有MinGW和cygwin,不过如何使用它们编译gdbm则是另一个话题了，和这篇文章关系不大。如果只是想单纯的使用GDBM，可以使用我做的gdbm-1.8.3
for windows port（windows7 64bits)，可以到https://github.com/storysnail上下载！

一：DBM数据库简介
一般的linux发行版中都会自带了一个符合X/Open技术规范的DBM数据库，这个数据库适合存储相对比较静态的索引化数据。有些人认为DBM根本算不上是个数据库，顶多算是个索引化的文件存储系统，事实也确实如此。DBM原来被称为
DB,最初开发的目的是以新的HASH访问算法来代替旧的hsearch函数和大量的dbm实现,它的第一个发行版出现在1991年，当时还包含了B+树数据访问算法。在1992年，BSD
UNIX-4.4发行版中包含了DB1.85版。大家基本上认为这是DB的第一个正式版。在1996年中期，开源软件公司Sleepycat成立 (http://www.sleepycat.com)
，推出了一个名为”The Berkley Database”的开放源代码的产品并提供商业支持。从这以后，DB得到了广泛的应用，并且出现了很多种分支，例如GDBM。2005年2月15日,甲骨文公司（Oracle
Corporation）收购了开源软件公司Sleepycat，并将The Berkley Database数据库添加到了Oracle嵌入式数据库产品线中。

GDBM是由GNU(http://www.gnu.org)
实现的DBM数据库，其特点是简单、小巧、可靠、高性能,并且已经被移植到了windows平台(http://sourceforge.jp/projects/mingw
/releases/)
。GDBM数据库包含若干条记录，每一个记录由关键字和数据记录（KEY/VALUE）构成。保存在GDBM数据库中的每一个记录都必须有一个独一无二的关键字，数据可以是简单的数据类型，也可以是复杂的数据类型，例如C语言中的结构。技术规范里允许具体实现时把关键字和数据的最大长度限制在1024个字节，但这个限制通常没有什么意义，因为具体实现出来的东西往往比规范更灵活。

二 GDBM的数据类型

GDBM在头文件gdbm.h中定义了两个新的类型：GDBM_FILE和datum.

复制代码
typedef struct {int dummy[10];} *GDBM_FILE;

/* The data and key structure. This structure is defined for compatibility. */

typedef struct {

char *dptr;

int dsize;

} datum;
复制代码

GDBM_FILE类型指向打开的数据库文件。datum是用typedef语句定义的类型，在使用GDBM数据库时，如果想引用一个数据记录，必须先声明一个datum类型的结构，然后让参数dptr指向数据库里数据记录的起始点，把数据记录的长度放在dsize参数里。

下面是错误代码，指出了出错类型，通过gdbm_strerr（）函数可以得到详细的出错信息。

0 GDBM_NO_ERROR No error

1 GDBM_MALLOC_ERROR Malloc error

2 GDBM_BLOCK_SIZE_ERROR Block size error

3 GDBM_FILE_OPEN_ERROR File open error

4 GDBM_FILE_WRITE_ERROR File write error

5 GDBM_FILE_SEEK_ERROR File seek error

6 GDBM_FILE_READ_ERROR File read error

7 GDBM_BAD_MAGIC_NUMBER Bad magic number

8 GDBM_EMPTY_DATABASE Empty database

9 GDBM_CANT_BE_READER Can't be reader

10 GDBM_CANT_BE_WRITER Can't be writer

11 GDBM_READER_CANT_DELETE Reader can't delete

12 GDBM_READER_CANT_STORE Reader can't store

13 GDBM_READER_CANT_REORGANIZE Reader can't reorganize

14 GDBM_UNKNOWN_UPDATE Unknown update

15 GDBM_ITEM_NOT_FOUND Item not found

16 GDBM_REORGANIZE_FAILED Reorganize failed

17 GDBM_CANNOT_REPLACE Cannot replace

18 GDBM_ILLEGAL_DATA Illegal data

19 GDBM_OPT_ALREADY_SET Option already set

20 GDBM_OPT_ILLEGAL Illegal option

三 GDBM数据库的访问函数

1:数据库的创建与打开

创建和打开数据库使用gdbm_open()函数,它返回一个GDBM_FILE类型的指针，指向打开的数据库文件。如果打开失败，则返回NULL。

GDBM_FILE gdbm_open(char *name,int block_size,int read_write,int mode,void (*fatal_func) ())
参数简介：

name:文件名，如果只是文件名，那么文件与程序在同一个目录内。

block_size:指一次从硬盘写到内存的块的大小，最小为512。通常设置为0，这样GDBM将使用文件系统的默认值。

read_write:

GDBM_READER 读模式

GDBM_WRITER 写模式

GDBM_WRCREAT 写模式，如果数据库文件不存在则创建数据库文件

GDBM_NEWDB 写模式，如果数据库文件存在则覆盖原数据库文件

通过"|"操作符还可以改变GDBM数据库的写入操作方式，有下面两种可选:

GDBM_FAST 在写入数据时，数据内容不会立刻保存到磁盘的数据库文件中，而是临时保存在内存里，若想将数据写入数据库文件,必须调用
gdbm_sync()函数. 该参数在gdbm-1.8之后成为默认值。

GDBM_SYNC 写入的数据时，数据内容会立刻保存到磁盘的数据库文件中.

还有一个特别的参数就是下面这个：

GDBM_NOLOCK 通常情况下,在某进程已经打开某数据库文件时, 若有其他进程试图打开该数据库文件的话,就会引发Error,若指定了该标识的话,
就可以同时打开该数据库文件而不会引发Error了.

mode:

S_IRWXU 00700 允许文件的属主读、写和执行文件

S_IRUSR(S_IREAD 00400 允许文件的属主读文件

S_IWUSR(S_IWRITE) 00200 允许文件的属主写文件

S_IXUSR(S_IEXEC) 00100 允许文件的属主执行文件

S_IRWXG 00070 允许文件所在的分组读、写和执行文件

S_IRGRP 00040 允许文件所在的分组读文件

S_IWGRP 00020 允许文件所在的分组写文件

S_IXGRP 00010 允许文件所在的分组执行文件

S_IRWXO 00007 允许其它用户读、写和执行文件

S_IROTH 00004 允许其它用户读文件

S_IWOTH 00002 允许其它用户写文件

S_IXOTH 00001 允许其它用户执行文件

fatal_func 当出错时执行其指向的函数，通常设置为NULL,那样GDBM可以使用自己默认的函数。

示例：

复制代码
GDBM_FILE dbf;

dbf = gdbm_open("mydata.db", 0, GDBM_READER, 0, NULL);

if( dbf == NULL ) {

printf("Can not open database\n, %s\n", gdbm_strerror(gdbm_errno) );

}
复制代码

2:数据库的关闭

关闭已经打开的数据库

void gdbm_close (GDBM_FILE dbf)

参数简介：

dbf:指向数据库文件的指针

示例：

gdbm_close(dbf);

3:数据的存储

GDBM数据库的存储方式是一个关键字对应一条数据记录，关键字类似于数据库中的主键，然而关键字并不一定为数据记录中的字段。GDBM数据库中定义了datum类型，无论是关键字还是数据记录都是以datum类型存储在数据库中的。GDBM不会创建两个一样的关键字；在gdbm_store（）函数中选用GDBM_INSERT参数，如果新数据记录的关键字已经存在，那么会返回1，但新的数据记录不会被插入到数据库中.gdbm_store（）函数成功插入数据会返回0，失败会返回-1.

int gdbm_store (GDBM_FILE dbf,datum key,datum content,int flag)
参数简介：

dbf 指向数据库文件的指针

key 关键字

content: 记录的数据

flag GDBM_INSERT 插入新记录，如果记录已经存在则报错

GDBM_REPLACE 插入新记录，如果记录存在则覆盖

示例：

复制代码
char keybuf[256], databuf[256];

datum key, data;

gets(keybuf);

gets(databuf);

key.dptr = keybuf; key.dsize = strlen(keybuf);

data.dptr = databuf; data.dsize = strlen(databuf);

rc = gdbm_store(dbf, key, data, GDBM_INSERT);

if( rc != 0 ) {

printf("Can not store record\n, %s\n", gdbm_strerror(gdbm_errno) );

}
复制代码

4:读取数据库中的数据记录

根据关键字获取数据库中对应的数据记录.如果在数据库中没有找到关键字，那么返回的datum结构中的dptr将被置空(NULL)
.如果找到了关键字，返回的datum结构中的dptr会指向一段由malloc申请的内存，在使用完这些数据后需要释放。如果你不喜欢free,可以去使用java版的GDBM。

datum gdbm_fetch (GDBM_FILE dbf,datum key)
参数简介：

dbf:指向数据库文件的指针

key:关键字

示例：

复制代码
char keybuf[256];

datum key, data;

gets(keybuf);

key.dptr = keybuf; key.dsize = strlen(keybuf);

data = gdbm_fetch(dbf, key);

if( data.dptr == NULL ) {

puts("Record not found!\n");

}

else {

printf("Record found (%d): %s", data.dsize, data.dptr);

free(data.dptr);

}
复制代码

5:数据的删除

删除一个关键字，注意只是删除了关键字，与该关键字关联的数据记录并没有被删除，如果想删除那个关键字关联的数据记录需要在调用gdbm_delete()
之后调用gdbm_reorganize（）.如果关键字不存在或者文件是使用GDBM_READER参数打开的，那么这个函数会返回-1,成功返回0.

int gdbm_delete (GDBM_FILE dbf,datum key)

参数简介：

dbf:指向数据库文件的指针

key:关键字

示例：

char keybuf[256];

datum key;

gets(keybuf);

key.dptr = keybuf; key.dsize = strlen(keybuf);

rc = gdbm_delete(dbf, key);

if( rc != 0 )

printf("Record can not delete.\n %s", gdbm_strerror(gdbm_errno));

6:数据的遍历

使用这两个函数可以依次遍历数据库中的所有数据记录。如果你使用gdbm_open()函数的GDBM_WRITER(或者类似的)
打开数据库,那么就需要小心操作，确定在遍历所有数据记录的过程中没有改变任何记录，否则会出现不能完全遍历所有数据记录的情况。如果返回的datum结构中的dptr为NULL,则表示已经遍历的所有的数据记录，已经到达数据库末尾了。

datum gdbm_firstkey (GDBM_FILE dbf)

datum gdbm_nextkey (GDBM_FILE dbf,datum key)

参数简介：

dbf:指向数据库文件的指针

key:关键字

示例：

datum key, nextkey;

int n = 1;

puts("Key list:\n");

key = gdbm_firstkey(dbf);

while( key.dptr != NULL ) {

printf("%d: %s", n, key.dptr);

n++;

nextkey = gdbm_nextkey(dbf, key);

free(key.dptr);

key = nextkey;

}

7:其它GDBM函数

在GDBM中, 因为删除所腾出空间将会被留作下次存储,所以删除元素后DB文件体积不会减小. 调用该函数后,
将重新生成数据库文件,这样可以避免浪费存储空间,删除大量数据后, 可以使用该方法来节省磁盘空间.

int gdbm_reorganize (GDBM_FILE dbf)

将元素的变更反映到文件中. 只有在FAST模式时才有效

void gdbm_sync (GDBM_FILE dbf)

检查数据库中是否有指定的关键字，一般会在读取数据库中的数据记录之前使用该函数。关键字存在，返回1，否则返回0.

int gdbm_exists (GDBM_FILE dbf,datum key)

根据给定的错误代码返回一段描述错误的字符串信息

char *gdbm_strerror (gdbm_error errno)

可以使用gdbm_setopt()函数设置GDBM的行为

int gdbm_setopt (GDBM_FILE dbf,int option,int *value,int size)

目前只有两个选项。

GDBM_CACHESIZE 设定GDBM数据库文件的缓存大小，默认值为100.

GDBM_FASTMODE 该选项允许你将GDBM数据库切换到fast mode. 如果fast mode被开启(value置TRUE), GDBM将 不会立刻将数据保存到磁盘的数据库文件中，
直到你调用gdbm_sync()函数才会将数据完全 保存到数据库文件里.

四：一个应用GDBM的例子

下面将使用一个具体的例子gdbm-test.c来说明GDBM的使用

复制代码
#include<gdbm.h>

#include<stdlib.h>

#include<sys/stat.h>

#include<string.h>

#include<stdio.h>

#include<ctype.h>

#define DB_FILE_BLOCK "book_data"

#define ISBN_MAX 13

#define AUTHOR_MAX 50

#define TITLE_MAX 50

#define FILED_MAX 50 /*最宽的数据域 */

/*定义图书结构体 */

typedef struct {

    char isbn[ISBN_MAX + 1];

    char author[AUTHOR_MAX + 1];

    char title[TITLE_MAX + 1];

    int numb;

} book_entry;

char *str_con(char *input, int len)
{

    int count = 0;

    do {

        input[count] = tolower(input[count]);

        count++;

    } while (count <= len);

    return input;

}

int main()
{

    book_entry newbook;    /*创建新的图书记录，并赋值 */

    /*datum结构体有两个成员：dptr指向存储的数据，dsize记录数据的大小 */
    datum key, data;
    GDBM_FILE dbm_ptr;
    char isbnarr[ISBN_MAX + 1] = { 0 };
    char *isbn = isbnarr;

    /*vbook存储数据库中的原始记录，sbook是转换成小写以后的*/
    book_entry vbook, sbook;
    char keyword[FILED_MAX];
    memset(&newbook, '\0', sizeof(newbook));
    strncpy(newbook.isbn, "9787302184942", ISBN_MAX);
    strncpy(newbook.author, "Microsoft Research Asia", AUTHOR_MAX);
    strncpy(newbook.title, "Microsoft's Dream Works", TITLE_MAX);

    newbook.numb = 735;
    key.dptr = (char *)newbook.isbn;    /*用ISBN作key */
    key.dsize = ISBN_MAX;
    data.dptr = (char *)&newbook;    /*用整条数据记录作value */
    data.dsize = sizeof(newbook);
    
    /*打开数据库（跟打开文件很相似），返回数据库句柄 */
    dbm_ptr = gdbm_open(DB_FILE_BLOCK,    /*文件名 */
                0,    /*文件大小，设为0时GDBM将使用文件系统的统计块大小 */
                GDBM_WRCREAT,    /*读写模式。WRCREAT读写，数据库文件不存在时创建,READER读,WRITER写 */
                S_IRUSR | S_IWUSR,    /*权限标志位 */
                NULL);    /*出错时的空参数回调函数 */

    /*把记录存入数据库 */
    gdbm_store(dbm_ptr,    /*数据库句柄 */
           key,        /*key值 */
           data,    /*value值 */
           GDBM_REPLACE);    /*GDBM_INSERT则插入重复记录会出错；GDBM_REPLACE则会覆盖存在的相同记录 */

    /*得到用户的输入，这里只是一个示例，并没考虑缓冲区溢出等问题*/
    puts("请输入你要查询图书的ISBN号:");
    scanf("%s", isbn);
    key.dptr = (char *)isbn;
    key.dsize = ISBN_MAX;
    
    /*读取数据库中的数据记录*/
    data = gdbm_fetch(dbm_ptr, key);

    if (data.dsize == 0)
    {
        printf("查无结果\n");
    }
    else
    {
        memset(&newbook, 0, sizeof(newbook));
        /*将从数据库读到的记录赋给book_entry结构体 */
        memcpy(&newbook, data.dptr, data.dsize);
        printf("%s\t%s\t%s\t%d\n", newbook.isbn, newbook.author,
               newbook.title, newbook.numb);
    }

    /*得到用户的输入*/
    printf("请输入一个关键字开始模糊查询:");
    scanf("%s", keyword);

    for (key = gdbm_firstkey(dbm_ptr); key.dptr;
         key = gdbm_nextkey(dbm_ptr, key)) {

        data = gdbm_fetch(dbm_ptr, key);
        memcpy(&sbook, data.dptr, data.dsize);
        memcpy(&vbook, data.dptr, data.dsize);
        strcpy(keyword, str_con(keyword, FILED_MAX));
        strcpy(sbook.isbn, str_con(sbook.isbn, ISBN_MAX));
        strcpy(sbook.title, str_con(sbook.title, TITLE_MAX));
        strcpy(sbook.author, str_con(sbook.author, AUTHOR_MAX));
        if ((strstr(sbook.isbn, keyword) || strstr(sbook.title, keyword)
             || strstr(sbook.author, keyword))) {
            printf("%s\t%s\t%s\t%d\n", vbook.isbn, vbook.author,
                   vbook.title, vbook.numb);
        } else {
            printf("查无记录\n");
        }

    }

    /*关闭数据库 */
    gdbm_close(dbm_ptr);

    exit(0);

}
复制代码

在windows下用codeblocks的MinGW编译,需要在 Settings->Compiler and debugger settings->Global compiler settings->Linker
settings中的 Other linker options中添加-lgdbm参数。

linux编译gdbm-test.c用下面的命令即可:

gcc -o gdbm-test gdbm-test.c -lgdbm

//有些版本还需要链接一个gdbm_compat库

gcc -o gdbm-test gdbm-test.c -lgdbm -lgdbm_compat