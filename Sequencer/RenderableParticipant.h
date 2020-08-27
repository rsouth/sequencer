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
#pragma once

#include "Participant.h"
#include "RenderingUtils.h"

#include "qpainter.h"


class RenderableParticipant
{
public:
	RenderableParticipant(Participant participant, QPainter* img);

	void draw(int header_y_offset, int total_interactions);
	int calculate_width();

private:

	Participant participant_;
	QPainter* img_;

	int get_participant_x();

	unsigned int font_height_ = 23;
};
