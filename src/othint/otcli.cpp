/* See other files here for the LICENCE that applies here. */
/* See header file .hpp for info */

#include "template.hpp"

#include "lib_common1.hpp"

namespace nOT {
namespace nNewcli {

INJECT_OT_COMMON_USING_NAMESPACE_COMMON_1; // <=== namespaces

void cOTCli::Run(const int argc, const char **argv) {
}

void cOTCli::Autostart() {
	LoadScript("autostart-dev.local", "autostart script"); // todo depending on execution mode?
}


bool cOTCli::LoadScript_Main(const std::string &thefile_name) { 
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

void cOTCli::LoadScript(const std::string &script_filename, const std::string &title) {
	_note("Script " + script_filename + " ("+title+")");
	try {
		LoadScript_Main(script_filename);
	}
	catch(const std::exception &e) {
		_erro("\n*** In SCRIPT "+script_filename+" got an exception: " << e.what());
	}
	catch(...) {
		_erro("\n*** In SCRIPT "+script_filename+" got an UNKNOWN exception!");
	}
}


}; // namespace nNewcli
}; // namespace OT


