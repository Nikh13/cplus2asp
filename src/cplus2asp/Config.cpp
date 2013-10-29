/* Generated by re2c 0.13.5 on Tue Oct 29 04:14:51 2013 */
#line 1 "Config.re2c"
/*
 * Copyright (c) 2010-2013 <Joseph Babb, Michael Cassollary, Joohyung Lee>
 *
 * For information on how to contact the authors, please visit
 *	http://reasoning.eas.asu.edu/cplus2asp
 *
 * This file is part of the cplus2asp system.
 *
 * cplus2asp is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * cplus2asp is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


/*
 * Config.cpp
 *
 *  Created on: Jan 23, 2013
 *      Author: Joseph Babb
 */

#include <cstring>
#include <cstdio>
#include <string>
#include <sstream>
#include <stdexcept>
#include <climits>

#ifndef BOOST_FILESYSTEM_VERSION
#define BOOST_FILESYSTEM_VERSION 3
#endif
#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include "boost/process.hpp"

#include "Config.h"
#include "utils.h"

namespace fs = boost::filesystem;
namespace bp = boost::process;

/***************************************************************/
/* Constants */
/***************************************************************/
unsigned int const Config::UNDEFINED = UINT_MAX;
unsigned int const Config::INF = UINT_MAX - 4;

/***************************************************************/
/* Methods */
/***************************************************************/

// Default Constructor
Config::Config(std::string const& name) {

	fs::path temppath = fs::temp_directory_path();

	if (name != "") {
	
		try {
			// NOTE: Requires boost::filesystem 1.44+
			fs::path tmp = bp::search_path(name);

			if (fs::is_empty(tmp)) {
				// No executable found.
				tmp = fs::current_path() / name;
				if (!fs::exists(tmp)) {
					utils::warning("Could not find '%s' in your path. Assuming it's in the working directory.", name.c_str());
					mPath = fs::current_path().native();
				}
			} else {

				while (fs::is_symlink(tmp)) {
					tmp = fs::read_symlink(tmp);
				}
				if (!fs::is_directory(tmp))
					tmp = tmp.parent_path();
				mPath = tmp.native();

			}

			// NOTE: Requred boost::filesystem 1.48+
			// mPath = fs::canonical(bp::search_path(name)).parent_path().native();
		} catch (fs::filesystem_error &e) {
			utils::debug("Caught exception: '%s'", true, e.what());
			utils::warning("Could not find '%s' in your path. Assuming it's in the working directory.", name.c_str());
			mPath = fs::current_path().native();
		} catch (std::runtime_error &e) {
			utils::debug("Caught exception: '%s'", true, e.what());
			utils::warning("Could not find '%s' in your path. Assuming it's in the working directory.", name.c_str());
			mPath = fs::current_path().native();
		}
	} else {
			utils::warning("Could not find '%s' in your path. Assuming it's in the working directory.", name.c_str());
			mPath = fs::current_path().native();
	}

	mErrFile = (temppath /  fs::unique_path()).native();

	mRunningMode = DEF_RUNNING_MODE;
	mCustomRunningMode = 0;

	mLang = DEF_LANG;
	mCustomLang = 0;

	strOpt(STR_NONE_ALIAS, "");

	strOpt(STR_SYMTAB_FILE, (temppath / fs::unique_path()).native());

	mConfigOpts[OPT_INCL_STD] = DEF_INCL_STD;
	mConfigOpts[OPT_INCL_ADDITIVE] = DEF_INCL_ADDITIVE;
	mConfigOpts[OPT_DISCARD_F2LP] = DEF_DISCARD_F2LP;
	mConfigOpts[OPT_SUPPRESS_INTERACTION] = DEF_SUPPRESS_INTERACTION;
	mConfigOpts[OPT_MINSTEP] = UNDEFINED;
	mConfigOpts[OPT_MAXSTEP] = UNDEFINED;
	mConfigOpts[OPT_MAXADDITIVE] = UNDEFINED;
	mConfigOpts[OPT_NUM_SOLN] = DEF_NUM_SOLN;
	mConfigOpts[OPT_EXT_PORT] = UNDEFINED;
	mConfigOpts[OPT_INT_PORT] = DEF_INTERNAL_PORT;
	mConfigOpts[OPT_SHIFT] = DEF_SHIFT;
	mConfigOpts[OPT_STATS] = DEF_STATS;

	memset(mCustomConfig,0,_OPT_LENGTH_);


	memset(mRun,1,_TC_LENGTH_);

	command(TC_TRANSLATOR,DEF_TRANS_CMD);
	command(TC_PREPROC,DEF_PREPROC_CMD);
	command(TC_GROUNDER,DEF_GRD_CMD);
	command(TC_SOLVER,DEF_SO_CMD);
	command(TC_POSTPROC,DEF_POSTPROC_CMD);
	command(TC_REACTIVE_BRIDGE,DEF_REACTIVE_BRIDGE_CMD);
	
	memset(mRun,1,_TC_LENGTH_);
	mRun[TC_GROUNDER] = false;
	memset(mCustomRun,0,_TC_LENGTH_);

	opts(TC_TRANSLATOR,DEF_TRANS_OPTS);
	opts(TC_PREPROC,DEF_PREPROC_OPTS);
	opts(TC_GROUNDER,DEF_GRD_OPTS);
	opts(TC_SOLVER,DEF_SO_OPTS);
	opts(TC_POSTPROC,DEF_POSTPROC_OPTS);
	opts(TC_REACTIVE_BRIDGE,DEF_REACTIVE_BRIDGE_OPTS);

	for (int i = (int)_TC_BEGIN_; i < (int)_TC_LENGTH_; i++) {
		output((Toolchain)i,(temppath / fs::unique_path()).native());
	}
	
	memset(mCustomStr,0,_STR_LENGTH_);

	// Default queries which should always be made available...
	mQueries[CONST_QUERY_TRANSITIONS] = Query("System transitions", CONST_QUERY_TRANSITIONS, 1, 1);
	mQueries[CONST_QUERY_STATES] = Query("System states", CONST_QUERY_STATES, 0, 0);
	mQueries[CONST_QUERY_NONE] = Query("Satisfiability check (no query)", CONST_QUERY_NONE, 0, 0);
}

// Install directory
std::string const& Config::installDir() const {
	return mPath;
/*
	char tmp[PATH_MAX];
	readlink("/proc/self/exe", tmp, PATH_MAX);
	std::string ret(tmp);
	ret = ret.substr(0,ret.find_last_of("/"));
	return ret;
*/
}

// standard file
std::string Config::stdFile() const { 
	fs::path path(installDir());

	if (lang() == LANG_MVPF) {
		return (path / MVPF_STD_FILE).native();
	} else if (mode() == MODE_INCREMENTAL || mode() == MODE_REACTIVE)
		return (path / CCALC2_ASP_STD_DYNAMIC_FILE).native();
	else
		return (path / CCALC2_ASP_STD_FILE).native();
}

// Additive file
inline std::string Config::additiveFile() const {
	fs::path path(installDir());

	if (mode() == MODE_INCREMENTAL || mode() == MODE_REACTIVE)
		return (path / CCALC2_ASP_ADDITIVE_DYNAMIC_FILE).native();
	else
		return (path / CCALC2_ASP_ADDITIVE_FILE).native();
}


// Gets the definition of a constant or NULL
std::string const* Config::def(std::string const& constant) const {
	try {
		return &mConstDefs.at(constant);
	}
	catch (std::out_of_range& e)
	{
		return NULL;
	}
	return NULL;
}


// Gets the query specified by the command, or null if it doesn't exist.
Config::Query const* Config::query(std::string const& queryCmd) const {
	if (hasQuery(queryCmd)) return &(mQueries.at(queryCmd));
	else return NULL;
}


// Set the running mode for the program
bool Config::mode(Mode newMode) {
	mCustomRunningMode++;
	if (mRunningMode == newMode) return false;
	mRunningMode = newMode;

	switch (newMode) {
	case MODE_STATIC_AUTO:
	case MODE_STATIC_MANUAL:
		if (!customCmd(TC_GROUNDER)) mStrOpts[TC_GROUNDER + _STR_TC_BEGIN_] = DEF_GRD_STATIC_CMD;
		if (!customCmd(TC_SOLVER)) mStrOpts[TC_SOLVER + _STR_TC_BEGIN_] = DEF_SO_STATIC_CMD;
		break;
	case MODE_INCREMENTAL:
		if (!customCmd(TC_GROUNDER)) mStrOpts[TC_GROUNDER + _STR_TC_BEGIN_] = DEF_GRD_INCREMENTAL_CMD;
		if (!customCmd(TC_SOLVER)) mStrOpts[TC_SOLVER + _STR_TC_BEGIN_] = DEF_SO_INCREMENTAL_CMD;
		break;
	case MODE_REACTIVE:
		if (!customCmd(TC_GROUNDER)) mStrOpts[TC_GROUNDER + _STR_TC_BEGIN_] = DEF_GRD_REACTIVE_CMD;
		if (!customCmd(TC_POSTPROC)) mRun[TC_POSTPROC] = false;
		if (!customCmd(TC_SOLVER)) mStrOpts[TC_SOLVER + _STR_TC_BEGIN_] = DEF_SO_REACTIVE_CMD;
		break;
	case MODE_UNKNOWN:
		break;
	}

	return (bool)(mCustomRunningMode - 1);
 }



// Parses the language represented in the string.
bool Config::parseLang(char const* str, Language& outLang) {
	if (boost::iequals(str, "bc")) outLang = LANG_BC;
	else if (boost::iequals(str, "bc+")) outLang = LANG_BCPLUS;
	else if (boost::iequals(str, "c+")) outLang = LANG_CPLUS;
	else if (boost::iequals(str, "mvpf")) outLang = LANG_MVPF;
	else return false;
	return true;
}

// Set the input language for the program
bool Config::lang(Language newLang) {
	mCustomLang++;
	if (mLang == newLang) return false;
	mLang = newLang;
	if (!mCustomRunningMode) {
		mode(MODE_STATIC_AUTO);
		mCustomRunningMode = 0;
	}

	if (newLang == LANG_MVPF) {
		mQueries.erase(CONST_QUERY_TRANSITIONS);
		mQueries.erase(CONST_QUERY_STATES);
		strOpt(STR_QUERY, CONST_QUERY_NONE);
	} else {
		mQueries[CONST_QUERY_TRANSITIONS] = Query("System transitions", CONST_QUERY_TRANSITIONS, 1, 1);
		mQueries[CONST_QUERY_STATES] = Query("System states", CONST_QUERY_STATES, 0, 0);
	}


	return (bool)(mCustomLang - 1);
 }

// Checks if a constant is defined
inline bool Config::isDefined(std::string const& constant) const {
	std::string constant_trimmed = utils::trimWhitespace(constant);

	if (constant_trimmed == CONST_MAXSTEP) {
		return customConfigOpt(OPT_MAXSTEP);
	} else if (constant_trimmed == CONST_MINSTEP) {
		return customConfigOpt(OPT_MINSTEP);
	} else if (constant_trimmed == CONST_QUERY) {
		return customStrOpt(STR_QUERY);
	} else if (constant_trimmed == CONST_MAXADDITIVE) {
		return customConfigOpt(OPT_MAXADDITIVE);
	} else {
		return (bool)mConstDefs.count(constant_trimmed);
	}
}

// Sets a config options to a boolean value.
bool Config::boolConfigOpt(ConfigOption opt, bool val) {
	mCustomConfig[opt]++;
	if (((bool)mConfigOpts[opt]) == val) return false;
	mConfigOpts[opt] = (unsigned int)val;
	return (bool)(mCustomConfig[opt] - 1);
}

// Sets a config option to an integral value.
bool Config::intConfigOpt(ConfigOption opt, unsigned int val) {
	mCustomConfig[opt]++;
	if (mConfigOpts[opt] == val) return false;
	mConfigOpts[opt] = val;
	return (bool)(mCustomConfig[opt] - 1);
}

// Sets a command option to the provided value.
bool Config::strOpt(StrOption opt, std::string const& val) {
	mCustomStr[opt]++;
	if (mStrOpts[opt] == val) return false;
	mStrOpts[opt] = val;
	return (bool)(mCustomStr[opt] - 1);
}

/// @return If the run status has been previously changed.
bool Config::run(Toolchain tool, bool val) {
	mCustomRun[tool]++;
	if(mRun[tool] == val) return false;
	mRun[tool] = val;
	return (bool)(mCustomRun[tool] - 1);
}


// Defines a constant
bool Config::def(std::string const& constant, std::string const& value) {
	std::string constant_trimmed = utils::trimWhitespace(constant);
	std::string value_trimmed = utils::trimWhitespace(value);
	unsigned int tmpVal;
	bool redef = false;
	bool bad = false;

	// Check this against several known constants and update their values if necessary...
	if (constant_trimmed == CONST_MAXSTEP) {
		std::pair<unsigned int,unsigned int> stepvals = parseMaxstep(value_trimmed);

		if (stepvals.second == UNDEFINED) {
			bad = true;
		} else {
			redef = intConfigOpt(OPT_MAXSTEP, stepvals.second);
			if (stepvals.first != UNDEFINED) intConfigOpt(OPT_MINSTEP, stepvals.first);
		}

	} else if (constant_trimmed == CONST_MINSTEP) {
		if (utils::from_string(tmpVal,value_trimmed)) {
			redef = intConfigOpt(OPT_MINSTEP, tmpVal);
		} else {
			// Oops... Throw a warning, ignore it, and continue.
			bad = true;
		}
	} else if (constant_trimmed == CONST_QUERY) {

	redef = strOpt(STR_QUERY,value_trimmed);

	} else if (constant_trimmed == CONST_MAXADDITIVE) {
		if (utils::from_string(tmpVal,value_trimmed)) {
			redef = intConfigOpt(OPT_MAXADDITIVE,tmpVal);
		} else {
			// Oops... Throw a warning, ignore it, and continue.
			bad = true;
		}
	} else {
		// It's a normal constant...
		redef = (bool)mConstDefs.count(constant_trimmed);
		mConstDefs[constant_trimmed] = value_trimmed;

	}

	if (bad) {
		// If the value was bad then go ahead and warn the user.
		utils::warning("The value '%s' is not valid for the reserved constant '%s'. It will be ignored.",true, value_trimmed.c_str() ,constant_trimmed.c_str());
	}

	return redef;
}

// Calculates the number of input files for a specific tool
size_t Config::cumulativeInputCount(Toolchain tool) const {

	size_t count = 0;

	// Let's count all the input files
	// which belong to
	// a) The current tool,
	// b) The tools immediately preceeding the tool which we aren't running.

	for (Toolchain i = tool; i >= _TC_BEGIN_; i = (Toolchain)((int)i - 1)) {
		// Only include files which haven't been included by a previous tool.
		if (i != tool && run(i)) break;

		for (InputList::const_iterator it = beginInput((Toolchain)i); it != endInput((Toolchain)i); it++) {
			count++;
		}
	}

	// Compile the input files from previous step's outputs.
	switch (tool) {
	case _TC_END_:
	case TC_REACTIVE_BRIDGE:
		// Reactive bridge is different.
		if (run(TC_TRANSLATOR)) {
			count++;
		}
		break;

	case TC_POSTPROC:
		if (run(TC_SOLVER)) {
			count++;
			break;
		}
		/* no break */

	case TC_SOLVER:
		if (run(TC_GROUNDER)) {
			count++;
			break;
		}
		/* no break */

	case TC_GROUNDER:
		if (run(TC_PREPROC)) {
			count++;
			break;
		}
		/* no break */

	case TC_PREPROC:
		if (run(TC_TRANSLATOR)) {
			count++;
			break;
		}
		/* no break */

	case TC_TRANSLATOR:
		// none
		break;

	}

	return count;
}

// Compiles a command line call for the given toolchain element
std::string Config::compileCommandLine(Toolchain tool, RunConfig const* subconfig) const {

	std::ostringstream out;
	std::list<std::string> tmp;
	compileArgs(tool, tmp, subconfig);

	out << command(tool);

	for (std::string const& arg : tmp) {
		out << " " << arg;
	}

	return out.str();
}

// Compiles the set of arguments used to call a specific element in the toolchain.
void Config::compileArgs(Toolchain tool, std::list<std::string>& arglist, RunConfig const* subconfig)  const {


	std::stringstream tmpstream;
	std::string tmpstr;

	tmpstream << opts(tool);

	while (tmpstream) {
		tmpstream >> tmpstr;
		arglist.push_back(tmpstr);
	}

	// Add step specific instructions
	switch (tool) {
	case _TC_END_:
	case TC_TRANSLATOR:
		compileInputArgs(tool, arglist);

		// The translator should be told to output the symbol table
		//TODO
		arglist.push_back("--symbol-table");
		arglist.push_back(strOpt(STR_SYMTAB_FILE));

		// We also should have it tell us what special constants it finds.
		arglist.push_back("--expressive-return");

		switch (lang()) {
		case LANG_CPLUS:
			arglist.push_back("--language=c+");
			break;

		case LANG_BC:
			arglist.push_back("--language=bc");
			break;
		case LANG_BCPLUS:
			arglist.push_back("--language=bc+");
			break;
		case LANG_MVPF:
			arglist.push_back("--language=mvpf");
			break;
		}


		// The translator should be told the translation mode.
		switch (mode()) {
		case MODE_STATIC_AUTO:
		case MODE_STATIC_MANUAL:
			arglist.push_back("--static");
			break;
		case MODE_INCREMENTAL:
		case MODE_REACTIVE:
		default:
			break;
		}

		break;

	case TC_PREPROC:

		arglist.push_back("-i");

		// The preprocessor should include the standard files in addition to the 'normal' include files.
		if (boolConfigOpt(OPT_INCL_STD))
			arglist.push_back(stdFile());
		if (boolConfigOpt(OPT_INCL_ADDITIVE))
			arglist.push_back(additiveFile());
		
		compileInputArgs(tool, arglist);

		break;

	case TC_SOLVER:
		// Solvers need:
		// * Number of solutions to find.
		// * Query information.
		// * Minimum step information
		// * Maximum step information.
		compileInputArgs(tool, arglist);

		// # solutions
		if (subconfig) {
			arglist.push_back(utils::to_string(subconfig->numSoln));
		} else {
			arglist.push_back(utils::to_string(intConfigOpt(OPT_NUM_SOLN)));
		}

		// special constants (if we're running what looks like a grounder/solver)
		if (!run(TC_GROUNDER)) {
			if (subconfig) {
				if (subconfig->query != "") arglist.push_back("-c query=" +subconfig->query);
				if (subconfig->maxstep != UNDEFINED) arglist.push_back("-c maxstep=" + utils::to_string(subconfig->maxstep));
				if (subconfig->minstep != UNDEFINED) arglist.push_back("-c minstep=" + utils::to_string(subconfig->minstep));
			} else {
				if (strOpt(STR_QUERY) != "") arglist.push_back("-c query=" + strOpt(STR_QUERY));
				if (intConfigOpt(OPT_MAXSTEP) != UNDEFINED) arglist.push_back("-c maxstep=" + utils::to_string(intConfigOpt(OPT_MAXSTEP)));
				if (intConfigOpt(OPT_MINSTEP) != UNDEFINED) arglist.push_back("-c minstep=" + utils::to_string(intConfigOpt(OPT_MINSTEP)));
			}


			if (intConfigOpt(OPT_MAXADDITIVE) != UNDEFINED) arglist.push_back("-c maxAdditive=" + utils::to_string(intConfigOpt(OPT_MAXADDITIVE)));
			if (strOpt(STR_NONE_ALIAS) != "") arglist.push_back("-c none=" + strOpt(STR_NONE_ALIAS));

			// The '--shift' flag signals that gringo should shift disjunction into the body of a rule.
			if (boolConfigOpt(OPT_SHIFT)) arglist.push_back("--shift");


			for (ConstantMap::const_iterator it = beginConstants(); it != endConstants(); it++) {
				arglist.push_back("-c");
				arglist.push_back(it->first + "=" + it->second);
			}
		}

		// min/max step
		if (mode() == MODE_INCREMENTAL || mode() == MODE_REACTIVE) {
			if (subconfig) {
				if (subconfig->minstep != UNDEFINED) arglist.push_back("--imin=" + utils::to_string(subconfig->minstep));
				if (subconfig->maxstep != UNDEFINED) {
					if (subconfig->maxstep > 0)
						arglist.push_back("--imax=" + utils::to_string(subconfig->maxstep));
					else
						arglist.push_back("--ibase");
				}
			} else {
				if (intConfigOpt(OPT_MINSTEP) != UNDEFINED) arglist.push_back("--imin=" + utils::to_string(intConfigOpt(OPT_MINSTEP)));
				if (intConfigOpt(OPT_MAXSTEP) != UNDEFINED){
					if (intConfigOpt(OPT_MAXSTEP) > 0)
						arglist.push_back("--imax=" + utils::to_string(intConfigOpt(OPT_MAXSTEP)));
					else
						arglist.push_back("--ibase");
				}
			}
		}

		// The --stats option
		if (boolConfigOpt(OPT_STATS)) {
			arglist.push_back("--stats");

			if (mode() == MODE_REACTIVE || mode() == MODE_INCREMENTAL)
				arglist.push_back("--istats");
		}


		if (mode() == MODE_REACTIVE && run(TC_REACTIVE_BRIDGE)) {

#ifdef NO_REACTIVE_BRIDGE
			if (intConfigOpt(OPT_EXT_PORT) != UNDEFINED)
				arglist.push_back("--port=" + utils::to_string(intConfigOpt(OPT_EXT_PORT)));
			else
#endif
				arglist.push_back("--port=" + utils::to_string(intConfigOpt(OPT_INT_PORT)));
		} else if (mode() == MODE_REACTIVE) {
			// we aren't running the reactive bridge.
			// connect to the external port instead.
			arglist.push_back("--port=" + utils::to_string(intConfigOpt(OPT_EXT_PORT)));
		} 
			

		break;
	case TC_GROUNDER:
		compileInputArgs(tool, arglist);

		if (subconfig) {
			if (subconfig->query != "") arglist.push_back("-c query=" +subconfig->query);
			if (subconfig->maxstep != UNDEFINED) arglist.push_back("-c maxstep=" + utils::to_string(subconfig->maxstep));
			if (subconfig->minstep != UNDEFINED) arglist.push_back("-c minstep=" + utils::to_string(subconfig->minstep));
		} else {
			if (strOpt(STR_QUERY) != "") arglist.push_back("-c query=" + utils::to_string(strOpt(STR_QUERY)));
			if (intConfigOpt(OPT_MAXSTEP) != UNDEFINED) arglist.push_back("-c maxstep=" + utils::to_string(intConfigOpt(OPT_MAXSTEP)));
			if (intConfigOpt(OPT_MINSTEP) != UNDEFINED) arglist.push_back("-c minstep=" + utils::to_string(intConfigOpt(OPT_MINSTEP)));
		}


		if (intConfigOpt(OPT_MAXADDITIVE) != UNDEFINED) arglist.push_back("-c maxAdditive=" + utils::to_string(intConfigOpt(OPT_MAXADDITIVE)));
		if (strOpt(STR_NONE_ALIAS) != "") arglist.push_back("-c none=" + strOpt(STR_NONE_ALIAS));

		// The '--shift' flag signals that gringo should shift disjunction into the body of a rule.
		if (boolConfigOpt(OPT_SHIFT)) arglist.push_back("--shift");


		for (ConstantMap::const_iterator it = beginConstants(); it != endConstants(); it++) {
			arglist.push_back("-c");
			arglist.push_back(it->first + "=" + it->second);
		}
		break;

	case TC_REACTIVE_BRIDGE:
#ifdef NO_REACTIVE_BRIDGE
		// Don't do anything!
#else
		// The reactive client doesn't need to know much.
		// Just the ports to use and where to find the symbol table
		compileInputArgs(tool, arglist);

		arglist.push_back("--port=" + utils::to_string(intConfigOpt(OPT_INT_PORT)));

		if (intConfigOpt(OPT_EXT_PORT) != UNDEFINED)
			arglist.push_back("--client-port=" + utils::to_string(intConfigOpt(OPT_EXT_PORT)));
		if (strOpt(STR_NONE_ALIAS) != "") 
			arglist.push_back("--none=" + strOpt(STR_NONE_ALIAS));
#endif
		break;

	case TC_POSTPROC:
		compileInputArgs(tool, arglist);
		if (strOpt(STR_NONE_ALIAS) != "")
			arglist.push_back("--none=" + strOpt(STR_NONE_ALIAS));
		break;
	}
}

// Sets the configuration to run up to (and including) the provided tool.
bool Config::setRunTo(Toolchain tool) {
	bool conflict = false;

//	for (int i = (int)_TC_BEGIN_; i < (int)tool+1; i++) {
//		conflict |= run((Toolchain)i, true);
//	}
	for (int i = ((int)tool)+1; i < (int)_TC_END_; i++) {
		conflict |= run((Toolchain)i, false);
	}
	return conflict;
}

// Sets the configuration to run from the provided tool.
bool Config::setRunFrom(Toolchain tool) {
	bool conflict = false;

	for (int i = (int)_TC_BEGIN_; i < (int)tool; i++) {
		conflict |= run((Toolchain)i, false);
	}
//	for (int i = (int)tool; i < (int)TC_END; i++) {
//		conflict |= run((Toolchain)i, true);
//	}
	return conflict;
}

// Sets the configuration to run only the provided tool.
bool Config::setOnlyRun(Toolchain tool) {
	bool conflict = false;

	for (int i = (int)_TC_BEGIN_; i < (int)tool; i++) {
		conflict |= run((Toolchain)i, false);
	}
	conflict |= run(tool,true);
	for (int i = ((int)tool)+1; i < (int)_TC_END_; i++) {
		conflict |= run((Toolchain)i, false);
	}
	return conflict;
}

// Attempts to add a query to the list of known queries.
bool Config::addQuery(std::string const& name, std::string const& cmd, unsigned int maxstep, unsigned int minstep) {
	bool unique = true;

	// ensure that the query is not already present...
	if (hasQuery(cmd)) unique = false;

	if (unique) {
		mQueries[cmd] = Query(name,cmd,minstep,maxstep);
	}

	return unique;
}

// Attempts to add a query to the list of known queries.
bool Config::addQuery(Query const& query) {
	bool unique = true;

	// ensure that the query is not already present...
	if (hasQuery(query.cmd)) unique = false;

	if (unique) {
		mQueries[query.cmd] = query;
	}

	return unique;
}

Config::FileType Config::addInput(std::string const& input) {

	char const* input_cstr = input.c_str();
	FileType type(false,_TC_BEGIN_, MODE_UNKNOWN);

	utils::debug("Adding input file '%s'.", true, input.c_str());

	// Try to find the extension the file extension.
	size_t pos = input.find_last_of('.');
	if (pos == std::string::npos) {
		// No file extension to speak of, default to the beginning of the toolchain.
		mInputs[_TC_BEGIN_].push_back(input);
		return type;
	}

	// We found an extension, let's test it against known extensions
	checkExtension(&input_cstr[pos], type);

	if (type.known) {
		utils::debug("Found the extension. It belongs to toolchain component '%d'", true, type.tool);
		mInputs[type.tool].push_back(input);
	} else {
		utils::debug("Unknown extension.", true);
		// Default to the beginning of the toolchain if we don't know what it is.
		mInputs[_TC_BEGIN_].push_back(input);
	}


	return type;
}

/// Parses a maxstep specification.
std::pair<unsigned int, unsigned int> Config::parseMaxstep(std::string const& maxstep) {
	size_t pos;
	std::pair<unsigned int, unsigned int> ret(UNDEFINED, UNDEFINED);

	std::string tmp;

	if ((pos = maxstep.find("..")) != std::string::npos) {
		// They've provided a range. Interpret it as a minstep and maxstep.
		tmp = utils::trimWhitespace(maxstep.substr(pos+2));

	} else {
		tmp = maxstep;
	}

	if (tmp == CONST_MAXSTEP_INFINITE) {
		ret.second = INF;	
	} else  if (!utils::from_string(ret.second,tmp)) {
		// error
		ret.first = UNDEFINED;
		ret.second = UNDEFINED;
	}

	if (ret.second != UNDEFINED 
		&& pos != std::string::npos 
		&& !utils::from_string(ret.first,utils::trimWhitespace(maxstep.substr(0,pos)))) {
		// error
		ret.first = UNDEFINED;
		ret.second = UNDEFINED;

	}

	return ret;
}

void Config::compileInputArgs(Toolchain tool, std::list<std::string>& args) const {
	// Otherwise, we need to aggregate all the input files
	// which belong to
	// a) The current tool,
	// b) The tools immediately preceeding the tool which we aren't running.

	// Compile the input files from previous step's outputs.
	switch (tool) {
	case _TC_END_:
	case TC_REACTIVE_BRIDGE:
		// Reactive bridge is different.
		// TODO Finalize this
		if (run(TC_TRANSLATOR)) {
//			out << " " << intTransSymTabFile();
		}
		break;

	case TC_POSTPROC:
		if (run(TC_SOLVER)) {
			args.push_back(output(TC_SOLVER));
			break;
		}
		/* no break */

	case TC_SOLVER:
		if (run(TC_GROUNDER)) {
			args.push_back(output(TC_GROUNDER));
			break;
		}
		/* no break */

	case TC_GROUNDER:
		if (run(TC_PREPROC)) {
			args.push_back(output(TC_PREPROC));
			break;
		}
		/* no break */

	case TC_PREPROC:
		if (run(TC_TRANSLATOR)) {
			args.push_back(output(TC_TRANSLATOR));
			break;
		}
		/* no break */

	case TC_TRANSLATOR:
		// none
		break;

	}

	for (int i = (int)tool; i >= (int)_TC_BEGIN_; i--) {
		// Only include files which haven't been included by a previous tool.
		if (i != (int)tool && run((Toolchain)i)) break;

		for (InputList::const_iterator it = beginInput((Toolchain)i); it != endInput((Toolchain)i); it++) {
			args.push_back(*it);
		}
	}
}


Config::FileType& Config::checkExtension(char const* ext, FileType& out) const {
	char const* marker;

	out.known = true;
	out.runningMode = MODE_UNKNOWN;
	out.tool = _TC_BEGIN_;



	// Skip the period if they included it.
	if (ext[0] == '.') ext++;

	utils::debug("Checking extension '%s'.", true, ext);

	
#line 894 "<stdout>"
	{
		char yych;
		unsigned int yyaccept = 0;

		yych = *ext;
		switch (yych) {
		case '\n':	goto yy2;
		case 'a':	goto yy5;
		case 'c':	goto yy3;
		case 'f':	goto yy8;
		case 'g':	goto yy10;
		case 'i':	goto yy7;
		case 'l':	goto yy9;
		case 'o':	goto yy6;
		case 's':	goto yy11;
		default:	goto yy12;
		}
yy2:
		ext = marker;
		switch (yyaccept) {
		case 0: 	goto yy4;
		case 1: 	goto yy34;
		case 2: 	goto yy59;
		case 3: 	goto yy85;
		}
yy3:
		++ext;
		switch ((yych = *ext)) {
		case '+':	goto yy82;
		case 'p':	goto yy84;
		default:	goto yy4;
		}
yy4:
#line 927 "Config.re2c"
		{ out.known = false; return out;}
#line 930 "<stdout>"
yy5:
		yyaccept = 0;
		yych = *(marker = ++ext);
		switch (yych) {
		case 'a':	goto yy54;
		case 'c':	goto yy57;
		case 'f':	goto yy56;
		case 'g':	goto yy53;
		case 'l':	goto yy55;
		case 's':	goto yy78;
		default:	goto yy4;
		}
yy6:
		yyaccept = 0;
		yych = *(marker = ++ext);
		switch (yych) {
		case 'a':	goto yy54;
		case 'c':	goto yy57;
		case 'f':	goto yy56;
		case 'g':	goto yy53;
		case 'l':	goto yy55;
		default:	goto yy4;
		}
yy7:
		yyaccept = 0;
		yych = *(marker = ++ext);
		switch (yych) {
		case 'a':	goto yy29;
		case 'c':	goto yy32;
		case 'f':	goto yy31;
		case 'g':	goto yy28;
		case 'l':	goto yy30;
		default:	goto yy4;
		}
yy8:
		yyaccept = 0;
		yych = *(marker = ++ext);
		switch (yych) {
		case '2':	goto yy24;
		default:	goto yy4;
		}
yy9:
		yych = *++ext;
		switch (yych) {
		case 'p':	goto yy22;
		default:	goto yy4;
		}
yy10:
		yyaccept = 0;
		yych = *(marker = ++ext);
		switch (yych) {
		case 'r':	goto yy19;
		default:	goto yy4;
		}
yy11:
		yyaccept = 0;
		yych = *(marker = ++ext);
		switch (yych) {
		case 'y':	goto yy13;
		default:	goto yy4;
		}
yy12:
		yych = *++ext;
		goto yy4;
yy13:
		yych = *++ext;
		switch (yych) {
		case 'm':	goto yy14;
		default:	goto yy2;
		}
yy14:
		yych = *++ext;
		switch (yych) {
		case 't':	goto yy15;
		default:	goto yy2;
		}
yy15:
		yych = *++ext;
		switch (yych) {
		case 'a':	goto yy16;
		default:	goto yy2;
		}
yy16:
		yych = *++ext;
		switch (yych) {
		case 'b':	goto yy17;
		default:	goto yy2;
		}
yy17:
		++ext;
#line 925 "Config.re2c"
		{ out.tool = TC_REACTIVE_BRIDGE; out.runningMode = MODE_REACTIVE; return out;}
#line 1023 "<stdout>"
yy19:
		yych = *++ext;
		switch (yych) {
		case 'd':	goto yy20;
		default:	goto yy2;
		}
yy20:
		++ext;
#line 919 "Config.re2c"
		{ out.tool = TC_SOLVER; out.runningMode = MODE_STATIC_AUTO | MODE_STATIC_MANUAL; return out;}
#line 1034 "<stdout>"
yy22:
		++ext;
#line 911 "Config.re2c"
		{ out.tool = TC_GROUNDER; out.runningMode = MODE_STATIC_AUTO | MODE_STATIC_MANUAL; return out;}
#line 1039 "<stdout>"
yy24:
		yych = *++ext;
		switch (yych) {
		case 'l':	goto yy25;
		default:	goto yy2;
		}
yy25:
		yych = *++ext;
		switch (yych) {
		case 'p':	goto yy26;
		default:	goto yy2;
		}
yy26:
		++ext;
#line 907 "Config.re2c"
		{ out.tool = TC_PREPROC; out.runningMode = MODE_STATIC_AUTO | MODE_STATIC_MANUAL; return out; }
#line 1056 "<stdout>"
yy28:
		yych = *++ext;
		switch (yych) {
		case 'r':	goto yy50;
		default:	goto yy2;
		}
yy29:
		yych = *++ext;
		switch (yych) {
		case 's':	goto yy47;
		default:	goto yy2;
		}
yy30:
		yych = *++ext;
		switch (yych) {
		case 'p':	goto yy45;
		default:	goto yy2;
		}
yy31:
		yych = *++ext;
		switch (yych) {
		case '2':	goto yy41;
		default:	goto yy2;
		}
yy32:
		yych = *++ext;
		switch (yych) {
		case '+':	goto yy35;
		case 'p':	goto yy33;
		default:	goto yy2;
		}
yy33:
		yyaccept = 1;
		yych = *(marker = ++ext);
		switch (yych) {
		case 'l':	goto yy37;
		default:	goto yy34;
		}
yy34:
#line 903 "Config.re2c"
		{ out.tool = TC_TRANSLATOR; out.runningMode = MODE_INCREMENTAL; return out;}
#line 1098 "<stdout>"
yy35:
		++ext;
#line 905 "Config.re2c"
		{ out.tool = TC_TRANSLATOR; out.runningMode = MODE_INCREMENTAL; return out;}
#line 1103 "<stdout>"
yy37:
		yych = *++ext;
		switch (yych) {
		case 'u':	goto yy38;
		default:	goto yy2;
		}
yy38:
		yych = *++ext;
		switch (yych) {
		case 's':	goto yy39;
		default:	goto yy2;
		}
yy39:
		++ext;
#line 904 "Config.re2c"
		{ out.tool = TC_TRANSLATOR; out.runningMode = MODE_INCREMENTAL; return out;}
#line 1120 "<stdout>"
yy41:
		yych = *++ext;
		switch (yych) {
		case 'l':	goto yy42;
		default:	goto yy2;
		}
yy42:
		yych = *++ext;
		switch (yych) {
		case 'p':	goto yy43;
		default:	goto yy2;
		}
yy43:
		++ext;
#line 909 "Config.re2c"
		{ out.tool = TC_PREPROC; out.runningMode = MODE_INCREMENTAL; return out;}
#line 1137 "<stdout>"
yy45:
		++ext;
#line 913 "Config.re2c"
		{ out.tool = TC_GROUNDER; out.runningMode = MODE_INCREMENTAL; return out;}
#line 1142 "<stdout>"
yy47:
		yych = *++ext;
		switch (yych) {
		case 'p':	goto yy48;
		default:	goto yy2;
		}
yy48:
		++ext;
#line 917 "Config.re2c"
		{ out.tool = TC_GROUNDER; out.runningMode = MODE_INCREMENTAL; return out;}
#line 1153 "<stdout>"
yy50:
		yych = *++ext;
		switch (yych) {
		case 'd':	goto yy51;
		default:	goto yy2;
		}
yy51:
		++ext;
#line 921 "Config.re2c"
		{ out.tool = TC_SOLVER; out.runningMode = MODE_INCREMENTAL; return out;}
#line 1164 "<stdout>"
yy53:
		yych = *++ext;
		switch (yych) {
		case 'r':	goto yy75;
		default:	goto yy2;
		}
yy54:
		yych = *++ext;
		switch (yych) {
		case 's':	goto yy72;
		default:	goto yy2;
		}
yy55:
		yych = *++ext;
		switch (yych) {
		case 'p':	goto yy70;
		default:	goto yy2;
		}
yy56:
		yych = *++ext;
		switch (yych) {
		case '2':	goto yy66;
		default:	goto yy2;
		}
yy57:
		yych = *++ext;
		switch (yych) {
		case '+':	goto yy60;
		case 'p':	goto yy58;
		default:	goto yy2;
		}
yy58:
		yyaccept = 2;
		yych = *(marker = ++ext);
		switch (yych) {
		case 'l':	goto yy62;
		default:	goto yy59;
		}
yy59:
#line 900 "Config.re2c"
		{ out.tool = TC_TRANSLATOR; out.runningMode = MODE_REACTIVE; return out;}
#line 1206 "<stdout>"
yy60:
		++ext;
#line 902 "Config.re2c"
		{ out.tool = TC_TRANSLATOR; out.runningMode = MODE_REACTIVE; return out;}
#line 1211 "<stdout>"
yy62:
		yych = *++ext;
		switch (yych) {
		case 'u':	goto yy63;
		default:	goto yy2;
		}
yy63:
		yych = *++ext;
		switch (yych) {
		case 's':	goto yy64;
		default:	goto yy2;
		}
yy64:
		++ext;
#line 901 "Config.re2c"
		{ out.tool = TC_TRANSLATOR; out.runningMode = MODE_REACTIVE; return out;}
#line 1228 "<stdout>"
yy66:
		yych = *++ext;
		switch (yych) {
		case 'l':	goto yy67;
		default:	goto yy2;
		}
yy67:
		yych = *++ext;
		switch (yych) {
		case 'p':	goto yy68;
		default:	goto yy2;
		}
yy68:
		++ext;
#line 908 "Config.re2c"
		{ out.tool = TC_PREPROC; out.runningMode = MODE_REACTIVE; return out;}
#line 1245 "<stdout>"
yy70:
		++ext;
#line 912 "Config.re2c"
		{ out.tool = TC_GROUNDER; out.runningMode = MODE_REACTIVE; return out;}
#line 1250 "<stdout>"
yy72:
		yych = *++ext;
		switch (yych) {
		case 'p':	goto yy73;
		default:	goto yy2;
		}
yy73:
		++ext;
#line 916 "Config.re2c"
		{ out.tool = TC_GROUNDER; out.runningMode = MODE_REACTIVE; return out;}
#line 1261 "<stdout>"
yy75:
		yych = *++ext;
		switch (yych) {
		case 'd':	goto yy76;
		default:	goto yy2;
		}
yy76:
		++ext;
#line 920 "Config.re2c"
		{ out.tool = TC_SOLVER; out.runningMode = MODE_REACTIVE; return out;}
#line 1272 "<stdout>"
yy78:
		++ext;
		switch ((yych = *ext)) {
		case 'p':	goto yy80;
		default:	goto yy79;
		}
yy79:
#line 923 "Config.re2c"
		{ out.tool = TC_POSTPROC; out.runningMode = MODE_STATIC_AUTO | MODE_STATIC_MANUAL | MODE_INCREMENTAL; return out;}
#line 1282 "<stdout>"
yy80:
		++ext;
#line 915 "Config.re2c"
		{ out.tool = TC_GROUNDER; out.runningMode = MODE_STATIC_AUTO | MODE_STATIC_MANUAL; return out;}
#line 1287 "<stdout>"
yy82:
		++ext;
#line 899 "Config.re2c"
		{ out.tool = TC_TRANSLATOR; out.runningMode = MODE_STATIC_AUTO | MODE_STATIC_MANUAL | MODE_INCREMENTAL; return out;}
#line 1292 "<stdout>"
yy84:
		yyaccept = 3;
		yych = *(marker = ++ext);
		switch (yych) {
		case 'l':	goto yy86;
		default:	goto yy85;
		}
yy85:
#line 897 "Config.re2c"
		{ out.tool = TC_TRANSLATOR; out.runningMode = MODE_STATIC_AUTO | MODE_STATIC_MANUAL | MODE_INCREMENTAL; return out;}
#line 1303 "<stdout>"
yy86:
		yych = *++ext;
		switch (yych) {
		case 'u':	goto yy87;
		default:	goto yy2;
		}
yy87:
		yych = *++ext;
		switch (yych) {
		case 's':	goto yy88;
		default:	goto yy2;
		}
yy88:
		++ext;
#line 898 "Config.re2c"
		{ out.tool = TC_TRANSLATOR; out.runningMode = MODE_STATIC_AUTO | MODE_STATIC_MANUAL | MODE_INCREMENTAL; return out;}
#line 1320 "<stdout>"
	}
#line 928 "Config.re2c"


	return out;
}
