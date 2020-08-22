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
