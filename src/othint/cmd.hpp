/* See other files here for the LICENCE that applies here. */
/*
Template for new files, replace word "template" and later delete this line here.
*/

#ifndef INCLUDE_OT_NEWCLI_cmd
#define INCLUDE_OT_NEWCLI_cmd

#include "lib_common1.hpp"

namespace nOT {
namespace nNewcli {

INJECT_OT_COMMON_USING_NAMESPACE_COMMON_1; // <=== namespaces

class cCmdParser;
class cCmdProcessing;
class cCmdFormat;
class cCmdData;

class cCmdName;
class cParamInfo;
class cParamString;


/**
Intance of a parser, that should contain some tree of possible commands and format/validatio/hint of each.
*/
class cCmdParser {
	protected:
		map< cCmdName , cCmdFormat > tree;
	public:
		cCmdParser()=default;

		cCmdProcessing StartProcessing(const vector<string> &words);
		cCmdProcessing StartProcessing(const string &words);
};

/**
Describes template how given command arguments should look like (validation, hint)
*/
class cCmdFormat {
	protected:
		vector<cParamInfo> var;
		vector<cParamInfo> varExt;
		vector<cParamInfo> option;
		vector<cParamInfo> optionExt;
	public:
};

/**
The parsed and interpreted data of command, arguments and options are ready in containers etc.
*/
class cCmdData {
	public:
};

// ============================================================================

/**
Name of command like "msg sendfrom"
*/
class cCmdName {
	public:
};


/**
How to validate and how to compelte this argument
*/
class cParamInfo {
	public:
	//	function<  >
};


}; // namespace nNewcli
}; // namespace nOT


#endif

