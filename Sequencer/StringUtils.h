#pragma once
#include <string>
#include <vector>

class StringUtils
{
public:

	// trim from start (in place)
	static void ltrim(std::string& s)
	{
		s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch)
		{
			return !std::isspace(ch);
		}));
	}

	// trim from end (in place)
	static void rtrim(std::string& s)
	{
		s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch)
		{
			return !std::isspace(ch);
		}).base(), s.end());
	}

	// trim from both ends (in place)
	static void trim(std::string& s)
	{
		ltrim(s);
		rtrim(s);
	}

	// trim from start (copying)
	static std::string ltrim_copy(std::string s)
	{
		ltrim(s);
		return s;
	}

	// trim from end (copying)
	static std::string rtrim_copy(std::string s)
	{
		rtrim(s);
		return s;
	}

	// trim from both ends (copying)
	static std::string trim_copy(std::string s)
	{
		trim(s);
		return s;
	}

	static bool starts_with(const std::string& str, const std::string& find)
	{
		return trim_copy(str).rfind(find, 0) == 0;
	}

	static std::string replace(std::string str, const std::string& from, const std::string& to)
	{
		const size_t start_pos = str.find(from);
		if (start_pos == std::string::npos)
			return nullptr;
		str.replace(start_pos, from.length(), to);
		return str;
	}

	static std::vector<std::string> split(const std::string& phrase, const std::string& delimiter)
	{
		std::vector<std::string> list;
		std::string s = std::string(phrase);
		size_t pos;
		while ((pos = s.find(delimiter)) != std::string::npos)
		{
			std::string token = s.substr(0, pos);
			list.push_back(token);
			s.erase(0, pos + delimiter.length());
		}
		list.push_back(s);
		return list;
	}

	static std::string get_token_value(const std::string& input, const std::string& token)
	{
		return trim_copy(replace(input, token, ""));
	}

	static bool contains(const std::string& input, const std::string& search_for)
	{
		return input.find(search_for) != std::string::npos;
	}
};
