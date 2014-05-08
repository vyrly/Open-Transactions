/* See other files here for the LICENCE that applies here. */
/* See header file .hpp for info */

#include "tests.hpp"

#include "lib_common2.hpp"

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

void exampleOfOT(); // TODO implementation ehre

}; // namespace nTests
}; // namespace nOT


