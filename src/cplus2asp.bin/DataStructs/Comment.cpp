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


#include <string>

#include "Comment.h"
#include "ltsglobals.h"

// Default constructor.
Comment::Comment()
{
	contents = "";
	fileName = "";
	loc = new YYLTYPE;
	loc->first_line = loc->last_line = loc->first_column = loc->last_column = 0;
	isRealComment = true;
}

// Assignment operator overload.
Comment& Comment::operator=(const Comment &rhs)
{
	// Skip self-assignment.
	if(this != &rhs)
	{
		this->contents = rhs.contents;
		this->fileName = rhs.fileName;
		if(rhs.loc != NULL)
		{
			if(this->loc == NULL)
			{
				this->loc = new YYLTYPE;
			}
			this->loc->first_line = rhs.loc->first_line;
			this->loc->last_line = rhs.loc->last_line;
			this->loc->first_column = rhs.loc->first_column;
			this->loc->last_column = rhs.loc->last_column;
		}
		else
		{
			if(this->loc != NULL)
			{
				delete this->loc;
			}
			this->loc = NULL;
		}
		this->isRealComment = rhs.isRealComment;
	}
	return *this;
}

// Checks if the comment came from the given file.
bool Comment::isInFile(std::string otherFileName)
{
	bool retVal = false; // Start pessimistic.
	if(this->fileName.compare(otherFileName) == 0)
	{
		retVal = true;
	}
	return retVal;
}

// Checks if the comment's location is totally past the given location.
bool Comment::isAfterLoc(YYLTYPE otherLoc)
{
	bool retVal = false; // Start pessimistic.
	if(otherLoc.last_line < this->loc->first_line)
	{
		retVal = true;
	}
	else if(otherLoc.last_line == this->loc->first_line && otherLoc.last_column < this->loc->first_column)
	{
		retVal = true;
	}
	return retVal;
}

// Checks if the comment's location is totally before the given location.
bool Comment::isBeforeLoc(YYLTYPE otherLoc)
{
	bool retVal = false; // Start pessimistic.
	if(otherLoc.first_line > this->loc->last_line)
	{
		retVal = true;
	}
	else if(otherLoc.first_line == this->loc->last_line && otherLoc.first_column > this->loc->last_column)
	{
		retVal = true;
	}
	return retVal;
}

// Turns the comment's contents back into a proper comment.
std::string Comment::output()
{
	std::string tempContents = "";
	if(isRealComment)
	{
		tempContents = "%";
		size_t newlineLoc = std::string::npos;
		size_t i = 0;
		while(i < this->contents.length())
		{
			newlineLoc = tempContents.find('\n', i);
			if(newlineLoc == std::string::npos)
			{
				tempContents += this->contents.substr(i);
				i = std::string::npos;
			}
			else
			{	// Handle a newline by adding a "%" after it so the next comment line is commented too.
				tempContents += this->contents.substr(i,newlineLoc - i);
				tempContents += "\n%";
				i = newlineLoc + 1;
			}
		}
	}
	else
	{	// Not a real comment, just pass the raw text through.
		tempContents = this->contents;
	}
	return tempContents;
}

// Destructor.
Comment::~Comment()
{
	if(loc != NULL)
	{
		delete loc;
		loc = NULL;
	}
}
