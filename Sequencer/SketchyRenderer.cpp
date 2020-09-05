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
#include "SketchyRenderer.h"
#include "LayoutConstants.h"
#include "RenderingUtils.h"

void SketchyRenderer::draw_rectangle(QPoint top_left, QPoint bottom_right)
{
  draw_line(
    QPoint(top_left.x(), top_left.y() + (LayoutConstants::LANE_HEIGHT * 0.85) + RenderingUtils::random_skew(LayoutConstants::LANE_WIDTH, 0.0, 10.0)),
    QPoint(top_left.x() + LayoutConstants::LANE_WIDTH, top_left.y() + (LayoutConstants::LANE_HEIGHT * 0.85) + RenderingUtils::random_skew(LayoutConstants::LANE_WIDTH, -10.0, 0.0)),
    false
  );
}

void SketchyRenderer::draw_line(QPoint from, QPoint to, bool dashed)
{
  canvas_->save();
  QBrush brush(Qt::black, Qt::BrushStyle::SolidPattern);
  QPen pen(brush, 2);
  canvas_->setPen(pen);
  canvas_->setRenderHints(QPainter::Antialiasing);

  if (from.x() == to.x()) {
    // vertical line
    double line_length = abs(from.y() - to.y());
    double first_skew_point = 0.5 * line_length;
    double second_skew_point = 0.75 * line_length;

    QPainterPath myPath;
    myPath.moveTo(from);
    myPath.cubicTo(
      QPoint(from.x() + RenderingUtils::random_skew(line_length), from.y() + first_skew_point),
      QPoint(from.x() + RenderingUtils::random_skew(line_length), from.y() + second_skew_point),
      to
    );

    if (dashed)
    {
      RenderingUtils::set_dashed_pen(line_length, *canvas_);
    }
    canvas_->drawPath(myPath);
  }
  else
  {
    // horizontal line
    double line_length = abs(from.x() - to.x());
    double first_skew_point = to.x() > from.x() ? 0.5 * line_length : -0.5 * line_length;
    double second_skeq_point = to.x() > from.x() ? 0.75 * line_length : -0.75 * line_length;

    QPainterPath myPath;
    myPath.moveTo(from);
    myPath.cubicTo(
      QPointF(from.x() + first_skew_point, from.y() + RenderingUtils::random_skew(line_length)),
      QPointF(from.x() + second_skeq_point, from.y() + RenderingUtils::random_skew(line_length)),
      to
    );

    if (dashed)
    {
      RenderingUtils::set_dashed_pen(line_length, *canvas_);
    }

    canvas_->drawPath(myPath);

    canvas_->restore();
  }
}