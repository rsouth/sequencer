#include "RenderableMetaData.h"

#include "LayoutConstants.h"

#include "CImg.h"
#include "RenderingUtils.h"

using namespace cimg_library;

// RenderableMetaData::RenderableMetaData() = default;

RenderableMetaData::RenderableMetaData(MetaData meta_data, RenderingUtils* rendering_utils, CImg<unsigned char>* img):
	meta_data_(std::move(meta_data)),
	rendering_utils_(std::move(rendering_utils)),
	img_(img)
{
}

void RenderableMetaData::draw() const
{
	const unsigned char black[] = {0, 0, 0};
	const unsigned char white[] = {255, 255, 255};

	const std::string title = this->meta_data_.get_title();
	if (!title.empty())
	{
		this->img_->draw_text(
			LayoutConstants::DIAGRAM_MARGIN,
			LayoutConstants::DIAGRAM_MARGIN,
			title.c_str(),
			black,
			white,
			1,
			this->title_font_height_);
	}

	const std::string author = this->meta_data_.get_author();
	if (!author.empty())
	{
		const int author_y = LayoutConstants::DIAGRAM_MARGIN + (title.empty() ? 0 : this->title_font_height_);
		this->img_->draw_text(
			LayoutConstants::DIAGRAM_MARGIN,
			author_y,
			author.c_str(),
			black,
			white,
			1,
			this->text_font_height_
		);
	}

	const std::string date = this->meta_data_.get_date();
	if (!date.empty())
	{
		const int date_y = LayoutConstants::DIAGRAM_MARGIN + (title.empty() ? 0 : this->title_font_height_) + (
			author.empty() ? 0 : this->text_font_height_);
		this->img_->draw_text(
			LayoutConstants::DIAGRAM_MARGIN,
			date_y,
			date.c_str(),
			black,
			white,
			1,
			this->text_font_height_
		);
	}
}

int RenderableMetaData::calculate_height()
{
	return LayoutConstants::DIAGRAM_MARGIN +
		(this->meta_data_.get_title().empty()
			 ? 0
			 : this->rendering_utils_->get_font_rendered_height(this->meta_data_.get_title(), this->title_font_height_))
		+
		(this->meta_data_.get_author().empty()
			 ? 0
			 : this->rendering_utils_->get_font_rendered_height(this->meta_data_.get_author(), this->text_font_height_))
		+
		(this->meta_data_.get_date().empty()
			 ? 0
			 : this->rendering_utils_->get_font_rendered_height(this->meta_data_.get_date(), this->text_font_height_));
}

int RenderableMetaData::calculate_width()
{
	const auto title_width = (this->meta_data_.get_title().empty()
		                          ? 0
		                          : this->rendering_utils_->get_font_rendered_width(this->meta_data_.get_title(), this->title_font_height_));
	const auto author_width = (this->meta_data_.get_author().empty()
		                           ? 0
		                           : this->rendering_utils_->get_font_rendered_width(this->meta_data_.get_author(), this->text_font_height_));
	const auto date_width = (this->meta_data_.get_date().empty()
		                         ? 0
		                         : this->rendering_utils_->get_font_rendered_width(this->meta_data_.get_date(), this->text_font_height_));

	return (2 * LayoutConstants::DIAGRAM_MARGIN) + std::max(std::max(title_width, author_width), date_width);
}
