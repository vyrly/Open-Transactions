/************************************************************
 *
 *  OTNewcli  -- Open Transactions new command line interface
 *  (including parts like othint, some util libs, and more)
 *
 * 	Written in 2013 by rfree (rfree@gmx.us) and other members of
 * 	open-source community.
 *
 * 	To the extent possible under law, the author(s) have dedicated all
 * 	copyright and related and neighboring rights to this software to
 * 	the public domain worldwide. This software is distributed without
 * 	any warranty.
 *
 * 	You should have received a copy of the CC0 legalcode along with this
 * 	work (COPYING file). If not, see:
 * 	http://creativecommons.org/publicdomain/zero/1.0/
 *
 * 	OTNewcli is developed as a part of OPEN TRANSACTIONS project
 *
 * 	Where applicable (under given jurisdiction's law system),
 * 	we want to give away our code as CC0 (Creative Commons 0);
 * 	However, some parts of code might be not fully ours to licence/decide
 * 	(from point of view of given law system),
 * 	because they are connecting to other work in some ways.
 *
 * 	In any such unclear cases, the general Open Transaction licence as
 * 	published by FellowTraveller on GitHub should be applied if possible
 * 	(because it clarifies how to deal with linking to work like Lucre code,
 * 	OpenSSL code, and so on).
 *
 * 	We also allow this code to be released to Public Domain, but again,
 * 	we do not verify how is that possible in given law system.
 *
 * 	In ANY CASE, we take absolutely NO legal responsibility about
 * 	licensing, sharing, using this code (nor patent nor copyright nor
 * 	any other law related issues that it might have) e.g. in your	country.
 *
 * 	We are not lawyers, and it is up to only You to find out what
 * 	laws apply for your case. Do not use any of this code if you don't
 * 	agree.
 *
 * 	PROJECT GIT REPOSITORY:
 * 	https://github.com/rfree/Open-Transactions/
 *
 ***********************************************************************
 * 	OPEN TRANSACTION RELATED INFORMATIONS: (copy pasted for information)
 ***********************************************************************
 *                    OPEN TRANSACTIONS
 *
 *       Financial Cryptography and Digital Cash
 *       Library, Protocol, API, Server, CLI, GUI
 *
 *       -- Anonymous Numbered Accounts.
 *       -- Untraceable Digital Cash.
 *       -- Triple-Signed Receipts.
 *       -- Cheques, Vouchers, Transfers, Inboxes.
 *       -- Basket Currencies, Markets, Payment Plans.
 *       -- Signed, XML, Ricardian-style Contracts.
 *       -- Scripted smart contracts.
 *
 *  Copyright (C) 2010-2013 by "Fellow Traveler" (A pseudonym)
 *
 * 	BITCOIN:  1NtTPVVjDsUfDWybS4BwvHpG2pdS9RnYyQ
 *
 *  OFFICIAL OPEN TRANSACTIONS PROJECT WIKI(s):
 *  https://github.com/FellowTraveler/Moneychanger
 *  https://github.com/FellowTraveler/Open-Transactions/wiki
 *
 *  WEBSITE:
 *  http://www.OpenTransactions.org/
 *
 *  Components and licensing:
 *   -- Moneychanger..A Java client GUI.....LICENSE:.....GPLv3
 *   -- otlib.........A class library.......LICENSE:...LAGPLv3
 *   -- otapi.........A client API..........LICENSE:...LAGPLv3
 *   -- opentxs/ot....Command-line client...LICENSE:...LAGPLv3
 *   -- otserver......Server Application....LICENSE:....AGPLv3
 *  Github.com/FellowTraveler/Open-Transactions/wiki/Components
 *
 *  All of the above OT components were designed and written by
 *  Fellow Traveler, with the exception of Moneychanger, which
 *  was contracted out to Vicky C (bitcointrader4@gmail.com).
 *  The open-source community has since actively contributed.
 *
 *  -----------------------------------------------------
 *
 *   LICENSE:
 *   This program is free software: you can redistribute it
 *   and/or modify it under the terms of the GNU Affero
 *   General Public License as published by the Free Software
 *   Foundation, either version 3 of the License, or (at your
 *   option) any later version.
 *
 *   ADDITIONAL PERMISSION under the GNU Affero GPL version 3
 *   section 7: (This paragraph applies only to the LAGPLv3
 *   components listed above.) If you modify this Program, or
 *   any covered work, by linking or combining it with other
 *   code, such other code is not for that reason alone subject
 *   to any of the requirements of the GNU Affero GPL version 3.
 *   (==> This means if you are only using the OT API, then you
 *   don't have to open-source your code--only your changes to
 *   Open-Transactions itself must be open source. Similar to
 *   LGPLv3, except it applies to software-as-a-service, not
 *   just to distributing binaries.)
 *
 *   Extra WAIVER for OpenSSL, Lucre, and all other libraries
 *   used by Open Transactions: This program is released under
 *   the AGPL with the additional exemption that compiling,
 *   linking, and/or using OpenSSL is allowed. The same is true
 *   for any other open source libraries included in this
 *   project: complete waiver from the AGPL is hereby granted to
 *   compile, link, and/or use them with Open-Transactions,
 *   according to their own terms, as long as the rest of the
 *   Open-Transactions terms remain respected, with regard to
 *   the Open-Transactions code itself.
 *
 *   Lucre License:
 *   This code is also "dual-license", meaning that Ben Lau-
 *   rie's license must also be included and respected, since
 *   the code for Lucre is also included with Open Transactions.
 *   See Open-Transactions/src/otlib/lucre/LUCRE_LICENSE.txt
 *   The Laurie requirements are light, but if there is any
 *   problem with his license, simply remove the Lucre code.
 *   Although there are no other blind token algorithms in Open
 *   Transactions (yet. credlib is coming), the other functions
 *   will continue to operate.
 *   See Lucre on Github:  https://github.com/benlaurie/lucre
 *   -----------------------------------------------------
 *   You should have received a copy of the GNU Affero General
 *   Public License along with this program.  If not, see:
 *   http://www.gnu.org/licenses/
 *
 *   If you would like to use this software outside of the free
 *   software license, please contact FellowTraveler.
 *   (Unfortunately many will run anonymously and untraceably,
 *   so who could really stop them?)
 *
 *   DISCLAIMER:
 *   This program is distributed in the hope that it will be
 *   useful, but WITHOUT ANY WARRANTY; without even the implied
 *   warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 *   PURPOSE.  See the GNU Affero General Public License for
 *   more details.
 **************************************************************/

#include "lib_common3.hpp"

/**

OT Hints (new CLI - new commandline : auto complete commands, verify, check, etc)

Goal: this project aims to provide auto completion of newCLI OT commands, see [Description_of_auto_completion]
Description: See [Description_of_auto_completion] below
Example: "ot msg send bob a<TAB>" will ask remote OT and auto-complete alice.

Usage:
	./othint --complete-one "ot msg send ali"
	./othint --one "ot msg send ali"
	./othint --complete-shell
	./othint --shell
	./othint --devel # test various things etc

This subproject is separated out of OT, and uses C++11 and few other modern coding style changes.

Rules of language: use C++11, do not use boost (thoug we could copy small part of boost source code if needed,
or headers-only library)

Currently this is developed rapidly as 1 big file, to be splited soon, composed of this parts:
- nExamplesOfConvention - documenation of coding style convention
- nOT::nUtils - various utils for modern (C++11) OT ; ToStr(), OT_CODE_STAMP
- nOT::nNewcli - new command line classes, to parse the command line options, and to execute commands
- nOT::nOTHint - new command line auto-completion. Move here things usable only for auto-completion and nothing else
- nOT::nTests - the testcases for our code
- main() is here

Coding rules:
- testcase driven development
- testcase on almost each compilation, commit often
- secure - use asserts, secure methods, etc. Use static analysis
- fast - optimize for speed overall, and in picked bottlenecks
- scalable - assume usage in massive scripts one day, e.g. 1 million users email server :)
- document all conventions, all code; Entire WG (working group) must know all of them
- flexible - easy to tune, to extend, in object-oriented way

File format of sources: identation with \t char, which we assume is 2 spaces wide. Unicode, UTF-8.

*/


// Editline. Check 'git checkout linenoise' to see linenoise version.
#ifndef CFG_USE_EDITLINE // should we use editline?
	#define CFG_USE_EDITLINE 1 // default
#endif

#if CFG_USE_EDITLINE
	#ifdef __unix__
		#include <editline/readline.h>
	#else // not unix
		// TODO: do support MinGWEditline for windows)
	#endif // not unix
#endif // not use editline

// OTNewcliCmdline


// Please read and follow this syntax examples:
namespace nExamplesOfConvention {
// Welcome, to the world of C++11 !

int gGlobalVariable; // g - global variable

class cFooBar {
private:
	static int sStaticVariable; // s - static variable

	int mFooBarBaz; // m - variable, member of class

	int Fooberize();
	int DerpTheHerp();

public:
	cFooBar(int x)
	: mFooBarBaz(x)
	{}

	inline int Foo() {
		int abc=42;
		return abc;
	}
};
int cFooBar::sStaticVariable = 0;

// In case of simple parameters, we can skip "m" prefix. In this case:
struct cSimpleParam {
	int x;
	int y;

	cSimpleParam(int x, int y)
	: x(x), y(y)
	{}
};


} // namespace

// #####################################################################
// #####################################################################
// #####################################################################
// Utilities - various utils that are used in OT (but don't have to be related to OT)

extern std::string GetObjectName_global_string; // extern to h
std::string GetObjectName_global_string="(global)"; // definition/initialization
std::string GetObjectName() {	return GetObjectName_global_string; }

#define OT_CODE_STAMP ( nOT::nUtils::ToStr("[") + nOT::nUtils::ShortenTheFile(__FILE__) + nOT::nUtils::ToStr("+") + nOT::nUtils::ToStr(__LINE__) + nOT::nUtils::ToStr(" ") + nOT::nUtils::ToStr(GetObjectName()) + nOT::nUtils::ToStr("::") + nOT::nUtils::ToStr(__FUNCTION__) + nOT::nUtils::ToStr("]"))

namespace nOT {

INJECT_OT_COMMON_USING_NAMESPACE_COMMON_1; // <=== namespaces

/*

Commandline-Functor - Cmdfunc
Commandline-Functor(s) are expressions that are expected to have certain value, e.g. one of your nyms (mynym).

Consider following command line:
	ot msg send mynym hisnym [ccnym]
	ot msg send $get_mynym $get_somenym [$get_somenym_o]
get_mynym is a Cmdfunc, and this one for example links to cUse::nymsGetMy

They are defined in code in order to have following functions:
- othint - completion, e.g. mynym provides list of possible your nyms
- othint - parsing/verification, checking if the so-far entered command line is vali
- otcli  - parsing/verification, verifying the value from cmd line and checking if it is valid
- help - in either program it could be good to show name/description of given argument and generate doc
- testcase - they could produce various example command lines with valid data filled in
- code - heaving in-memory representation with tree of possible commands, with functors (named functions) could
	have other uses in future C++ code.

Cmdfunc in this C++ code are functions (methods), that take some extra data e.g. state of entire command line (usable in some cases),
and return possible data (mainly some vector of strings).

Syntax:
cCmdfuncReturn is the returnded data, mainly some vector of strings
cCmdfuncInput is the additional input data, that some functors might use
Functors will exist as member functions in various objects (mainly in cUse) called cCmdfuncProvider
- tCommandlineFunction is the functor type
- cCmdfuncProvider is the class that contains said members being pointed to by tCommandlineFunction

*/

// this class provides methods that can be plugged into command line parsing,
// e.g. that take state of command line,
// and return possible words that could be used in command line

class cCmdfuncProvider;

struct cCmdfuncReturn {
	vector<string> mWord;
};

struct cCmdfuncInput {
	public:
		const string& mSoFar; // the string with so-far provided command line
		cCmdfuncInput(const string &soFar);
};
cCmdfuncInput::cCmdfuncInput(const string &soFar) : mSoFar(soFar) { }

// tCmdfuncPtr - pointer to the Cmdfunc:
typedef cCmdfuncReturn (cCmdfuncProvider::*tCmdfuncPtr)(cCmdfuncInput);

class cCmdfunc { // the main Cmdfunc object - contains the pointer to member function doing the work, name, etc
	public:
		cCmdfunc( tCmdfuncPtr fun , const string & name);
	protected:
		tCmdfuncPtr mFun; // <---- PTR ! function
		const string mName;
};
cCmdfunc::cCmdfunc( tCmdfuncPtr fun , const string & name)
: mFun(fun), mName(name) { }

// ====================================================================

class cCmdfuncProvider {
	public:
};

}; // nOT

// ====================================================================


// TODO: move to utils
namespace nOT {
namespace nUtils {

INJECT_OT_COMMON_USING_NAMESPACE_COMMON_1; // <=== namespaces

struct cNullstream : std::ostream {
		cNullstream() : std::ios(0), std::ostream(0) {}
};
cNullstream g_nullstream; // a stream that does nothing (eats/discards data)

// ====================================================================

template <class T>
std::string ToStr(const T & obj) {
	std::ostringstream oss;
	oss << obj;
	return oss.str();
}

// ====================================================================


#define _dbg3(X) do { nOT::nUtils::current_logger.write_stream(20) << OT_CODE_STAMP << ' ' << X << std::endl; } while(0)
#define _dbg2(X) do { nOT::nUtils::current_logger.write_stream(30) << OT_CODE_STAMP << ' ' << X << std::endl; } while(0)
#define _dbg1(X) do { nOT::nUtils::current_logger.write_stream(40) << OT_CODE_STAMP << ' ' << X << std::endl; } while(0) // details
#define _info(X) do { nOT::nUtils::current_logger.write_stream(50) << OT_CODE_STAMP << ' ' << X << std::endl; } while(0) // more boring info
#define _note(X) do { nOT::nUtils::current_logger.write_stream(70) << OT_CODE_STAMP << ' ' << X << std::endl; } while(0) // interesting event
#define _warn(X) do { nOT::nUtils::current_logger.write_stream(90) << OT_CODE_STAMP << ' ' << X << std::endl; } while(0) // some problem
#define _erro(X) do { nOT::nUtils::current_logger.write_stream(100) << OT_CODE_STAMP << ' ' << X << std::endl; } while(0) // error - report

const char* ShortenTheFile(const char *s) {
	const char *p = s;
	const char *a = s;
	while (*p) {
		++p;
		if ((*p)=='/') a=p;
	}
	return a;
}

class cLogger {
	public:
		cLogger();
		std::ostream &write_stream(int level) { if ((level >= mLevel) && (mStream)) { *mStream << icon(level) << ' '; return *mStream; } return g_nullstream; }
		std::string icon(int level) const;
		void setDebugLevel(int level);
	protected:
		std::ostream *mStream; // pointing only
		int mLevel;
};

cLogger current_logger;

void cLogger::setDebugLevel(int level) {
	bool note_before = (mLevel > level); // report the level change before or after the change? (on higher level)
	if (note_before) _note("Setting debug level to "<<level);
	mLevel = level;
	if (!note_before) _note("Setting debug level to "<<level);
}

cLogger::cLogger() : mStream(NULL), mLevel(20) { mStream = & std::cout; }


std::string cLogger::icon(int level) const {
	if (level >= 100) return "!!!!";
	if (level >=  90) return "!!! ";
	if (level >=  70) return "WARN";
	if (level >=  50) return "Info";
	if (level >=  40) return "Dbg ";
	if (level >=  30) return "dbg ";
	if (level >=  20) return "dbg ";
	return "  ";
}

// ====================================================================

template <class T>
std::string vectorToStr(const T & v) {
	std::ostringstream oss;
	for(auto rec: v) {
		oss << rec <<",";
		}
	return oss.str();
}
std::string cSpaceFromEscape(const std::string &s) {
	std::ostringstream  newStr;
		for(int i = 0; i < s.length();i++) {
			if(s[i] == '\\' && s[i+1] ==32)
				newStr<<"";
			else
				newStr<<s[i];
			}
	return newStr.str();
}

template <class T>
void DisplayVector(std::ostream & out, const std::vector<T> &v, const std::string &delim=" ") {
	std::copy( v.begin(), v.end(), std::ostream_iterator<T>(out, delim.c_str()) );
}

template <class T>
void EndlDisplayVector(std::ostream & out, const std::vector<T> &v, const std::string &delim=" ") {
	out << std::endl;
	DisplayVector(out,v,delim);
}

template <class T>
void DisplayVectorEndl(std::ostream & out, const std::vector<T> &v, const std::string &delim=" ") {
	DisplayVector(out,v,delim);
	out << std::endl;
}

template <class T>
void DBGDisplayVector(const std::vector<T> &v, const std::string &delim=" ") {
	std::cerr << "[";
	std::copy( v.begin(), v.end(), std::ostream_iterator<T>(std::cerr, delim.c_str()) );
	std::cerr << "]";
}

template <class T>
void DBGDisplayVectorEndl(const std::vector<T> &v, const std::string &delim=" ") {
	DBGDisplayVector(v,delim);
	std::cerr << std::endl;
}

void DisplayStringEndl(std::ostream & out, const std::string text) {
	out << text;
	out << std::endl;
}

bool CheckIfBegins(const std::string & beggining, const std::string & all) {
	if (all.compare(0, beggining.length(), beggining) == 0) {
		return 1;
	}
	else {
		return 0;
	}
}

std::string cEscapeFromSpace(const std::string &s) {
	std::ostringstream  newStr;
	for(int i = 0; i < s.length();i++) {
		if(s[i] == 32)
			newStr << "\\" << " ";
		else
			newStr << s[i];
	}
	return newStr.str();
}

vector<string> WordsThatMatch(const std::string & sofar, const vector<string> & possib) {
	vector<string> ret;
	for ( auto rec : possib) { // check of possibilities
		if (CheckIfBegins(sofar,rec)) {
			rec = cEscapeFromSpace(rec);
			ret.push_back(rec); // this record matches
		}
	}
	return ret;
}

char GetLastChar(const std::string & str) { // TODO unicode?
	auto s = str.length();
	if (s==0) throw std::runtime_error("Getting last character of empty string (" + ToStr(s) + ")" + OT_CODE_STAMP);
	return str.at( s - 1);
}

std::string GetLastCharIf(const std::string & str) { // TODO unicode?
	auto s = str.length();
	if (s==0) return ""; // empty string signalizes ther is nothing to be returned
	return std::string( 1 , str.at( s - 1) );
}

std::string cEscapeString(const std::string &s) {
	std::ostringstream  newStr;
		for(int i = 0; i < s.length();i++) {
			if(s[i] >=32 && s[i] <= 126)
				newStr<<s[i];
			else
				newStr<<"\\"<< (int) s[i];
			}

	return newStr.str();
}


// ASRT - assert. Name like ASSERT() was too long, and ASS() was just... no.
// Use it like this: ASRT( x>y );  with the semicolon at end, a clever trick forces this syntax :)
#define ASRT(x) do { if (!(x)) Assert(false, OT_CODE_STAMP); } while(0)

void Assert(bool result, const std::string &stamp) {
	if (!result) throw std::runtime_error("Assert failed at "+stamp);
}

std::string GetMultiline(string endLine = "~") {
	nOT::nUtils::DisplayStringEndl( cout, "Please enter multiple lines of input to be encoded, followed by ~ on a blank line:" );
	std::string result(""); // Taken from OT_CLI_ReadUntilEOF
	while (true) {
		std::string input_line("");
		if (std::getline(std::cin, input_line, '\n'))
		{
			input_line += "\n";
				if (input_line[0] == '~')
					break;
			result += input_line;
		}
		if (std::cin.eof() )
		{
			std::cin.clear();
				break;
		}
		if (std::cin.fail() )
		{
			std::cin.clear();
				break;
		}
		if (std::cin.bad())
		{
			std::cin.clear();
				break;
		}
	}
	return result;
}

namespace nOper { // nOT::nUtils::nOper
// cool shortcut operators, like vector + vecotr operator working same as string (appending)
// isolated to namespace because it's unorthodox ide to implement this

using namespace std;

// TODO use && and move?
template <class T>
vector<T> operator+(const vector<T> &a, const vector<T> &b) {
	vector<T> ret = a;
	ret.insert( ret.end() , b.begin(), b.end() );
	return ret;
}

template <class T>
vector<T> & operator+=(vector<T> &a, const vector<T> &b) {
	return a.insert( a.end() , b.begin(), b.end() );
}

} // nOT::nUtils::nOper

} // nUtils
} // nOT


// ====================================================================

// TODO: move to own file
namespace nOT {
namespace nNewcli {

// list of things from libraries that we pull into namespace nOT::nNewcli
using std::string;
using std::vector;
using std::list;
using std::set;
using std::map;
using std::unique_ptr;
using std::cin;
using std::cerr;
using std::cout;
using std::endl;
using nOT::nUtils::ToStr;

/*

[Description_of_auto_completion]

=== Introduction ===

First an advance example of magic of OT hints:
	ot msg send bob al<TAB>
will auto-complete options:
	alice alex alcapone
In this situation, bash autocomplete with othint program
will query the OT server to list your contacts named al...

With respecting your privacy, trying to use remote server only if
data was not cached, and only asking servers that you trust (the --HT option)
that is the default. Start with "ot --H0" to make sure there will be 0 network
activity, no servers will be asked:
	ot --H0 msg send bob a<TAB>
will auto-complete with data that can be given without causing network traffic.

ot_secure:
If it's more convinient, we might provide separate command: "ot_net", "ot_secure"
with other level of discretion in the hinting process as well with say more
confirmations when also EXECUTING a command that will connect to OT server.
	ot_quiet mint spawn bob silve<TAB>
	1. will NOT ask any server about the list of currenies silve... will use cache
		silvergrams silvertest silverbob {showing only cached data, last update 3h ago}
	2. when the command is finished and executed as
		ot_quiet mint spawn bob silvergrams 1000<ENTER>
	it will ask: "Please confirm do you want to connect NOW to OT server aliased BigTest1,
	with ID=855gusd2dffj2d9uisdfokj233 (unknown/new server), and execute
	mint-spawn command? Type 2 words: 'unknown spawn' to confirm, or 'no'"

Also name alice is in front (instead alphabet sorting) since it was recently/frequently used.

All OT commands will be neatly supported in this way.


=== Commands are in form ===

ot [front1,front2...] topic action [--subact] var1,...  [varM,...] [--optNameN[=[optArgN]]...]

ot <-front options--> <- cCmdname ----------> <---- arguments ------------------------------->
ot                    <- cmd name ----------> <---- vars -----> <-- options ----------------->
ot <--- optional ---> <- mandatory-------------------> <--- optional ------------------------>
ot <-- cmdFrontOpt -> <- cmdPart -----------> <-------------- cmdArgs ----------------------->

Examples:
ot  --H0              msg   send              bob a
ot                    msg   send              bob alice            --attach scan.jpeg
ot                    msg   send              bob alice carol      --attach scan.jpeg
ot                    msg   send              bob alice carol      -v -v -v
ot  --hint-private    msg   send              bob alice carol      -v -v -v
ot  --hint-cached     msg   send              bob alice carol      -v -v -v
ot  --hint-cached     msg   help

Examples of SYNTAX ERRORS:
ot                    msg                     bob  alice # missing subcommand
ot                    msg   send              bob  # requires at least 2 arguments(*)
ot                    msg   send              bob  alice           --date=now --date=0 # date is unique
ot                    msg   send              bob  --hint-cachead=0 # forward command must be in font

(*) possibly such errors will instead allow execution and have the program interactivly ask for missing mandatory vars.

Therefore the syntax is:
[front-options] 2 words of command name, 0..N mandatory variables, 0..M extra variables, any options

	- subaction will be probably not used but leaving such possibility, then it would be 2..3 words

ARGUMENTS:
	- front-options are special options that must appear in front because they change meaning/parsing
		of everything next - particullary, auto-completion options. Read section [front-options] for details

	- Arguments available depend on the command name.

	- Options for command depend on the command name, as well are imported from global.

	- Options can't be placed before variables!

	- Options can be unique or can repeat. Options can have no value/data,
		or can have one.This gives 2*2 = 4 kinds of options: uniq, uniqData,
		repeat, repeatData.

	- Options can be both global and comming from selected action/subaction.

SEE testcases below in functions

#----------------Errors------------------#
msg     # error: incomplete action
msg send     # error: missing required options
msg send <mynym>     # error: missing required options
#----------------Errors------------------#

[*] - works
[/] - wip

#------List of all included commands-----#
account			# can display active (default) account
*account ls			# list all accounts
*account new			# make new account with UI
*account new <assetName>			# make new account by giving only <assetID>...
*account new <assetName> <accountName>			#... and <accountName>
account refresh			#	refresh database of private accounts' list
*account rm <accountName>			# delete account
*account mv <oldAccountName>	<newAccountName>		# rename account
--- Account inbox actions ---
account-in ls			# for active account
account-in ls <accountID>			# for specific <accountID>
account-in accept <paymentID>				#	accept this particullar payment
account-in accept --all		# accept all incoming transfers, as well as receipts
--- Account outbox actions ---
account-out ls
------------------------------
asset				# can display active (default) asset
*asset ls		# display all assets
asset new 	# TODO: change to issue?
asset new <assetName>			# set new asset with given <assetName>
basket new
basket ls
basket exchange
cash send <mynym> <hisnym>
cheque new
contract new
contract get <contractID>
contract sign
market
market ls
mint new
*msg			# should show what options do you have with this topic
/msg send		# should ask you about nyms ?
msg send <mynym> 		# should take your nym and ask about addressee's name
*msg send <mynym> <hisnym> 		# an example of usage
msg send <mynym> <hisnym> --push     		# global option
msg send <mynym> <hisnym> --no-footer     # action option
msg send <mynym> <hisnym> --cc <ccnym>     # action option with value
msg send <mynym> <hisnym> --cc <ccnym> --cc <ccnym2>
msg send <mynym> <hisnym> --cc <ccnym> --cc <ccnym2> --push  	 # example of force send (?) - not sure if it will appear
*msg ls			# list all messages for all nyms
/msg ls <mynym> # list all messages for nym
msg mv			# move message to different directory in your mail box
msg rm <index>		# remove message with <index> number
msg rm --all		# remove all messages from mail box
--- Test ---
msguard info   # test, imaginary comand "msguard" (microsoft guard) info - shows windows firewall status for OT tcp
msguard start
msguard stop
------------
*nym 			# can display active (default) nym
*nym ls			# list of all nyms
nym new			# make new nym with UI (it should ask potential user to give the name
*nym new <nymName>			# make new nym by giving name without UI
nym rm <name>			# remove nym with such <name>
nym rm <nymID>		# remove nym with such <nymID>
nym info <nymID>		# show information about such <nymID>
nym edit <nymID>		# allows to edit information about such <nymID>
*nym register <nymName>	# register nym defined by nymName on default server
nym register <nymID>	# register nym defined by nymID on default server
/nym register <nymID> <serverID>	# register this specific <nymID> to specific <serverID> server
nym set-default <nymID> # set default nym
nym import		# import saved (somewhere?) nyms
nym export		# export nyms to (outerspace) :) ?
*nym check <nymID>			# returns Public Key of this <nymID> nym
nym refresh			# refresh nym's list and its included informations
nym-cred new 			# change credential to trust?
nym-cred revoke
nym-cred show			# show all credential to trust?
receipt?
server			# can display active (default) server
/server ls			# as above but all servers are listed TODO: Display mode information about servers
server add		# add new server
server new 	# like newserver
server set-default # set default server
*text encode	# interactively get multiline text
*text encode <text>
text encode <textfile>
*text decode # interactively get multiline text
text decode <textfile>
*text encrypt <recipientNymName> <text>
text encrypt <textfile>
*text decrypt # interactively get multiline text
text decrypt <textfile>
voucher new
wallet? status
#------List of all included commands-----#

That's all commands included to OTHint for now.
(?) means that we're not sure if it will appear in main program, those keywords are implemente but commented for now

------------------------------------------------------------------------
older opentxs commands:

acceptall	acceptinbox	acceptinvoices	acceptmoney
acceptpayments	acceptreceipts	accepttransfers	addasset
addserver	addsignature	balance		buyvoucher
cancel		changepw	nymCheck	clearexpired
clearrecords	confirm		credentials	decode
decrypt		delmail		deloutmail	deposit
discard		editacct	editasset	editnym
editserver	encode		encrypt		exchange
expired		exportcash	exportnym	getboxreceipt
getcontract	getmarkets	getmyoffers	getoffers
importcash	importnym	inbox		issueasset
killoffer	killplan	mail		newacct
newasset	newbasket	newcred		newkey
newnym		newoffer	newserver	outbox
outmail		outpayment	pass_decrypt	pass_encrypt
paydividend	payinvoice	payments	propose
records		refresh		refreshacct	refreshnym
register	revokecred	sendcash	sendcheque
sendinvoice	msgSend		sendvoucher	showaccounts
showacct	showassets	showbasket	showcred
showincoming	showmarkets	showmint	showmyoffers
shownym		shownyms	showoffers	showoutgoing
showpayment	showpurse	showservers	sign
stat		transfer	trigger		verifyreceipt
verifysig	withdraw	writecheque	writeinvoice
------------------------------------------------------------------------

[front-options] usage is for example:
If you type -HN in front of options, then Hints will use Network (-HN) to autocomplete, typing
ot -HN msg send myuser1 bo<TAB> will e.g. ask OT server(s) (e.g. over internet) about you address book
ot -HT msg send myuser1 bo<TAB> the same but for Trusted servers only (will not accidentially talk to other servers)
ot -H0 .... will make sure you will not ask OT servers, just use data cached
ot -HR .... will force othint to refresh all information from servers. Option useful if you want fresh information from servers in real time. Slow and dagerous for privacy.

The exact planned options are 2 settings: accessing remote and accessing cache.
	--hint-remote=V set's the privacy to level 0..9. 0=never ask remote severs for data needed for
	this autocompletion, 9 freely ask (less secure, because remote server see that we compose a command).
	1=local server (e.g. localhost that was marked as trusted)
	3=trusted servers (e.g. several servers you configure as trusted)
	5=uses network (all servers) but might avoid some really sensive data
	9=you fully ask the server owners and consent to possiblity of them (or their ISP, hosting) learning
	what you are planning to do

	--hint-cached=V set's the usage of cached data. 0=revalidate now all data from server.
	5=normal reasonable use of cache
	8=only cached data, unless we have no choice, 9=only cached data even if it causes an error

--hint-remote=0 implies --hint-cached=9 as we are not allowed to touch remote server at all
--hint-cached=0 implied --hints-remote=0 as we are ordering to touch remote server so we are not working in private mode

--hint-remote=0 --hint-cached=0 is disallowed syntax,
even though some commands that indeed do not need neither cached nor remote data could work,
like "ot --hint-remote=0 --hint-cached=0 msg help"
or "ot --hint-remote=0 --hint-cached=0 msg draft"
but for clarity it will be an error because likelly someone confused the options.
But then, --hint-allow-strange option will allow such syntax, if it appears in front of option causing this
contradiction.
E.g. this is allowed syntax:
ot --hint-allow-strange --hint-remote=0 --hint-cached=0 msg draft

Shortcuts:
--H0 gives hints offline        equals --hint-offline     equals --hint-remote=0 --hint-cached=9
--HL gives hints local          equals --hint-local       equals --hint-remote=1 --hint-cached=5
--HT gives hints trusted        equals --hint-trusted     equals --hint-remote=3 --hint-cached=5
--HN gives hints from network   equals --hint-net         equals --hint-remote=5 --hint-cached=5
--HR is forced net reload       equals --hint-reload      equals --hint-remote=9 --hint-cached=0
--HV gives VPNed network        equals --hint-vpn         equals --vpn-all-net --hint-remote=9 --hint-cached=5

VPN:
option --vpn-all-net will force hint autocompletion (and also the actuall commands, unless later
canceled with other options) to use only VPN or similar secure networking. Details will be
configured, it could be e.g. a VPN network, or possibly other secured (private) network facility.
It is guarnateed that if such secure network fails to work, then no network will be touched
and program will not leak any activity to open network (LAN, Internet, etc)
--HV might be most comfortable and yet quite secure option, usable e.g. from hotels.

VPN forced:
Global configuration option could force to always use VPN (append --vpn-all-net)
then use "ot --HN" will not auto-complete on <TAB> but show:
	{can not use --HN because your configuration disabled it, please try --HV}
and if executed as full command, will also refuse to work, with explanation.

Please remember that VPNs or even more advanced solutions are not that secure, and that
ot hint sends anyway lots of data of intended action, with timing correlation, to the OT server
in --HV case.
VPN only hides your IP a bit.
Full caching with --H0 or --HL is most secure, there is no home like localhost :)

*/


// more rich information about a nym
class cNyminfo {
	public:
		cNyminfo(std::string name);

		operator const std::string&() const;

	public:
		string mName;
		int mScore;
};

cNyminfo::cNyminfo(std::string name)
: mName(name), mScore(0)
{ }

cNyminfo::operator const string&() const {
	return mName;
}


class cCmdname { // holds (2)-part name of command like "msg","send"
	// represents name of one command, including the (1)-2-3 components e.g. msg,send or msg,export,msg
	// "msg send"
	// "msg list"
	// "msg export msg"
	// "msg export all"
	// "msg" (not a valid command, will be used with null_function, is just to provide global options to inherit)

	protected:
		const string mTopic;
		const string mAction;
		const string mSubaction;

	public:
		cCmdname(const string &topic, const string &action, const string &subaction);
};

cCmdname::cCmdname(const string &topic, const string &action, const string &subaction)
:mTopic(topic), mAction(action), mSubaction(subaction)
{
}


/*
Build:
Tree of max options:
[msg] ---------> { --unicode }
[msg send] ----> (2) + (3) + {--now,--later,--sign,--red} , msg_send_complete()

msg_send_complete() {
	if (stage==arg) { if (arg_pos==1) get_my_nyms();    if (arg_pos==2) get_your_nyms(); }
	else if (stage==extra) { ... }
	else if (stage==option) {
		foreach (opt) ..
			if (--now) delete --later;
			if (uniq) delete this_option;
		} // existing options eliminate possibilities
		if (half_world) finish_option( remaining_options );
		else show_other_options();
	}
}
*/


/*
class argument_info {
	// class says what kind of argument is this i.e. that argument is "mynym" and it have to be string or integer or only boolean
	// and provide class!!! for auto complete

	string mName; // "mynym" "hisnym" (even those arguments which have specific order, so they don't have "name", will have, for example for generating help text

	// other mName will be for eg. "cc"  for option --cc which remain name

};
*/

/*
typedef string argument_data ; // for now...

class cCmdoptions {

		// required arguments
		vector< argument_info > // here should be { ("msg","send")  ,  ("msg","send","body") ect. same as in cCmdname::returnStandard

		map< argument_info , vector< argument_data > > // here will be map
}

class cCmdlineInfo {
	public:
	protected:
		vector<cCmdname> mPossible; // store here possible command names
		map<cCmdname , details_of_command> mPossibleDetails;
};
*/



} // namespace nNewcli
} // namespace nOT
// ########################################################################
// ########################################################################
// ########################################################################

namespace nOT {
namespace nUse {

	INJECT_OT_COMMON_USING_NAMESPACE_COMMON_2; // <=== namespaces

		class cUseOT {

			string mServerID = "r1fUoHwJOWCuK3WBAAySjmKYqsG6G2TYIxdqY6YNuuG"; // TODO read default ServerID
			string mUserID = "DYEB6U7dcpbwdGrftPnslNKz76BDuBTFAjiAgKaiY2n"; // TODO read default UserID

		public:

		vector<nOT::nNewcli::cNyminfo> mNymsMy;
		vector<std::string> mNymsMy_str; // TODO optimize/share memory? or convert on usage

		bool mNymsMy_loaded;
		bool OTAPI_loaded;
		bool OTAPI_error;

		cUseOT() : mNymsMy_loaded(false), OTAPI_loaded(false),OTAPI_error(false) 	{

		}

		~cUseOT() {
			if (OTAPI_loaded) OTAPI_Wrap::AppCleanup(); // UnInit OTAPI
		}

		bool Init() {
			if (OTAPI_error) return false;
			if (OTAPI_loaded) return true;
			try {
				if (!OTAPI_Wrap::AppInit()) {// Init OTAPI
					_erro("Error while init OTAPI thrown an UNKNOWN exception!");
					return false; // <--- RET
				}

				_info("Trying to load wallet: ");
				//if not pWrap it means that AppInit is not successed
				OTAPI_Wrap *pWrap = OTAPI_Wrap::It();
				if (!pWrap) {
					OTAPI_error = true;
					_erro("Error while init OTAPI (1)");
					return false;
				}

				if(OTAPI_Wrap::LoadWallet()) {
					_info("wallet was loaded.");
					OTAPI_loaded = true;
				}	else _erro("Error while loading wallet.");
			}
			catch(const std::exception &e) {
				_erro("Error while OTAPI init (2) - " << e.what());
				return false;
			}
			catch(...) {
				_erro("Error while OTAPI init thrown an UNKNOWN exception!");
				OTAPI_error = true;
				return false;
			}
			return OTAPI_loaded;
		}

		const std::vector<std::string> nymsGetMy() {
			if(!Init())	return vector<std::string> {};

			if (!mNymsMy_loaded) {
				try {
				mNymsMy_loaded=0; // to mark that we start to delete data/data is inconsistent
				mNymsMy.clear();
				mNymsMy_str.clear();

				for(int i = 0 ; i < OTAPI_Wrap::GetNymCount ();i++) {
					std::string nym_ID = OTAPI_Wrap::GetNym_ID (i);
					std::string nym_Name = OTAPI_Wrap::GetNym_Name (nym_ID);

					mNymsMy_str.push_back(nym_Name);
					}
			}
			catch(...) { }
			mNymsMy_loaded = true;
			}
		return mNymsMy_str;
		}

		const string nymGetId(const string & nymName) {
			if(!Init())
			return "";

			if (nymName.at(0) == '%') { // nym ID
				return nymName.substr(1);
			}
			else { // nym Name
				for(int i = 0 ; i < OTAPI_Wrap::GetNymCount ();i++) {
					string nymID = OTAPI_Wrap::GetNym_ID (i);
					string nymName_ = OTAPI_Wrap::GetNym_Name (nymID);
					if (nymName_ == nymName)
						return nymID;
				}
			}
			return "";
		}

		const string nymGetInfo(const string & nymName) {
			if(!Init())
			return "";

			for(int i = 0 ; i < OTAPI_Wrap::GetNymCount ();i++) {
				string nymID = OTAPI_Wrap::GetNym_ID (i);
				string nymName_ = OTAPI_Wrap::GetNym_Name (nymID);
				if (nymName_ == nymName)
					return nymName_ + " - " + nymID;
			}
			return "";
		}

		const std::vector<std::string> accountsGet() {
			if(!Init())
			return vector<std::string> {};

			_dbg3("Retrieving accounts names");
			vector<std::string> accounts;
			for(int i = 0 ; i < OTAPI_Wrap::GetAccountCount ();i++) {
				accounts.push_back(OTAPI_Wrap::GetAccountWallet_Name ( OTAPI_Wrap::GetAccountWallet_ID (i)));
			}
			return accounts;
		}

		const nUtils::vector<std::string> accountGetIds() {
			if(!Init())
			return vector<std::string> {};

			_dbg3("Retrieving accounts ID's");
			vector<std::string> accountsIDs;
			for(int i = 0 ; i < OTAPI_Wrap::GetAccountCount ();i++) {
				accountsIDs.push_back(OTAPI_Wrap::GetAccountWallet_ID (i));
			}
			return accountsIDs;
		}

		const std::string accountGetId(const std::string & accountName) {
			if(!Init())
			return "";

			for(int i = 0 ; i < OTAPI_Wrap::GetAccountCount ();i++) {
				if(OTAPI_Wrap::GetAccountWallet_Name ( OTAPI_Wrap::GetAccountWallet_ID (i))==accountName)
				return OTAPI_Wrap::GetAccountWallet_ID (i);
			}
			return "";
		}

		const std::vector<std::string> assetsGetNames() {
			if(!Init())
			return vector<std::string> {};

			vector<std::string> assets;
			for(int i = 0 ; i < OTAPI_Wrap::GetAssetTypeCount ();i++) {
				assets.push_back(OTAPI_Wrap::GetAssetType_Name ( OTAPI_Wrap::GetAssetType_ID (i)));
			}
			return assets;
		}

		const std::string assetGetId(const std::string & assetName) {
			if(!Init())
			return "";

			for(int i = 0 ; i < OTAPI_Wrap::GetAssetTypeCount ();i++) {
				if(OTAPI_Wrap::GetAssetType_Name ( OTAPI_Wrap::GetAssetType_ID (i))==assetName)
					return OTAPI_Wrap::GetAssetType_ID (i);
			}
			return "";
		}

		const std::string accountRename(const std::string & oldAccountName, const std::string & newAccountName) {

				accountSetName (accountGetId(oldAccountName), newAccountName);
			return "";
		}

		const std::string accountSetName(const std::string & accountID, const std::string & NewAccountName) { //TODO: passing to function: const std::string & nymName, const std::string & signerNymName,
			if(!Init())
			return "";

				OTAPI_Wrap::SetAccountWallet_Name (accountID, mUserID, NewAccountName);
			return "";
		}

		void accountCreate(const std::string & assetName, const std::string & newAccountName) {
			if(!Init())
			return ;

			OT_ME madeEasy;
			string strResponse;
			strResponse = madeEasy.create_asset_acct(mServerID, mUserID, assetGetId(assetName));

			// -1 error, 0 failure, 1 success.
			if (1 != madeEasy.VerifyMessageSuccess(strResponse))
			{
				_erro("Failed trying to create Account at Server.");
				return;
			}

			// Get the ID of the new account.
			string strID = OTAPI_Wrap::Message_GetNewAcctID(strResponse);
			if (!strID.size())
      {
				_erro("Failed trying to get the new account's ID from the server response.");
				return;
			}

			// Set the Name of the new account.
			accountSetName(strID,newAccountName);

			cout << "Account " << newAccountName << "(" << strID << ")" << " created successfully." << endl;
		}

		void nymCreate(const std::string & nymName) {
			if(!Init())
			return ;

			OT_ME madeEasy;
			int32_t nKeybits = 1024;
			string NYM_ID_SOURCE = ""; //TODO: check
			string ALT_LOCATION = "";
			string strID = madeEasy.create_pseudonym(nKeybits, NYM_ID_SOURCE, ALT_LOCATION);

			if (strID.empty())
			{
				_erro("Failed trying to create new Nym.");
				return;
			}

			// Set the Name of the new Nym.
			OTAPI_Wrap::SetNym_Name(strID, strID, nymName);

			_info("Nym " << nymName << "(" << strID << ")" << " created successfully.");
		}

		void nymRegister(const std::string & nymName) {
			if(!Init())
			return ;

			OT_ME madeEasy;

			_warn("Checking for default server only");

			string nymID = nymGetId(nymName);

			bool isReg = OTAPI_Wrap::IsNym_RegisteredAtServer(nymID, mServerID);

			if (!isReg)
			{
				string response = madeEasy.register_nym(mServerID, nymID);
				nOT::nUtils::DisplayStringEndl(cout, response);
				nOT::nUtils::DisplayStringEndl(cout, "Nym " + ToStr(nymName) + "(" + ToStr(nymID) + ")" + " was registered successfully");
			}
			else
				cout << "Nym " << nymName << "(" << nymID << ")" << " was already registered" << endl;
		}

		void nymRegister(const std::string & nymName, const std::string & serverName) {
			if(!Init())
			return ;
			//TODO: Add servers naming???
		}

		std::string accountDelete(const std::string & accountName) { ///<
			if(!Init())
			return "";

			if(!OTAPI_Wrap::Wallet_CanRemoveAccount (accountGetId(accountName))) {
				// inBox and OutBox must be get from server because without it account not work properly
				// example if you can't delete account without inbox and outbox
				int32_t  inBoxInt = OTAPI_Wrap::getInbox 	(mServerID,mUserID,accountGetId(accountName));
				int32_t outBoxInt = OTAPI_Wrap::getOutbox 	(mServerID,mUserID,accountGetId(accountName));
			}

			if(OTAPI_Wrap::deleteAssetAccount(mServerID, mUserID, accountGetId(accountName))==-1)
				return "Error while deleting account";
			else
				return "";
		}

		const vector<string> serversGet() { ///< Get all servers name
			if(!Init())
			return vector<string> {};

			vector<string> servers;
			for(int i = 0 ; i < OTAPI_Wrap::GetServerCount ();i++) {
				servers.push_back(OTAPI_Wrap::GetServer_Name(OTAPI_Wrap::GetServer_ID(i)));
			}
			return servers;
		}

		const vector<string> msgGetAll() { ///< Get all messages from all Nyms.
			if(!Init())
			return vector<string> {};

			for(int i = 0 ; i < OTAPI_Wrap::GetNymCount ();i++) {
				string nym_ID = OTAPI_Wrap::GetNym_ID (i);
				string nym_Name = OTAPI_Wrap::GetNym_Name (nym_ID);
				cout << "===" << nym_Name << "(" << nym_ID << ")"  << "===" << endl;
				cout << "INBOX" << endl;
				cout << "id\tfrom\t\tcontent:" << endl;
				for(int i = 0 ; i < OTAPI_Wrap::GetNym_MailCount (nym_ID);i++) {
					cout << i+1<< "\t" << OTAPI_Wrap::GetNym_Name(OTAPI_Wrap::GetNym_MailSenderIDByIndex(nym_ID, i))  << "\t" << OTAPI_Wrap::GetNym_MailContentsByIndex (nym_ID,i) << endl;
				}
				cout << "OUTBOX" << endl;
				cout << "id\tto\t\tcontent:" << endl;
				for(int i = 0 ; i < OTAPI_Wrap::GetNym_OutmailCount (nym_ID);i++) {
					cout << i+1<< "\t" << OTAPI_Wrap::GetNym_Name(OTAPI_Wrap::GetNym_OutmailRecipientIDByIndex(nym_ID, i)) << "\t" << OTAPI_Wrap::GetNym_OutmailContentsByIndex (nym_ID,i) << endl;
				}
			}
			return vector<string> {};
		}

		const vector<string> msgGetForNym(const string & nym_Name) { ///< Get all messages from Nym.
			if(!Init())
				return vector<string> {};

			//string nym_Name = OTAPI_Wrap::GetNym_Name (nymID);
			//cout <<"mid\tfrom\t\tcontent inbox:"<< endl;
			//for(int i = 0 ; i < OTAPI_Wrap::GetNym_MailCount (nymID);i++) {
				//cout << i+1<< "\t"<< OTAPI_Wrap::GetNym_Name(nymID)<<"\t" << OTAPI_Wrap::GetNym_MailContentsByIndex (nymID,i);
			//}
			//cout << endl << "mid\tto\t\tcontent outbox:" << endl;
			//for(int i = 0 ; i < OTAPI_Wrap::GetNym_OutmailCount (nymID);i++) {
				//cout << i+1<< "\t"<< OTAPI_Wrap::GetNym_Name(nymID)<<"\t" << OTAPI_Wrap::GetNym_OutmailContentsByIndex (nymID,i);
			//}
			return vector<string> {};
		}

		void msgSend(const string & nymSender, const string & nymRecipient, const string & msg) { ///< Send message from Nym1 to Nym2
			if(!Init())
				return;

			OT_ME madeEasy;
			string sender = nymGetId(nymSender);
			string recipient = nymGetId(nymRecipient);

			_dbg1(sender);
			_dbg1(recipient);

			string strResponse = madeEasy.send_user_msg ( mServerID, sender, recipient, msg);

			// -1 error, 0 failure, 1 success.
			if (1 != madeEasy.VerifyMessageSuccess(strResponse))
			{
				_erro("Failed trying to send the message");
				return;
			}

			_info("Message was sent successfully.");
		}

		void removeMailByIndex(const string &) { //Change name of the function
			//bool OTAPI_Wrap::Nym_RemoveMailByIndex (const std::string & NYM_ID, const int32_t & nIndex)
		}

		bool nymCheckByName(const string & nymName) {
			vector<string> v = nymsGetMy();
			if (std::find(v.begin(), v.end(), nymName) != v.end())
				return true;
			return false;
		}

		void nymCheck(const string & hisNymID) { // wip
			if(!Init())
				return;

			OT_ME madeEasy;
			string strResponse = madeEasy.check_user( mServerID, mUserID, hisNymID );
			// -1 error, 0 failure, 1 success.
			if (1 != madeEasy.VerifyMessageSuccess(strResponse))
			{
				_erro("Failed trying to download user public key.");
				return;
			}
			_info("Successfully downloaded user public key.");
		}

		bool assetCheckIfExists(const string & assetName) {
			vector<string> v = assetsGetNames();
			if (std::find(v.begin(), v.end(), assetName) != v.end())
				return true;
			return false;
		}

		bool accountCheckIfExists(const string & accountName) {
			vector<string> v = accountsGet();
			if (std::find(v.begin(), v.end(), accountName) != v.end())
				return true;
			return false;
		}

		const string textEncode(const string & plainText) {
			if(!Init())
				return "";

			bool bLineBreaks = true; // FIXME? OTAPI_Wrap - bLineBreaks should usually be set to true
			string encodedText;
			encodedText = OTAPI_Wrap::Encode (plainText, bLineBreaks);
			return encodedText;
		}

		const string textDecode(const string & encodedText) {
			if(!Init())
				return "";

			bool bLineBreaks = true; // FIXME? OTAPI_Wrap - bLineBreaks should usually be set to true
			string plainText;
			plainText = OTAPI_Wrap::Decode (encodedText, bLineBreaks);
			return plainText;
		}

		const string textEncrypt(const string & recipientNymName, const string & plainText) {
			if(!Init())
				return "";
			string encryptedText;
			encryptedText = OTAPI_Wrap::Encrypt(nymGetId(recipientNymName), plainText);
			return encryptedText;
		}

		const string textDecrypt(const string & recipientNymName, const string & encryptedText) {
			if(!Init())
				return "";
			string plainText;
			plainText = OTAPI_Wrap::Decrypt(nymGetId(recipientNymName), encryptedText);
			return plainText;
		}
	};

	cUseOT useOT;
} // nUse
} // nOT


namespace nOT {
namespace nTests {

INJECT_OT_COMMON_USING_NAMESPACE_COMMON_2; // <=== namespaces

using namespace nOT::nUtils;

std::string StreamName(std::ostream &str) {
	if (str == std::cout) return "cout";
	if (str == std::cout) return "cin";
	return "other-stream";
}

struct cTestCaseCfg {
	std::ostream &ossErr;
	bool debug;

	cTestCaseCfg(std::ostream &ossErr, bool debug)
	: ossErr(ossErr) , debug(debug)
	{ }

	std::ostream & print(std::ostream &ostr) const { ostr << "[" << (debug ? "debug":"quiet") << " " << StreamName(ossErr) << "]";  return ostr; }

};

std::ostream & operator<<(std::ostream &ostr, const cTestCaseCfg &cfg) { return cfg.print(ostr); }

bool testcase_run_all_tests();

int main_main(int argc, char **argv); // some tests will execute the main... e.g. against errors in args parsing TODO move to namespace

bool testcase_complete_1(const std::string &sofar); // TODO ... testcase or really used???
bool testcase_complete_1_wrapper(); // TODO ... testcase or really used???

typedef bool ( * tTestCaseFunction )(const cTestCaseCfg &) ;
// ^- tTestCaseFunction is a function:  bool ....(const cTestCaseCfg &)
void exampleOfOT();
} // nTests
} // nOT

// TODO: move to own file
namespace nOT {
namespace nOTHint {

// list of thigs from libraries that we pull into namespace nOT::nNewcli
using std::string;
using std::vector;
using std::list;
using std::set;
using std::map;
using std::unique_ptr;
using std::cin;
using std::cerr;
using std::cout;
using std::endl;

using namespace nOT::nUtils;
using namespace nOT::nUtils::nOper; // vector + vector and other shortcut operators. It's appen, as in strings! :)


// Data for hinting, e.g. cached or local information.
class cHintData {
	public:
		cHintData();
};

cHintData::cHintData()
{
}




// ====================================================================

// The Manager to access OT-hint (autocompletion) functionality
class cHintManager {

	public:
		cHintManager();

		vector<string> AutoComplete(const string &sofar_str) const; // the main function to auto-complete. The command line after "ot ", e.g. "msg send al"
		vector<string> AutoCompleteEntire(const string &sofar_str) const; // the same, but takes entire command line including "ot ", e.g. "ot msg send al"

		void TestNewFunction_Tree(); // testing new code [wip]

	protected:
		vector<string> BuildTreeOfCommandlines(const string &sofar_str, bool show_all) const; // return command lines tree that is possible from this place
		unique_ptr<cHintData> mHintData;
};

cHintManager::cHintManager()
: mHintData(new cHintData)
{ }

void cHintManager::TestNewFunction_Tree() { // testing new code [wip]
	_info("Working on this="<<(void*)this);
/*

ot msg send
ot msg ls
ot msg new

ot nym ls
ot nym new
ot [front] nym del $mynym [--a] [--b] [--c]

*/
}

vector<string> cHintManager::AutoCompleteEntire(const string &sofar_str) const {
	const std::string cut_begining="ot"; // minimal begining
	const int cut_begining_size = cut_begining.length();
	_info("cut_begining=[" << cut_begining << "]");
	// <= add space if we are at ot<tab>
	if (sofar_str.length() <= cut_begining_size) return WordsThatMatch(sofar_str, vector<string>{ cut_begining }); // too short, force completio to "ot"

	std::string ot = sofar_str.substr(0,cut_begining_size); // separate out the part that is know to has correct size and should be "ot"
	if (ot!=cut_begining) return vector<string>{}; // nothing matches, not command ot...

	// TODO optimize, avoid copy?
	std::string line = sofar_str;
	line.erase(0, cut_begining_size);

	return AutoComplete(line);
}

vector<string> cHintManager::AutoComplete(const string &sofar_str) const { // the main function to auto-complete
	// cerr << "COMPLETE for sofar=[" << sofar_str << "]." << endl;
	auto possible = BuildTreeOfCommandlines(sofar_str,false);
	return possible;
}


vector<string> cHintManager::BuildTreeOfCommandlines(const string &sofar_str, bool show_all) const {
/*
	nOT::nNewcli::cNew newcli;
	newcli.assign(sofar_str);
	newcli.parse();

}
*/
	bool dbg = false;

	string sofar_str_tmp = sofar_str;

	if (dbg) { _dbg3("sofar_str "<<sofar_str);};

	string esc ("\\ ");


	string newEsc = "#x#";
	// change Escape on new unique substring
	while(sofar_str_tmp.find(esc)!=std::string::npos) {
		sofar_str_tmp.replace(sofar_str_tmp.find(esc),esc.length(),newEsc);
		if (dbg) { _dbg3("sofar_str_tmp "<< sofar_str_tmp);}
	}



	std::istringstream iss(sofar_str_tmp);

	vector<string> sofar { std::istream_iterator<string>{iss}, std::istream_iterator<string>{} };

	if (dbg) { _dbg3("sofar.size()  "<<sofar.size());};

	for (auto& rec : sofar) {
		while(rec.find(newEsc)!=std::string::npos) {
			//first back to Escape
			rec = rec.replace(rec.find(newEsc),newEsc.length(),esc);
			//second remove Escape
			rec = cSpaceFromEscape(rec);
		}
	}


		for (auto& rec : sofar) {
				if (dbg) { _dbg3("rec "<< rec);};
			}

	// exactly 2 elements, with "" for missing elements
	decltype(sofar) cmdPart;
	decltype(sofar) cmdArgs;
	if (sofar.size()<2) {
		cmdPart = sofar;
	}
	else {
		cmdPart.insert( cmdPart.begin(), sofar.begin(), sofar.begin()+2 );
		cmdArgs.insert( cmdArgs.begin(), sofar.begin()+2, sofar.end() );

	}
	while (cmdPart.size()<2) cmdPart.push_back("");
	if (dbg) { _dbg3("parts "<< vectorToStr(cmdPart));};
	if (dbg) { _dbg3("args "<< vectorToStr(cmdArgs));}

	if (GetLastCharIf(sofar_str)==" ") {
		if( sofar.size()>=1 ) { // if there is any last-word element:
		_dbg3("Adding space after last word to mark that it was ended");
			sofar.at( sofar.size()-1 )+=" "; // append the last space - to the last word so that we know it was ended.
		}
	}

	const vector<string> cmdFrontOpt = {"--H0","--HL","--HT","--HV","--hint-remote","--hint-cached","--vpn-all-net"};

	const string topic  =  cmdPart.at(0) ;
	const string action =  cmdPart.at(1) ;

	int full_words=0;
	int started_words=0;

	bool last_word_pending=false;
	size_t nr=0;
	string prev_char;
	for (auto rec : sofar) {
		if (rec!="") started_words++;
		if (last_word_pending) { full_words++; last_word_pending=0; }
		if (GetLastCharIf(rec)==" ") full_words++; else last_word_pending=1; // we ended this part, without a space, so we have a chance to count it
		// still as finished word if there is a word after this one
		++nr;
		prev_char = rec;
	}
	string current_word="";
	if (full_words < started_words) current_word = sofar.at(full_words);
	if (dbg) { _dbg3("full_words=" << full_words << " started_words="<<started_words
		<< " topic="<<topic << " action="<<action
		<< " current_word="<<current_word <<endl);
	}

	// TODO produce the object of parsed commandline by the way of parsing current sofar string
	// (and return - via referenced argument)

	// * possib variable - short for "possibilities"

	// TODO support discarding forward-opion flags
	// ...

	// === at 1st (non-front-option) word (topic) ===

	if (full_words<1) { // at 1st word (topic) -> show all level 1 cmdnames

		return WordsThatMatch(  current_word  ,  vector<string>{"account", "account-in", "account-out", "asset", "basket", "cash", "cheque", "contract", "market", "mint", "msg", "msguard", "nym", "nym-cred", /*"receipt"??,*/ "server", "text", "voucher"/*, "wallet"??*/} + cmdFrontOpt  ) ;
		//commented procedures are those which we ain't sure if they will appear - definitions below
	}

	// === at 2nd (non-forward-option) word (action) ===


	if (topic=="account") {

		if (full_words<2) { // word2 - the action:
			return WordsThatMatch(  current_word  ,  vector<string>{"new", "ls", "refresh", "rm", "mv"} ) ;
		}
		if (full_words<3) { // word3 (cmdArgs.at(0))
			if (action=="new") {
				return WordsThatMatch(  current_word  ,  nOT::nUse::useOT.assetsGetNames() ) ;
			}
			if (action=="ls") {
				nOT::nUtils::DisplayVectorEndl( cout, nOT::nUse::useOT.accountsGet() ); // <====== Execute
				return vector<string>{};
			}
			if (action=="refresh") {
				return WordsThatMatch(  current_word  ,  nOT::nUse::useOT.nymsGetMy() ) ;
			}
			if (action=="rm") {
				return WordsThatMatch(  current_word  ,  nOT::nUse::useOT.accountsGet() ) ;
			}
			if (action=="mv") {
				return WordsThatMatch(  current_word  ,  nOT::nUse::useOT.accountsGet() ) ;
			}
		}

		if (full_words<4) { // word4 (cmdArgs.at(1))
			if (action=="new") {
				if (nOT::nUse::useOT.assetCheckIfExists(cmdArgs.at(0))) {
					return vector<string>{};
				}
				else {
					std::cout << "asset " << cSpaceFromEscape(cmdArgs.at(0)) << " don't exists" << endl;
					return vector<string>{};
				}
			}
			if (action=="rm") {
				if (nOT::nUse::useOT.accountCheckIfExists(cmdArgs.at(0))) {
					return vector<string>{nOT::nUse::useOT.accountDelete(cmdArgs.at(0))};
				}
				else {
					std::cout << "No account with this name: "  << (cmdArgs.at(0)) << endl;
					return vector<string>{};
				}
			}
			if (action=="mv") {
				std::cout <<"Pass new account name";
				return vector<string>{};
			}
		}

		if (full_words<5) { // word5 (cmdArgs.at(2))
			if (action=="new") {
				if (!nOT::nUse::useOT.accountCheckIfExists(cmdArgs.at(1))) { // make sure that the name is unique
 					nOT::nUse::useOT.accountCreate(cmdArgs.at(0), cmdArgs.at(1)); // <====== Execute
					return vector<string>{};
				}
				else {
					std::cout << "Name " << cmdArgs.at(1) << " exists, choose another name ";
					return vector<string>{};
				}

			}
			if (action=="mv") {
				if (!nOT::nUse::useOT.accountCheckIfExists(cmdArgs.at(1))) { // make sure that the name is unique
					nOT::nUse::useOT.accountRename(cmdArgs.at(0), cmdArgs.at(1)); // <====== Execute
					return vector<string>{};
				}
				else {
					std::cout << "Name " << cmdArgs.at(1) << " exists, choose another name ";
					return vector<string>{};
				}
			}
		}

	} // account

	if (topic=="account-in") {
		if (full_words<2) { // we work on word2 - the action:
			return WordsThatMatch(  current_word  ,  vector<string>{"accept", "ls"} ) ;
		}
		if (full_words<3) { // we work on word3 - var1
			if (action=="accept") {
				//TODO
				return WordsThatMatch(  current_word  ,  vector<string>{"--all", "<paymentID>"} ) ;
			}
			if (action=="ls") {
				//TODO
				return WordsThatMatch(  current_word  ,  vector<string>{"<accountID>"} ) ;
			}
		}
	}

	if (topic=="account-out") {
		return WordsThatMatch(  current_word  ,  vector<string>{"ls"} ) ;
	}

	if (topic=="asset") {
		if (full_words<2) { // we work on word2 - the action:
			return WordsThatMatch(  current_word  ,  vector<string>{"new", "ls"} ) ;
		}
		if (full_words<3) { // we work on word3 - cmdArgs.at(0) - asset name
			if (action=="ls") {
				return WordsThatMatch(  current_word  ,  nOT::nUse::useOT.assetsGetNames() ) ;
			}
			else if (action=="new") {
				std::cerr << "Type name of asset" << endl;
				return vector<string>{};
			}
		}
	}

	if (topic=="basket") {
		return WordsThatMatch(  current_word  ,  vector<string>{"exchange", "ls","new" } ) ;
	}

	if (topic=="cash") {
		if (full_words<2) { // we work on word2 - the action:
			return WordsThatMatch(  current_word  ,  vector<string>{"send"} ) ;
		}
		if (full_words<3) {
			if (action=="send") {
				return WordsThatMatch(  current_word  ,  vector<string>{"<mynym>"} ); //TODO Suitable changes to this part - propably after merging with otlib
			}
		}
		if (full_words<4) { // we work on word3 - var1
			if (cmdArgs.at(0)=="send") {
				return WordsThatMatch(  current_word  ,  vector<string>{"<hisnym>"} ); //TODO Suitable changes to this part - propably after merging with otlib
			}
		}
	}

	if (topic=="cheque") {
		return WordsThatMatch(  current_word  ,  vector<string>{"new"} ) ;
	}

	if (topic=="contract") {
		if (full_words<2) { // we work on word2 - the action:
			return WordsThatMatch(  current_word  ,  vector<string>{"get", "new", "sign"} ) ;
		}
		if (full_words<3) {
			if (action=="get") {
				return WordsThatMatch(  current_word  ,  vector<string>{"<contractID>"} ); //TODO Suitable changes to this part - propably after merging with otlib
			}
		}
	}

	if (topic=="market") {
		return WordsThatMatch(  current_word  ,  vector<string>{"ls"} ) ;
	}

	if (topic=="mint") {
		return WordsThatMatch(  current_word  ,  vector<string>{"new"} ) ;
	}

	if (topic=="msg") {
		if (full_words<2) { // we work on word2 - the action:
			return WordsThatMatch(  current_word  , vector<string>{"send","ls","rm","mv"} );
		}

		if (full_words<3) { // we work on word3 - var1 - sender name
			if (action=="ls") {
				//return WordsThatMatch(  current_word  ,  nOT::nUse::useOT.nymsGetMy() ) ;
				nOT::nUse::useOT.msgGetAll(); // <====== Execute
				return vector<string>{};
			}
			if (action=="send") {
				//nOT::nUse::useOT.msgSend();
				//return vector<string>{};
				return WordsThatMatch(  current_word  ,  nOT::nUse::useOT.nymsGetMy() );
			}
			if (action=="mv") {
				return WordsThatMatch(  current_word  ,  vector<string>{"Where-to?"} ); // in mail box... will there be other directories?
			}
			if (action=="rm") {
				return WordsThatMatch(  current_word  ,  vector<string>{"--all", "index"} );
			}
		}

		if (full_words<4) { // we work on word4 - var2 -  recipient name
			if (action=="ls") {
				if (nOT::nUse::useOT.nymCheckByName(cmdArgs.at(0))) {
					nOT::nUse::useOT.msgGetAll(); // <====== Execute
					return vector<string>{};
				}
				else {
					std::cerr << "Can't find that nym: " << cmdArgs.at(0);
					return vector<string>{};
				}
			}
			if (action=="send") {
				if (nOT::nUse::useOT.nymCheckByName(cmdArgs.at(0))) {
					return WordsThatMatch(  current_word  , nOT::nUse::useOT.nymsGetMy() );
				}
				else {
					std::cerr << "Can't find that nym: " << cmdArgs.at(0);
					return vector<string>{};
				}
			}
		}

		if (full_words<5) { // we work on word5 - var3
			if (action=="send") {
				if (nOT::nUse::useOT.nymCheckByName(cmdArgs.at(1))) {
					return vector<string>{}; // ready for message
				}
				else {
					std::cerr << "Can't find that nym: " << cmdArgs.at(1);
					return vector<string>{};
				}
			}
		}

		if (full_words<6) { // we work on word6
			if (action=="send") { // message text
				nOT::nUse::useOT.msgSend(cmdArgs.at(0), cmdArgs.at(1), cmdArgs.at(2)); // <====== Execute
				return vector<string>{};
			}
		}


	} // msg

	if (topic=="nym") {
		if (full_words<2) { // we work on word2 - the action:
			return WordsThatMatch(  current_word  ,  vector<string>{"check", "edit", "export", "import", "info", "ls", "new", "refresh", "register", "rm"} ) ;
		}
		if (full_words<3) { // we work on word3 - cmdArgs.at(0)

			if (action=="ls") {
				nOT::nUtils::DisplayVectorEndl(cout, nOT::nUse::useOT.nymsGetMy(), "\n"); // <====== Execute
				return vector<string>{};
			}

			if (action=="new") {
				nOT::nUtils::DisplayStringEndl(cout, "Type new Nym name"); // <====== Execute
				return vector<string>{};
			}
			if (action=="rm") {
				return WordsThatMatch( current_word  ,  nOT::nUse::useOT.nymsGetMy() );//TODO Suitable changes to this part - propably after merging with otlib
			}
			if (action=="info") {
				return WordsThatMatch( current_word  ,  nOT::nUse::useOT.nymsGetMy() );//TODO Suitable changes to this part - propably after merging with otlib
			}
			if (action=="edit") {
				return WordsThatMatch( current_word  ,  nOT::nUse::useOT.nymsGetMy() );//TODO Suitable changes to this part - propably after merging with otlib
			}
			if (action=="register") {
				return WordsThatMatch( current_word  ,  nOT::nUse::useOT.nymsGetMy() );//TODO server name
			}
			if (action=="check") { // TODO interactive input
				nOT::nUtils::DisplayStringEndl(cout, "Type NymID to check"); // <====== Execute
				return vector<string>{};
			}
		}

		if (full_words<4) { // we work on word4 - var2
			if (action=="new") {
				nOT::nUse::useOT.nymCreate(cmdArgs.at(0)); // <====== Execute
				return vector<string>{};
			}
			if (action=="info") {
				nOT::nUtils::DisplayStringEndl( cout, nOT::nUse::useOT.nymGetInfo(cmdArgs.at(0)) ); // <====== Execute
				return vector<string>{};
			}
			if (action=="register") {
				nOT::nUse::useOT.nymRegister(cmdArgs.at(0)); // <====== Execute
				return vector<string>{};
			}
			if (action=="check") {
				nOT::nUse::useOT.nymCheck(cmdArgs.at(0)); // <====== Execute
				return vector<string>{};
			}
		}



	} // nym

	if (topic=="nym-cred") {
		return WordsThatMatch(  current_word  ,  vector<string>{"new", "revoke" , "show"} ) ;
	}

	/*if (topic=="receipt") {
		return WordsThatMatch(  current_word  ,  vector<string>{"[BLANK]"} ) ;
	}*/

	if (topic=="server") {
		if (full_words<2) { // we work on word2 - the action:
			return WordsThatMatch(  current_word  ,  vector<string>{"ls", "new", "add"} ) ;
		}

		if (full_words<3) { // we work on word3 - var1
			if (action=="ls") {
				return WordsThatMatch(  current_word  ,  nOT::nUse::useOT.serversGet() ) ;
			}
		}

	}

	if (topic=="text") {
		if (full_words<2) { // we work on word2 - the action:
			return WordsThatMatch(  current_word  ,  vector<string>{"encode", "decode", "encrypt", "decrypt" } ) ; //coding
		}

		if (full_words<3) { // we work on word3 - var1
			if (action=="encode") { // text to encode
				nOT::nUtils::DisplayStringEndl( cout, nOT::nUse::useOT.textEncode(nOT::nUtils::GetMultiline())); // <====== Execute
				return vector<string>{};
			}

			if (action=="decode") { // text to decode
				nOT::nUtils::DisplayStringEndl( cout, nOT::nUse::useOT.textDecode(nOT::nUtils::GetMultiline()) ); // <====== Execute
				return vector<string>{};
			}

			if (action=="encrypt") { // recipient Nym Name
				return WordsThatMatch(  current_word  ,  nOT::nUse::useOT.nymsGetMy());
			}

			if (action=="decrypt") { // recipient Nym Name
				return WordsThatMatch(  current_word  ,  nOT::nUse::useOT.nymsGetMy());
			}
		}

		if (full_words<4) { // we work on word4 - var2
			if (action=="encode") {
				nOT::nUtils::DisplayStringEndl( cout, nOT::nUse::useOT.textEncode(cmdArgs.at(0))); // <====== Execute
				return vector<string>{};
			}

			if (action=="decode") {
				return WordsThatMatch(  current_word  ,  vector<string>{} ) ; //encoded text will be always multiline
			}

			if (action=="encrypt") {
				nOT::nUtils::DisplayStringEndl( cout, nOT::nUse::useOT.textEncrypt(cmdArgs.at(0), nOT::nUtils::GetMultiline())); // <====== Execute
				return vector<string>{};
			}

			if (action=="decrypt") {
				nOT::nUtils::DisplayStringEndl( cout, nOT::nUse::useOT.textDecrypt(cmdArgs.at(0), nOT::nUtils::GetMultiline())); // <====== Execute
				return vector<string>{};
			}
		}

		if (full_words<5) { // we work on word5 - var3
			if (action=="encrypt") { // if plain text is passed as argument (don't implemented for decrypt action because of multiline encrytped block)
				nOT::nUtils::DisplayStringEndl( cout, nOT::nUse::useOT.textEncrypt(cmdArgs.at(0), cmdArgs.at(1))); // <====== Execute
				return vector<string>{};
			}
		}
	} // topic=="text"

	if (topic=="voucher") {
		return WordsThatMatch(  current_word  ,  vector<string>{"new"} ) ;
	}

	/*if (topic=="wallet") {
		return WordsThatMatch(  current_word  ,  vector<string>{"status"} ) ;
	}*/
	return vector<string>{};
	//throw std::runtime_error("Unable to handle following completion: sofar_str='" + ToStr(sofar_str) + "' in " + OT_CODE_STAMP);
}

class cInteractiveShell {
	public:
		cInteractiveShell();
		void runOnce(const string line);
		void runEditline();
	protected:
		bool dbg;
};

cInteractiveShell::cInteractiveShell()
:dbg(false)
{ }

void cInteractiveShell::runOnce(const string line) { // used with bash autocompletion
	nOT::nUtils::current_logger.setDebugLevel(100);
	nOT::nOTHint::cHintManager hint;
	vector<string> out = hint.AutoCompleteEntire(line);
	nOT::nUtils::DisplayVectorEndl(std::cout, out);
}

extern bool my_rl_wrapper_debug; // external

bool my_rl_wrapper_debug; // external

// [null-trem-cstr] definition: as defined by readline, the format of null-term-cstr is:
// dynamic array, null terminated, of dynamic c-strings.
// caller is responsible for deallocation of the pointed strings data (using free) as well as the array itself
// (using free).
// it can be NULL for 0 element array
// exmple:
// NULL - empty array
// { strdup("foo") , NULL } - 1 record array
// { strdup("foo") , strdup("bar", NULL } - 2 record array


// When readline will call us to complete "ot m" then our function will be called with number=0,
// then it should cache possibilities of endings "msg" "mint" "msguard", and return 0th (first) one.
// Next it will be called with other number (probably 1,2,3..) and return N-th possibility.
// Function is non-reentrant also in the meaing that it can not be called in interlace, e.g.
// ("ot m",0) then ("ot m",1) then ("ot x",0) and suddenly back to ("ot x",2) without reinitialization
// (done with number=0) is an error (at least currently, in future we might cache various completion
// arrays, or recalculate on change)


static char* completionReadlineWrapper(const char *sofar , int number) {
	bool dbg = my_rl_wrapper_debug || 1;
	if (dbg) _dbg3("sofar="<<sofar<<" number="<<number<<" rl_line_buffer="<<rl_line_buffer<<endl);
	string line;
	if (rl_line_buffer) line = rl_line_buffer;
	line = line.substr(0, rl_point); // Complete from cursor position
	nOT::nOTHint::cHintManager hint;
	static vector <string> completions;
	if (number == 0) {
		_dbg3("Start autocomplete (during first callback, number="<<number<<")");
		completions = hint.AutoCompleteEntire(line); // <--
		nOT::nUtils::DBGDisplayVectorEndl(completions); //TODO: display in debug
		_dbg3("Done autocomplete (during first callback, number="<<number<<")");
	}

	auto completions_size = completions.size();
	if (!completions_size) {
		_dbg3("Stop autocomplete: no matching words found because completions_size="<<completions_size);
		return NULL; // <--- RET
	}
	if (dbg) _dbg3( "completions_size=" << completions_size << endl);
	if (number==completions_size) { // stop
		_dbg3("Stop autocomplete because we are at last callback number="<<number<<" completions_size="<<completions_size);
		return NULL;
	}
	_dbg3("Current completion number="<<number<<" is: [" + completions.at(number) + "]");
	return strdup( completions.at(number).c_str() ); // caller must free() this memory
}

char ** completion(const char* text, int start, int end __attribute__((__unused__))) {
	char **matches;
	matches = (char **)NULL;
	matches = rl_completion_matches (text, completionReadlineWrapper);
	return (matches);
}

void cInteractiveShell::runEditline() {
	char *buf = NULL;
	my_rl_wrapper_debug = dbg;
	rl_attempted_completion_function = completion;
	rl_bind_key('\t',rl_complete);
	while((buf = readline("commandline-part> "))!=NULL) { // <--- readline()
		std::string word;
		if (buf) word=buf; // if not-null buf, then assign
		if (buf) { free(buf); buf=NULL; }
		// do NOT use buf variable below.

		if (dbg) cout << "Word was: " << word << endl;
		std::string cmd;
		if (rl_line_buffer) cmd = rl_line_buffer; // save the full command into string
		cmd = cmd.substr(0, cmd.length()-1); // remove \n

		if (dbg) cout << "Command was: " << cmd << endl;
		auto cmd_trim = nOT::nUtils::trim(cmd);
		if (cmd_trim=="exit") break;
		if (cmd_trim=="quit") break;
		if (cmd_trim=="q") break;

		if (cmd.length()) {
		add_history(cmd.c_str()); // TODO (leaks memory...) but why

		//Execute in BuildTreeOfCommandlines:
		nOT::nOTHint::cHintManager hint;
		hint.AutoCompleteEntire(cmd);
		}
	}
	if (buf) { free(buf); buf=NULL; }
	clear_history(); // http://cnswww.cns.cwru.edu/php/chet/readline/history.html#IDX11
}

}; // namespace nOTHint
}; // namespace nOT
// ########################################################################
// ########################################################################
// ########################################################################

std::string gVar1; // to keep program input argument for testcase_complete_1
// ====================================================================

bool LoadScript_Main(const std::string &thefile_name) { // here we temporarly call in source code that is totall experimental (taken from git branches)
// returns true if we should continue with the main program
	using std::string;
	std::string cmd="";
	std::ifstream thefile( thefile_name.c_str() );
	bool anything=false; // did we run any speciall test
	bool force_continue=false; // should we continue to main program forcefully
	bool read_anything=false;
	while (  (!thefile.eof()) && (thefile.good())  ) {
		getline(thefile, cmd);
		_dbg2("cmd="+cmd);
		if (!read_anything) { read_anything=true; _dbg1("Started reading data from "+thefile_name); }
		if (cmd=="quit") {
			_note("COMMAND: "<<cmd<<" - QUIT");
			return false;
		}
		else if (cmd=="tree") {
			_note("Will test new functions and exit");
			_note("TTTTTTTT");
			nOT::nOTHint::cHintManager hint;
			hint.TestNewFunction_Tree();
			_note("That is all, goodby");
		}
		else if ((cmd=="hello")) {
			_note("COMMAND: Hello world.");
		}
		else if ((cmd=="continue")||(cmd=="cont")) {
			_dbg1("Will continue");
			force_continue = true;
		}
	} // entire file
	bool will_continue = (!anything) || force_continue ;
	if (!will_continue) _note("Will exit then.");
	return will_continue;
} // LocalDeveloperCommands()

void LoadScript(const std::string &script_filename, const std::string &title) {
	_note("Script " + script_filename + " ("+title+")");
	try {
		LoadScript_Main(script_filename);
	}
	catch(const std::exception &e) {
		_erro("\n*** In SCRIPT "+script_filename+" The testcases code thrown an exception: " << e.what());
	}
	catch(...) {
		_erro("\n*** In SCRIPT "+script_filename+" The testcases code thrown an UNKNOWN exception!");
	}
}

// ====================================================================

int main(int argc, char **argv) {
	LoadScript("autostart-dev.local", "autostart script");
	int a=42; // test

	// demo of OT
	/*try {
				nOT::nTests::exampleOfOT();
		}
	catch(const std::exception &e) {
		std::cerr << "\n*** The exampleOfOT code thrown an exception: " << e.what() << std::endl;
	}
	catch(...) {
		std::cerr << "\n*** The exampleOfOT code thrown an UNKNOWN exception!" << std::endl;
	}*/

	try {
		//nOT::nTests::testcase_run_all_tests();
	}
	catch(const std::exception &e) {
		_erro("\n*** The testcases code thrown an exception: " << e.what());
	}
	catch(...) {
		_erro("\n*** The testcases code thrown an UNKNOWN exception!");
	}

	int ret=1;
	try {
		LoadScript_Main("autostart.local"); // move to main_main() probably
		ret = nOT::nTests::main_main(argc, argv);
	}
	catch(const std::exception &e) {
		_erro("\n*** The testcases code thrown an exception: " << e.what());
	}
	catch(...) {
		_erro("\n*** The testcases code thrown an UNKNOWN exception!");
	}

	return ret;
}

// int pole(const int r) { 	r=3; }


int nOT::nTests::main_main(int argc, char **argv) {
	vector<string> args;
	int status = 0;
	if (! (argc>=1)) {
		throw std::runtime_error("Main program called with 0 arguments (not even program name).");
	}
	args.reserve(argc-1); for (int i=1; i<argc; ++i) args.push_back(argv[i]); // from 1 - skip program name

	size_t nr=0;
	for(auto arg: args) {
		if (arg=="--complete-shell") {
			nOT::nOTHint::cInteractiveShell shell;
			shell.runEditline();
		}
		else if (arg=="--complete-one") {
			string v;  bool ok=1;  try { v=args.at(nr+1); } catch(...) { ok=0; } //
			if (ok) {
				nOT::nOTHint::cInteractiveShell shell;
				shell.runOnce(v);
			}
			else {
				_erro("Missing variables for command line argument '"<<arg<<"'");
				status = 1;
			}
		}
		++nr;
	}

/*
	if (argc>1) {
		std::string arg1 = argv[1];

		if (arg1=="--complete-shell") {
		} // SHELL
		else if (arg1=="--complete-one") {
			if (argc>2) {
				gVar1 = argv[2];
				nOT::nTests::testcase_complete_1_wrapper();
				//std::cout << gVar1 << std::endl;
			} // COMPLETE with it's var1
			else { std::cerr<<"No string provided for completion."<<std::endl; return 1; }
		} // COMPLETE
	} else {
		std::cerr<<"No arguments given."<<std::endl; return 1;
	}
*/
	return status;
}
// ====================================================================

// #####################################################################
// #####################################################################
// #####################################################################

namespace nOT {
namespace nTests {


INJECT_OT_COMMON_USING_NAMESPACE_COMMON_2; // <=== namespaces

bool testcase_complete_1(const string &sofar) {
	map<string , vector<string> > const cases {
		 { "m", { "msg", "msguard" } }
		,{ "ms", { "msg", "msguard" } }
		,{ "msg", { "msg", "msguard" } }
		,{ "msg ", { "send", "ls", "mv", "rm" } }
		,{ "msg s", { "send" } }
		,{ "msg se", { "send" } }
		,{ "msg sen", { "send" } }
		,{ "msg send", { "send" } }
		,{ "msg send ", { "mynym1", "mynym2" } }
		,{ "msg send m", { "mynym1", "mynym2" } }
		,{ "msg send my", { "mynym1", "mynym2" } }
		,{ "msg send myn", { "mynym1", "mynym2" } }
		,{ "msg send myny", { "mynym1", "mynym2" } }
		,{ "msg send mynym", { "mynym1", "mynym2" } }
		,{ "msg send mynym1", { "mynym1" } }
		,{ "msg send mynym1 ", { "hisnym1", "hisnym2" } }
		,{ "msg send mynym1 h", { "hisnym1", "hisnym2" } }
		,{ "msg send mynym1 hi", { "hisnym1", "hisnym2" } }
		,{ "msg send mynym1 his", { "hisnym1", "hisnym2" } }
		,{ "msg send mynym1 hisn", { "hisnym1", "hisnym2" } }
		,{ "msg send mynym1 hisny", { "hisnym1", "hisnym2" } }
		,{ "msg send mynym1 hisnym", { "hisnym1", "hisnym2" } }
		,{ "msg send mynym1 hisnym1", { "hisnym1" } }
		,{ "msg send mynym1 hisnym2", { "hisnym2" } }
		,{ "msg send mynym2", { "mynym2" } }
		,{ "msg send mynym2 ", { "hisnym1", "hisnym2" } }
		,{ "msg send mynym2 h", { "hisnym1", "hisnym2" } }
		,{ "msg send mynym2 hi", { "hisnym1", "hisnym2" } }
		,{ "msg send mynym2 his", { "hisnym1", "hisnym2" } }
		,{ "msg send mynym2 hisn", { "hisnym1", "hisnym2" } }
		,{ "msg send mynym2 hisny", { "hisnym1", "hisnym2" } }
		,{ "msg send mynym2 hisnym", { "hisnym1", "hisnym2" } }
		,{ "msg send mynym2 hisnym1", { "hisnym1" } }
		,{ "msg send mynym2 hisnym2", { "hisnym2" } }
		,{ "msg l", { "ls" } }
		,{ "msg ls", { "ls" } }
		,{ "msg m", { "mv" } }
		,{ "msg mv", { "mv" } }
		,{ "msg mv ", { "msgid1", "msgid2" } }
		,{ "msg mv m", { "msgid1", "msgid2" } }
		,{ "msg mv ms", { "msgid1", "msgid2" } }
		,{ "msg mv msg", { "msgid1", "msgid2" } }
		,{ "msg mv msgi", { "msgid1", "msgid2" } }
		,{ "msg mv msgid", { "msgid1", "msgid2" } }
		,{ "msg mv msgid1", { "msgid1" } }
		,{ "msg mv msgid2", { "msgid2" } }
		,{ "msg r", { "rm" } }
		,{ "msg rm", { "rm" } }
		,{ "msg rm ", { "msgid1", "msgid2" } }
		,{ "msg rm m", { "msgid1", "msgid2" } }
		,{ "msg rm ms", { "msgid1", "msgid2" } }
		,{ "msg rm msg", { "msgid1", "msgid2" } }
		,{ "msg rm msgi", { "msgid1", "msgid2" } }
		,{ "msg rm msgid", { "msgid1", "msgid2" } }
		,{ "msg rm msgid1", { "msgid1" } }
		,{ "msg rm msgid2", { "msgid2" } }
		,{ "msgu", { "msguard" } }
		,{ "msgua", { "msguard" } }
		,{ "msguar", { "msguard" } }
		,{ "msguard", { "msguard" } }
		,{ "msguard ", { "info", "start", "stop" } }
		,{ "msguard i", { "info" } }
		,{ "msguard in", { "info" } }
		,{ "msguard inf", { "info" } }
		,{ "msguard info", { "info" } }
		,{ "msguard s", { "start", "stop" } }
		,{ "msguard st", { "start", "stop" } }
		,{ "msguard sta", { "start" } }
		,{ "msguard star", { "start" } }
		,{ "msguard start", { "start" } }
		,{ "msguard sto", { "stop" } }
		,{ "msguard stop", { "stop" } }
		,{ "n" , { "nym"} }
		,{ "ny" , { "nym"} }
		,{ "nym" , { "nym"} }
		,{ "nym " , { "ls", "new" , "rm"} }
		,{ "nym l" , { "ls" } }
		,{ "nym ls" , { "ls" } }
		,{ "nym n" , { "new" } }
		,{ "nym ne" , { "new" } }
		,{ "nym new" , { "new" } }
		,{ "nym r" , { "rm"} }
		,{ "nym rm" , { "rm"} }
	};

	nOT::nOTHint::cHintManager hint;

	string line(sofar);
	line.erase (0,3); // need to erase 'ot' word from intput string // TODO erase it before, length of argv[0] could differ, e.g. "ot_secure"
	// TODO verify length (avoid underflow)

	vector<string> out = hint.AutoComplete(line);

	//Convert each Escape on Space
	int i = 0;
	for(auto rec:out)	{
		out[i] = cSpaceFromEscape(rec);
		i++;
	}
	//nOT::nUtils::DisplayVector(std::cout, out); // FIXME polluting in testcase


	bool ok = 1;

	return ok;
}

bool testcase_complete_1_wrapper() {
	return nOT::nTests::testcase_complete_1(gVar1);
}

// ==================================================================
// ==================================================================
bool testcase_namespace_pollution(const cTestCaseCfg &testCfg) {
	class a {
	};

	using namespace nOT::nOTHint;

	#ifdef __unittest_mustfail_compile1
	{
		// using std::string; // without this
		string s; // <-- must be a compile error
	}
	#endif
	{
		using std::string;
		string s; // <-- must work
	}

	return true;
}

bool testcase_cxx11_memory(const cTestCaseCfg &testCfg) {
	using namespace nOT::nNewcli;
	using namespace nOT::nOTHint;

	// TODO capture output and verify expected output

	struct cObj {
			cObj() { /*cout<<"new"<<endl;*/ }
			~cObj() { /*cout<<"delete"<<endl;*/ }
	};

	unique_ptr<cObj> A( new cObj );

	return true;
}

bool testcase_fail1(const cTestCaseCfg &testCfg) {
	if (testCfg.debug) testCfg.ossErr<<"This special testcase will always FAIL, on purpose of testing the testcases framework."<<endl;
	return false;
}

bool testcase_fail2(const cTestCaseCfg &testCfg) {
	if (testCfg.debug) testCfg.ossErr<<"This special testcase will always FAIL, on purpose of testing the testcases framework."<<endl;
	throw std::runtime_error("This test always fails.");
}

bool helper_testcase_run_main_with_arguments(const cTestCaseCfg &testCfg , vector<string> tab ) {
	int argc = tab.size(); // <--
	typedef char * char_p;
	char_p * argv  = new char_p[argc]; // C++ style new[]

	bool dbg = testCfg.debug;   auto &err = testCfg.ossErr;
	if (dbg) err << "Testing " << __FUNCTION__ << " with " << argc << " argument(s): "  << endl;

	size_t nr=0;
	for(auto rec:tab) {
		argv[nr] = strdup(rec.c_str()); // C style strdup/free
		//if( dbg) {err << "argv " << argv[nr];}

		++nr;
		if( dbg) {err << rec; };
	}
	if (dbg) err << endl;

	bool ok=true;
	try {
		ok = main_main(argc, argv) == 0 ; // ... ok? TODO

		if (!ok) err << "BAD TEST " << __FUNCTION__ << " with " << argc << " argument(s): ";
	}
	catch(const std::exception &e) {
		ok=false;
		testCfg.ossErr << "\n *** in " << __FUNCTION__ << " catched exception: " << e.what() << endl;
	}
	for (int i=0; i<argc; ++i) { free( argv[i] ); argv[i]=NULL; } // free!
	delete []argv; argv=nullptr;
	return ok;
}

// Separate functions for failing tests:
bool testcase_run_main_args_fail1(const cTestCaseCfg &testCfg) {
	bool ok=true;
	const string programName="othint";

	if (!	helper_testcase_run_main_with_arguments(testCfg, vector<string>{programName,"--complete-one", "ot "} ) ) ok=false;
	if (!	helper_testcase_run_main_with_arguments(testCfg, vector<string>{programName,"--complete-one"} ) ) ok=false;
	if (!	helper_testcase_run_main_with_arguments(testCfg, vector<string>{programName} ) ) ok=false;

	return ok;
}

//All this tests should succeed:
bool testcase_run_main_args(const cTestCaseCfg &testCfg) {
	bool ok=true;
	const string programName="othint";

	if (!	helper_testcase_run_main_with_arguments(testCfg, vector<string>{programName,"--complete-one", "ot account new game\\ toke_ns TEST_CASE"} ) ) ok=false;
	if (!	helper_testcase_run_main_with_arguments(testCfg, vector<string>{programName,"--complete-one", "ot account rm TEST_CA_SE"} ) ) ok=false;
	if (!	helper_testcase_run_main_with_arguments(testCfg, vector<string>{programName,"--complete-one", "ot msg sen"} ) ) ok=false;

	return ok;
}

bool testcase_account(const cTestCaseCfg &testCfg) {
	bool ok=true;
/* TODO: check output
	map<string , vector<string> > const cases {
		 { "ot account ls", { ,  } }
		,{ "ot account new game\\ toke_ns TEST_CASE", { ,  } }
		,{ "ot account mv TEST_CASE TEST_CASE_MOVED", { ,  } }
		,{ "ot account refresh", { ,  } }
		,{ "ot account rm TEST_CASE_MOVED", { ,  } }
	}
	for(auto rec:out)

	nOT::nOTHint::cHintManager hint;
	vector<string> out = hint.AutoCompleteEntire(line);
	int i = 0;
	for(auto rec:out)	{
		out[i] = cSpaceFromEscape(rec);
		i++;
	}
	nOT::nUtils::DisplayVectorEndl(std::cout, out);

	*/

	// TODO: This code breaks autocompletion (autocompletion don't see current and previous word and complete with previous word):
	const string programName="othint";
	if (!	helper_testcase_run_main_with_arguments(testCfg, vector<string>{programName,"--complete-one", "ot account new game\\ toke_ns TEST_CASE"} ) ) ok=false;
	if (!	helper_testcase_run_main_with_arguments(testCfg, vector<string>{programName,"--complete-one", "ot account ls"} ) ) ok=false;
	if (!	helper_testcase_run_main_with_arguments(testCfg, vector<string>{programName,"--complete-one", "ot account mv"} ) ) ok=false;
	if (!	helper_testcase_run_main_with_arguments(testCfg, vector<string>{programName,"--complete-one", "ot account refresh"} ) ) ok=false;
	if (!	helper_testcase_run_main_with_arguments(testCfg, vector<string>{programName,"--complete-one", "ot account rm TEST_CA_SE"} ) ) ok=false;
	return ok;
}

bool testcase_run_cEscapeString(const cTestCaseCfg &testCfg) {
	bool ok=true;
	std::string test = "TestTest";
	std::string shouldBe = "T\\3stTe\\3t";
	test[1] = 3;
	test[6] = 3;
	std::string out = cEscapeString(test);
	if(out!=shouldBe) {
		ok = false;
		if (testCfg.debug)
		testCfg.ossErr<<"Bad Test cEscapeString: test string "<<test << " out " << out << " should be " <<shouldBe <<endl;
	}
	return ok;
}

bool testcase_run_all_tests() { // Can only run bool(*)(void) functions (to run more types casting is needed)
	_dbg3("=== test cases, unit tests ============================================");

	long int number_errors = 0; // long :o

	std::ostringstream quiet_oss;

	cTestCaseCfg testCfg(cerr, true);
	cTestCaseCfg testCfgQuiet(quiet_oss, false); // to quiet down the tests

	struct cTestCaseNamed {
		cTestCaseNamed( tTestCaseFunction func  , const string &name, bool expectedOutcome)
		:mFunc(func), mName(name) , mExpectedOutcome(expectedOutcome) // XXX
		{
		}

		tTestCaseFunction mFunc;
		string mName;
		bool mExpectedOutcome; // must succeed or fail?
	};
	vector<cTestCaseNamed> vectorOfFunctions;

	// [stringification], [macro-semicolon-trick]
	#define xstr(s) str(s)
	#define str(s) #s
	#define AddFunction(XXX) do {   vectorOfFunctions.push_back( cTestCaseNamed( & XXX , str(XXX) , true ));   } while(0)
	#define AddFunctionMustFail(XXX) do {   vectorOfFunctions.push_back( cTestCaseNamed( & XXX , str(XXX) , false ));   } while(0)
	AddFunction(testcase_namespace_pollution);
	AddFunction(testcase_cxx11_memory);
	AddFunction(testcase_run_main_args);
	AddFunction(testcase_run_cEscapeString);
	//AddFunction(testcase_account);

	AddFunctionMustFail(testcase_fail1); // only for testing of this test code
	AddFunctionMustFail(testcase_fail2); // only for testing of this test code
	AddFunctionMustFail(testcase_run_main_args_fail1);

	#undef AddFunction
	#undef xstr
	#undef str

	std::ostringstream failure_details;

	int nr=0;
	for(auto it = vectorOfFunctions.begin(); it != vectorOfFunctions.end(); ++it) { // Calling all test functions
		const cTestCaseNamed &test = *it;
		bool result = 0;
		string exception_msg;
		try {
			cTestCaseCfg & config = ( (test.mExpectedOutcome == 0) ? testCfgQuiet : testCfg ); // if test should fail - make it quiet
			cerr << "--- start test --- " << test.mName << " (config=" << config << ")" << " \n";
			result = (   test.mFunc   )( config ); // <--- run the test with config
			cerr << "--- done test --- " << test.mName << " \n\n";
		} catch(const std::exception &e) { exception_msg = e.what(); }

		bool as_expected = (result == test.mExpectedOutcome);

		if (!as_expected) {
			number_errors++;
			std::ostringstream msgOss; msgOss << "test #" << nr << " " << test.mName  <<  " failed"
				<< "(result was "<<result<<" instead expected "<<test.mExpectedOutcome<<") ";
			if (exception_msg.size()) msgOss << " [what: " << exception_msg << "]";
			msgOss<<"!";
			string msg = msgOss.str();
			//_dbg3(" *** " << msg);
			failure_details << " " << msg << " ";
		}
		++nr;
	}

	if (number_errors == 0) {
		//cout << "All tests completed successfully." << endl;
	}
	else {
		cerr << "*** Some tests were not completed! (" << failure_details.str() << ")" << endl;
	}
		cerr << "=== test cases, unit tests - done =====================================" << endl;

	return number_errors==0;
}

void exampleOfOT() {
	OTAPI_Wrap::AppInit(); // Init OTAPI
	std::cout <<"loading wallet: ";
	if(OTAPI_Wrap::LoadWallet())
	std::cout <<"wallet was loaded "<<std::endl;
	else
	std::cout <<"error while loanding wallet "<<std::endl<<std::endl;

	std::cout <<std::endl<<"account count :"<< OTAPI_Wrap::GetAccountCount()<<std::endl;
	std::cout <<"list of account :"<< std::endl;

	std::string SERVER_ID;
	std::string  USER_ID = "DYEB6U7dcpbwdGrftPnslNKz76BDuBTFAjiAgKaiY2n";

		for(int i = 0 ; i < OTAPI_Wrap::GetAccountCount ();i++) {
			std::string ACCOUNT_ID = OTAPI_Wrap::GetAccountWallet_ID (i);
			std::cout <<OTAPI_Wrap::GetAccountWallet_Name ( OTAPI_Wrap::GetAccountWallet_ID (i)	) <<std::endl;

			std::cout << std::endl<<"server count: " << OTAPI_Wrap::GetServerCount () << std::endl;
			std::cout << "list of servers: " << std::endl;

			for(int i = 0 ; i < OTAPI_Wrap::GetServerCount ();i++) {
					SERVER_ID = OTAPI_Wrap::GetServer_ID (i);
					std::string Name = OTAPI_Wrap::GetServer_Name (SERVER_ID);
					std::cout << Name<< "\t\t\tid "<<  SERVER_ID  << std::endl;

					/*std::cout <<"connecting to server: ";
					std::cout <<OTAPI_Wrap::checkServerID(SERVER_ID,USER_ID)<< std::endl;

					std::cout << std::endl<< "asset from server "<<OTAPI_Wrap::getAccount(SERVER_ID, USER_ID,ACCOUNT_ID);
*/
			/*
			std::string  Pubkey_Encryption = OTAPI_Wrap::LoadUserPubkey_Encryption 	( 	USER_ID	);
	bool OTAPI_Wrap::ConnectServer 	( 	ID,USER_ID,
		const std::string &  	strCA_FILE,
		const std::string &  	strKEY_FILE,
		const std::string &  	strKEY_PASSWORD
	) */
			}
		}

	//bool connected  = OTAPI_Wrap::ConnectServer 	( SERVER_ID,USER_ID,strCA_FILE,strKEY_FILE,strKEY_PASSWORD);

	std::cout << std::endl<<"nym count: " << OTAPI_Wrap::GetNymCount () << std::endl;

	std::cout << "list of nyms: " << std::endl;
	for(int i = 0 ; i < OTAPI_Wrap::GetNymCount ();i++) {
			std::string nym_ID = OTAPI_Wrap::GetNym_ID (i);
			std::string nym_Name = OTAPI_Wrap::GetNym_Name (nym_ID);
			std::cout << nym_Name<< "\t\t\tid "<<  nym_ID  << std::endl;

			std::cout <<" inbox mail count for nym:"<<OTAPI_Wrap::GetNym_MailCount(nym_ID) << std::endl;
			for(int i = 0 ; i < OTAPI_Wrap::GetNym_MailCount (nym_ID);i++) {
					std::cout << std::endl<< "inbox mail numer "<< i+1<<std::endl << OTAPI_Wrap::GetNym_MailContentsByIndex (nym_ID,i)<<std::endl;
					}

			std::cout <<" outbox mail count for nym:"<<OTAPI_Wrap::GetNym_OutmailCount(nym_ID) << std::endl;
			for(int i = 0 ; i < OTAPI_Wrap::GetNym_OutmailCount (nym_ID);i++) {
					std::cout << std::endl<< "outbox mail numer "<< i+1<<std::endl << OTAPI_Wrap::GetNym_OutmailContentsByIndex (nym_ID,i)<<std::endl;
					}
			std::cout <<"RevokedCred for nym:"<<OTAPI_Wrap::GetNym_RevokedCredCount(nym_ID) << std::endl;
			for(int i = 0 ; i < OTAPI_Wrap::GetNym_RevokedCredCount (nym_ID);i++) {
					std::cout << std::endl<< "RevokedCred numer "<< i+1<<std::endl << OTAPI_Wrap::GetNym_RevokedCredID (nym_ID,i)<<std::endl;
					}
			std::cout <<"Statistic for nym:" <<OTAPI_Wrap::GetNym_Stats(nym_ID);
			}



		/*std::string ASSET_ID = OTAPI_Wrap::GetAssetType_ID (0);
		//CREATE ACCOUNT
		OTAPI_Wrap::accountCreate(SERVER_ID,USER_ID,ASSET_ID);
	*/

	}


} // nTests
} // nOT
