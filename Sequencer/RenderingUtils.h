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
#include <string>

#include "LayoutConstants.h"
#include "qfont.h"
#include "qfontmetrics.h"
#include "qpainter.h"
#include "qpainterpath.h"

class RenderingUtils
{
public:

  const enum class ArrowDirection {
    Right, Left
  };

  const enum class ArrowStyle {
    Open, Closed
  };

  static auto RenderingUtils::get_font_rendered_height(const QFont font) -> int
  {
    QFontMetrics fm(font);
    return fm.ascent();
  }

  static auto RenderingUtils::get_font_rendered_width(const std::string& input, const QFont font) -> int
  {
    QFontMetrics fm(font);
    return fm.horizontalAdvance(input.c_str());
  }

  static void RenderingUtils::draw_text(int x, int y, const std::string& text, QPainter& canvas, const int font_size = 12)
  {
    canvas.save();

    QFont font("Arial", font_size);
    int offset = get_font_rendered_height(font);

    canvas.setFont(font);
    canvas.drawText(x, y + offset, text.c_str());

    // restore original font
    canvas.restore();
  }

  static void RenderingUtils::draw_line(QPoint from, QPoint to, QPainter& canvas, bool dashed = false)
  {
    canvas.save();
    if (dashed)
    {
      canvas.setPen(Qt::PenStyle::DashLine);
    }
    canvas.drawLine(from, to);
    canvas.restore();
  }

  static void RenderingUtils::draw_arrowhead(QPoint point_at, QPainter& canvas, ArrowDirection direction, ArrowStyle filled)
  {
    QPolygonF polygon;
    if (direction == ArrowDirection::Right) {
      polygon << QPoint(point_at.x() - LayoutConstants::ARROWHEAD_LINE_LENGTH, point_at.y() - LayoutConstants::ARROWHEAD_LINE_LENGTH)
        << QPoint(point_at.x(), point_at.y())
        << QPoint(point_at.x() - LayoutConstants::ARROWHEAD_LINE_LENGTH, point_at.y() + LayoutConstants::ARROWHEAD_LINE_LENGTH);
    }
    else
    {
      polygon << QPoint(point_at.x() + LayoutConstants::ARROWHEAD_LINE_LENGTH, point_at.y() + LayoutConstants::ARROWHEAD_LINE_LENGTH)
        << QPoint(point_at.x(), point_at.y())
        << QPoint(point_at.x() + LayoutConstants::ARROWHEAD_LINE_LENGTH, point_at.y() - LayoutConstants::ARROWHEAD_LINE_LENGTH);
    }

    canvas.save();
    if (ArrowStyle::Closed == filled) {
      // fill the arrowhead
      QBrush brush(Qt::black, Qt::SolidPattern);
      QPainterPath path;
      path.addPolygon(polygon);
      canvas.fillPath(path, brush);
    }

    // Draw polygon
    canvas.drawPolyline(polygon);
    canvas.restore();
  }
};
