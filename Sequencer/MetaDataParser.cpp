#include "MetaDataParser.h"

#include "MetaData.h"
#include "QStringList"

#include <ctime>
#include <chrono>
#include <iomanip>

#include "StringUtils.h"

const char* MetaDataParser::TITLE_TOKEN = ":title ";
const char* MetaDataParser::AUTHOR_TOKEN = ":author ";
const char* MetaDataParser::DATE_TOKEN = ":date";
const char* MetaDataParser::FONT_SIZE_TOKEN = ":fontsize ";

MetaData MetaDataParser::parse(const std::string& input)
{
	std::string title;
	std::string author;
	std::string date;
	try
	{
		auto lines = StringUtils::split(input, "\n");
		for (const auto& line : lines)
		{
			if (StringUtils::starts_with(line, TITLE_TOKEN))
			{
				// :title My Title
				title = StringUtils::get_token_value(line, TITLE_TOKEN);
			}

			if (StringUtils::starts_with(line, AUTHOR_TOKEN))
			{
				// :author Joe Diagram
				author = StringUtils::get_token_value(line, AUTHOR_TOKEN);
			}

			if (StringUtils::trim_copy(line) == DATE_TOKEN)
			{
				// :date
				std::time_t t_t = std::time(nullptr);
				tm t;
				char buffer[100];
				localtime_s(&t, &t_t);
				std::strftime(buffer, sizeof(buffer), "%F", &t);
				date = buffer;
			}
		}
	}
	catch (const std::exception& e)
	{
		/* */
	}

	return MetaData(title, author, date);
}
