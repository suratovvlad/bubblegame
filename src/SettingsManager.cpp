#include "stdafx.h"
#include "SettingsManager.h"

SettingsManager::SettingsManager()
{
}

SettingsManager::~SettingsManager()
{
	m_settingsMap.clear();
}

void SettingsManager::ReadSettingsFromFile(const std::string& filepath)
{
	if (!Core::fileSystem.FileExists(filepath)) {
		return;
	}

	IO::InputStreamPtr stream = Core::fileSystem.OpenRead(filepath);
	if (NULL == stream)	{
		return;
	}

	IO::TextReader textReader = IO::TextReader(stream.get());

	std::string str = "";
	while (textReader.ReadAsciiLine(str)) {
		std::string name = "";
		std::string value = "";
		utils::ReadNvp(str, name, value);
		m_settingsMap.insert(std::pair<std::string, std::string>(name, value));
	}
}

std::string SettingsManager::GetSettingByName(const std::string& setting_name, const std::string& defaultVal) const
{
	std::map<std::string, std::string>::const_iterator it = m_settingsMap.find(setting_name);
	if (it == m_settingsMap.end()) {
		return defaultVal; // default returning
	}
	else {
		return it->second;
	}
}