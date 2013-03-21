/* Generated by re2c 0.13.5 on Thu Mar 21 14:42:34 2013 */
#line 1 "Interpreter.re2c"
/*
 * Copyright (c) 2010-2013 <Joseph Babb, Michael Cassollary, Joohyung Lee>
 *
 * For information on how to contact the authors, please visit
 *      http://reasoning.eas.asu.edu/cplus2asp
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



#include <iostream>
#include <string>
#include <iomanip>

#include "Interpreter.h"
#include "utils.h"
#include "Config.h"

// Shows the help dialog.
void Interpreter::showHelp(std::ostream& output) {
	std::cout 
		<< "You may specify one or more of the following options, each followed by a return.\n"
		<< std::endl
		<< '\t' << std::setw(15) << std::left << "queries" << "- Displays the list of queries that are available to run.\n"
		<< '\t' << std::setw(15) << std::left << "config" << "- Displays the current run configuration.\n"
		<< '\t' << std::setw(15) << std::left << "query=ID " << "- Selects and runs an available query.\n"
		<< '\t' << std::setw(15) << std::left << "sol=#" << "- Sets the number of solutions to find to #.\n"
		<< "\t\t" << "- Specifying '" << CONST_DEFAULT << "' for # resets the option to the default value."
		<< '\t' << std::setw(15) << std::left << "maxstep=#" << "- Overrides the maximum step on the next query.\n"
		<< "\t\t" << "- Specifying '" << CONST_MAXSTEP_INFINITE << "' indicates that there should be no maximum step.\n"
		<< "\t\t" << "- Specifying '" << CONST_DEFAULT << "' for # resets the option to the default value."
		<< '\t' << std::setw(15) << std::left << "minstep=#" << "- Overrides the minimum step on the next query, setting it to #.\n"
		<< "\t\t" << "- Specifying '" << CONST_DEFAULT << "' for # resets the option to the default value."
		<< '\t' << std::setw(15) << std::left << "help" << "- Displays this dialog.\n"
		<< '\t' << std::setw(15) << std::left << "exit" << "- Exits the program.\n";	
}



// Interprets an action and provides the action requested an any additional value provided.
Interpreter::Action Interpreter::interpret(std::string const& command, std::string& outVal) {
	size_t pos;
	Action action;


	// Figure out the action.
	if ((pos = command.find("=")) != std::string::npos) {
		action = lex(trimWhitespace(command.substr(0,pos)));
	} else {
		action = lex(trimWhitespace(command));
	}

	// get the associated value if applicable.
	if (action != INVALID && pos != std::string::npos && pos + 1 <= command.size()) {
		outVal = trimWhitespace(command.substr(pos+1));
	} else {
		outVal = "";
	}


	return action;
}


// Determines the action requested based on its name
Interpreter::Action Interpreter::lex(std::string const& commandName) {
	char const* cstr = commandName.c_str();
	char const* marker;

	
#line 88 "<stdout>"
	{
		char yych;

		yych = *cstr;
		switch (yych) {
		case '\n':	goto yy2;
		case 'C':
		case 'c':	goto yy5;
		case 'E':
		case 'e':	goto yy9;
		case 'H':
		case 'h':	goto yy8;
		case 'M':
		case 'm':	goto yy7;
		case 'Q':
		case 'q':	goto yy3;
		case 'S':
		case 's':	goto yy6;
		default:	goto yy10;
		}
yy2:
		cstr = marker;
		goto yy4;
yy3:
		yych = *(marker = ++cstr);
		switch (yych) {
		case 'U':
		case 'u':	goto yy42;
		default:	goto yy4;
		}
yy4:
#line 99 "Interpreter.re2c"
		{ return INVALID; }
#line 122 "<stdout>"
yy5:
		yych = *(marker = ++cstr);
		switch (yych) {
		case 'O':
		case 'o':	goto yy36;
		default:	goto yy4;
		}
yy6:
		yych = *(marker = ++cstr);
		switch (yych) {
		case 'O':
		case 'o':	goto yy33;
		default:	goto yy4;
		}
yy7:
		yych = *(marker = ++cstr);
		switch (yych) {
		case 'A':
		case 'a':	goto yy20;
		case 'I':
		case 'i':	goto yy19;
		default:	goto yy4;
		}
yy8:
		yych = *(marker = ++cstr);
		switch (yych) {
		case 'E':
		case 'e':	goto yy15;
		default:	goto yy4;
		}
yy9:
		yych = *(marker = ++cstr);
		switch (yych) {
		case 'X':
		case 'x':	goto yy11;
		default:	goto yy4;
		}
yy10:
		yych = *++cstr;
		goto yy4;
yy11:
		yych = *++cstr;
		switch (yych) {
		case 'I':
		case 'i':	goto yy12;
		default:	goto yy2;
		}
yy12:
		yych = *++cstr;
		switch (yych) {
		case 'T':
		case 't':	goto yy13;
		default:	goto yy2;
		}
yy13:
		++cstr;
#line 98 "Interpreter.re2c"
		{ return EXIT; }
#line 181 "<stdout>"
yy15:
		yych = *++cstr;
		switch (yych) {
		case 'L':
		case 'l':	goto yy16;
		default:	goto yy2;
		}
yy16:
		yych = *++cstr;
		switch (yych) {
		case 'P':
		case 'p':	goto yy17;
		default:	goto yy2;
		}
yy17:
		++cstr;
#line 97 "Interpreter.re2c"
		{ return SHOW_HELP; }
#line 200 "<stdout>"
yy19:
		yych = *++cstr;
		switch (yych) {
		case 'N':
		case 'n':	goto yy27;
		default:	goto yy2;
		}
yy20:
		yych = *++cstr;
		switch (yych) {
		case 'X':
		case 'x':	goto yy21;
		default:	goto yy2;
		}
yy21:
		yych = *++cstr;
		switch (yych) {
		case 'S':
		case 's':	goto yy22;
		default:	goto yy2;
		}
yy22:
		yych = *++cstr;
		switch (yych) {
		case 'T':
		case 't':	goto yy23;
		default:	goto yy2;
		}
yy23:
		yych = *++cstr;
		switch (yych) {
		case 'E':
		case 'e':	goto yy24;
		default:	goto yy2;
		}
yy24:
		yych = *++cstr;
		switch (yych) {
		case 'P':
		case 'p':	goto yy25;
		default:	goto yy2;
		}
yy25:
		++cstr;
#line 95 "Interpreter.re2c"
		{ return SET_MAXSTEP; }
#line 247 "<stdout>"
yy27:
		yych = *++cstr;
		switch (yych) {
		case 'S':
		case 's':	goto yy28;
		default:	goto yy2;
		}
yy28:
		yych = *++cstr;
		switch (yych) {
		case 'T':
		case 't':	goto yy29;
		default:	goto yy2;
		}
yy29:
		yych = *++cstr;
		switch (yych) {
		case 'E':
		case 'e':	goto yy30;
		default:	goto yy2;
		}
yy30:
		yych = *++cstr;
		switch (yych) {
		case 'P':
		case 'p':	goto yy31;
		default:	goto yy2;
		}
yy31:
		++cstr;
#line 96 "Interpreter.re2c"
		{ return SET_MINSTEP; }
#line 280 "<stdout>"
yy33:
		yych = *++cstr;
		switch (yych) {
		case 'L':
		case 'l':	goto yy34;
		default:	goto yy2;
		}
yy34:
		++cstr;
#line 94 "Interpreter.re2c"
		{ return SET_NUMSOLN; }
#line 292 "<stdout>"
yy36:
		yych = *++cstr;
		switch (yych) {
		case 'N':
		case 'n':	goto yy37;
		default:	goto yy2;
		}
yy37:
		yych = *++cstr;
		switch (yych) {
		case 'F':
		case 'f':	goto yy38;
		default:	goto yy2;
		}
yy38:
		yych = *++cstr;
		switch (yych) {
		case 'I':
		case 'i':	goto yy39;
		default:	goto yy2;
		}
yy39:
		yych = *++cstr;
		switch (yych) {
		case 'G':
		case 'g':	goto yy40;
		default:	goto yy2;
		}
yy40:
		++cstr;
#line 92 "Interpreter.re2c"
		{ return SHOW_CONFIG; }
#line 325 "<stdout>"
yy42:
		yych = *++cstr;
		switch (yych) {
		case 'E':
		case 'e':	goto yy43;
		default:	goto yy2;
		}
yy43:
		yych = *++cstr;
		switch (yych) {
		case 'R':
		case 'r':	goto yy44;
		default:	goto yy2;
		}
yy44:
		yych = *++cstr;
		switch (yych) {
		case 'I':
		case 'i':	goto yy45;
		case 'Y':
		case 'y':	goto yy46;
		default:	goto yy2;
		}
yy45:
		yych = *++cstr;
		switch (yych) {
		case 'E':
		case 'e':	goto yy48;
		default:	goto yy2;
		}
yy46:
		++cstr;
#line 93 "Interpreter.re2c"
		{ return SET_QUERY; }
#line 360 "<stdout>"
yy48:
		yych = *++cstr;
		switch (yych) {
		case 'S':
		case 's':	goto yy49;
		default:	goto yy2;
		}
yy49:
		++cstr;
#line 91 "Interpreter.re2c"
		{ return SHOW_QUERIES; }
#line 372 "<stdout>"
	}
#line 100 "Interpreter.re2c"

}

