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

#include "Interaction.h"
#include "RenderingUtils.h"

namespace cimg_library
{
	template <typename T>
	struct CImg;
}


class RenderableInteraction
{
public:
	RenderableInteraction(Interaction interaction, RenderingUtils* rendering_utils,
	                      cimg_library::CImg<unsigned char>* img);

	auto draw(int y_offset) const -> void;
	auto get_rightmost_x() const -> int;

private:

	Interaction interaction_;
	RenderingUtils* rendering_utils_;
	cimg_library::CImg<unsigned char>* img_;
	unsigned int text_font_height_ = 23;


	auto draw_self_referential_interaction(int y_offset) const -> void;

	auto draw_arrowhead(int line_end_x, int line_end_y) const -> void;

	auto draw_line(int x0, int y0, int x1, int y1, bool dashed = false) const -> void;

	static auto get_participant_x(const Participant& participant) -> int;
	auto draw_point_to_point_interaction(int y_offset) const -> void;

	auto render_interaction_message(int interaction_from_x,
	                                int interaction_from_y,
	                                int interaction_to_x) const -> void;

	auto draw_string(int x, int y, const std::string& text, int font_height) const -> void;

};

