#pragma once
#include <string>

class MetaData;

class MetaDataParser
{
public:
	static MetaData parse(const std::string& input);

private:
	static const char* TITLE_TOKEN;
	static const char* AUTHOR_TOKEN;
	static const char* DATE_TOKEN;
	static const char* FONT_SIZE_TOKEN;
};
