################################################################################
##
##  Tool-definitions
##
################################################################################

#
#   Macros used by the make file to invoke specific build tools.
#

#   Macro for the C++ compiler.
CPP = g++

#   Macro for the archive utility.
AR = ar


################################################################################
################################################################################
##
##  Configuration directories
##
################################################################################
################################################################################

INSTALL_DIR = /usr/bin

MYSQL_INC_DIR = -I/usr/include/mysql
MYSQL_LIB_DIR = -L/usr/lib/x86_64-linux-gnu

POSTGRESQL_INC_DIR = -I/usr/include/postgresql
POSTGRESQL_LIB_DIR =


################################################################################
################################################################################
##
##  Build-time configuration options. Disabling language features in this
##  section affects the files that are compiled when building the interreter.
##  This is useful for run-time libraries that require external ependencies,
##  such as the database module, allowing you to build the interpreter when the
##  MySQL or PostgreSQL libraries are not present.
##
################################################################################
################################################################################

#   Compile support for File I/O functions.
COMP_LIB_FILEIO = 1


#   Compile support for string functions.
COMP_LIB_STRING = 1


#   Compile support for date/time functions.
COMP_LIB_DATETIME = 1


#   Compile support for core math functions.
COMP_LIB_MATH_CORE = 1


#   Compile support for trigonometric math functions.
COMP_LIB_MATH_TRIG = 1


#   Compile support for hyperbolic math functions.
COMP_LIB_MATH_HYPERBOLIC = 1


#   Compile support for random math functions.
COMP_LIB_MATH_RANDOM = 1


#   Compile support for complex math functions.
COMP_LIB_MATH_COMPLEX = 1


#   Compile support for matrix math functions.
COMP_LIB_MATH_MATRIX = 1


#   Compile support for integer math functions.
COMP_LIB_MATH_INTEGER = 1


#   Compile support for text I/O (curses) functions.
COMP_LIB_TEXTIO = 1


#   Compile support for network functions.
COMP_LIB_NETWORK = 1


#   Compile support for file-system functions.
COMP_LIB_FILESYS = 1


#   Compile support for text debug functions.
COMP_LIB_DEBUG = 1


#   Compile support for MySQL into the interpreter. Requires the installation
#   of the MySQL database on the build environment.
#COMP_LIB_DB_MYSQL = 1


#   Compile support for PostgreSQL into the interpreter. Requires
#
#       sudo apt-get install libpq-dev
#
#   in Ubuntu/Mint linux.
#COMP_LIB_DB_POSTGRESQL = 1


#   Compile support for regular expressions into the interpreter. Requires regex
#   support in the C++ 2011 STL, so g++ v4.9 or later.
#COMP_LIB_REGEX = 1


#   Compile support for serial communications (RS-232).
#COMP_LIB_RS232 = 1


#   Compile support for graphics. Requires X11 headers and libraries to be
#   installed.
COMP_LIB_GRAPHICS = 1


#   Compile support for the extended colorset. Extends LIB_GRAPHICS.
COMP_LIB_GRAPHICS_ALL_COLORS = 1


#   Compile support for array-zipping.
COMP_LIB_ZIP = 1


################################################################################
################################################################################
##
##  Compile-time configuration options. These options control the internal
##  behavior of the interpreter but should not affect the run-time *behavior* of
##  the interpreter (run-time performance may be impacted, however).
##
################################################################################
################################################################################

#
#   One of COMP_SYMTAB_HASH_FUNC_WHOLE_ID, COMP_SYMTAB_HASH_FUNC_PARTIAL_ID, or
#   COMP_SYMTAB_HASH_FUNC_MULTI_BYTE must be defined in the makefile to specify
#   how the hashed-symbol table hashes an identifier. See the implementation of
#   dish::HashedSymbolTable::h() in symtab.cpp for more detail.
#
#COMP_SYMTAB_HASH_FUNC_MULTI_BYTE = 1
#COMP_SYMTAB_HASH_FUNC_WHOLE_ID = 1
COMP_SYMTAB_HASH_FUNC_PARTIAL_ID = 1
#COMP_SYMTAB_HASH_FUNC_HASHED_WHOLE_ID = 1
#COMP_SYMTAB_HASH_FUNC_HASHED_PARTIAL_ID = 1
COMP_SYMTAB_HASH_FUNC_PARTIAL_ID_SPREAD = 1


#
#   Either COMP_LANG_TABLE_HASHED or COMP_LANG_TABLE_BASIC must be defined in
#   the makefile to specify which type of symbol table will be used for the
#   language table and global namespace table.
#
COMP_LANG_TABLE_HASHED = 1
#COMP_LANG_TABLE_BASIC = 1

#
#   Define the makefile macro COMP_LIST_TYPE_PREFER_VECTOR if the build should
#   prefer to use std::vector over std::list. Use of std::vector may be of
#   slight bennefit with respect to run-time at the expense of wasting some
#   memory. If you define this macro, define it to be an integer that will be
#   the reserved-size of vectors when constructed.
#
COMP_LIST_TYPE_PREFER_VECTOR=6

#
#   Select the size of atomic values used at runtime, either 32- or 64-bit. This
#   affects the types that are wrapped up in the atomic classes (Booleans, 
#   Integers, and Reals) in atomics.h and atomics.cpp.
#
#COMP_LANG_ATOMOIC_SIZE_32BIT = 1
COMP_LANG_ATOMOIC_SIZE_64BIT = 1


################################################################################
################################################################################
##
##  Compile-time optimization options.
##
################################################################################
################################################################################

#
#   Control function/method inlining.
#

#   Aggressively prevent inlining. In practice this dramatically increases the
#   size of the executable. I have not looked into this but suspect is has to do
#   with declaring all C-style functions as static (to avoid duplicate-symbol
#   errors), resulting in multiple copies of those functions in the executable.
#COMP_PREVENT_INLINE = 1

#   Aggressively inline functions and methods within the dish interpreter.
#   Enabling aggressive-inlining may increase the size of the executable.
COMP_AGGRESSIVE_INLINE = 1

################################################################################

#   Enable the reuse of primitive objects. NOTE: This optimization is still 
#   under development and may result in an error when the interpreter
#   terminates!
#COMP_RECYCLE_PRIMITIVES = 1

#   Enable the recycling of symbol-tables within StackedSymbolTable.
#COMP_RECYCLE_SYMBOL_TABLES = 1


################################################################################
################################################################################
##
##  Compile-time debug options.
##
################################################################################
################################################################################

#   Enable trace information to be printed while parsing.
#COMP_DEBUG_TRACE = 1


################################################################################
################################################################################
##
##  Compile-time build options
##
################################################################################
################################################################################

#
#   Whether or not a MAP file is to be generated during the build.
#

MAPFILE =
MAPFILE += -Wl,-Map=dish.map


#
#   Whether or not support for the gprof profiler will be compiled and linked
#   into the dish executable.
#

PROFILE =
PROFILE += -pg


#
#   Whether or not debug information should be built into the dish executable.
#

DEBUG =
#DEBUG += -g --param=max-vartrack-size=2000000000


#
#   Control the optimizations that are applied when building the dish
#   executable. Optimizations are specified in the following manners:
#

#   Select the compiler's optimization level:
#OPTIMIZATIONS = -O0
OPTIMIZATIONS = -O4
#OPTIMIZATIONS = -Os


##
###############################################################
##
################################################################################
################################################################################
################################################################################
##
##  What follows are the build rules for the interpreter and libraries; there
##  should be no need to modify anything below this point.
##
################################################################################
################################################################################
################################################################################
##
###############################################################
##

################################################################################
##
##  Build the rules for contructing dishconfig.h based on the macros defined
##  earlier in this makefile.
##
################################################################################

CONFIG = CONFIG_FILE_HEADER


################################################################################
##
##  Configure the symbol table's hash function. 
##
################################################################################

ifdef COMP_SYMTAB_HASH_FUNC_MULTI_BYTE
CONFIG += CONFIG_SYMTAB_HASH_FUNC_MULTI_BYTE
endif

ifdef COMP_SYMTAB_HASH_FUNC_WHOLE_ID
CONFIG += CONFIG_SYMTAB_HASH_FUNC_WHOLE_ID
endif

ifdef COMP_SYMTAB_HASH_FUNC_PARTIAL_ID
CONFIG += CONFIG_SYMTAB_HASH_FUNC_PARTIAL_ID
endif

ifdef COMP_SYMTAB_HASH_FUNC_HASHED_WHOLE_ID
CONFIG += CONFIG_SYMTAB_HASH_FUNC_HASHED_WHOLE_ID
endif

ifdef COMP_SYMTAB_HASH_FUNC_HASHED_PARTIAL_ID
CONFIG += CONFIG_SYMTAB_HASH_FUNC_HASHED_PARTIAL_ID
endif

ifdef COMP_SYMTAB_HASH_FUNC_PARTIAL_ID_SPREAD
CONFIG += CONFIG_SYMTAB_HASH_FUNC_PARTIAL_ID_SPREAD
endif


################################################################################
##
##  Configure the language's symbol-table-type. 
##
################################################################################

ifdef COMP_LANG_TABLE_HASHED
CONFIG += CONFIG_LANG_TABLE_HASHED
endif

ifdef COMP_LANG_TABLE_BASIC
CONFIG += CONFIG_LANG_TABLE_BASIC
endif


################################################################################
##
##  Should vectors be preferred over lists? 
##
################################################################################

ifdef COMP_LIST_TYPE_PREFER_VECTOR
CONFIG += CONFIG_LIST_TYPE_PREFER_VECTOR
endif


################################################################################
##
##  Configure the language's atomic-type size. 
##
################################################################################

ifdef COMP_LANG_ATOMOIC_SIZE_32BIT
CONFIG += CONFIG_LANG_ATOMOIC_SIZE_32BIT
endif

ifdef COMP_LANG_ATOMOIC_SIZE_64BIT
CONFIG += CONFIG_LANG_ATOMOIC_SIZE_64BIT
endif


################################################################################
##
##  Configure the builds' optimizations.
##
################################################################################

ifdef COMP_PREVENT_INLINE
OPTIMIZATIONS += -fno-inline
CONFIG += CONFIG_PREVENT_INLINE
endif

ifdef COMP_AGGRESSIVE_INLINE
CONFIG += CONFIG_AGGRESSIVE_INLINE
endif

ifdef COMP_RECYCLE_PRIMITIVES
CONFIG += CONFIG_RECYCLE_PRIMITIVES
endif

ifdef COMP_RECYCLE_SYMBOL_TABLES
CONFIG += CONFIG_RECYCLE_SYMBOL_TABLES
endif


################################################################################
##
##  Configure the run-time libraries that will be available to dish programs
##  based on the configuration above (the makefile macros that begin with
##  COMP_LIB_). 
##
################################################################################

#   Compile the core run-time library into the Dish interpreter. NOTE: The core
#   run-time library *MUST* be compiled into the interpreter for the definition
#   of the Inc functions, which are required for for-loops.
CONFIG += CONFIG_LIB_CORE

ifdef COMP_LIB_FILEIO
CONFIG += CONFIG_LIB_FILEIO
endif

ifdef COMP_LIB_STRING
CONFIG += CONFIG_LIB_STRING
endif

ifdef COMP_LIB_DATETIME
CONFIG += CONFIG_LIB_DATETIME
endif

ifdef COMP_LIB_MATH_CORE
CONFIG += CONFIG_LIB_MATH_CORE
endif

ifdef COMP_LIB_MATH_TRIG
CONFIG += CONFIG_LIB_MATH_TRIG
endif

ifdef COMP_LIB_MATH_HYPERBOLIC
CONFIG += CONFIG_LIB_MATH_HYPERBOLIC
endif

ifdef COMP_LIB_MATH_RANDOM
CONFIG += CONFIG_LIB_MATH_RANDOM
endif

ifdef COMP_LIB_MATH_COMPLEX
CONFIG += CONFIG_LIB_MATH_COMPLEX
endif

ifdef COMP_LIB_MATH_MATRIX
CONFIG += CONFIG_LIB_MATH_MATRIX
endif

ifdef COMP_LIB_MATH_INTEGER
CONFIG += CONFIG_LIB_MATH_INTEGER
endif

ifdef COMP_LIB_TEXTIO
CONFIG += CONFIG_LIB_TEXTIO
endif

ifdef COMP_LIB_NETWORK
CONFIG += CONFIG_LIB_NETWORK
endif

ifdef COMP_LIB_FILESYS
CONFIG += CONFIG_LIB_FILESYS
endif

ifdef COMP_LIB_DEBUG
CONFIG += CONFIG_LIB_DEBUG
endif

ifdef COMP_LIB_DB_MYSQL
CONFIG += CONFIG_LIB_DATABASE
else ifdef COMP_LIB_DB_POSTGRESQL
CONFIG += CONFIG_LIB_DATABASE
endif

ifdef COMP_LIB_DB_MYSQL
CONFIG += CONFIG_LIB_DB_MYSQL
endif

ifdef COMP_LIB_DB_POSTGRESQL
CONFIG += CONFIG_LIB_DB_POSTGRESQL
endif

ifdef COMP_LIB_REGEX
CONFIG += CONFIG_LIB_REGULAR_EXPRESSION
endif

ifdef COMP_LIB_RS232
CONFIG += CONFIG_LIB_RS232
endif

ifdef COMP_LIB_GRAPHICS
CONFIG += CONFIG_LIB_GRAPHICS
endif

ifdef COMP_LIB_GRAPHICS_ALL_COLORS
CONFIG += CONFIG_LIB_GRAPHICS_ALL_COLORS
endif

ifdef COMP_LIB_ZIP
CONFIG += CONFIG_LIB_ZIP
endif

CONFIG += CONFIG_FILE_TRAILER

#
#   Build the compiler flags.
#
CFLAGS =
CFLAGS = -fPIC -std=c++11 -Wall
CFLAGS += $(PROFILE)
CFLAGS += $(DEBUG)
CFLAGS += $(OPTIMIZATIONS)

#
#   Build the linker flags.
#
LFLAGS =
LFLAGS += $(MAPFILE)
LFLAGS += $(PROFILE)

#
#   Add the targets necessary to build the interpreter. Targets needed for some 
#   functionality are only included if the support is requested earlier in this 
#   makefile to reduce externl dependencies to only those that are absolutely
#   necessary for the requested functionality.
#
#   Targets are built in alphabetical order except for the main language symbol-
#   table, located in language.o. This file is built first because it can take a
#   long time to compile when optimizations are applied and its compile-time can 
#   be amortized over the build-time of the other targets when building in a
#   multi-processor environment (pass the -j <# CPUs> option to make).
#
BINS =

BINS += language.o
BINS += atomicops.o
BINS += atomics.o
BINS += cmdln.o
    
ifdef COMP_LIB_DB_MYSQL
BINS += db.o
else ifdef COMP_LIB_DB_POSTGRESQL
BINS += db.o
endif

ifdef COMP_LIB_DB_MYSQL
BINS += dbmysql.o
endif

ifdef COMP_LIB_DB_POSTGRESQL
BINS += dbpostgresql.o
endif

BINS += exception.o
BINS += graph.o
BINS += input.o
BINS += langcore.o
    
ifdef COMP_LIB_DB_MYSQL
BINS += langdb.o
else ifdef COMP_LIB_DB_POSTGRESQL
BINS += langdb.o
endif

ifdef COMP_LIB_DEBUG
BINS += langdebug.o
endif

BINS += langerr.o

ifdef COMP_LIB_FILEIO
BINS += langfile.o
endif

ifdef COMP_LIB_FILESYS
BINS += langfilesys.o
endif

ifdef COMP_LIB_GRAPHICS
BINS += langgraph.o
endif

BINS += langio.o

ifdef COMP_LIB_MATH_CORE
BINS += langmath.o
else ifdef COMP_LIB_MATH_TRIG
BINS += langmath.o
else ifdef COMP_LIB_MATH_HYPERBOLIC
BINS += langmath.o
else ifdef COMP_LIB_MATH_RANDOM
BINS += langmath.o
else ifdef COMP_LIB_MATH_COMPLEX
BINS += langmath.o
else ifdef COMP_LIB_MATH_MATRIX
BINS += langmath.o
else ifdef COMP_LIB_MATH_INTEGER
BINS += langmath.o
endif

ifdef COMP_LIB_NETWORK
BINS += langnet.o
endif

ifdef COMP_LIB_REGEX    
BINS += langregex.o
endif

ifdef COMP_LIB_RS232
BINS += langrs232.o
endif

ifdef COMP_LIB_STRING
BINS += langstr.o
endif

ifdef COMP_LIB_DATETIME
BINS += langtime.o
endif

ifdef COMP_LIB_TEXTIO
BINS += langtxtio.o
endif

ifdef COMP_LIB_ZIP
BINS += langzip.o
endif

BINS += log.o
BINS += parser.o
BINS += pldish.o
BINS += profile.o
BINS += ptnode.o
BINS += symtab.o
BINS += textio.o
BINS += tokenizer.o
BINS += types.o
BINS += utility.o
BINS += version.o

################################################################################

LIBS = -lm

ifdef COMP_LIB_TEXTIO
    LIBS += -lncurses
endif

ifdef COMP_LIB_GRAPHICS
    LIBS += -lX11
endif

################################################################################

TARGETS = dish libdish.a libshdish.so

################################################################################
 
#
#   CFlags for building the application. This information is obtained from the
#   following command-lines: 
#
#       $ mysql_config --cflags
#   
#   and
#
#       $ mysql_config --libs
#
MYSQL_CFLAGS =
ifdef COMP_LIB_DB_MYSQL
    MYSQL_CFLAGS    += $(MYSQL_INC_DIR)
    MYSQL_CFLAGS    += -DBIG_JOINS=1 -fno-strict-aliasing

    LFLAGS          += $(MYSQL_LIB_DIR)
	LIBS            += -lmysqlclient
endif

#
#   CFLags for building the application. This information is obtained from the
#   following command-line:
#
#       $ pg_config
#
POSTGRES_CFLAGS =
ifdef COMP_LIB_DB_POSTGRESQL
    POSTGRES_CFLAGS += $(POSTGRESQL_INC_DIR)
    POSTGRES_CFLAGS += --param=ssp-buffer-size=4 -pie -DLINUX_OOM_SCORE_ADJ=0 -fno-omit-frame-pointer -fwrapv -fstack-protector -fno-strict-aliasing

    LFLAGS          += $(POSTGRESQL_LIB_DIR)
	LIBS            += -lpq
endif

################################################################################


.PHONY: all
all : $(TARGETS)

.PHONY: clean
clean :
	rm -f ../bin/dish
	rm -f ../bin/libdish.a
	rm -f ../bin/libshdish.so
	rm -f *.o
	rm -f dish.map
	rm -f gmon.out
	rm -f *~
	
.PHONY: cleanall
cleanall: clean
	rm -f dishconfig.h
	
.PHONY: config
config : CONFIG_FILE_CLEAN $(CONFIG)

.PHONY: help
help:
	@echo
	@echo "Description of the build-rules supported by the makefile."
	@echo
	@echo "make all         : Build all dish targets: the interpreter and shared- and static-libraries."
	@echo "make clean       : Remove the object files and targets, forcing a complete rebuild of all targets."
	@echo "make config      : Build dishconfig.h based on the configiuration settings in the makefile."
	@echo "make help        : Display basic help information (this screen)."
	@echo -n "make install     : Build all targets and copy the interpreter to "
	@echo $(INSTALL_DIR)
	@echo -n "make remove      : Remove the object files and targets, including from "
	@echo $(INSTALL_DIR)
	@echo "make rundemo     : Build and install the interpreter, and run the demo app."
	@echo

.PHONY: install
install : all
	cp -f ../bin/dish $(INSTALL_DIR)

.PHONY: remove
remove : clean
	rm -f $(INSTALL_DIR)/dish
    
rundemo : all
	../bin/dish -I../dishsrc/game/ game.dish -allowcheats

################################################################################
##
##  Targets: rules to build the binary targets
##
################################################################################

dish : dishconfig.h $(BINS) main.o
	$(CPP) $(LFLAGS) $(DB_LFLAGS) -o dish main.o $(BINS) $(LIBS)
	mkdir -p ../bin
	mv dish ../bin
	
libdish.a : dishconfig.h $(BINS) librarydep.o
	$(AR) rcs libdish.a $(BINS) librarydep.o
	mkdir -p ../bin
	mv libdish.a ../bin
	
libshdish.so : dishconfig.h $(BINS) librarydep.o
	$(CPP) -shared -o libshdish.so $(BINS) librarydep.o
	mkdir -p ../bin
	mv libshdish.so ../bin


################################################################################
##
##  Headers: rule to build the default configuration header file
##
################################################################################
	
dishconfig.h:
	@echo "#ifndef DISH_CONFIG_H" >> dishconfig.h
	@echo "#define DISH_CONFIG_H" >> dishconfig.h
	@echo >> dishconfig.h
	@echo "#error Need to run 'make config' first to build dishconfig.h." >> dishconfig.h
	@echo >> dishconfig.h
	@echo "#endif" >> dishconfig.h
	@echo >> dishconfig.h


################################################################################
##
##  Binaries: rules to build individual obj files
##
################################################################################

atomicops.o : atomicops.cpp
	$(CPP) -c $(CFLAGS) atomicops.cpp

atomics.o : atomics.cpp
	$(CPP) -c $(CFLAGS) atomics.cpp

cmdln.o : cmdln.cpp
	$(CPP) -c $(CFLAGS) cmdln.cpp

db.o : db.cpp
	$(CPP) -c $(MYSQL_CFLAGS) $(POSTGRES_CFLAGS) $(CFLAGS) db.cpp

dbmysql.o : dbmysql.cpp
	$(CPP) -c $(MYSQL_CFLAGS) $(CFLAGS) dbmysql.cpp

dbpostgresql.o : dbpostgresql.cpp
	$(CPP) -c $(POSTGRES_CFLAGS) $(CFLAGS) dbpostgresql.cpp

exception.o : exception.cpp
	$(CPP) -c $(CFLAGS) exception.cpp

graph.o : graph.cpp
	$(CPP) -c $(CFLAGS) graph.cpp

input.o : input.cpp
	$(CPP) -c $(CFLAGS) input.cpp

langcore.o : langcore.cpp
	$(CPP) -c $(CFLAGS) langcore.cpp

langdb.o : langdb.cpp
	$(CPP) -c $(CFLAGS) langdb.cpp

langdebug.o : langdebug.cpp
	$(CPP) -c $(CFLAGS) langdebug.cpp

langerr.o : langerr.cpp
	$(CPP) -c $(CFLAGS) langerr.cpp

langfile.o : langfile.cpp
	$(CPP) -c $(CFLAGS) langfile.cpp

langfilesys.o : langfilesys.cpp
	$(CPP) -c $(CFLAGS) langfilesys.cpp

langgraph.o : langgraph.cpp
	$(CPP) -c $(CFLAGS) langgraph.cpp

langio.o : langio.cpp
	$(CPP) -c $(CFLAGS) langio.cpp

langmath.o : langmath.cpp
	$(CPP) -c $(CFLAGS) langmath.cpp

langnet.o : langnet.cpp
	$(CPP) -c $(CFLAGS) langnet.cpp

langregex.o : langregex.cpp
	$(CPP) -c $(CFLAGS) langregex.cpp
	
langrs232.o : langrs232.cpp
	$(CPP) -c $(CFLAGS) langrs232.cpp

langstr.o : langstr.cpp
	$(CPP) -c $(CFLAGS) langstr.cpp

langtime.o : langtime.cpp
	$(CPP) -c $(CFLAGS) langtime.cpp

langtxtio.o : langtxtio.cpp
	$(CPP) -c $(CFLAGS) langtxtio.cpp

langzip.o : langzip.cpp
	$(CPP) -c $(CFLAGS) langzip.cpp

language.o : language.cpp
	$(CPP) -c $(CFLAGS) language.cpp

librarydep.o : librarydep.cpp
	$(CPP) -c $(CFLAGS) librarydep.cpp

log.o : log.cpp
	$(CPP) -c $(CFLAGS) log.cpp

main.o : main.cpp
	$(CPP) -c $(CFLAGS) main.cpp
	
parser.o : parser.cpp
	$(CPP) -c $(CFLAGS) parser.cpp
	
pldish.o : pldish.cpp
	$(CPP) -c $(CFLAGS) pldish.cpp

profile.o : profile.cpp
	$(CPP) -c $(CFLAGS) profile.cpp

ptnode.o : ptnode.cpp
	$(CPP) -c $(CFLAGS) ptnode.cpp

symtab.o : symtab.cpp
	$(CPP) -c $(CFLAGS) symtab.cpp

textio.o : textio.cpp
	$(CPP) -c $(CFLAGS) textio.cpp

tokenizer.o : tokenizer.cpp
	$(CPP) -c $(CFLAGS) tokenizer.cpp

types.o : types.cpp
	$(CPP) -c $(CFLAGS) types.cpp

utility.o : utility.cpp
	$(CPP) -c $(CFLAGS) utility.cpp

version.o : version.cpp
	$(CPP) -c $(CFLAGS) version.cpp


################################################################################
##
##  Config: rules to build dishconfig.h based on the configuration in this
##          makefile.
##
################################################################################

.PHONY: CONFIG_FILE_CLEAN
CONFIG_FILE_CLEAN:
	rm -f dishconfig.h
	
.PHONY: CONFIG_FILE_HEADER
CONFIG_FILE_HEADER:
	@echo "Generating dishconfig.h..."
	@echo "/*" >> dishconfig.h
	@echo -n "    This file was auto-generated on " >> dishconfig.h
	@date >> dishconfig.h
	@echo "*/" >> dishconfig.h
	@echo "#ifndef DISH_CONFIG_H" >> dishconfig.h
	@echo "#define DISH_CONFIG_H" >> dishconfig.h
	
################################################################################
	
.PHONY: CONFIG_SYMTAB_HASH_FUNC_MULTI_BYTE
CONFIG_SYMTAB_HASH_FUNC_MULTI_BYTE:
	@echo >> dishconfig.h
	@echo "    #ifndef SYMTAB_HASH_FUNC_MULTI_BYTE" >> dishconfig.h
	@echo "        #define SYMTAB_HASH_FUNC_MULTI_BYTE" >> dishconfig.h
	@echo "    #endif" >> dishconfig.h
	
.PHONY: CONFIG_SYMTAB_HASH_FUNC_WHOLE_ID
CONFIG_SYMTAB_HASH_FUNC_WHOLE_ID:
	@echo >> dishconfig.h
	@echo "    #ifndef SYMTAB_HASH_FUNC_WHOLE_ID" >> dishconfig.h
	@echo "        #define SYMTAB_HASH_FUNC_WHOLE_ID" >> dishconfig.h
	@echo "    #endif" >> dishconfig.h
	
.PHONY: CONFIG_SYMTAB_HASH_FUNC_PARTIAL_ID
CONFIG_SYMTAB_HASH_FUNC_PARTIAL_ID:
	@echo >> dishconfig.h
	@echo "    #ifndef SYMTAB_HASH_FUNC_PARTIAL_ID" >> dishconfig.h
	@echo "        #define SYMTAB_HASH_FUNC_PARTIAL_ID" >> dishconfig.h
	@echo "    #endif" >> dishconfig.h
	
.PHONY: CONFIG_SYMTAB_HASH_FUNC_HASHED_WHOLE_ID
CONFIG_SYMTAB_HASH_FUNC_HASHED_WHOLE_ID:
	@echo >> dishconfig.h
	@echo "    #ifndef SYMTAB_HASH_FUNC_HASHED_WHOLE_ID" >> dishconfig.h
	@echo "        #define SYMTAB_HASH_FUNC_HASHED_WHOLE_ID" >> dishconfig.h
	@echo "    #endif" >> dishconfig.h

.PHONY: CONFIG_SYMTAB_HASH_FUNC_HASHED_PARTIAL_ID
CONFIG_SYMTAB_HASH_FUNC_HASHED_PARTIAL_ID:
	@echo >> dishconfig.h
	@echo "    #ifndef SYMTAB_HASH_FUNC_HASHED_PARTIAL_ID" >> dishconfig.h
	@echo "        #define SYMTAB_HASH_FUNC_HASHED_PARTIAL_ID" >> dishconfig.h
	@echo "    #endif" >> dishconfig.h

.PHONY: CONFIG_SYMTAB_HASH_FUNC_PARTIAL_ID_SPREAD
CONFIG_SYMTAB_HASH_FUNC_PARTIAL_ID_SPREAD:
	@echo >> dishconfig.h
	@echo "    #ifndef SYMTAB_HASH_FUNC_PARTIAL_ID_SPREAD" >> dishconfig.h
	@echo "        #define SYMTAB_HASH_FUNC_PARTIAL_ID_SPREAD" >> dishconfig.h
	@echo "    #endif" >> dishconfig.h
	
################################################################################
	
.PHONY: CONFIG_LANG_TABLE_HASHED	
CONFIG_LANG_TABLE_HASHED:
	@echo >> dishconfig.h
	@echo "    #ifndef LANG_TABLE_HASHED" >> dishconfig.h
	@echo "        #define LANG_TABLE_HASHED" >> dishconfig.h
	@echo "    #endif" >> dishconfig.h
	
.PHONY: CONFIG_LANG_TABLE_BASIC	
CONFIG_LANG_TABLE_BASIC:
	@echo >> dishconfig.h
	@echo "    #ifndef LANG_TABLE_BASIC" >> dishconfig.h
	@echo "        #define LANG_TABLE_BASIC" >> dishconfig.h
	@echo "    #endif" >> dishconfig.h
	
################################################################################
	
.PHONY: CONFIG_LIST_TYPE_PREFER_VECTOR
CONFIG_LIST_TYPE_PREFER_VECTOR:
	@echo >> dishconfig.h
	@echo "    #ifndef LIST_TYPE_PREFER_VECTOR" >> dishconfig.h
	@echo -n "        #define LIST_TYPE_PREFER_VECTOR " >> dishconfig.h
	@echo $(COMP_LIST_TYPE_PREFER_VECTOR) >> dishconfig.h
	@echo "    #endif" >> dishconfig.h
	
################################################################################
	
.PHONY: CONFIG_LANG_ATOMOIC_SIZE_32BIT
CONFIG_LANG_ATOMOIC_SIZE_32BIT:
	@echo >> dishconfig.h
	@echo "    #ifndef DISH_32BIT_ATOMICS" >> dishconfig.h
	@echo "        #define DISH_32BIT_ATOMICS" >> dishconfig.h
	@echo "    #endif" >> dishconfig.h
	
.PHONY: CONFIG_LANG_ATOMOIC_SIZE_64BIT
CONFIG_LANG_ATOMOIC_SIZE_64BIT:
	@echo >> dishconfig.h
	@echo "    #ifndef DISH_64BIT_ATOMICS" >> dishconfig.h
	@echo "        #define DISH_64BIT_ATOMICS" >> dishconfig.h
	@echo "    #endif" >> dishconfig.h
	
################################################################################
	
.PHONY: CONFIG_PREVENT_INLINE
CONFIG_PREVENT_INLINE:
	@echo >> dishconfig.h
	@echo "    #ifndef PREVENT_INLINE" >> dishconfig.h
	@echo "        #define PREVENT_INLINE" >> dishconfig.h
	@echo "    #endif" >> dishconfig.h
	
.PHONY: CONFIG_AGGRESSIVE_INLINE
CONFIG_AGGRESSIVE_INLINE:
	@echo >> dishconfig.h
	@echo "    #ifndef AGGRESSIVE_INLINE" >> dishconfig.h
	@echo "        #define AGGRESSIVE_INLINE" >> dishconfig.h
	@echo "    #endif" >> dishconfig.h
	
.PHONY: CONFIG_RECYCLE_PRIMITIVES
CONFIG_RECYCLE_PRIMITIVES:
	@echo >> dishconfig.h
	@echo "    #ifndef RECYCLE_PRIMITIVES" >> dishconfig.h
	@echo "        #define RECYCLE_PRIMITIVES" >> dishconfig.h
	@echo "    #endif" >> dishconfig.h
	
.PHONY: CONFIG_RECYCLE_SYMBOL_TABLES
CONFIG_RECYCLE_SYMBOL_TABLES:
	@echo >> dishconfig.h
	@echo "    #ifndef RECYCLE_SYMBOL_TABLES" >> dishconfig.h
	@echo "        #define RECYCLE_SYMBOL_TABLES" >> dishconfig.h
	@echo "    #endif" >> dishconfig.h
	
################################################################################
	
.PHONY: CONFIG_DEBUG_TRACE
CONFIG_DEBUG_TRACE:
	@echo >> dishconfig.h
	@echo "    #ifndef TRACE" >> dishconfig.h
	@echo "        #define TRACE" >> dishconfig.h
	@echo "    #endif" >> dishconfig.h
	
################################################################################
	
.PHONY: CONFIG_LIB_CORE
CONFIG_LIB_CORE:
	@echo >> dishconfig.h
	@echo "    #ifndef LANG_LIB_CORE" >> dishconfig.h
	@echo "        #define LANG_LIB_CORE" >> dishconfig.h
	@echo "    #endif" >> dishconfig.h

.PHONY: CONFIG_LIB_FILEIO
CONFIG_LIB_FILEIO:
	@echo >> dishconfig.h
	@echo "    #ifndef LANG_LIB_FILEIO" >> dishconfig.h
	@echo "        #define LANG_LIB_FILEIO" >> dishconfig.h
	@echo "    #endif" >> dishconfig.h

.PHONY: CONFIG_LIB_STRING
CONFIG_LIB_STRING:
	@echo >> dishconfig.h
	@echo "    #ifndef LANG_LIB_STRING" >> dishconfig.h
	@echo "        #define LANG_LIB_STRING" >> dishconfig.h
	@echo "    #endif" >> dishconfig.h

.PHONY: CONFIG_LIB_DATETIME
CONFIG_LIB_DATETIME:
	@echo >> dishconfig.h
	@echo "    #ifndef LANG_LIB_DATETIME" >> dishconfig.h
	@echo "        #define LANG_LIB_DATETIME" >> dishconfig.h
	@echo "    #endif" >> dishconfig.h

.PHONY: CONFIG_LIB_MATH_CORE
CONFIG_LIB_MATH_CORE:
	@echo >> dishconfig.h
	@echo "    #ifndef LANG_LIB_MATH_CORE" >> dishconfig.h
	@echo "        #define LANG_LIB_MATH_CORE" >> dishconfig.h
	@echo "    #endif" >> dishconfig.h

.PHONY: CONFIG_LIB_MATH_TRIG
CONFIG_LIB_MATH_TRIG:
	@echo >> dishconfig.h
	@echo "    #ifndef LANG_LIB_MATH_TRIG" >> dishconfig.h
	@echo "        #define LANG_LIB_MATH_TRIG" >> dishconfig.h
	@echo "    #endif" >> dishconfig.h

.PHONY: CONFIG_LIB_MATH_HYPERBOLIC
CONFIG_LIB_MATH_HYPERBOLIC:
	@echo >> dishconfig.h
	@echo "    #ifndef LANG_LIB_MATH_HYPERBOLIC" >> dishconfig.h
	@echo "        #define LANG_LIB_MATH_HYPERBOLIC" >> dishconfig.h
	@echo "    #endif" >> dishconfig.h

.PHONY: CONFIG_LIB_MATH_RANDOM
CONFIG_LIB_MATH_RANDOM:
	@echo >> dishconfig.h
	@echo "    #ifndef LANG_LIB_MATH_RANDOM" >> dishconfig.h
	@echo "        #define LANG_LIB_MATH_RANDOM" >> dishconfig.h
	@echo "    #endif" >> dishconfig.h

.PHONY: CONFIG_LIB_MATH_COMPLEX
CONFIG_LIB_MATH_COMPLEX:
	@echo >> dishconfig.h
	@echo "    #ifndef LANG_LIB_MATH_COMPLEX" >> dishconfig.h
	@echo "        #define LANG_LIB_MATH_COMPLEX" >> dishconfig.h
	@echo "    #endif" >> dishconfig.h

.PHONY: CONFIG_LIB_MATH_MATRIX
CONFIG_LIB_MATH_MATRIX:
	@echo >> dishconfig.h
	@echo "    #ifndef LANG_LIB_MATH_MATRIX" >> dishconfig.h
	@echo "        #define LANG_LIB_MATH_MATRIX" >> dishconfig.h
	@echo "    #endif" >> dishconfig.h

.PHONY: CONFIG_LIB_MATH_INTEGER
CONFIG_LIB_MATH_INTEGER:
	@echo >> dishconfig.h
	@echo "    #ifndef LANG_LIB_MATH_INTEGER" >> dishconfig.h
	@echo "        #define LANG_LIB_MATH_INTEGER" >> dishconfig.h
	@echo "    #endif" >> dishconfig.h

.PHONY: CONFIG_LIB_TEXTIO
CONFIG_LIB_TEXTIO:
	@echo >> dishconfig.h
	@echo "    #ifndef LANG_LIB_TEXTIO" >> dishconfig.h
	@echo "        #define LANG_LIB_TEXTIO" >> dishconfig.h
	@echo "    #endif" >> dishconfig.h

.PHONY: CONFIG_LIB_NETWORK
CONFIG_LIB_NETWORK:
	@echo >> dishconfig.h
	@echo "    #ifndef LANG_LIB_NETWORK" >> dishconfig.h
	@echo "        #define LANG_LIB_NETWORK" >> dishconfig.h
	@echo "    #endif" >> dishconfig.h

.PHONY: CONFIG_LIB_FILESYS
CONFIG_LIB_FILESYS:
	@echo >> dishconfig.h
	@echo "    #ifndef LANG_LIB_FILESYS" >> dishconfig.h
	@echo "        #define LANG_LIB_FILESYS" >> dishconfig.h
	@echo "    #endif" >> dishconfig.h

.PHONY: CONFIG_LIB_DEBUG
CONFIG_LIB_DEBUG:
	@echo >> dishconfig.h
	@echo "    #ifndef LANG_LIB_DEBUG" >> dishconfig.h
	@echo "        #define LANG_LIB_DEBUG" >> dishconfig.h
	@echo "    #endif" >> dishconfig.h
	
.PHONY: CONFIG_LIB_DB_MYSQL
CONFIG_LIB_DB_MYSQL:
	@echo >> dishconfig.h
	@echo "    #ifndef LIB_DB_MYSQL" >> dishconfig.h
	@echo "        #define LIB_DB_MYSQL" >> dishconfig.h
	@echo "    #endif" >> dishconfig.h
	@echo >> dishconfig.h
	@echo "    #ifndef MYSQLDB" >> dishconfig.h
	@echo "        #define MYSQLDB" >> dishconfig.h
	@echo "    #endif" >> dishconfig.h
	
.PHONY: CONFIG_LIB_DB_POSTGRESQL
CONFIG_LIB_DB_POSTGRESQL:
	@echo >> dishconfig.h
	@echo "    #ifndef LIB_DB_POSTGRESQL" >> dishconfig.h
	@echo "        #define LIB_DB_POSTGRESQL" >> dishconfig.h
	@echo "    #endif" >> dishconfig.h
	@echo >> dishconfig.h
	@echo "    #ifndef POSTGRESQLDB" >> dishconfig.h
	@echo "        #define POSTGRESQLDB" >> dishconfig.h
	@echo "    #endif" >> dishconfig.h

.PHONY: CONFIG_LIB_DATABASE
CONFIG_LIB_DATABASE:
	@echo >> dishconfig.h
	@echo "    #ifndef LANG_LIB_DATABASE" >> dishconfig.h
	@echo "        #define LANG_LIB_DATABASE" >> dishconfig.h
	@echo "    #endif" >> dishconfig.h

.PHONY: CONFIG_LIB_REGULAR_EXPRESSION
CONFIG_LIB_REGULAR_EXPRESSION:
	@echo >> dishconfig.h
	@echo "    #ifndef LANG_LIB_REGULAR_EXPRESSION" >> dishconfig.h
	@echo "        #define LANG_LIB_REGULAR_EXPRESSION" >> dishconfig.h
	@echo "    #endif" >> dishconfig.h

.PHONY: CONFIG_LIB_RS232
CONFIG_LIB_RS232:
	@echo >> dishconfig.h
	@echo "    #ifndef LANG_LIB_RS232" >> dishconfig.h
	@echo "        #define LANG_LIB_RS232" >> dishconfig.h
	@echo "    #endif" >> dishconfig.h

.PHONY: CONFIG_LIB_GRAPHICS
CONFIG_LIB_GRAPHICS:
	@echo >> dishconfig.h
	@echo "    #ifndef LANG_LIB_GRAPH" >> dishconfig.h
	@echo "        #define LANG_LIB_GRAPH" >> dishconfig.h
	@echo "    #endif" >> dishconfig.h

.PHONY: CONFIG_LIB_GRAPHICS_ALL_COLORS
CONFIG_LIB_GRAPHICS_ALL_COLORS:
	@echo >> dishconfig.h
	@echo "    #ifndef LANG_LIB_GRAPH_ALL_COLORS" >> dishconfig.h
	@echo "        #define LANG_LIB_GRAPH_ALL_COLORS" >> dishconfig.h
	@echo "    #endif" >> dishconfig.h

.PHONY: CONFIG_LIB_ZIP
CONFIG_LIB_ZIP:
	@echo >> dishconfig.h
	@echo "    #ifndef LANG_LIB_ZIP" >> dishconfig.h
	@echo "        #define LANG_LIB_ZIP" >> dishconfig.h
	@echo "    #endif" >> dishconfig.h

################################################################################

.PHONY: CONFIG_FILE_TRAILER
CONFIG_FILE_TRAILER:
	@echo >> dishconfig.h
	@echo '    #include "verifyconfig.h"' >> dishconfig.h
	@echo >> dishconfig.h
	@echo "#endif" >> dishconfig.h
	@echo >> dishconfig.h
	@echo "Done."

