// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "bot.h"
#include "bot_coop.h"
#include "bot_buttons.h"
#include "bot_globals.h"
#include "bot_profile.h"

#include "vstdlib/random.h" // for random functions

#include <cstring>
#include <array>

void CBotCoop::modThink()
{
	// find enemies and health stations / objectives etc
}

bool CBotCoop::isEnemy(edict_t* pEdict, bool bCheckWeapons)
{
	if (pEdict == nullptr || ENTINDEX(pEdict) == 0)
		return false;

	// no shooting players
	if (ENTINDEX(pEdict) <= CBotGlobals::maxClients())
	{
		return false;
	}

	// List of friendly NPCs

	if (const char* classname = pEdict->GetClassName(); std::strncmp(classname, "npc_", 4) == 0)
	{
		constexpr std::array<const char*, 5> friendlyNPCs = {
			"npc_antlionguard",
			"npc_citizen",
			"npc_barney",
			"npc_kliener",
			"npc_alyx"
		};

		for (const char* const& friendly : friendlyNPCs)
		{
			if (std::strcmp(classname, friendly) == 0)
			{
				return false; // ally
			}
		}
		return true;
	}

	return false;
}

bool CBotCoop::startGame()
{
	return true;
}