#pragma once

#include "MetaData.h"
#include "RenderingUtils.h"

namespace cimg_library
{
	template <typename T>
	struct CImg;
}

class RenderableMetaData
{
public:

	RenderableMetaData(MetaData meta_data, RenderingUtils* rendering_utils, cimg_library::CImg<unsigned char>* img);

	void draw() const;

	int calculate_height();
	int calculate_width();

private:
	MetaData meta_data_ = MetaData();
	RenderingUtils* rendering_utils_;
	cimg_library::CImg<unsigned char>* img_ = nullptr;

	// \param font_height_ Height of the text font(exact match for 13, 23, 53, 103, interpolated otherwise).
	unsigned int title_font_height_ = 53;
	unsigned int text_font_height_ = 23;
};
