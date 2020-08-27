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
#include "RenderableParticipant.h"

#include <utility>


#include "LayoutConstants.h"
#include "RenderingUtils.h"

#include "qpainter.h"

RenderableParticipant::RenderableParticipant(Participant participant, QPainter* img):
	participant_(std::move(participant)),
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
	this->img_->drawRect(participant_x0, participant_y0, LayoutConstants::LANE_WIDTH, LayoutConstants::LANE_HEIGHT);
	

	const std::string partic_name = this->participant_.get_name();
	const unsigned int font_height = this->font_height_;

	QFont title_font("Arial", font_height);
	const int text_x = get_participant_x() + (LayoutConstants::LANE_WIDTH / 2) - ( RenderingUtils::get_font_rendered_width(partic_name, title_font) / 2);


	const int text_y = header_y_offset + LayoutConstants::V_GAP + (LayoutConstants::LANE_HEIGHT / 2) - (RenderingUtils::get_font_rendered_height(partic_name, title_font) / 2);

	QFont f = this->img_->font();
	this->img_->setFont(title_font);
	this->img_->drawText(text_x, text_y, partic_name.c_str());
	this->img_->setFont(f);

	// draw vertical line
	// int totalInteractions = 1; // todo <<<-----
	const int y1 = header_y_offset + LayoutConstants::LANE_HEIGHT + LayoutConstants::V_GAP;
	const int y2 = y1 + LayoutConstants::INTERACTION_GAP + (total_interactions * (LayoutConstants::INTERACTION_GAP + LayoutConstants::V_GAP));
	
	// last VGAP should be a 'lane height padding' type.
	this->img_->drawLine(
		participant_x0 + LayoutConstants::LANE_WIDTH / 2,
		y1,
		participant_x0 + LayoutConstants::LANE_WIDTH / 2,
		y2);
}

int RenderableParticipant::calculate_width()
{
	return (2 * LayoutConstants::DIAGRAM_MARGIN) + LayoutConstants::LANE_WIDTH + LayoutConstants::LANE_GAP;
}
