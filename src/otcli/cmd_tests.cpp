
#include "cmd.hpp"
#include "cmd_detail.hpp"

#include "lib_common2.hpp"
#include "ccolor.hpp"

namespace nOT {
namespace nNewcli {

INJECT_OT_COMMON_USING_NAMESPACE_COMMON_2; // <=== namespaces

using namespace nUse;

void cCmdParser::_cmd_test(  shared_ptr<cUseOT> use  ) {
	_cmd_test_completion( use );
//	_cmd_test_tree();
}

void cCmdParser::_cmd_test_completion( shared_ptr<cUseOT> use ) {
	_mark("TEST COMPLETION");
	shared_ptr<cCmdParser> parser(new cCmdParser);
	parser->Init();

	auto alltest = vector<string>{ ""
//	,"~"
//	,"ot~"
	,"ot msg send~ ali"
//	,"ot msg send ali~"
	,"ot msg sen~ alice bob"
//	,"ot msg send-from ali~ bo"
//	,"ot msg send-from ali bo~"
	,"ot msg send-from alice bob subject message --prio 3 --dryr~"
	,"ot msg send-from alice bob subject message --pr~ 3 --dryrun"
//	,"ot help securi~"
//	,"help securi~"
//	,"ot msg sendfrom ali bobxxxxx~"
//	,"ot msg sendfrom ali       bob      subject message_hello --cc charlie --cc dave --prio 4 --cc eve --dry~ --cc xray"
	};
	for (const auto cmd_raw : alltest) {
		try {
			if (!cmd_raw.length()) continue;

			auto pos = cmd_raw.find_first_of("~");
			if (pos == string::npos) {
				_erro("Bad example - no TAB position given!");
				continue; // <---
			}
			auto cmd = cmd_raw; 
			cmd.erase( pos , 1 );

			_mark("====== Testing completion: [" << cmd << "] for position pos=" << pos << " (from cmd_raw="<<cmd_raw<<")" );
			auto processing = parser->StartProcessing(cmd, use);
			vector<string> completions = processing.UseComplete( pos  );
			_note("Completions: " << DbgVector(completions));

		} 
		catch (const myexception &e) { e.Report(); } 
		catch (const std::exception &e) { _erro("Exception " << e.what()); }
		// continue anyway
	}
}


void cCmdParser::_cmd_test_tree( shared_ptr<cUseOT> use ) {
	_mark("TEST TREE");
	shared_ptr<cCmdParser> parser(new cCmdParser);
	parser->Init();

	auto alltest = vector<string>{ ""
	//ot msg --dryrun
	,"ot help"
/*	,"ot msg ls --dryrun"
	,"ot msg ls alice --dryrun"*/
	,"ot msg send-from alice bob --prio 1 --dryrun"
/*	,"ot msg send-from alice bob --cc eve --cc mark --bcc john --prio 4 --dryrun"
	,"ot msg send-from alice bob message subject --cc eve --cc mark --bcc john --prio 4 --dryrun"
	,"ot msg send-to bob hello --cc eve --cc mark --bcc john --prio 4 --dryrun"
	,"ot msg rm alice 0 --dryrun"
	,"ot msg rm-out alice 0 --dryrun"
	//ot msg
//	"ot msg ls"
//	,"ot msg ls alice"
//	,"ot msg send-from alice bob --prio 1"
//	,"ot msg send-from alice bob --cc eve --cc mark --bcc john --prio 4"
//	,"ot msg send-from alice bob --cc eve --cc mark --bcc john --prio 4"
//	,"ot msg send-to bob hello --cc eve --cc mark --bcc john --prio 4"
//	,"ot msg rm alice 0"
//	,"ot msg rm-out alice 0"

	//ot nym --dryrun
	,"ot nym check alice --dryrun"
	,"ot nym info alice --dryrun"
	,"ot nym register alice --dryrun"
	,"ot nym rm alice --dryrun"
	,"ot nym new alice --dryrun"
	,"ot nym set-default alice --dryrun"
	,"ot nym refresh --dryrun"
	,"ot nym refresh alice --dryrun"
	,"ot nym ls --dryrun"
	//ot nym
//	,"ot nym check alice"
//	,"ot nym info alice"
//	,"ot nym register alice"
//	,"ot nym rm alice"
//	,"ot nym new alice"
//	,"ot nym set-default alice"
//	,"ot nym refresh"
//	,"ot nym refresh alice"
//	,"ot nym ls"
	//ot account --dryrun
	,"ot account new assetname accountname --dryrun"
	,"ot account refresh --dryrun"
	,"ot account refresh accountname --dryrun"
	,"ot account set-default accountname --dryrun"
	,"ot account rm accountname --dryrun"
	,"ot account ls --dryrun"
	,"ot account mv accountname newaccountname --dryrun"
	//ot account
//	,"ot account new assetname accountname"
//	,"ot account refresh"
//	,"ot account refresh accountname"
//	,"ot account set-default accountname"
//	,"ot account rm accountname"
//	,"ot account ls"
//	,"ot account mv accountname newaccountname"
	//ot asset --dryrun
	,"ot asset new assetname --dryrun"
	,"ot asset issue --dryrun"
	,"ot asset ls --dryrun"
	//ot asset
//	,"ot asset new"
//	,"ot asset issue"
//	,"ot asset ls"
	//ot server --dryrun
	,"ot server add --dryrun"
	,"ot server ls --dryrun"
	,"ot server new --dryrun"
	,"ot server rm servername --dryrun"
	,"ot server set-default servername --dryrun"
	//ot server
//	,"ot server add"
//	,"ot server ls"
//	,"ot server new"
//	,"ot server rm servername"
//	,"ot server set-default servername"
	//ot text --dryrun
	,"ot text encode texttoprocess --dryrun"
	,"ot text decode text --dryrun"
	,"ot text encrypt bob text --dryrun"
	,"ot text decrypt text --dryrun"
	//ot text
//	,"ot text encode texttoprocess"
//	,"ot text decode text"
//	,"ot text encrypt bob text"
//	,"ot text decrypt text"
*/
	};
	for (auto cmd : alltest) {
		try {
			if (!cmd.length()) continue;
			_mark("====== Testing command: " << cmd );
			auto processing = parser->StartProcessing(cmd, use);
			processing.UseExecute();
		} catch (const myexception &e) { e.Report(); throw ; } catch (const std::exception &e) { _erro("Exception " << e.what()); throw ; }
	}

}

void cCmdParser::cmd_test( shared_ptr<cUseOT> use ) {
	try {
		_cmd_test(use);
	} catch (const myexception &e) { e.Report(); throw ; } catch (const std::exception &e) { _erro("Exception " << e.what()); throw ; }
}




} // namespace 
} // namespace 


