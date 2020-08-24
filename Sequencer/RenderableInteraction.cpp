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
#include "RenderableInteraction.h"

#include "CImg.h"
#include "LayoutConstants.h"
#include "RenderingUtils.h"


using namespace cimg_library;

RenderableInteraction::RenderableInteraction(Interaction interaction, RenderingUtils* rendering_utils,
                                             CImg<unsigned char>* img): interaction_(std::move(interaction)),
                                                                        rendering_utils_(std::move(rendering_utils)),
                                                                        img_(img)
{
}

auto RenderableInteraction::draw(const int y_offset) const -> void
{
	if (this->interaction_.is_self_referential())
	{
		this->draw_self_referential_interaction(y_offset);
	}
	else
	{
		this->draw_point_to_point_interaction(y_offset);
	}
}

auto RenderableInteraction::draw_point_to_point_interaction(const int y_offset) const -> void
{
	const auto line_from_x = get_participant_x(this->interaction_.get_from());
	const auto line_to_x = get_participant_x(this->interaction_.get_to());

	const auto line_y = y_offset + (this->interaction_.get_index() * LayoutConstants::INTERACTION_GAP) + LayoutConstants::INTERACTION_GAP;

	// draw line
	this->draw_line(line_from_x, line_y, line_to_x, line_y, this->interaction_.is_reply());

	// draw message
	this->render_interaction_message(line_from_x, line_y, line_to_x);

	// Arrow head
	draw_arrowhead(line_to_x, line_y);
}

auto RenderableInteraction::draw_self_referential_interaction(const int y_offset) const -> void
{
	const int line_from_x = get_participant_x(this->interaction_.get_from());
	const int line_to_x = line_from_x + (LayoutConstants::LANE_WIDTH / 2);

	const int from_line_y = y_offset + (this->interaction_.get_index() * LayoutConstants::INTERACTION_GAP) + LayoutConstants::INTERACTION_GAP;
	const int to_line_y = from_line_y + (LayoutConstants::INTERACTION_GAP);

	// render line
	this->draw_line(line_from_x, from_line_y, line_to_x, from_line_y, this->interaction_.is_reply());

	// vertical line
	this->draw_line(line_to_x, from_line_y, line_to_x, to_line_y, this->interaction_.is_reply());

	// second line
	this->draw_line(line_from_x, to_line_y, line_to_x, to_line_y, this->interaction_.is_reply());

	// Render message
	this->render_interaction_message(line_from_x, from_line_y, line_to_x);

	// draw arrowhead
	this->draw_arrowhead(line_from_x, to_line_y);
}

auto RenderableInteraction::draw_arrowhead(const int line_end_x, const int line_end_y) const -> void
{
	const auto from_lane_index = this->interaction_.get_from().get_index();
	const auto to_lane_index = this->interaction_.get_to().get_index();

	const boolean is_pointing_right = from_lane_index < to_lane_index;
	if (is_pointing_right)
	{
		if (this->interaction_.is_async()) {
			// draw down-right
			this->draw_line(
				line_end_x - LayoutConstants::ARROWHEAD_LINE_LENGTH,
				line_end_y - LayoutConstants::ARROWHEAD_LINE_LENGTH,
				line_end_x,
				line_end_y);

			// draw /
			this->draw_line(
				line_end_x - LayoutConstants::ARROWHEAD_LINE_LENGTH,
				line_end_y + LayoutConstants::ARROWHEAD_LINE_LENGTH,
				line_end_x,
				line_end_y);
		} else {
			CImg<int> points(3, 2);
			int arrowhead_points[] = {
				line_end_x, line_end_y,
				line_end_x - LayoutConstants::ARROWHEAD_LINE_LENGTH, line_end_y - LayoutConstants::ARROWHEAD_LINE_LENGTH,
				line_end_x - LayoutConstants::ARROWHEAD_LINE_LENGTH, line_end_y + LayoutConstants::ARROWHEAD_LINE_LENGTH
			};
			const int* iterator = arrowhead_points;

			cimg_forX(points, i) {
				points(i, 0) = *(iterator++); points(i, 1) = *(iterator++);
			}
			this->img_->draw_polygon(points, RenderingUtils::BLACK);
		}
	}
	else
	{
		if (this->interaction_.is_async()) {
			// draw /
			this->draw_line(
				line_end_x + LayoutConstants::ARROWHEAD_LINE_LENGTH,
				line_end_y - LayoutConstants::ARROWHEAD_LINE_LENGTH,
				line_end_x,
				line_end_y);
			// draw down-right
			this->draw_line(
				line_end_x + LayoutConstants::ARROWHEAD_LINE_LENGTH,
				line_end_y + LayoutConstants::ARROWHEAD_LINE_LENGTH,
				line_end_x,
				line_end_y);
		} else {
			// draw filled polygon for synchronous calls
			CImg<int> points(3, 2);
			int arrowhead_points[] = {
				line_end_x, line_end_y,
				line_end_x + LayoutConstants::ARROWHEAD_LINE_LENGTH, line_end_y - LayoutConstants::ARROWHEAD_LINE_LENGTH,
				line_end_x + LayoutConstants::ARROWHEAD_LINE_LENGTH, line_end_y + LayoutConstants::ARROWHEAD_LINE_LENGTH
			};
			const int* iterator = arrowhead_points;

			cimg_forX(points, i) {
				points(i, 0) = *(iterator++); points(i, 1) = *(iterator++);
			}
			this->img_->draw_polygon(points, RenderingUtils::BLACK);
		}
	}
}


auto RenderableInteraction::render_interaction_message(const int interaction_from_x, const int interaction_from_y,
                                                       const int interaction_to_x) const -> void
{
	if (!this->interaction_.get_message().empty())
	{
		const bool right_facing = interaction_from_x < interaction_to_x;
		const int message_width = this->rendering_utils_->get_font_rendered_width(this->interaction_.get_message(), this->text_font_height_);
		const int label_x = right_facing
			                    ? interaction_from_x + LayoutConstants::MESSAGE_X_PADDING
			                    : interaction_from_x - message_width - LayoutConstants::MESSAGE_X_PADDING;

		this->img_->draw_text(label_x, interaction_from_y - this->text_font_height_, this->interaction_.get_message().c_str(),
		                      RenderingUtils::BLACK, RenderingUtils::WHITE, 1, this->text_font_height_);
	}
}

auto RenderableInteraction::get_rightmost_x() const -> int
{
	const auto line_from_x = get_participant_x(this->interaction_.get_from());
	if (is_pointing_right()) {
		const auto font_rendered_width = this->rendering_utils_->get_font_rendered_width(this->interaction_.get_message(), this->text_font_height_);
		return 100 + line_from_x + font_rendered_width + LayoutConstants::MESSAGE_X_PADDING + (2 * LayoutConstants::DIAGRAM_MARGIN);
	}
	else
	{
		return line_from_x;
	}
}


auto RenderableInteraction::draw_string(const int x, const int y, const std::string& text,
                                        const int font_height) const -> void
{
	this->img_->draw_text(x, y, text.c_str(), RenderingUtils::BLACK, RenderingUtils::WHITE, 1, font_height);
}

auto RenderableInteraction::is_pointing_right() const -> bool
{
	return interaction_.get_from().get_index() < interaction_.get_to().get_index();	
}

auto RenderableInteraction::draw_line(const int x0, const int y0, const int x1, const int y1, bool dashed) const -> void
{
	this->img_->draw_line(
		x0,
		y0,
		x1,
		y1,
		RenderingUtils::BLACK,
		1, // opacity
		dashed ? 0xFFFFFF00 : 0xFFFFFFFF
	);
}

auto RenderableInteraction::get_participant_x(const Participant& participant) -> int
{
	return LayoutConstants::DIAGRAM_MARGIN + 
		(participant.get_index() * LayoutConstants::LANE_WIDTH) +
		(participant.get_index() * LayoutConstants::LANE_GAP) +
		(LayoutConstants::LANE_WIDTH / 2);
}
