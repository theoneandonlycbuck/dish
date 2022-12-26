I.      Introduction

dish is a simple, interpreted programming language suitable for many 
applications, including learning basic programming concepts or integration into
another application. It is loosely typed and supports a rich run-time library
that includes terminal I/O, mathematical functions, file I/O, and much more.


II.     Directory Structure

The disk interpreter comes in the following directories:

	\dish\dishsrc		Contains example code for the dish programming language.
	\dish\dishsrc\game	Contains a simple game written in dish.
	\dish\doc		    Contains documentation for the dish programming language, 
                        interpreter, and libraries needed by an application
                        incorporating the interpreter. (This is a work-in-
                        progress.)
	\dish\pldish		Contains examples for embedding the dish interpreter in
                        another application.
	\dish\src		    Contains the source files (.h and .cpp) needed to build
                        the dish interpreter and libraries needed by an
                        application incorporating the interpreter, and the 
                        makefile.


III.    Building the Interpreter

A makefile is located in the same directory as all of the source files,
\dish\src. A stripped-down configuration of the interpreter, including support
for terminal I/O, accessing files, is present so you can get started
immediately. Navigate into the \dish\src directory and type:

~/dish/src $ make
rm -f ../bin/dish
rm -f ../bin/libdish.a
rm -f ../bin/libshdish.so
rm -f *.o
rm -f dish.map
rm -f gmon.out
rm -f *~
g++ -c -fPIC -std=c++11 -Wall  -pg  -O4 language.cpp
g++ -c -fPIC -std=c++11 -Wall  -pg  -O4 atomicops.cpp
g++ -c -fPIC -std=c++11 -Wall  -pg  -O4 atomics.cpp
g++ -c -fPIC -std=c++11 -Wall  -pg  -O4 cmdln.cpp
g++ -c -fPIC -std=c++11 -Wall  -pg  -O4 exception.cpp
g++ -c -fPIC -std=c++11 -Wall  -pg  -O4 graph.cpp
g++ -c -fPIC -std=c++11 -Wall  -pg  -O4 input.cpp
g++ -c -fPIC -std=c++11 -Wall  -pg  -O4 langcore.cpp
g++ -c -fPIC -std=c++11 -Wall  -pg  -O4 langdebug.cpp
g++ -c -fPIC -std=c++11 -Wall  -pg  -O4 langerr.cpp
g++ -c -fPIC -std=c++11 -Wall  -pg  -O4 langfile.cpp
g++ -c -fPIC -std=c++11 -Wall  -pg  -O4 langfilesys.cpp
g++ -c -fPIC -std=c++11 -Wall  -pg  -O4 langgraph.cpp
g++ -c -fPIC -std=c++11 -Wall  -pg  -O4 langio.cpp
g++ -c -fPIC -std=c++11 -Wall  -pg  -O4 langmath.cpp
g++ -c -fPIC -std=c++11 -Wall  -pg  -O4 langnet.cpp
g++ -c -fPIC -std=c++11 -Wall  -pg  -O4 langstr.cpp
g++ -c -fPIC -std=c++11 -Wall  -pg  -O4 langtime.cpp
g++ -c -fPIC -std=c++11 -Wall  -pg  -O4 langtxtio.cpp
g++ -c -fPIC -std=c++11 -Wall  -pg  -O4 langzip.cpp
g++ -c -fPIC -std=c++11 -Wall  -pg  -O4 log.cpp
g++ -c -fPIC -std=c++11 -Wall  -pg  -O4 parser.cpp
g++ -c -fPIC -std=c++11 -Wall  -pg  -O4 pldish.cpp
g++ -c -fPIC -std=c++11 -Wall  -pg  -O4 profile.cpp
g++ -c -fPIC -std=c++11 -Wall  -pg  -O4 ptnode.cpp
g++ -c -fPIC -std=c++11 -Wall  -pg  -O4 symtab.cpp
g++ -c -fPIC -std=c++11 -Wall  -pg  -O4 textio.cpp
g++ -c -fPIC -std=c++11 -Wall  -pg  -O4 tokenizer.cpp
g++ -c -fPIC -std=c++11 -Wall  -pg  -O4 types.cpp
g++ -c -fPIC -std=c++11 -Wall  -pg  -O4 utility.cpp
g++ -c -fPIC -std=c++11 -Wall  -pg  -O4 version.cpp
g++ -c -fPIC -std=c++11 -Wall  -pg  -O4 main.cpp
g++ -c -fPIC -std=c++11 -Wall  -pg  -O4 librarydep.cpp
g++   -Wl,-Map=dish.map  -pg  -o dish main.o  language.o atomicops.o atomics.o cmdln.o exception.o graph.o input.o langcore.o langdebug.o langerr.o langfile.o langfilesys.o langgraph.o langio.o langmath.o langnet.o langstr.o langtime.o langtxtio.o langzip.o log.o parser.o pldish.o profile.o ptnode.o symtab.o textio.o tokenizer.o types.o utility.o version.o -lm -lncurses -lX11
ar rcs libdish.a  language.o atomicops.o atomics.o cmdln.o exception.o graph.o input.o langcore.o langdebug.o langerr.o langfile.o langfilesys.o langgraph.o langio.o langmath.o langnet.o langstr.o langtime.o langtxtio.o langzip.o log.o parser.o pldish.o profile.o ptnode.o symtab.o textio.o tokenizer.o types.o utility.o version.o librarydep.o
g++ -shared -o libshdish.so  language.o atomicops.o atomics.o cmdln.o exception.o graph.o input.o langcore.o langdebug.o langerr.o langfile.o langfilesys.o langgraph.o langio.o langmath.o langnet.o langstr.o langtime.o langtxtio.o langzip.o log.o parser.o pldish.o profile.o ptnode.o symtab.o textio.o tokenizer.o types.o utility.o version.o librarydep.o
mv libdish.a ../bin
mv libshdish.so ../bin
mv dish ../bin
~/dish/src $ 

At the end of the build three binary artifacts are present:

	/dish/bin/dish		    The stand-alone dish interpreter.
	/dish/bin/libshdish.so	The shared library required when building the
	                        interpreter into another application.
	/dish/bin/libdish.a	    The static library required when building the
	                        interpreter into another application.

You can also install the interpreter's binaries in /usr/bin directory, making
them available to all users on Linux computer, by running “make install”.
Because this is modifying a directory owned by the administrator it will need
to execute as the 'root' user; this can be done using the sudo command:

~/dish/src $ sudo make install
[sudo] password for cbuck: 
g++-6   -Wl,-Map=dish.map   -o dish main.o language.o atomicops.o atomics.o cmdln.o exception.o graph.o input.o langcore.o langdebug.o langerr.o langfile.o langfilesys.o langgraph.o langio.o langmath.o langnet.o langregex.o langrs232.o langstr.o langtime.o langtxtio.o langzip.o log.o parser.o pldish.o ptnode.o symtab.o textio.o tokenizer.o utility.o version.o -lm -lncurses -lX11
mv dish ../bin
ar rcs libdish.a language.o atomicops.o atomics.o cmdln.o exception.o graph.o input.o langcore.o langdebug.o langerr.o langfile.o langfilesys.o langgraph.o langio.o langmath.o langnet.o langregex.o langrs232.o langstr.o langtime.o langtxtio.o langzip.o log.o parser.o pldish.o ptnode.o symtab.o textio.o tokenizer.o utility.o version.o librarydep.o
mv libdish.a ../bin
g++-6 -shared -o libshdish.so language.o atomicops.o atomics.o cmdln.o exception.o graph.o input.o langcore.o langdebug.o langerr.o langfile.o langfilesys.o langgraph.o langio.o langmath.o langnet.o langregex.o langrs232.o langstr.o langtime.o langtxtio.o langzip.o log.o parser.o pldish.o ptnode.o symtab.o textio.o tokenizer.o utility.o version.o librarydep.o
mv libshdish.so ../bin
cp -f ../bin/dish /usr/bin
~/dish/src $

NOTE: Depending on the features configured, the total build-time can take
several minutes. Of all the files in the build, compiling language.cpp takes
the longest and it is compiled first in the build 


IV.      Running the Demo Applications

Successfully building the dish interpreter as described in the previous section,
How do I build dish?, is the prerequisite of this step. Make certain the
executable binary artifact /dish/bin/dish is present before proceeding with this
step.

The directory /dish/dishsrc contains a number of example programs that can be
executed and examined. A larger, more complete example can be found in
/dish/dishsrc/game. To execute a program you need to invoke the dish interpreter
and pass the name of the program you wish to execute on the command-line. dish
applications may be comprised of several source files, so it is usually best to
run the application from the directory in which all of the application source
files are installed. But the OS needs to know how to find the interpreter
executable, /dish/src/dish. There are two options to accomplish this:

1. You can specify the path to the executable, absolute or relative, on the
   command-line when you invoke the interpreter. For an example, let's run the
   hello.dish program located in /dish/dishsrc. First, navigate to that
   directory in the terminal. Using a relative path to the executable, type the
   following at the command prompt:

        ~/dish/dishsrc $ ../bin/dish hello.dish

2. Alternatively, you can add /dish/bin to the PATH environment variable. Once
   this is done navigate to the /dish/dishsrc directory and type the following
   at the command prompt:

        ~/dish/dishsrc $ dish hello.dish

The entry-point game is /dish/dishsrc/game/game.dish. You can run the game
either by navigating to the directory /dish/dishsrc/game and type the following
at the command prompt

        ~/dish/dishsrc/game $ ../../bin/dish game.dish

if you are using option 1 to invoke the interpreter, or

        ~/dish/dishsrc/game $ dish game.dish

if you are using option 2.


V.     Configuring the Build

Some of the library features of dish rely on external libraries that may not be
included by some Linux installations. These libraries are not configured into
the default build process but can be added later by editing the makefile. The
third section of the makefile, titled "Build-time configuration options,"
allows support for the various features to be compiled into the interpreter. To
add support for a feature simple uncomment the line "<feature> = 1". For
example, uncommenting the line "COMP_LIB_DB_MYSQL = 1" will enable support for
the MySQL database. Similarly, commenting out the line "COMP_LIB_NETWORK = 1"
removes support for networking from the interpreter.

Once changes have been made to the configuration we need to regenerate the
configuration header file that controls the build. At the command-prompt type:

~/dish/src $ make config
rm -f dishconfig.h
Generating dishconfig.h...
Done.
~/dish/src $

Then repeat the steps in section III to rebuild the interpreter with the new
configuration.


VI. Final Thoughts


