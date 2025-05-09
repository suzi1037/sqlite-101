# Generated automatically from Makefile.in by configure.
#!/usr/make
#
# Makefile for SQLITE

# The toplevel directory of the source tree
#
TOP = ../sqlite

# C Compiler and options for use in building executables that
# will run on the platform that is doing the build.
#
BCC = clang -std=c89

# C Compile and options for use in building executables that 
# will run on the target platform.
#
TCC = clang -std=c89 -DOS_UNIX=1 -DOS_WIN=0 -DHAVE_USLEEP=1 -I. -I${TOP}/src

# Tools used to build a static library.
#
AR = ar cr
RANLIB = ranlib

# Compiler options needed for programs that use the GDBM library.
#
GDBM_FLAGS = 

# The library that programs using GDBM must link against.
#
LIBGDBM = -lgdbm 

# Compiler options needed for programs that use the TCL library.
#
TCL_FLAGS = 

# The library that programs using TCL must link against.
#
LIBTCL = -ltcl  -ldl -lm

# Compiler options needed for programs that use the readline() library.
#
READLINE_FLAGS = -DHAVE_READLINE=1 -I/usr/include/readline

# The library that programs using readline() must link against.
#
LIBREADLINE = -lreadline 

# Object files for the SQLite library.
#
LIBOBJ = build.o dbbe.o delete.o expr.o insert.o \
         main.o parse.o select.o tokenize.o update.o \
         util.o vdbe.o where.o

# All of the source code files.
#
SRC = \
  $(TOP)/src/build.c \
  $(TOP)/src/dbbe.c \
  $(TOP)/src/dbbe.h \
  $(TOP)/src/delete.c \
  $(TOP)/src/expr.c \
  $(TOP)/src/insert.c \
  $(TOP)/src/main.c \
  $(TOP)/src/parse.y \
  $(TOP)/src/select.c \
  $(TOP)/src/shell.c \
  $(TOP)/src/sqlite.h.in \
  $(TOP)/src/sqliteInt.h \
  $(TOP)/src/tclsqlite.c \
  $(TOP)/src/tokenize.c \
  $(TOP)/src/update.c \
  $(TOP)/src/util.c \
  $(TOP)/src/vdbe.c \
  $(TOP)/src/vdbe.h \
  $(TOP)/src/where.c

# This is the default Makefile target.  The objects listed here
# are what get build when you type just "make" with no arguments.
#
all:	sqlite.h libsqlite.a sqlite 

# Generate the file "last_change" which contains the date of change
# of the most recently modified source code file
#
last_change:	$(SRC)
	cat $(SRC) | grep '$$Id: ' | sort +4 | tail -1 \
          | awk '{print $$5,$$6}' >last_change

libsqlite.a:	$(LIBOBJ)
	$(AR) libsqlite.a $(LIBOBJ)
	$(RANLIB) libsqlite.a

sqlite:	$(TOP)/src/shell.c libsqlite.a sqlite.h
	$(TCC) $(READLINE_FLAGS) -o sqlite $(TOP)/src/shell.c \
		libsqlite.a $(LIBGDBM) $(LIBREADLINE)

# Rules to build the LEMON compiler generator
#
lemon:	$(TOP)/tool/lemon.c $(TOP)/tool/lempar.c
	$(BCC) -o lemon $(TOP)/tool/lemon.c
	cp $(TOP)/tool/lempar.c .

# Header files used by all library source files.
#
HDR = \
   sqlite.h  \
   $(TOP)/src/sqliteInt.h  \
   $(TOP)/src/dbbe.h  \
   $(TOP)/src/vdbe.h  \
   parse.h

build.o:	$(TOP)/src/build.c $(HDR)
	$(TCC) $(GDBM_FLAGS) -c $(TOP)/src/build.c

dbbe.o:	$(TOP)/src/dbbe.c $(HDR)
	$(TCC) $(GDBM_FLAGS) -c $(TOP)/src/dbbe.c

main.o:	$(TOP)/src/main.c $(HDR)
	$(TCC) $(GDBM_FLAGS) -c $(TOP)/src/main.c

parse.o:	parse.c $(HDR)
	$(TCC) $(GDBM_FLAGS) -c parse.c

parse.h:	parse.c

parse.c:	$(TOP)/src/parse.y lemon
	cp $(TOP)/src/parse.y .
	./lemon parse.y

sqlite.h:	$(TOP)/src/sqlite.h.in
	sed s/--VERS--/`cat ${TOP}/VERSION`/ $(TOP)/src/sqlite.h.in >sqlite.h

tokenize.o:	$(TOP)/src/tokenize.c $(HDR)
	$(TCC) $(GDBM_FLAGS) -c $(TOP)/src/tokenize.c

util.o:	$(TOP)/src/util.c $(HDR)
	$(TCC) $(GDBM_FLAGS) -c $(TOP)/src/util.c

vdbe.o:	$(TOP)/src/vdbe.c $(HDR)
	$(TCC) $(GDBM_FLAGS) -c $(TOP)/src/vdbe.c

where.o:	$(TOP)/src/where.c $(HDR)
	$(TCC) $(GDBM_FLAGS) -c $(TOP)/src/where.c

delete.o:	$(TOP)/src/delete.c $(HDR)
	$(TCC) $(GDBM_FLAGS) -c $(TOP)/src/delete.c

expr.o:	$(TOP)/src/expr.c $(HDR)
	$(TCC) $(GDBM_FLAGS) -c $(TOP)/src/expr.c

insert.o:	$(TOP)/src/insert.c $(HDR)
	$(TCC) $(GDBM_FLAGS) -c $(TOP)/src/insert.c

select.o:	$(TOP)/src/select.c $(HDR)
	$(TCC) $(GDBM_FLAGS) -c $(TOP)/src/select.c

update.o:	$(TOP)/src/update.c $(HDR)
	$(TCC) $(GDBM_FLAGS) -c $(TOP)/src/update.c

gdbmdump:	$(TOP)/tool/gdbmdump.c
	$(TCC) $(GDBM_FLAGS) -o gdbmdump $(TOP)/tool/gdbmdump.c $(LIBGDBM)

tclsqlite:	$(TOP)/src/tclsqlite.c libsqlite.a
	$(TCC) $(TCL_FLAGS) -DTCLSH=1 -o tclsqlite \
		$(TOP)/src/tclsqlite.c libsqlite.a $(LIBGDBM) $(LIBTCL)

test:	tclsqlite sqlite
	./tclsqlite $(TOP)/test/all.test

sqlite.tar.gz:	
	pwd=`pwd`; cd $(TOP)/..; tar czf $$pwd/sqlite.tar.gz sqlite

index.html:	$(TOP)/www/index.tcl sqlite.tar.gz last_change
	tclsh $(TOP)/www/index.tcl `cat $(TOP)/VERSION` >index.html

sqlite.html:	$(TOP)/www/sqlite.tcl
	tclsh $(TOP)/www/sqlite.tcl >sqlite.html

c_interface.html:	$(TOP)/www/c_interface.tcl
	tclsh $(TOP)/www/c_interface.tcl >c_interface.html

changes.html:	$(TOP)/www/changes.tcl
	tclsh $(TOP)/www/changes.tcl >changes.html

fileformat.html:	$(TOP)/www/fileformat.tcl
	tclsh $(TOP)/www/fileformat.tcl >fileformat.html

lang.html:	$(TOP)/www/lang.tcl
	tclsh $(TOP)/www/lang.tcl >lang.html

vdbe.html:	$(TOP)/www/vdbe.tcl
	tclsh $(TOP)/www/vdbe.tcl >vdbe.html

arch.html:	$(TOP)/www/arch.tcl
	tclsh $(TOP)/www/arch.tcl >arch.html

arch.png:	$(TOP)/www/arch.png
	cp $(TOP)/www/arch.png .

opcode.html:	$(TOP)/www/opcode.tcl $(TOP)/src/vdbe.c
	tclsh $(TOP)/www/opcode.tcl $(TOP)/src/vdbe.c >opcode.html

crosscompile.html:	$(TOP)/www/crosscompile.tcl
	tclsh $(TOP)/www/crosscompile.tcl >crosscompile.html

mingw.html:	$(TOP)/www/mingw.tcl
	tclsh $(TOP)/www/mingw.tcl >mingw.html


# Files to be published on the website.
#
PUBLISH = \
  sqlite.tar.gz \
  index.html \
  sqlite.html \
  changes.html \
  fileformat.html \
  lang.html \
  opcode.html \
  arch.html \
  arch.png \
  vdbe.html \
  c_interface.html \
  crosscompile.html \
  mingw.html

website:	$(PUBLISH)

publish:	$(PUBLISH)
	chmod 0644 $(PUBLISH)
	scp $(PUBLISH) hwaci@oak.he.net:public_html/sw/sqlite

clean:	
	rm -f *.o sqlite libsqlite.a sqlite.h
	rm -f lemon lempar.c parse.* sqlite.tar.gz
	rm -f $(PUBLISH)
	rm -f *.da *.bb *.bbg gmon.out
