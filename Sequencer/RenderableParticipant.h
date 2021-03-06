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

#include "Renderer.h"

#include "qpainter.h"

class RenderableParticipant
{
public:
  RenderableParticipant(const Participant& participant, Renderer* renderer);

  auto draw(int header_y_offset, int total_interactions) -> void;
  auto calculate_width() const -> int;

private:

  Participant participant_;
  Renderer* renderer_;

  auto get_participant_x() const -> int;
};
