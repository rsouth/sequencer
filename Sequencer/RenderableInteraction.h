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
#include "Renderer.h"
#include "qpainter.h"

class RenderableInteraction {
public:
  RenderableInteraction(const Interaction& interaction, Renderer* renderer);

  auto draw(int y_offset) const -> void;
  auto get_rightmost_x() const -> int;

private:

  Interaction interaction_;
  Renderer* renderer_;

  auto draw_self_referential_interaction(int y_offset) const -> void;

  auto draw_arrowhead(int line_end_x, int line_end_y) const -> void;

  static auto get_participant_x(const Participant& participant) -> int;

  auto draw_point_to_point_interaction(int y_offset) const -> void;

  auto render_interaction_message(int interaction_from_x,
                                  int interaction_from_y,
                                  int interaction_to_x) const -> void;

  auto is_pointing_right() const -> bool;
};
