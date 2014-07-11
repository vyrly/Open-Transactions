/* See other files here for the LICENCE that applies here. */
/* See header file .hpp for info */

#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>

#include "utils.hpp"

#include "ccolor.hpp"

#include "lib_common1.hpp"

#include "runoptions.hpp"

namespace nOT {
namespace nUtils {

INJECT_OT_COMMON_USING_NAMESPACE_COMMON_1; // <=== namespaces

myexception::myexception(const char * what) 
	: std::runtime_error(what)
{ }

myexception::myexception(const std::string &what) 
	: std::runtime_error(what)
{ }

void myexception::Report() const {
	_erro("Error: " << what());
}

myexception::~myexception() { }

// ====================================================================

// text trimming
// http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
std::string & ltrim(std::string &s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
	return s;
}

std::string & rtrim(std::string &s) {
	s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
  return s;
} 

std::string & trim(std::string &s) {
	return ltrim(rtrim(s));
}

cNullstream g_nullstream; // extern a stream that does nothing (eats/discards data)

// ====================================================================

const char* DbgShortenCodeFileName(const char *s) {
	const char *p = s;
	const char *a = s;

	bool inc=1;
	while (*p) {
		++p;
		if (inc && ('\0' != * p)) { a=p; inc=false; } // point to the current character (if valid) becasue previous one was slash
		if ((*p)=='/') { a=p; inc=true; } // point at current slash (but set inc to try to point to next character)
	}
	return a;
}


// ====================================================================

std::ostream & cLogger::write_stream(int level) {
	if ((level >= mLevel) && (mStream)) { *mStream << icon(level) << ' '; return *mStream; } 
	return g_nullstream; 
}

template<typename T, typename ...Args>
std::unique_ptr<T> make_unique( Args&& ...args )
{
    return std::unique_ptr<T>( new T( std::forward<Args>(args)... ) );
}

void cLogger::setOutStream() {
	if ( gRunOptions.getDebug() ) {
		if ( gRunOptions.getDebugSendToFile() ) {
			outfile =  make_unique<std::ofstream> ("debuglog.txt");
			mStream = & (*outfile);
		}
		else if ( gRunOptions.getDebugSendToCerr() ) {
			mStream = & std::cerr;
		}
		else {
			mStream = & g_nullstream;
		}
	}
	else {
		mStream = & g_nullstream;
	}
}

void cLogger::setDebugLevel(int level) {
	bool note_before = (mLevel > level); // report the level change before or after the change? (on higher level)
	if (note_before) _note("Setting debug level to "<<level);
	mLevel = level;
	if (!note_before) _note("Setting debug level to "<<level);
}

cLogger::cLogger() : mStream(NULL), mLevel(20) { mStream = & std::cout; }

std::string cLogger::icon(int level) const {
	// TODO replan to avoid needles converting back and forth char*, string etc

	using namespace zkr;

	if (level >= 100) return cc::back::red     + ToStr(cc::fore::black) + ToStr("ERROR ") + ToStr(cc::fore::lightyellow) + " " ;
	if (level >=  90) return cc::back::lightyellow  + ToStr(cc::fore::black) + ToStr("Warn  ") + ToStr(cc::fore::red)+ " " ;
	if (level >=  80) return cc::back::lightmagenta + ToStr(cc::fore::black) + ToStr("MARK  "); //+ zkr::cc::console + ToStr(cc::fore::lightmagenta)+ " ";
	if (level >=  75) return cc::back::lightyellow + ToStr(cc::fore::black) + ToStr("FACT ") + zkr::cc::console + ToStr(cc::fore::lightyellow)+ " ";
	if (level >=  70) return cc::fore::green    + ToStr("Note  ");
	if (level >=  50) return cc::fore::cyan   + ToStr("info  ");
	if (level >=  40) return cc::fore::lightwhite    + ToStr("dbg   ");
	if (level >=  30) return cc::fore::lightblue   + ToStr("dbg   ");
	if (level >=  20) return cc::fore::blue    + ToStr("dbg   ");

	return "  ";
}

std::string cLogger::endline() const {
	return ToStr("") + zkr::cc::console + ToStr("\n"); // TODO replan to avoid needles converting back and forth char*, string etc
}



// ====================================================================
// vector debug

void DisplayStringEndl(std::ostream & out, const std::string text) {
	out << text;
	out << std::endl;
}

std::string SpaceFromEscape(const std::string &s) {
	std::ostringstream  newStr;
		for(int i = 0; i < s.length();i++) {
			if(s[i] == '\\' && s[i+1] ==32)
				newStr<<"";
			else
				newStr<<s[i];
			}
	return newStr.str();
}

std::string EscapeFromSpace(const std::string &s) {
	std::ostringstream  newStr;
	for(int i = 0; i < s.length();i++) {
		if(s[i] == 32)
			newStr << "\\" << " ";
		else
			newStr << s[i];
	}
	return newStr.str();
}


std::string EscapeString(const std::string &s) {
	std::ostringstream  newStr;
		for(int i = 0; i < s.length();i++) {
			if(s[i] >=32 && s[i] <= 126)
				newStr<<s[i];
			else
				newStr<<"\\"<< (int) s[i];
			}

	return newStr.str();
}

bool CheckIfBegins(const std::string & beggining, const std::string & all) {
	if (all.compare(0, beggining.length(), beggining) == 0) {
		return 1;
	}
	else {
		return 0;
	}
}

bool CheckIfEnds (std::string const & ending, std::string const & all){
    if (all.length() >= ending.length()) {
        return (0 == all.compare (all.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}


vector<string> WordsThatMatch(const std::string & sofar, const vector<string> & possib) {
	vector<string> ret;
	for ( auto rec : possib) { // check of possibilities
		if (CheckIfBegins(sofar,rec)) {
			rec = EscapeFromSpace(rec);
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

// ====================================================================

// ASRT - assert. Name like ASSERT() was too long, and ASS() was just... no.
// Use it like this: ASRT( x>y );  with the semicolon at end, a clever trick forces this syntax :)

void Assert(bool result, const std::string &stamp, const std::string &condition) {
	if (!result) {
		_erro("Assert failed at "+stamp+": ASSERT( " << condition << ")");
		throw std::runtime_error("Assert failed at "+stamp+": ASSERT( " + condition + ")");
	}
}

// ====================================================================
// advanced string

const std::string GetMultiline(string endLine) {
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

vector<string> SplitString(const string & str){
		std::istringstream iss(str);
		vector<string> vec { std::istream_iterator<string>{iss}, std::istream_iterator<string>{} };
		return vec;
}

const bool checkPrefix(const string & str, char prefix){
	if (str.at(0) == prefix)
		return true;
	return false;
}

// ====================================================================
// nUse utils

string SubjectType2String(const eSubjectType & type) {
	using subject = eSubjectType;

	switch (type) {
	case subject::Account:
		return "Account";
	case subject::Asset:
			return "Asset";
	case subject::User:
			return "User";
	case subject::Server:
			return "Server";
	case subject::Unknown:
				return "Unknown";
	}
	return "";
}

eSubjectType String2SubjectType(const string & type) {
	using subject = eSubjectType;

	if (type == "Account")
		return subject::Account;
	if (type == "Asset")
			return subject::Asset;
	if (type == "User")
			return subject::User;
	if (type == "Server")
			return subject::Server;

	return subject::Unknown;
}

// ====================================================================
// operation on files

bool cConfigManager::Load(const string & fileName, map<eSubjectType, string> & configMap){
	_dbg1("Loading defaults.");

	std::ifstream inFile(fileName.c_str());
	if( inFile.good() && !(inFile.peek() == std::ifstream::traits_type::eof()) ) {
		string line;
		while( std::getline (inFile, line) ) {
			_dbg2("Line: ["<<line<<"]");
			vector<string> vec = SplitString(line);
			if (vec.size() == 2) {
			_dbg3("config2:"<<vec.at(0)<<","<<vec.at(1));
				configMap.insert ( std::pair<eSubjectType, string>( String2SubjectType( vec.at(0) ), vec.at(1) ) );
			}
			else {
			_dbg3("config1:"<<vec.at(0));
				configMap.insert ( std::pair<eSubjectType, string>( String2SubjectType( vec.at(0) ), "-" ) );
			}
		}
		_dbg1("Finished loading");
		return true;
	}
	_dbg1("Unable to load");
	return false;
}

void cConfigManager::Save(const string & fileName, const map<eSubjectType, string> & configMap) {
	_dbg1("Will save config");

	std::ofstream outFile(fileName.c_str());
	for (auto pair : configMap) {
		_dbg2("Got: "<<SubjectType2String(pair.first)<<","<<pair.second);
		outFile << SubjectType2String(pair.first) << " ";
		outFile << pair.second;
		outFile << endl;
		_dbg3("line saved");
	}
	_dbg1("All saved");
}

cConfigManager configManager;

#ifdef __unix

void cEnvUtils::GetTmpTextFile() {
	char filename[] = "/tmp/otcli_text.XXXXXX";
	fd = mkstemp(filename);
	if (fd == -1) {
		_erro("Can't create the file: " << filename);
		return;
	}
	mFilename = filename;
}

void cEnvUtils::CloseFile() {
	close(fd);
	unlink( mFilename.c_str() );
}

void  cEnvUtils::OpenEditor() {
	char* editor = std::getenv("OT_EDITOR"); //TODO Read editor from configuration file
	if (editor == NULL)
		editor = std::getenv("VISUAL");
	if (editor == NULL)
		editor = std::getenv("EDITOR");

	string command;
	if (editor != NULL)
		command = ToStr(editor) + " " + mFilename;
	else
		command = "/usr/bin/editor " + mFilename;
	_dbg3("Opening editor with command: " << command);
	if ( system( command.c_str() ) == -1 )
		_erro("Cannot execute system command: " << command);
}

const string cEnvUtils::ReadFromTmpFile() {
	std::ifstream ifs(mFilename);
	string msg((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
	return msg;
}

const string cEnvUtils::Compose() {
	GetTmpTextFile();
	OpenEditor();
	string input = ReadFromTmpFile();
	CloseFile();
	return input;
}

#endif

const string cEnvUtils::ReadFromFile(const string path) {
	std::ifstream ifs(path);
	string msg((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
	return msg;
}



// ====================================================================
// algorthms


}; // namespace nUtil


}; // namespace OT

// global namespace

const extern int _dbg_ignore = 0; // see description in .hpp

std::string GetObjectName() {	
	//static std::string * name=nullptr;
	//if (!name) name = new std::string("(global)");
	return "";
}

