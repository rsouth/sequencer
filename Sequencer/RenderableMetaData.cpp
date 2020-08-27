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
#include "RenderableMetaData.h"

#include "LayoutConstants.h"

#include "RenderingUtils.h"

#include "qpainter.h"

RenderableMetaData::RenderableMetaData(MetaData meta_data, QPainter* img): meta_data_(std::move(meta_data)), img_(img)
{
}

void RenderableMetaData::draw() const
{
	const std::string title(this->meta_data_.get_title());
	if (!title.empty())
	{
		this->img_->drawText(
			LayoutConstants::DIAGRAM_MARGIN,
			LayoutConstants::DIAGRAM_MARGIN,
			title.c_str()
		);
	}

	const std::string author = this->meta_data_.get_author();
	if (!author.empty())
	{
		const int author_y = LayoutConstants::DIAGRAM_MARGIN + (title.empty() ? 0 : this->title_font_height_);
		this->img_->drawText(
			LayoutConstants::DIAGRAM_MARGIN,
			author_y,
			author.c_str()
		);
	}

	const std::string date = this->meta_data_.get_date();
	if (!date.empty())
	{
		const int date_y = LayoutConstants::DIAGRAM_MARGIN + (title.empty() ? 0 : this->title_font_height_) + (
			author.empty() ? 0 : this->text_font_height_);
		this->img_->drawText(
			LayoutConstants::DIAGRAM_MARGIN,
			date_y,
			date.c_str()
		);
	}
}

int RenderableMetaData::calculate_height()
{
	return LayoutConstants::DIAGRAM_MARGIN +
		(this->meta_data_.get_title().empty()
			 ? 0
			 : RenderingUtils::get_font_rendered_height(this->meta_data_.get_title(), this->img_->font())) // todo when the font changes, this will need to also......
		+
		(this->meta_data_.get_author().empty()
			 ? 0
			 : RenderingUtils::get_font_rendered_height(this->meta_data_.get_author(), this->img_->font()))
		+
		(this->meta_data_.get_date().empty()
			 ? 0
			 : RenderingUtils::get_font_rendered_height(this->meta_data_.get_date(), this->img_->font()));
}

int RenderableMetaData::calculate_width()
{
	const auto title_width = (this->meta_data_.get_title().empty()
		                          ? 0
		                          : RenderingUtils::get_font_rendered_width(this->meta_data_.get_title(), this->img_->font()));
	const auto author_width = (this->meta_data_.get_author().empty()
		                           ? 0
		                           : RenderingUtils::get_font_rendered_width(this->meta_data_.get_author(), this->img_->font()));
	const auto date_width = (this->meta_data_.get_date().empty()
		                         ? 0
		                         : RenderingUtils::get_font_rendered_width(this->meta_data_.get_date(), this->img_->font()));

	return (2 * LayoutConstants::DIAGRAM_MARGIN) + std::max(std::max(title_width, author_width), date_width);
}
