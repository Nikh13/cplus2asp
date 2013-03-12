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


/* Generated by re2c 0.13.5 on Wed Feb 20 16:46:54 2013 */
#line 1 "DataStructs/Constant.re2c"
/* Generated by re2c 0.13.5 on Fri Feb  1 20:07:26 2013 */
#line 1 "DataStructs/Constant.re2c"

#include "Attribute.h"
#include "Element.h"
#include "Variable.h"
#include "Sort.h"
#include "utilities.h"
#include "Translator.h"
#include "ElementCounter.h"
#include "Constant.h"
#include "Context.h"

// Full constructor.
Constant::Constant(std::string const& name, Sort const* domain, ConstantType type, ConstSortList const* params)
	: Element(name, Translator::sanitizeConstantName(name), Element::ELEM_CONST)
{
	mConstType = type;
	mDomain = domain;

	if (params) mParams = *params;

	mFullName = baseName();
	if(!mParams.empty())
	{
		mFullName += "(";
		mFullName += utils::elementVectorToFullNameString<Sort const*>(mParams);
		mFullName += ")";
	}

	mFullTransName = baseTransName();
	if(!mParams.empty())
	{
		mFullTransName += "(";
		mFullTransName += utils::elementVectorToFullTransNameString<Sort const*>(mParams);
		mFullTransName += ")";
	}
}

Constant::Constant(std::string const& name, ConstantType type, ConstSortList const* params)
	: Element(name, Translator::sanitizeConstantName(name), Element::ELEM_CONST)
{
	mConstType = type;
	mDomain = NULL;

	if (params) mParams = *params;

	mFullName = baseName();
	if(!mParams.empty())
	{
		mFullName += "(";
		mFullName += utils::elementVectorToFullNameString<Sort const*>(mParams);
		mFullName += ")";
	}

	mFullTransName = baseTransName();
	if(!mParams.empty())
	{
		mFullTransName += "(";
		mFullTransName += utils::elementVectorToFullTransNameString<Sort const*>(mParams);
		mFullTransName += ")";
	}
}

bool Constant::isNumeric() const {
	return domain() && domain()->isNumeric();
}

bool Constant::isBoolean() const {
	return domain() && domain()->isBoolean();
}

bool Constant::isStarred() const {
	return domain() && domain()->isStarred();
}

// Standard toString function.
std::string Constant::toString() const
{
	std::string tempStr;
	tempStr += "[Constant]";
	tempStr += "\n  params = (";
	if(!mParams.empty())
	{
		tempStr += utils::elementVectorToFullNameString<Sort const*>(mParams, ", ", true);
	}
	tempStr += ")";
	tempStr += "\n  domain = ";
	if(!mDomain)
	{
		tempStr += "NULL";
	}
	else
	{
		tempStr += "\"";
		tempStr += mDomain->fullName();
		tempStr += "\"";
	}
	tempStr += "\n  constType = ";

	// Print out the English version of the possible enum values of constType.
	tempStr += Constant::constTypeToString(mConstType);
	return tempStr;
}

// Generates a string representation of a Constant's type.
std::string Constant::constTypeToString(ConstantType _constType)
{
	// Print out the English version of the possible enum values of constType.
	switch (_constType)
	{
	case CONST_ACTION:
		return "action";
	case CONST_ABACTION:
		return "abAction";
	case CONST_ABFLUENT:
		return "abFluent";
	case CONST_ATTRIBUTE:
		return "attribute";
	case CONST_EXOGENOUSACTION:
		return "exogenousAction";
	case CONST_INERTIALFLUENT:
		return "inertialFluent";
	case CONST_RIGID:
		return "rigid";
	case CONST_SDFLUENT:
		return "sdFluent";
	case CONST_SIMPLEFLUENT:
		return "simpleFluent";
	case CONST_ADDITIVEACTION:
		return "additiveAction";
	case CONST_ADDITIVEFLUENT:
		return "additiveFluent";
	case CONST_STATICAB:
		return "staticAbnormality";
	case CONST_DYNAMICAB:
		return "dynamicAbnormality";
	default:
		// Unknown or unrecognized constant type.
		return "UNKNOWN";
	}
}

enum Constant::ConstantType Constant::stringToConstType(char const* _constType) {
	char const* marker;
	
#line 150 "<stdout>"
	{
		char yych;

		yych = *_constType;
		switch (yych) {
		case '\n':	goto yy2;
		case 'a':	goto yy3;
		case 'd':	goto yy9;
		case 'e':	goto yy5;
		case 'i':	goto yy6;
		case 'r':	goto yy7;
		case 's':	goto yy8;
		default:	goto yy10;
		}
yy2:
		_constType = marker;
		goto yy4;
yy3:
		yych = *(marker = ++_constType);
		switch (yych) {
		case 'b':	goto yy102;
		case 'c':	goto yy103;
		case 'd':	goto yy100;
		case 't':	goto yy101;
		default:	goto yy4;
		}
yy4:
#line 165 "DataStructs/Constant.re2c"
		{ return CONST_UNKNOWN; }
#line 180 "<stdout>"
yy5:
		yych = *(marker = ++_constType);
		switch (yych) {
		case 'x':	goto yy85;
		default:	goto yy4;
		}
yy6:
		yych = *(marker = ++_constType);
		switch (yych) {
		case 'n':	goto yy71;
		default:	goto yy4;
		}
yy7:
		yych = *(marker = ++_constType);
		switch (yych) {
		case 'i':	goto yy66;
		default:	goto yy4;
		}
yy8:
		yych = *(marker = ++_constType);
		switch (yych) {
		case 'd':	goto yy31;
		case 'i':	goto yy30;
		case 't':	goto yy29;
		default:	goto yy4;
		}
yy9:
		yych = *(marker = ++_constType);
		switch (yych) {
		case 'y':	goto yy11;
		default:	goto yy4;
		}
yy10:
		yych = *++_constType;
		goto yy4;
yy11:
		yych = *++_constType;
		switch (yych) {
		case 'n':	goto yy12;
		default:	goto yy2;
		}
yy12:
		yych = *++_constType;
		switch (yych) {
		case 'a':	goto yy13;
		default:	goto yy2;
		}
yy13:
		yych = *++_constType;
		switch (yych) {
		case 'm':	goto yy14;
		default:	goto yy2;
		}
yy14:
		yych = *++_constType;
		switch (yych) {
		case 'i':	goto yy15;
		default:	goto yy2;
		}
yy15:
		yych = *++_constType;
		switch (yych) {
		case 'c':	goto yy16;
		default:	goto yy2;
		}
yy16:
		yych = *++_constType;
		switch (yych) {
		case 'A':	goto yy17;
		default:	goto yy2;
		}
yy17:
		yych = *++_constType;
		switch (yych) {
		case 'b':	goto yy18;
		default:	goto yy2;
		}
yy18:
		yych = *++_constType;
		switch (yych) {
		case 'n':	goto yy19;
		default:	goto yy2;
		}
yy19:
		yych = *++_constType;
		switch (yych) {
		case 'o':	goto yy20;
		default:	goto yy2;
		}
yy20:
		yych = *++_constType;
		switch (yych) {
		case 'r':	goto yy21;
		default:	goto yy2;
		}
yy21:
		yych = *++_constType;
		switch (yych) {
		case 'm':	goto yy22;
		default:	goto yy2;
		}
yy22:
		yych = *++_constType;
		switch (yych) {
		case 'a':	goto yy23;
		default:	goto yy2;
		}
yy23:
		yych = *++_constType;
		switch (yych) {
		case 'l':	goto yy24;
		default:	goto yy2;
		}
yy24:
		yych = *++_constType;
		switch (yych) {
		case 'i':	goto yy25;
		default:	goto yy2;
		}
yy25:
		yych = *++_constType;
		switch (yych) {
		case 't':	goto yy26;
		default:	goto yy2;
		}
yy26:
		yych = *++_constType;
		switch (yych) {
		case 'y':	goto yy27;
		default:	goto yy2;
		}
yy27:
		++_constType;
#line 164 "DataStructs/Constant.re2c"
		{ return CONST_DYNAMICAB; }
#line 316 "<stdout>"
yy29:
		yych = *++_constType;
		switch (yych) {
		case 'a':	goto yy50;
		default:	goto yy2;
		}
yy30:
		yych = *++_constType;
		switch (yych) {
		case 'm':	goto yy39;
		default:	goto yy2;
		}
yy31:
		yych = *++_constType;
		switch (yych) {
		case 'F':	goto yy32;
		default:	goto yy2;
		}
yy32:
		yych = *++_constType;
		switch (yych) {
		case 'l':	goto yy33;
		default:	goto yy2;
		}
yy33:
		yych = *++_constType;
		switch (yych) {
		case 'u':	goto yy34;
		default:	goto yy2;
		}
yy34:
		yych = *++_constType;
		switch (yych) {
		case 'e':	goto yy35;
		default:	goto yy2;
		}
yy35:
		yych = *++_constType;
		switch (yych) {
		case 'n':	goto yy36;
		default:	goto yy2;
		}
yy36:
		yych = *++_constType;
		switch (yych) {
		case 't':	goto yy37;
		default:	goto yy2;
		}
yy37:
		++_constType;
#line 159 "DataStructs/Constant.re2c"
		{ return CONST_SDFLUENT; }
#line 369 "<stdout>"
yy39:
		yych = *++_constType;
		switch (yych) {
		case 'p':	goto yy40;
		default:	goto yy2;
		}
yy40:
		yych = *++_constType;
		switch (yych) {
		case 'l':	goto yy41;
		default:	goto yy2;
		}
yy41:
		yych = *++_constType;
		switch (yych) {
		case 'e':	goto yy42;
		default:	goto yy2;
		}
yy42:
		yych = *++_constType;
		switch (yych) {
		case 'F':	goto yy43;
		default:	goto yy2;
		}
yy43:
		yych = *++_constType;
		switch (yych) {
		case 'l':	goto yy44;
		default:	goto yy2;
		}
yy44:
		yych = *++_constType;
		switch (yych) {
		case 'u':	goto yy45;
		default:	goto yy2;
		}
yy45:
		yych = *++_constType;
		switch (yych) {
		case 'e':	goto yy46;
		default:	goto yy2;
		}
yy46:
		yych = *++_constType;
		switch (yych) {
		case 'n':	goto yy47;
		default:	goto yy2;
		}
yy47:
		yych = *++_constType;
		switch (yych) {
		case 't':	goto yy48;
		default:	goto yy2;
		}
yy48:
		++_constType;
#line 160 "DataStructs/Constant.re2c"
		{ return CONST_SIMPLEFLUENT; }
#line 428 "<stdout>"
yy50:
		yych = *++_constType;
		switch (yych) {
		case 't':	goto yy51;
		default:	goto yy2;
		}
yy51:
		yych = *++_constType;
		switch (yych) {
		case 'i':	goto yy52;
		default:	goto yy2;
		}
yy52:
		yych = *++_constType;
		switch (yych) {
		case 'c':	goto yy53;
		default:	goto yy2;
		}
yy53:
		yych = *++_constType;
		switch (yych) {
		case 'A':	goto yy54;
		default:	goto yy2;
		}
yy54:
		yych = *++_constType;
		switch (yych) {
		case 'b':	goto yy55;
		default:	goto yy2;
		}
yy55:
		yych = *++_constType;
		switch (yych) {
		case 'n':	goto yy56;
		default:	goto yy2;
		}
yy56:
		yych = *++_constType;
		switch (yych) {
		case 'o':	goto yy57;
		default:	goto yy2;
		}
yy57:
		yych = *++_constType;
		switch (yych) {
		case 'r':	goto yy58;
		default:	goto yy2;
		}
yy58:
		yych = *++_constType;
		switch (yych) {
		case 'm':	goto yy59;
		default:	goto yy2;
		}
yy59:
		yych = *++_constType;
		switch (yych) {
		case 'a':	goto yy60;
		default:	goto yy2;
		}
yy60:
		yych = *++_constType;
		switch (yych) {
		case 'l':	goto yy61;
		default:	goto yy2;
		}
yy61:
		yych = *++_constType;
		switch (yych) {
		case 'i':	goto yy62;
		default:	goto yy2;
		}
yy62:
		yych = *++_constType;
		switch (yych) {
		case 't':	goto yy63;
		default:	goto yy2;
		}
yy63:
		yych = *++_constType;
		switch (yych) {
		case 'y':	goto yy64;
		default:	goto yy2;
		}
yy64:
		++_constType;
#line 163 "DataStructs/Constant.re2c"
		{ return CONST_STATICAB; }
#line 517 "<stdout>"
yy66:
		yych = *++_constType;
		switch (yych) {
		case 'g':	goto yy67;
		default:	goto yy2;
		}
yy67:
		yych = *++_constType;
		switch (yych) {
		case 'i':	goto yy68;
		default:	goto yy2;
		}
yy68:
		yych = *++_constType;
		switch (yych) {
		case 'd':	goto yy69;
		default:	goto yy2;
		}
yy69:
		++_constType;
#line 158 "DataStructs/Constant.re2c"
		{ return CONST_RIGID; }
#line 540 "<stdout>"
yy71:
		yych = *++_constType;
		switch (yych) {
		case 'e':	goto yy72;
		default:	goto yy2;
		}
yy72:
		yych = *++_constType;
		switch (yych) {
		case 'r':	goto yy73;
		default:	goto yy2;
		}
yy73:
		yych = *++_constType;
		switch (yych) {
		case 't':	goto yy74;
		default:	goto yy2;
		}
yy74:
		yych = *++_constType;
		switch (yych) {
		case 'i':	goto yy75;
		default:	goto yy2;
		}
yy75:
		yych = *++_constType;
		switch (yych) {
		case 'a':	goto yy76;
		default:	goto yy2;
		}
yy76:
		yych = *++_constType;
		switch (yych) {
		case 'l':	goto yy77;
		default:	goto yy2;
		}
yy77:
		yych = *++_constType;
		switch (yych) {
		case 'F':	goto yy78;
		default:	goto yy2;
		}
yy78:
		yych = *++_constType;
		switch (yych) {
		case 'l':	goto yy79;
		default:	goto yy2;
		}
yy79:
		yych = *++_constType;
		switch (yych) {
		case 'u':	goto yy80;
		default:	goto yy2;
		}
yy80:
		yych = *++_constType;
		switch (yych) {
		case 'e':	goto yy81;
		default:	goto yy2;
		}
yy81:
		yych = *++_constType;
		switch (yych) {
		case 'n':	goto yy82;
		default:	goto yy2;
		}
yy82:
		yych = *++_constType;
		switch (yych) {
		case 't':	goto yy83;
		default:	goto yy2;
		}
yy83:
		++_constType;
#line 157 "DataStructs/Constant.re2c"
		{ return CONST_INERTIALFLUENT; }
#line 617 "<stdout>"
yy85:
		yych = *++_constType;
		switch (yych) {
		case 'o':	goto yy86;
		default:	goto yy2;
		}
yy86:
		yych = *++_constType;
		switch (yych) {
		case 'g':	goto yy87;
		default:	goto yy2;
		}
yy87:
		yych = *++_constType;
		switch (yych) {
		case 'e':	goto yy88;
		default:	goto yy2;
		}
yy88:
		yych = *++_constType;
		switch (yych) {
		case 'n':	goto yy89;
		default:	goto yy2;
		}
yy89:
		yych = *++_constType;
		switch (yych) {
		case 'o':	goto yy90;
		default:	goto yy2;
		}
yy90:
		yych = *++_constType;
		switch (yych) {
		case 'u':	goto yy91;
		default:	goto yy2;
		}
yy91:
		yych = *++_constType;
		switch (yych) {
		case 's':	goto yy92;
		default:	goto yy2;
		}
yy92:
		yych = *++_constType;
		switch (yych) {
		case 'A':	goto yy93;
		default:	goto yy2;
		}
yy93:
		yych = *++_constType;
		switch (yych) {
		case 'c':	goto yy94;
		default:	goto yy2;
		}
yy94:
		yych = *++_constType;
		switch (yych) {
		case 't':	goto yy95;
		default:	goto yy2;
		}
yy95:
		yych = *++_constType;
		switch (yych) {
		case 'i':	goto yy96;
		default:	goto yy2;
		}
yy96:
		yych = *++_constType;
		switch (yych) {
		case 'o':	goto yy97;
		default:	goto yy2;
		}
yy97:
		yych = *++_constType;
		switch (yych) {
		case 'n':	goto yy98;
		default:	goto yy2;
		}
yy98:
		++_constType;
#line 156 "DataStructs/Constant.re2c"
		{ return CONST_EXOGENOUSACTION; }
#line 700 "<stdout>"
yy100:
		yych = *++_constType;
		switch (yych) {
		case 'd':	goto yy124;
		default:	goto yy2;
		}
yy101:
		yych = *++_constType;
		switch (yych) {
		case 't':	goto yy116;
		default:	goto yy2;
		}
yy102:
		yych = *++_constType;
		switch (yych) {
		case 'A':	goto yy109;
		default:	goto yy2;
		}
yy103:
		yych = *++_constType;
		switch (yych) {
		case 't':	goto yy104;
		default:	goto yy2;
		}
yy104:
		yych = *++_constType;
		switch (yych) {
		case 'i':	goto yy105;
		default:	goto yy2;
		}
yy105:
		yych = *++_constType;
		switch (yych) {
		case 'o':	goto yy106;
		default:	goto yy2;
		}
yy106:
		yych = *++_constType;
		switch (yych) {
		case 'n':	goto yy107;
		default:	goto yy2;
		}
yy107:
		++_constType;
#line 153 "DataStructs/Constant.re2c"
		{ return CONST_ACTION; }
#line 747 "<stdout>"
yy109:
		yych = *++_constType;
		switch (yych) {
		case 'c':	goto yy110;
		default:	goto yy2;
		}
yy110:
		yych = *++_constType;
		switch (yych) {
		case 't':	goto yy111;
		default:	goto yy2;
		}
yy111:
		yych = *++_constType;
		switch (yych) {
		case 'i':	goto yy112;
		default:	goto yy2;
		}
yy112:
		yych = *++_constType;
		switch (yych) {
		case 'o':	goto yy113;
		default:	goto yy2;
		}
yy113:
		yych = *++_constType;
		switch (yych) {
		case 'n':	goto yy114;
		default:	goto yy2;
		}
yy114:
		++_constType;
#line 154 "DataStructs/Constant.re2c"
		{ return CONST_ABACTION; }
#line 782 "<stdout>"
yy116:
		yych = *++_constType;
		switch (yych) {
		case 'r':	goto yy117;
		default:	goto yy2;
		}
yy117:
		yych = *++_constType;
		switch (yych) {
		case 'i':	goto yy118;
		default:	goto yy2;
		}
yy118:
		yych = *++_constType;
		switch (yych) {
		case 'b':	goto yy119;
		default:	goto yy2;
		}
yy119:
		yych = *++_constType;
		switch (yych) {
		case 'u':	goto yy120;
		default:	goto yy2;
		}
yy120:
		yych = *++_constType;
		switch (yych) {
		case 't':	goto yy121;
		default:	goto yy2;
		}
yy121:
		yych = *++_constType;
		switch (yych) {
		case 'e':	goto yy122;
		default:	goto yy2;
		}
yy122:
		++_constType;
#line 155 "DataStructs/Constant.re2c"
		{ return CONST_ATTRIBUTE; }
#line 823 "<stdout>"
yy124:
		yych = *++_constType;
		switch (yych) {
		case 'i':	goto yy125;
		default:	goto yy2;
		}
yy125:
		yych = *++_constType;
		switch (yych) {
		case 't':	goto yy126;
		default:	goto yy2;
		}
yy126:
		yych = *++_constType;
		switch (yych) {
		case 'i':	goto yy127;
		default:	goto yy2;
		}
yy127:
		yych = *++_constType;
		switch (yych) {
		case 'v':	goto yy128;
		default:	goto yy2;
		}
yy128:
		yych = *++_constType;
		switch (yych) {
		case 'e':	goto yy129;
		default:	goto yy2;
		}
yy129:
		yych = *++_constType;
		switch (yych) {
		case 'A':	goto yy130;
		case 'F':	goto yy131;
		default:	goto yy2;
		}
yy130:
		yych = *++_constType;
		switch (yych) {
		case 'c':	goto yy138;
		default:	goto yy2;
		}
yy131:
		yych = *++_constType;
		switch (yych) {
		case 'l':	goto yy132;
		default:	goto yy2;
		}
yy132:
		yych = *++_constType;
		switch (yych) {
		case 'u':	goto yy133;
		default:	goto yy2;
		}
yy133:
		yych = *++_constType;
		switch (yych) {
		case 'e':	goto yy134;
		default:	goto yy2;
		}
yy134:
		yych = *++_constType;
		switch (yych) {
		case 'n':	goto yy135;
		default:	goto yy2;
		}
yy135:
		yych = *++_constType;
		switch (yych) {
		case 't':	goto yy136;
		default:	goto yy2;
		}
yy136:
		++_constType;
#line 162 "DataStructs/Constant.re2c"
		{ return CONST_ADDITIVEFLUENT; }
#line 901 "<stdout>"
yy138:
		yych = *++_constType;
		switch (yych) {
		case 't':	goto yy139;
		default:	goto yy2;
		}
yy139:
		yych = *++_constType;
		switch (yych) {
		case 'i':	goto yy140;
		default:	goto yy2;
		}
yy140:
		yych = *++_constType;
		switch (yych) {
		case 'o':	goto yy141;
		default:	goto yy2;
		}
yy141:
		yych = *++_constType;
		switch (yych) {
		case 'n':	goto yy142;
		default:	goto yy2;
		}
yy142:
		++_constType;
#line 161 "DataStructs/Constant.re2c"
		{ return CONST_ADDITIVEACTION; }
#line 930 "<stdout>"
	}
#line 166 "DataStructs/Constant.re2c"

}

// Checks if the type is an action constant.
bool Constant::isActionType(ConstantType _constType)
{
	switch (_constType)
	{
	case CONST_ACTION:
	case CONST_ABACTION:
	case CONST_ATTRIBUTE:
	case CONST_EXOGENOUSACTION:
	case CONST_ADDITIVEACTION:
		return true;
	default:
		return false;
	}
}

// Checks if the type is an abnormality constant.
bool Constant::isAbnormalityType(ConstantType _constType)
{
	switch (_constType)
	{
	case CONST_STATICAB:
	case CONST_DYNAMICAB:
		return true;
	default:
		return false;
	}
}
// Checks if the type is a fluent constant.
bool Constant::isFluentType(ConstantType _constType, bool includeRigid)
{
	switch (_constType)
	{
	case CONST_INERTIALFLUENT:
	case CONST_SDFLUENT:
	case CONST_SIMPLEFLUENT:
	case CONST_ADDITIVEFLUENT:
	case CONST_ABFLUENT:
		return true;
	case CONST_RIGID:
		return includeRigid;
	default:
		return false;
	}
}

// Checks if the type is a fluent constant.
bool Constant::isAdditiveType(ConstantType _constType)
{
	switch (_constType)
	{
	case CONST_ADDITIVEACTION:
	case CONST_ADDITIVEFLUENT:
		return true;
	default:
		return false;
	}
}

// Generates a prefix used to wrap the atom's name in.
std::string Constant::translatePrefix(ConstantType constType)
{
	switch (constType) {
	case CONST_ACTION:
	case CONST_ABACTION:
	case CONST_ATTRIBUTE:
	case CONST_EXOGENOUSACTION:
	case CONST_ADDITIVEACTION:
		return "occ(eql(";
	case CONST_STATICAB:
		return "ab_h(";
	case CONST_DYNAMICAB:
		return "ab_occ(";
	case CONST_INERTIALFLUENT:
	case CONST_RIGID:
	case CONST_SDFLUENT:
	case CONST_SIMPLEFLUENT:
	case CONST_ADDITIVEFLUENT:
	default:
		return "h(eql(";
	}
}

// Generates a postfix used to wrap the atom's name in.
std::string Constant::translatePostfix(ConstantType constType, Context const& context) {
	std::stringstream out;
	if (Constant::isAbnormalityType(constType)) {
		return ", " + context.getTimestamp() + ")";
	} else {
		context.getNegated();

		out << ", "
		// make sure we handle the case where the context is blind to this being an atom.
		// Default the value to "true".
			<< context.getValue()
			<< ")"
			<< ((constType == Constant::CONST_RIGID) ? "" : ", " + context.getTimestamp())
			<< ")";

		return out.str();
	}
}

bool Constant::translate(
		std::ostream& out,
		ClauseList& outClauses,
		ElementCounter* runningCount,
		std::vector<std::pair<Sort const*, std::string> >* matchMap,
		std::vector<std::pair<Sort const*, std::string> >* outMap) const {

	bool matchingMap = (bool)matchMap;							// Whether we are currently matching the mapped arguments.
	size_t count;												// The number of times this sort has appeared to date.
	std::string newVar;											// The name of the new variable to add.
	if (!runningCount) runningCount = new ElementCounter();

	// Translate the name...
	out << baseTransName();

	// Transform any parameters into sort variables.
	if(arity())
	{
		out << "(";

		// Use an occurrence counter to get guaranteed unique variable
		// names representing the sorts that comprise the parameters
		// of this constant.
		for(size_t i = 0; i < arity(); i++)
		{
			// check the argument against the known parameter list
			// Pragma: I'm fully aware that this does pointer-wise comparison.
			if (matchingMap && i < matchMap->size() && param(i) == matchMap->at(i).first) {
				// Everything (including this argument) has matched so far.
				// Keep using the mapped variables.
				if (i > 0) out << ", ";
				out << matchMap->at(i).second;
				if (outMap) outMap->push_back(std::pair<Sort const*, std::string>(param(i), matchMap->at(i).second));
			} else {
				// nope! Stop trying.
				matchingMap = false;

				newVar = param(i)->varTransName();
				// Generate our own variable to use.
				count = runningCount->add(param(i));
				if (count > 1) {
					newVar += "_" + utils::to_string(count);
				}

				// Add and register the new variable.
				if (i > 0) out << ", ";
				out << newVar;
				if (outMap) outMap->push_back(std::pair<Sort const*, std::string>(param(i), newVar));

				// Add the appropriate clause...
				if (count > 1) {
					outClauses.push_back(param(i)->fullTransName() + "(" + newVar + ")");
				}
			}
		}

		out << ")";
	}

	return !matchMap || matchingMap;
}

// Determines if the constant appears to be the contribution constant.
bool Constant::isContribConstant() const {
	return arity() == 2 && constType() == CONST_ACTION && baseName() == "contribution" && domain() && domain()->isNumeric();
}


// Gets the names associated with each parameter.
void Constant::getParamFullNames(NameList& out) const	{
	utils::elementVectorToFullNameVector<Sort const*>(mParams, out);
}

// Copies this constant as an attribute
Attribute* Constant::makeAttribute(Constant const* parent) const {
	return new Attribute(baseName(), domain(), parent, &mParams);

}