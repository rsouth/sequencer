#pragma once
#include <map>
#include <string>

class RenderingUtils
{
public:

	static const unsigned char BLACK[];

	static const unsigned char WHITE[];

	auto get_font_rendered_height(const std::string& input, const int font_height) -> int;

	auto get_font_rendered_width(const std::string& input, const int font_height) -> int;

private:

	// cache for the rendered height/width of strings
	std::map<std::string, int> rendered_size_map_;// = std::map<std::string, int>();
};
