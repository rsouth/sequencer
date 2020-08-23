#pragma once

#include <string>
#include "StringUtils.h"

class ParsingUtils
{
public:
	static std::string parse_token(const std::string& input)
	{
		// -> or --> (msg vs reply)
		std::string token = StringUtils::contains(input, "-->") ? "-->" : "->";
		
		// > is sync >> is async
		auto pos = input.find(token);
		bool is_async = input.at(pos + token.length()) == '>';
		if (is_async) {
			token += '>';
		}

		return token;
	}
};
