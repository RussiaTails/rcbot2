/*
 *    This file is part of RCBot.
 *
 *    RCBot by Paul Murphy adapted from Botman's HPB Bot 2 template.
 *
 *    RCBot is free software; you can redistribute it and/or modify it
 *    under the terms of the GNU General Public License as published by the
 *    Free Software Foundation; either version 2 of the License, or (at
 *    your option) any later version.
 *
 *    RCBot is distributed in the hope that it will be useful, but
 *    WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with RCBot; if not, write to the Free Software Foundation,
 *    Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *    In addition, as a special exception, the author gives permission to
 *    link the code of this program with the Half-Life Game Engine ("HL
 *    Engine") and Modified Game Libraries ("MODs") developed by Valve,
 *    L.L.C ("Valve").  You must obey the GNU General Public License in all
 *    respects for all of the code used other than the HL Engine and MODs
 *    from Valve.  If you modify this file, you may extend this exception
 *    to your version of the file, but you are not obligated to do so.  If
 *    you do not wish to do so, delete this exception statement from your
 *    version.
 *
 */
#ifndef __BOT_STRINGS_H__
#define __BOT_STRINGS_H__

#include <vector>

enum : std::uint8_t
{
	MAX_STRINGS_HASH = 26
};

/*
 * CStrings
 *
 * A global static method only class which stores a list of strings used
 * that you want to store through the duration of the game
 *
 * The neatness of this is that you can create strings with ease and they
 * will all be automatically freed upon game exit
 *
 * Another good thing is that it will save memory if there are duplicate strings
 * it only keeps one unique copy of a string. If it tries to make a duplicate string
 * then a pointer to to current string is sent back
 *
 */
class CStrings
{
public:
	CStrings();
	static void freeAllMemory();
	static char* getString(const char* szString);

private:
	// dataStack is like a linked list, dont want 
	// to use an array for lots of stuff like this
	static std::vector<char*> m_Strings[MAX_STRINGS_HASH];
};

#endif