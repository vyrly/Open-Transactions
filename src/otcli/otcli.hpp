/* See other files here for the LICENCE that applies here. */
/*
This class represents an application of otcli,
that runs either in mode:
- mode to execute commands
- mode to hint/complete/shell-complete commands
*/

#ifndef INCLUDE_OT_NEWCLI
#define INCLUDE_OT_NEWCLI

#include "lib_common2.hpp"
#include "othint.hpp"

namespace nOT {
namespace nNewcli {

INJECT_OT_COMMON_USING_NAMESPACE_COMMON_2; // <=== namespaces

class cOTCli {
	private:
		int _Run(const vector<string> args_without_programname);

		int mDaemonOutfd;
		string mDaemonOutFilename;

		bool IsDaemonRunning();
		void GetTmpFileOut();

		void OpenPipe(const string & cmd);
		void ReadFromTmpFileOut();

	public:

		int Run(const vector<string> args_without_programname);

		bool LoadScript_Main(const std::string &thefile_name);
		void LoadScript(const std::string &script_filename, const std::string &title);
};

class cDaemon {
	private:
		pid_t mSID;
		shared_ptr<nUse::cUseOT> mUseOT;
		void ForkProcess();
		void DaemonMainLoop();
		string ReadCmd();
	public:
		cDaemon();
		pid_t GetDaemonPID();
};

}; // namespace nNewcli
}; // namespace nOT


#endif

