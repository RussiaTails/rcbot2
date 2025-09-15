// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
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

#pragma push_macro("clamp") //Fix for C++17 [APG]RoboCop[CL]
#undef clamp
#include <algorithm>
#include <functional>
#pragma pop_macro("clamp")

//caxanga334: SDK 2013 contains macros for std::min and std::max which causes errors when compiling
//#if SOURCE_ENGINE == SE_SDK2013 || SOURCE_ENGINE == SE_BMS
#include "valve_minmax_off.h"
//#endif

constexpr int INVALID_BOT_COUNT = -1;

CBotCommandInline GameEventVersion("event_version", CMD_ACCESS_CONFIG, [](CClient* pClient, const BotCommandArgs& args)
	{
		if (!args[0] || !*args[0])
			return COMMAND_ERROR;

		CBotGlobals::setEventVersion(std::atoi(args[0]));

		return COMMAND_ACCESSED;
	});

namespace
{
	void SetBotLimit(const CClient* pClient, const BotCommandArgs& args, const char* commandName,
		const std::function<void(int)>& setter, const std::function<int()>& getter,
		const std::function<bool(int, int)>& validation, const char* validationMessage)
	{
		edict_t* pEntity = pClient ? pClient->getPlayer() : nullptr;

		if (args[0] && *args[0])
		{
			int value = std::atoi(args[0]);
			bool hasError = false;

			if (value <= INVALID_BOT_COUNT)
			{
				value = INVALID_BOT_COUNT;
			}
			else if (validation(value, getter()))
			{
				CBotGlobals::botMessage(pEntity, 0, validationMessage, getter());
				hasError = true;
			}

			value = std::min(value, CBotGlobals::maxClients());

			if (!hasError)
			{
				setter(value);
				CBotGlobals::botMessage(pEntity, 0, "%s set to %d", commandName, value);
			}
		}
		else
		{
			CBotGlobals::botMessage(pEntity, 0, "%s is currently %d", commandName, getter());
		}
	}
}

CBotCommandInline MaxBotsCommand("max_bots", CMD_ACCESS_CONFIG | CMD_ACCESS_DEDICATED, [](const CClient* pClient, const BotCommandArgs& args)
	{
		SetBotLimit(pClient, args, "max_bots",
			CBots::setMaxBots, CBots::getMinBots,
			[](int maxBots, int minBots) { return (minBots >= 0) && (maxBots <= minBots); },
			"max_bots must be greater than min_bots (min_bots is currently: %d)");

		return COMMAND_ACCESSED;
	});

CBotCommandInline MinBotsCommand("min_bots", CMD_ACCESS_CONFIG | CMD_ACCESS_DEDICATED, [](const CClient* pClient, const BotCommandArgs& args)
	{
		SetBotLimit(pClient, args, "min_bots",
			CBots::setMinBots, CBots::getMaxBots,
			[](int minBots, int maxBots) { return (maxBots >= 0) && (minBots >= maxBots); },
			"min_bots must be less than max_bots (max_bots is currently: %d)");

		return COMMAND_ACCESSED;
	});

CBotSubcommands ConfigSubcommands("config", CMD_ACCESS_DEDICATED, {
&GameEventVersion,
&MaxBotsCommand,
&MinBotsCommand
});