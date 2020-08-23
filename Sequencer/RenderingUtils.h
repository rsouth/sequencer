/*
 *     Copyright (C) 2020 rsouth (https://github.com/rsouth)
 *
 *     This program is free software: you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation, either version 3 of the License, or
 *     (at your option) any later version.
 *
 *     This program is distributed in the hope that it will be useful,
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *     GNU General Public License for more details.
 *
 *     You should have received a copy of the GNU General Public License
 *     along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
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
