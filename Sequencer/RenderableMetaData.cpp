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

RenderableMetaData::RenderableMetaData(const MetaData& meta_data, QPainter* img): meta_data_(meta_data), img_(img)
{
}

void RenderableMetaData::draw() const
{
	int titleheight = 0;
	if (!this->meta_data_.get_title().empty())
	{
		RenderingUtils::draw_text(
			LayoutConstants::DIAGRAM_MARGIN,
			LayoutConstants::DIAGRAM_MARGIN,
			this->meta_data_.get_title().c_str(),
			*this->img_,
			this->title_font_height_
		);

		titleheight = RenderingUtils::get_font_rendered_height(QFont("Arial", this->title_font_height_));
	}

	int authorheight = 0;
	if (!this->meta_data_.get_author().empty())
	{
		// calculate offset needed due to presence/absence of title
		const int author_y = LayoutConstants::DIAGRAM_MARGIN + titleheight;

		// draw author text
		RenderingUtils::draw_text(
			LayoutConstants::DIAGRAM_MARGIN,
			author_y,
			this->meta_data_.get_author().c_str(),
			*this->img_,
			this->text_font_height_
		);

		authorheight = RenderingUtils::get_font_rendered_height(QFont("Arial", this->text_font_height_));
	}

	if (!this->meta_data_.get_date().empty())
	{
		const int date_y = LayoutConstants::DIAGRAM_MARGIN + (titleheight) + (authorheight);
		RenderingUtils::draw_text(
			LayoutConstants::DIAGRAM_MARGIN,
			date_y,
			this->meta_data_.get_date().c_str(),
			*this->img_,
			this->text_font_height_
		);
	}
}

int RenderableMetaData::calculate_height() const
{
	return LayoutConstants::DIAGRAM_MARGIN +
		(this->meta_data_.get_title().empty() ? 0 : RenderingUtils::get_font_rendered_height(QFont("Arial", this->title_font_height_))) +
		(this->meta_data_.get_author().empty() ? 0 : RenderingUtils::get_font_rendered_height(QFont("Arial", this->text_font_height_))) +
		(this->meta_data_.get_date().empty() ? 0 : RenderingUtils::get_font_rendered_height(QFont("Arial", this->text_font_height_)));
}

int RenderableMetaData::calculate_width() const
{
	QFont title_font("Arial",   this->title_font_height_);
	QFont message_font("Arial", this->text_font_height_);
	const auto title_width = (this->meta_data_.get_title().empty() ? 0 : RenderingUtils::get_font_rendered_width(this->meta_data_.get_title(), title_font));
	const auto author_width = (this->meta_data_.get_author().empty() ? 0 : RenderingUtils::get_font_rendered_width(this->meta_data_.get_author(), message_font));
	const auto date_width = (this->meta_data_.get_date().empty() ? 0 : RenderingUtils::get_font_rendered_width(this->meta_data_.get_date(), message_font));

	return (2 * LayoutConstants::DIAGRAM_MARGIN) + std::max(std::max(title_width, author_width), date_width);
}
