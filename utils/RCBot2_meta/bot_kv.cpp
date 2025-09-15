// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "bot.h"
#include "bot_kv.h"
#include "bot_globals.h"

#include <cstring>
#include <string>
#include <algorithm>

#include "rcbot/logging.h"

void CRCBotKeyValueList::parseFile(std::fstream& fp)
{
	std::string line;
	std::size_t iLine = 0;

	// parse profile ini
	while (std::getline(fp, line))
	{
		iLine++;

		// remove carriage return if present
		if (!line.empty() && line.back() == '\r')
		{
			line.pop_back();
		}

		if (line.empty() || line[0] == '#') // skip empty lines and comments
			continue;

		std::string key, value;
		bool bHaveKey = false;

		for (const char c : line)
		{
			if (c == ' ') // ignore spacing
				continue;

			if (!bHaveKey)
			{
				if (c == '=')
				{
					bHaveKey = true;
				}
				else
				{
					key += c;
				}
			}
			else
			{
				value += c;
			}
		}

		if (key.length() >= RCBOT_MAX_KV_LEN || value.length() >= RCBOT_MAX_KV_LEN)
		{
			logger->Log(LogLevel::WARN, "Key or value too long on line %zu in KV file.", iLine);
			continue;
		}

		logger->Log(LogLevel::TRACE, "m_KVs.emplace_back(%s,%s)", key.c_str(), value.c_str());

		m_KVs.emplace_back(std::make_unique<CRCBotKeyValue>(key.c_str(), value.c_str()));
	}
}

CRCBotKeyValue* CRCBotKeyValueList::getKV(const char* key) const
{
	for (const std::unique_ptr<CRCBotKeyValue>& m_KV : m_KVs)
	{
		if (FStrEq(m_KV->getKey(), key))
			return m_KV.get();
	}

	return nullptr;
}

bool CRCBotKeyValueList::getFloat(const char* key, float* val) const
{
	const CRCBotKeyValue* pKV = getKV(key);

	if (!pKV)
		return false;

	*val = static_cast<float>(std::atof(pKV->getValue()));

	return true;
}


bool CRCBotKeyValueList::getInt(const char* key, int* val) const
{
	const CRCBotKeyValue* pKV = getKV(key);

	if (!pKV)
		return false;

	*val = std::atoi(pKV->getValue());

	return true;
}


bool CRCBotKeyValueList::getString(const char* key, const char** val) const
{
	const CRCBotKeyValue* pKV = getKV(key);

	if (!pKV)
		return false;

	*val = pKV->getValue();

	return true;
}

CRCBotKeyValue::CRCBotKeyValue(const char* szKey, const char* szValue)
{
	std::strncpy(m_szKey, szKey, RCBOT_MAX_KV_LEN - 1);
	m_szKey[RCBOT_MAX_KV_LEN - 1] = 0;

	std::strncpy(m_szValue, szValue, RCBOT_MAX_KV_LEN - 1);
	m_szValue[RCBOT_MAX_KV_LEN - 1] = 0;
}