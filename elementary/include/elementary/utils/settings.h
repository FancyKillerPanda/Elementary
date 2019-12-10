#pragma once

#include <unordered_map>

namespace el
{

class Settings
{
public:
	std::string filepath = "res/settings.txt";
	
private:
	std::unordered_map<std::string, std::string> defaultSettings = {};
	std::unordered_map<std::string, std::string> settings = {};
	
public:
	Settings() = default;
	Settings(std::unordered_map<std::string, std::string> defaultSettings);

	void loadFromFile();
	void loadFromFile(std::string newFilepath);

	void writeToFile();
	void writeToFile(std::string newFilepath);

	void setValue(std::string key, std::string value);
	const std::string& getValue(const std::string& key);
};
	
}
