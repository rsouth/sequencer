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
	this->draw_line(line_from_x, line_y, line_to_x, line_y);

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
	this->draw_line(line_from_x, from_line_y, line_to_x, from_line_y);

	// vertical line
	this->draw_line(line_to_x, from_line_y, line_to_x, to_line_y);

	// second line
	this->draw_line(line_from_x, to_line_y, line_to_x, to_line_y);

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
		// draw >
		this->draw_line(
			line_end_x - LayoutConstants::ARROWHEAD_LINE_LENGTH,
			line_end_y - LayoutConstants::ARROWHEAD_LINE_LENGTH,
			line_end_x,
			line_end_y);

		// draw <
		this->draw_line(
			line_end_x - LayoutConstants::ARROWHEAD_LINE_LENGTH,
			line_end_y + LayoutConstants::ARROWHEAD_LINE_LENGTH,
			line_end_x,
			line_end_y);
	}
	else
	{
		// draw <
		this->draw_line(
			line_end_x + LayoutConstants::ARROWHEAD_LINE_LENGTH,
			line_end_y - LayoutConstants::ARROWHEAD_LINE_LENGTH,
			line_end_x,
			line_end_y);
		// draw >
		this->draw_line(
			line_end_x + LayoutConstants::ARROWHEAD_LINE_LENGTH,
			line_end_y + LayoutConstants::ARROWHEAD_LINE_LENGTH,
			line_end_x,
			line_end_y);
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
	const auto font_rendered_width = this->rendering_utils_->get_font_rendered_width(this->interaction_.get_message(), this->text_font_height_);
	return 100 + line_from_x + font_rendered_width + LayoutConstants::MESSAGE_X_PADDING + (2 * LayoutConstants::DIAGRAM_MARGIN);
}


auto RenderableInteraction::draw_string(const int x, const int y, const std::string& text,
                                        const int font_height) const -> void
{
	this->img_->draw_text(x, y, text.c_str(), RenderingUtils::BLACK, RenderingUtils::WHITE, 1, font_height);
}

auto RenderableInteraction::draw_line(const int x0, const int y0, const int x1, const int y1) const -> void
{
	this->img_->draw_line(
		x0,
		y0,
		x1,
		y1,
		RenderingUtils::BLACK,
		1,
		~0U);
}

auto RenderableInteraction::get_participant_x(const Participant& participant) -> int
{
	return LayoutConstants::DIAGRAM_MARGIN + 
		(participant.get_index() * LayoutConstants::LANE_WIDTH) +
		(participant.get_index() * LayoutConstants::LANE_GAP) +
		(LayoutConstants::LANE_WIDTH / 2);
}
