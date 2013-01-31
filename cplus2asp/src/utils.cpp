/*
 * utils.cpp
 *
 *  Created on: Jan 24, 2013
 *      Author: joseph
 */
#include <cstdarg>
#include <cstdlib>
#include <cctype>
#include <sstream>
#include <iostream>
#include <cstring>

#include "utils.h"

bool isInteger(const char *str)
{
	bool retVal = true; // Start optimistic.
	size_t strLength = strlen(str);
	if(strLength == 0 || !(isdigit(str[0]) || str[0] == '+' || str[0] == '-'))
	{ // Must be >0 length and start with a digit, +, or -.
		retVal = false;
	}
	else
	{
		// The rest of the string must be digits.
		for(unsigned int i = 1; i < strLength; i++)
		{
			if(!isdigit(str[i]))
			{
				retVal = false;
				break;
			}
		}
	}
	return retVal;
}

void nice_exit(int exitCode, const char* message)
{
	if(exitCode == 0 && message != NULL)
	{
		std::cout << message << std::endl;
	}
	else if(exitCode != 0 && message != NULL)
	{
		std::cerr << message << std::endl;
	}
	exit(exitCode);
}

std::string trimWhitespace(std::string const& text)
{
	std::string retVal = "";
	std::string whitespace = " \n\f\r\t\v";
	size_t sztFirstPos = 0, sztSecondPos = 0;
	if(text.length() > 0)
	{
		sztFirstPos = text.find_first_not_of(whitespace);
		sztSecondPos = text.find_last_not_of(whitespace);
		if(sztFirstPos != std::string::npos)
		{	// We got two valid positions, trim accordingly.
			retVal = text.substr(sztFirstPos, sztSecondPos - sztFirstPos + 1);
		}
		else
		{	// The whole dang string is whitespace, return blank.
			retVal = "";
		}
	}
	return retVal;
}


void pragma(char const* fmt, bool newline, ...) {
	   va_list arg;

	   fprintf(stdout, "%% Pragma: ");

	   va_start(arg, newline);
	   vfprintf(stdout, fmt, arg);
	   va_end(arg);

	   if (newline)
		   fprintf(stdout, "\n");
}


void warning(char const* fmt, bool newline, ...) {
	   va_list arg;

	   fprintf(stderr, "%% Warning: ");

	   va_start(arg, newline);
	   vfprintf(stderr, fmt, arg);
	   va_end(arg);

	   if (newline)
		   fprintf(stderr, "\n");
}


void error(char const* fmt, bool newline, unsigned char exitCode, ...) {
	   va_list arg;

	   fprintf(stderr, "%% Error: ");

	   va_start(arg, exitCode);
	   vfprintf(stderr, fmt, arg);
	   va_end(arg);

	   if (newline)
		   fprintf(stderr, "\n");

	   if (exitCode) exit(exitCode);
}

void debug(char const* fmt, bool newline, ...) {
#ifdef DEBUG
	   va_list arg;

	   fprintf(stdout, "%% Debug: ");

	   va_start(arg, newline);
	   vfprintf(stdout, fmt, arg);
	   va_end(arg);

	   if (newline)
		   fprintf(stdout, "\n");
#endif
}
