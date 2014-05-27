/* See other files here for the LICENCE that applies here. */

#include "lib_common1.hpp"
#include "runoptions.hpp"

#include "otcli.hpp"

#include "easylogging++.h"

INJECT_OT_COMMON_USING_NAMESPACE_COMMON_1

_INITIALIZE_EASYLOGGINGPP
#define _ELPP_UNICODE

nOT::nUtils::cLogger gCurrentLogger;

int main(int argc, const char **argv) {
	int ret=0;
	_START_EASYLOGGINGPP(argc, argv);
	// Load configuration from file
	el::Configurations conf("logger.conf");
	// Reconfigure single logger
	el::Loggers::reconfigureLogger("default", conf);
	// Actually reconfigure all loggers instead
	el::Loggers::reconfigureAllLoggers(conf);
	// Now all the loggers will use configuration from file
	LOG(INFO) << "Logger initialized";

	try {
		ret=1; // if aborted then this indicated error
		nOT::nNewcli::cOTCli application;


		vector<string> args_full;	// eg: args_full: ot +debug +debugfile msg sendfrom rafal piotr +thisisplussign
		for (int i=0; i<argc; ++i) {
			args_full.push_back( argv[i] );
		}

		vector<string> args_clear = nOT::gRunOptions.ExecuteRunoptionsAndRemoveThem(args_full); 
		// eg: args_clear: ot msg sendfrom rafal piotr +thisisplussign 
		// +debug +debugfile <-- this will be Executed by gRunOptions

		gCurrentLogger.setOutStream();
		_dbg1("Running the program with arguments: " + nOT::nUtils::vectorToStr(args_clear));

		ret = application.Run(args_clear);
		_dbg1("Main after application with ret="<<ret);
	}
	catch (const std::exception &e) {
  	_erro("\n*** Captured exception:" << e.what());
	}
	catch (...) {
  	_erro("\n*** Captured UNKNOWN exception:");
	}

	// nOT::nTests::exampleOfOT(); // TODO from script
	// nOT::nTests::testcase_run_all_tests(); // TODO from script

	_dbg2("The main will now return with ret="<<ret);


	return ret;
}

