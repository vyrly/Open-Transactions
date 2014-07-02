/* See other files here for the LICENCE that applies here. */
/* See header file .hpp for info */

#include "otcli.hpp"
#include "cmd.hpp"

#include "lib_common2.hpp"
#include "useot.hpp"

#ifdef __unix
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <fcntl.h>
	#include <signal.h>
#endif

namespace nOT {
namespace nNewcli {

INJECT_OT_COMMON_USING_NAMESPACE_COMMON_1; // <=== namespaces

int cOTCli::Run(const vector<string> args_without_programname) {
	try {
		return _Run(args_without_programname);
	} catch (const myexception &e) { e.Report(); throw ; } catch (const std::exception &e) { _erro("Exception " << e.what()); throw ; }
}

int cOTCli::_Run(const vector<string> args_without_programname) {
	LoadScript("autostart-dev.local", "autostart script"); // todo depending on execution mode? +devel ?

	if (nOT::gRunOptions.getDoRunDebugshow()) {
		_note("Running test Debugshow:");
		string msg="Testing debug system.";
		_erro(msg);
		_warn(msg);
		_mark(msg);
		_fact(msg);
		_note(msg);
		_info(msg);
		_dbg1(msg);
		_dbg2(msg);
		_dbg3(msg);
	}

	auto args = args_without_programname;

	int status = 0;
	if (args.size() == 0) {
		throw std::runtime_error("Main program called with 0 arguments (not even program name).");
	}

	auto useOT = std::make_shared<nUse::cUseOT>("Normal");

	size_t nr=0;
	for(auto arg : args) {
		if (arg=="--complete-shell") {
			nOT::nOTHint::cInteractiveShell shell;

			switch ( gRunOptions.getTRunMode() ){
				case gRunOptions.eRunModeNormal :
					shell.RunEditline(useOT);
					break;
				case gRunOptions.eRunModeDemo :
					shell.RunEditline(useOT);
					break;
				case gRunOptions.eRunModeCurrent :
					using namespace nOT::nNewcli;
					nNewcli::cCmdParser::cmd_test(useOT);
					break;
			}
		}
		else if (arg=="--complete-one") { // otcli "--complete-one" "ot msg sendfr"
			string v;  bool ok=1;  try { v=args.at(nr+1); } catch(...) { ok=0; } //
			if (ok) {
				GetTmpFileOut();

				if ( !IsDaemonRunning() ) {
//					nUtils::DisplayStringEndl(cerr, "Demon is not running");
					nOT::nOTHint::cInteractiveShell shell;
					shell.CompleteOnce(v, useOT);

					cDaemon completeDaemon;
				}
				else {
					OpenPipe(v);
					ReadFromTmpFileOut();
				}
			}
		}
		else if (arg=="--run-one") { // otcli "--run-one" "ot msg sendfr"
			string v;  bool ok=1;  try { v=args.at(nr+1); } catch(...) { ok=0; } //
			if (ok) {
				nOT::nOTHint::cInteractiveShell shell;
				shell.RunOnce(v, useOT);
			}
			else {
				_erro("Missing variables for command line argument '"<<arg<<"'");
				status = 1;
			}
		}
		++nr;
	}
	_note("Finished main run of application, will clean up now");

	_note("Exiting application with status="<<status);
	return status;
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

#ifdef __unix

void cOTCli::ReadFromTmpFileOut() {
	//	std::ofstream ofs(mDaemonInFilename);
	//	ofs << cmd;

	close(mDaemonOutfd);
	unlink( mDaemonOutFilename.c_str() );
}

void cOTCli::GetTmpFileOut() {
	char filename[] = "/tmp/otshell-out.XXXXXX";
	int mDaemonOutfd = mkstemp(filename);
	if ( mDaemonOutfd == -1 ) {
		_erro("Can't create the file: " << filename);
		return;
	}
	mDaemonOutFilename = filename;
}

bool cOTCli::IsDaemonRunning() {
	std::ifstream pidFile("daemon.pid");
	string pid;
	if (pidFile.good()) {
		pidFile >> pid;

//		nUtils::DisplayStringEndl(cerr, "Checking if pid exists");

		if (0 == kill(stoi(pid), 0)) {
//				nUtils::DisplayStringEndl(cerr, "Daemon is running");
				return true;
		}
	}
//	nUtils::DisplayStringEndl(cerr, "Daemon is not running");
	return false;
}

void cOTCli::OpenPipe(const string & cmd) {
	int fd;
	char buf[4096];
//	nUtils::DisplayStringEndl(cerr, "Creating Pipe... Waiting for receiver process...");
	//TRY TO CRATE A NAMED PIPE
	if (mkfifo("OT_DAEMON_IN_FIFO_PIPE",0600)<0)
	{
		nUtils::DisplayStringEndl(cerr, "FIFO (named pipe) could not be created.");
		return;
	}
//	else nUtils::DisplayStringEndl(cerr, "Pipe has been created...");

	//OPEN PIPE
	if ((fd = open("OT_DAEMON_IN_FIFO_PIPE", O_WRONLY))<0)
	{
		nUtils::DisplayStringEndl(cerr, "Could not open named pipe.");
		return;
	}
//	else nUtils::DisplayStringEndl(cerr, "Pipe has been opened.");

	//WRITE TO PIPE
	strcpy( buf, cmd.c_str() );

	if( write (fd,buf, strlen(buf)+1) < 0 )
	{
		nUtils::DisplayStringEndl(cerr, "Error writing to named Pipe (FIFO)");
		return;
	}
//	else nUtils::DisplayStringEndl(cerr, "Message has been written to pipe.");

	//CLOSE FIFO
	if (close(fd)<0)
	{
		nUtils::DisplayStringEndl(cerr, "Error closing FIFO");
		return;
	}
}

cDaemon::cDaemon() {
	ForkProcess();
	DaemonMainLoop();

}

pid_t cDaemon::GetDaemonPID() {
	return mSID;
}

void cDaemon::ForkProcess() {
	//-------------------
//	daemon(0, 0);

	//Fork the Parent Process
	pid_t pid = fork();

	if (pid < 0) { exit(EXIT_FAILURE); }

	//We got a good pid, Close the Parent Process
	if (pid > 0) { exit(EXIT_SUCCESS); }

	//Change File Mask
//	umask(0);

	//Create a new Signature Id for our child
	mSID = setsid();
	if (mSID < 0) { exit(EXIT_FAILURE); }

	std::ofstream pidFile("daemon.pid");
	pidFile << mSID;
	nUtils::DisplayStringEndl(cerr, "Daemon PID:" + to_string(mSID) );

	//Change Directory
	//If we cant find the directory we exit with failure.
	//if ((chdir("/")) < 0) { exit(EXIT_FAILURE); }

	//Close Standard File Descriptors
//	close(STDIN_FILENO);
//	close(STDOUT_FILENO);
//	close(STDERR_FILENO);

}

void cDaemon::DaemonMainLoop() {
	auto useOT = std::make_shared<nUse::cUseOT>("Daemon");
	nOT::nOTHint::cInteractiveShell shell;
	while(1) {
		string command = ReadCmd();
		if ( !command.empty() ) {
			nUtils::DisplayStringEndl(cerr, "Execute");
			shell.CompleteOnce(command, useOT);
		}
		sleep(1);    //Sleep for 2 seconds
	}
}

string cDaemon::ReadCmd() {
	const int max = 4096;

  int fd;
  char buf[4096];

  string filename;

  //OPEN PIPE WITH READ ONLY
  if ((fd = open ("OT_DAEMON_IN_FIFO_PIPE", O_RDONLY ))<0)
  {
//  	nUtils::DisplayStringEndl(cerr, "Could not open named pipe for reading.");
      return "";
  }
//  nUtils::DisplayStringEndl(cerr, "Pipe has been opened. Trying to read from...");

  //READ FROM PIPE
  if (read( fd,buf,max) < 0 )
  {
  	nUtils::DisplayStringEndl(cerr, "Error reading pipe.");
      return "";
  }
  filename = buf;
  nUtils::DisplayStringEndl(cerr,"Message I got from pipe - " + filename);

  if (close(fd)<0)
  {
  	nUtils::DisplayStringEndl(cerr, "Error closing FIFO.");
      return "";
  }

  if (unlink("OT_DAEMON_IN_FIFO_PIPE")<0)
  {
  	nUtils::DisplayStringEndl(cerr, "Error deleting pipe file.");
      return "";
  }
  return filename;
}


#endif //__unix


}; // namespace nNewcli
}; // namespace OT


