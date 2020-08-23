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
#include "RenderingUtils.h"

#include "CImg.h"

const unsigned char RenderingUtils::BLACK[] = {0, 0, 0};

const unsigned char RenderingUtils::WHITE[] = {255, 255, 255};

auto RenderingUtils::get_font_rendered_height(const std::string& input, const int font_height) -> int
{
	// look up in the cache first, so we don't have to 'dummy render' so much
	auto cache_key = input + "_" + std::to_string(font_height) + "_height";
	if (rendered_size_map_.find(cache_key) != rendered_size_map_.end())
	{
		return rendered_size_map_[cache_key];
	}

	// render the dummy image to capture it's height & width
	cimg_library::CImg<unsigned char> img_text;
	unsigned char color = 1;
	img_text.draw_text(0, 0, input.c_str(), &color, 0, 1, font_height);

	// insert to cache
	this->rendered_size_map_.insert(std::make_pair(cache_key, img_text.height()));

	return img_text.height();
}

auto RenderingUtils::get_font_rendered_width(const std::string& input, const int font_height) -> int
{
	// look up in the cache first, so we don't have to 'dummy render' so much
	auto cache_key = input + "_" + std::to_string(font_height) + "_width";
	if (rendered_size_map_.find(cache_key) != rendered_size_map_.end())
	{
		return rendered_size_map_[cache_key];
	}

	// dummy render the string on an empty CImg so we can measure it
	cimg_library::CImg<unsigned char> img_text;
	unsigned char color = 1;
	img_text.draw_text(0, 0, input.c_str(), &color, 0, 1, font_height);

	// insert to cache
	rendered_size_map_.emplace(std::make_pair(cache_key, img_text.width()));
	// std::string height_key = input + "_" + std::to_string(font_height_) + "_height";

	return img_text.width();
}
