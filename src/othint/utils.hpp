/* See other files here for the LICENCE that applies here. */
/*
Utils provides various utilities and general-purpose functions that
we find helpful in coding this project.
*/

#ifndef INCLUDE_OT_NEWCLI_UTILS
#define INCLUDE_OT_NEWCLI_UTILS

#include <string>


namespace nOT {

namespace nUtils {


// text trimming
std::string & ltrim(std::string &s);
std::string & rtrim(std::string &s);
std::string & trim(std::string &s);

}; // namespace nUtils 

}; // namespace nOT


#endif



