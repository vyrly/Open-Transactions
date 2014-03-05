
========================================================================
START
------------------------------------------------------------------------
This are tools for OT (Open Transactions - secure messages and banking software).
othint - is a tool to easily type, and auto-complete commands for OT for otcli
otcli - is ot new cli - Open Transactions NEW Command Line Interface
------------------------------------------------------------------------
* do "make" or possibly first "cmake ." or see BUILDING
* do "make run" or ./othint will run program - or see USING
========================================================================


========================================================================
USING
------------------------------------------------------------------------
run "make run" or execute the binary ./othint

Now you are in interactive shell called
newcli (Open Transactions NEW Command-Line Interface)
here you execute OT commands, and auto-completion (tab key) works!

========================================================================


========================================================================
BUILDING
------------------------------------------------------------------------
building Othint

Dependencies:
- System libs, tools
- Editline
- OpenTransactions (development - with includes headers)

Dependencies installation (Debian):
	* Download OpenTransactions and build it, using instructions from  ../../docs/INSTALL-linux-modern.txt or other suitable
	* Checklist, in ~ .local you should have files like:
		$ find  /home/opentransactions/.local/lib/ | grep libot
			/home/opentransactions/.local/lib/libot.so.0
			/home/opentransactions/.local/lib/libot.a
			/home/opentransactions/.local/lib/libotapi.so
			/home/opentransactions/.local/lib/libotapi.la
			etc.
	* Get, build and install latest editline locally (editline in debian 7 has bugs)
		$ wget http://thrysoee.dk/editline/libedit-20130712-3.1.tar.gz
		$ tar -xzf libedit-20130712-3.1.tar.gz
		$ cd libedit-20130712-3.1
		$ ./configure --prefix=$HOME/.local
		$ make
		$ make install

If want to use ccmake (curses gui):
	# aptitude install cmake-curses-gui
Or Qt gui:
	# aptitude install cmake-gui

Build with default configuration:

	$ cmake .
	$ make

With locally installed editline and compiler wrapper:

	$ cmake . -DLOCAL_EDITLINE=ON -DWITH_WRAPPER=ON
	$ make

With ccmake can easly change options in gui:
	$ ccmake . (configure [c] and generate [g] in gui)
	make

========================================================================

