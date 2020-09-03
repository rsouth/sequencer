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
    draw_sketchy_line(from, to, canvas);
    //canvas.drawLine(from, to);
    canvas.restore();
  }

  static void draw_sketchy_line(QPoint from, QPoint to, QPainter& canvas)
  {
    QBrush brush(Qt::black, Qt::BrushStyle::SolidPattern);
    QPen pen(brush, 2);
    canvas.setPen(pen);
    canvas.setRenderHints(QPainter::Antialiasing);

    if (from.x() == to.x()) {
      // vertical line
      double len = abs(from.y() - to.y());
      double first_skew_point = 0.5 * len;
      double second_skeq_point = 0.75 * len;

      QPainterPath myPath;
      myPath.moveTo(from);
      double skew_1 = ((rand() % 10) + ((len / 100.0))) - (len / 100.0) / 2;
      double skew_2 = ((rand() % 10) + ((len / 100.0))) - (len / 100.0) / 2;
      myPath.cubicTo(QPoint(from.x() + skew_1, from.y() + first_skew_point), QPoint(from.x() + skew_2, from.y() + second_skeq_point), to);

      canvas.drawPath(myPath);
    }
    else
    {
      // horizontal line
      double len = abs(from.x() - to.x());
      double first_skew_point = to.x() > from.x() ? 0.5 * len : -0.5 * len;
      double second_skeq_point = to.x() > from.x() ? 0.75 * len : -0.75 * len;

      QPainterPath myPath;
      myPath.moveTo(from);
      double skew_1 = ((rand() % 5) + ((len / 100.0))) - (len / 100.0) / 2;
      double skew_2 = ((rand() % 5) + ((len / 100.0))) - (len / 100.0) / 2;
      myPath.cubicTo(
        QPointF(from.x() + first_skew_point, from.y() + skew_1),
        QPointF(from.x() + second_skeq_point, from.y() + skew_2),
        to
      );

      canvas.drawPath(myPath);
    }
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
