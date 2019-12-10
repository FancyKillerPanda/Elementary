#include <fstream>

#include "utils/settings.h"
#include "utils/log.h"

namespace el
{

Settings::Settings(std::unordered_map<std::string, std::string> defaultSettings)
	: settings(defaultSettings), defaultSettings(defaultSettings)
{
}

void Settings::loadFromFile()
{
	std::string key;
	std::string value;
	
	std::ifstream settingsFile;
	settingsFile.open(filepath);

	if (!settingsFile)
	{
		error("Settings file open failed, using default settings if provided.");
		settings = defaultSettings;

		return;
	}

	while (settingsFile >> key)
	{
		if (!(settingsFile >> value))
		{
			error("Settings file has uneven number of items, using default settings if provided.");
			settings = defaultSettings;
			
			return;
		}

		settings[key] = value;
	}

	settingsFile.close();
}

void Settings::loadFromFile(std::string newFilepath)
{
	filepath = newFilepath;
	loadFromFile();
}

void Settings::writeToFile()
{
	// TODO(fkp): Make temp copy of settings file in case of error	
	std::ofstream settingsFile;
	settingsFile.open(filepath, std::ofstream::out | std::ofstream::trunc);

	if (!settingsFile)
	{
		error("Settings file open failed, could not write settings.");
		return;
	}

	for (const std::pair<std::string, std::string>& pair : settings)
	{
		settingsFile << pair.first << " " << pair.second << "\n";
	}

	settingsFile.close();
}

void Settings::writeToFile(std::string newFilepath)
{
	filepath = newFilepath;
	writeToFile();
}

const std::string& Settings::getValue(const std::string& key)
{
	// TODO(fkp): Find better solution for this
	static const std::string empty = "";
	
	const auto& result = settings.find(key);

	if (result != settings.end())
	{
		return result->second;
	}

	warn("Key (%s) does not exist in settings.", key.c_str());
	return empty;
}

void Settings::setValue(std::string key, std::string value)
{
	settings[key] = value;
}
	
}
