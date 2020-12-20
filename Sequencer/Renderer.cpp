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
#include "Renderer.h"

void Renderer::draw_text(int x, int y, const std::string& text, const QFont font) {
  canvas_->save();

  int offset = RenderingUtils::get_font_rendered_height(font);

  canvas_->setFont(font);
  canvas_->drawText(x, y + offset, text.c_str());

  // restore original font
  canvas_->restore();
}

void Renderer::draw_arrowhead(QPoint point_at, RenderingUtils::ArrowDirection direction,
                              RenderingUtils::ArrowStyle filled) {
  QPolygonF polygon;
  if (direction == RenderingUtils::ArrowDirection::Right) {
    polygon << QPoint(point_at.x() - LayoutConstants::ARROWHEAD_LINE_LENGTH,
                      point_at.y() - LayoutConstants::ARROWHEAD_LINE_LENGTH)
      << QPoint(point_at.x(), point_at.y())
      << QPoint(point_at.x() - LayoutConstants::ARROWHEAD_LINE_LENGTH,
                point_at.y() + LayoutConstants::ARROWHEAD_LINE_LENGTH);
  }
  else {
    polygon << QPoint(point_at.x() + LayoutConstants::ARROWHEAD_LINE_LENGTH,
                      point_at.y() + LayoutConstants::ARROWHEAD_LINE_LENGTH)
      << QPoint(point_at.x(), point_at.y())
      << QPoint(point_at.x() + LayoutConstants::ARROWHEAD_LINE_LENGTH,
                point_at.y() - LayoutConstants::ARROWHEAD_LINE_LENGTH);
  }

  canvas_->save();
  if (RenderingUtils::ArrowStyle::Closed == filled) {
    // fill the arrowhead
    QBrush brush(Qt::black, Qt::SolidPattern);
    QPainterPath path;
    path.addPolygon(polygon);
    canvas_->fillPath(path, brush);
  }

  // Draw polygon
  canvas_->drawPolyline(polygon);
  canvas_->restore();
}
