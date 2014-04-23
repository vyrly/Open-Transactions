
Project otcli for Open-Transactions: main documentation.

========================================================================
START
------------------------------------------------------------------------
This is "otcli" a sub project for Open-Transactions (secure messages and banking software - OT)
that provides tools for it:
* part otcli - is new Command Line Interface for easy access to advanced modern OT functions
* part othint - is a nice wrapper providing console line and bash autocomplete for otcli commands
------------------------------------------------------------------------
* do "make" or possibly first "cmake ." or see BUILDING
* do "make run" or ./othint will run program - or see USING
========================================================================


========================================================================
USING
------------------------------------------------------------------------
(Assuming project is already compiled or at least set up to compile correctly)

To test othint part:
Run "make run" or execute the binary ./othint --complete-shell
Now you are in interactive shell called
newcli (Open Transactions NEW Command-Line Interface)
here you execute OT commands, and auto-completion (tab key) works!

The otcli part is not currently delivered as separate program, use othint instead.

========================================================================


========================================================================
BUILDING
------------------------------------------------------------------------

How to building/compile otcli from source code:

1) Build otcli - choosing compiler
2) Build otcli - dependencies
3) Build otcli - main

---------------------------------------
1) Build othint - choosing compiler
Project otcli does use C++11, and therefore requires clang >= 3.3, or gcc >= 4.7 , MSVC12 (2013). 
Maybe some older versions could work too, or other compiler with good enough C++11 support.
Even if Open-Transactions main project builded correctly, it is possible that you will need
to set up newer compiler for this otcli sub-project.

Common solution is to install llvm 3.3 or higher locally (in ~/.local/) and then in ~/.profile append:
export CC="ccache $HOME/.local/bin/clang" ; export CXX="ccache $HOME/.local/bin/clang++" ; export CPP="$HOME/.local/bin/clang -E"
read details in global documentation: Open-Transactions/docs/INSTALL-linux-modern.txt
do not forget to reload ~/.profile and delete cmake cache after changes.

---------------------------------------
2) Build otcli - dependencies
- System libs, tools
- Editline
- OpenTransactions (development - with includes headers)

The dependencies here should build also with older compiler versions, so the point of selecting
compiler applies rather to the main build of ot.

Dependencies installation (Debian):
	* Download OpenTransactions and build it, using instructions from  ../../docs/INSTALL-linux-modern.txt or other suitable
	* Get, build and install latest editline locally (editline in debian 7 has bugs)
		wget http://thrysoee.dk/editline/libedit-20130712-3.1.tar.gz
		tar -xzf libedit-20130712-3.1.tar.gz
		cd libedit-20130712-3.1
		./configure --prefix=$HOME/.local
		make
		make install

---------------------------------------
3) Build otcli - main

Build with default configuration:
	cmake .
	make

If you need to tweak cmake build options e.g. some library path
or if your compiler is triggering false warning and you want to 
disable that,

ON LINUX/UNIX: (e.g. Debian)
you can make it from command line:
	cmake . -DLOCAL_EDITLINE=ON -DWITH_WRAPPER=ON
or instead use GUI: install this 2 (or one of them):
	aptitude install cmake-curses-gui cmake-gui
and then as user in the otcli sources directory do either of:
	ccmake .     # (then: configure [c] and generate [g] in gui)
	cmake-gui .  # (and follow the graphical instructions)
After doing such change run the command "make" again.

ON OTHER SYSTEMS (e.g. Windows)
follow system specific way to choose/use given compiler.

TODO @vyrly - Windows cmake + MSVC short description.

========================================================================
MORE
------------------------------------------------------------------------

Read other text files distributed here for more information;
Also read the main documentation of Open-Transactions itself, their readme, wiki.


