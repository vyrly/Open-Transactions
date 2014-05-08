/* See other files here for the LICENCE that applies here. */

#include "lib_common1.hpp"

#include "otcli.hpp"

INJECT_OT_COMMON_USING_NAMESPACE_COMMON_1

int main(int argc, const char **argv) {

	nOT::nNewcli::cOTCli application;
	int ret = application.Run(argc,argv);

	// nOT::nTests::exampleOfOT(); // TODO from script
	// nOT::nTests::testcase_run_all_tests(); // TODO from script

	return ret;
}

/*

	catch(const std::exception &e) {
		_erro("\n*** The testcases code thrown an exception: " << e.what());
	}
	catch(...) {
		_erro("\n*** The testcases code thrown an UNKNOWN exception!");
	}

*/

// #####################################################################

