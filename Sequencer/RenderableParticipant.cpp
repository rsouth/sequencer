#include "RenderableParticipant.h"

#include <utility>


#include "CImg.h"
#include "LayoutConstants.h"
#include "RenderingUtils.h"


using namespace cimg_library;

RenderableParticipant::RenderableParticipant(Participant participant, RenderingUtils *rendering_utils,
                                             CImg<unsigned char>* img):
	participant_(std::move(participant)),
	rendering_utils_(rendering_utils),
	img_(img)
{
}

int RenderableParticipant::get_participant_x()
{
	return LayoutConstants::DIAGRAM_MARGIN +
		(this->participant_.get_index() * LayoutConstants::LANE_WIDTH) +
		(this->participant_.get_index() * LayoutConstants::LANE_GAP);
}

void RenderableParticipant::draw(const int header_y_offset, const int total_interactions)
{
	const int participant_x0 = this->get_participant_x();
	const int participant_x1 = participant_x0 + LayoutConstants::LANE_WIDTH;
	const int participant_y0 = LayoutConstants::V_GAP + header_y_offset;
	const int participant_y1 = participant_y0 + LayoutConstants::LANE_HEIGHT;

	// render rectangle...
	this->img_->draw_rectangle(
		participant_x0,
		participant_y0,
		participant_x1,
		participant_y1,
		RenderingUtils::BLACK,
		1,
		~0U);

	const std::string partic_name = this->participant_.get_name();
	const unsigned int font_height = this->font_height_;

	const int text_x = get_participant_x() + (LayoutConstants::LANE_WIDTH / 2) - (this->rendering_utils_->get_font_rendered_width(partic_name, font_height) / 2);


	const int text_y = header_y_offset + LayoutConstants::V_GAP + (LayoutConstants::LANE_HEIGHT / 2) - (this
	                                                                                                    ->
	                                                                                                    rendering_utils_
	                                                                                                    ->get_font_rendered_height(
		                                                                                                    partic_name,
		                                                                                                    font_height)
		/ 2);

	this->img_->draw_text(text_x, text_y, partic_name.c_str(), RenderingUtils::BLACK, RenderingUtils::WHITE, 1,
	                      font_height);


	// draw vertical line
	// int totalInteractions = 1; // todo <<<-----
	const int y1 = header_y_offset + LayoutConstants::LANE_HEIGHT + LayoutConstants::V_GAP;
	const int y2 = y1 + LayoutConstants::INTERACTION_GAP + (total_interactions * (LayoutConstants::INTERACTION_GAP + LayoutConstants::V_GAP));
	
	// last VGAP should be a 'lane height padding' type.

	this->img_->draw_line(
		participant_x0 + LayoutConstants::LANE_WIDTH / 2,
		y1,
		participant_x0 + LayoutConstants::LANE_WIDTH / 2,
		y2,
		RenderingUtils::BLACK,
		1);
}

int RenderableParticipant::calculate_width()
{
	return (2 * LayoutConstants::DIAGRAM_MARGIN) + LayoutConstants::LANE_WIDTH + LayoutConstants::LANE_GAP;
}
