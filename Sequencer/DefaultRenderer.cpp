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
#include "DefaultRenderer.h"
#include "LayoutConstants.h"

void DefaultRenderer::draw_rectangle(QPoint top_left, QPoint bottom_right)
{
  canvas_->drawRoundedRect(top_left.x(), top_left.y(), LayoutConstants::LANE_WIDTH, LayoutConstants::LANE_HEIGHT, 5, 5, Qt::SizeMode::AbsoluteSize);
}

void DefaultRenderer::draw_line(QPoint from, QPoint to, bool dashed)
{
  canvas_->save();
  if (dashed)
  {
    canvas_->setPen(Qt::PenStyle::DashLine);
  }
  canvas_->drawLine(from, to);
  canvas_->restore();
}