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
#include <random>

#include "LayoutConstants.h"
#include "qfont.h"
#include "qfontmetrics.h"
#include "qpainter.h"
#include "qpainterpath.h"
#include "qdebug.h"

class RenderingUtils
{
public:

  const enum class Theme {
    Default, Sketchy
  };

  const enum class ArrowDirection {
    Right, Left
  };

  const enum class ArrowStyle {
    Open, Closed
  };

  static auto get_font_rendered_height(const QFont font) -> int
  {
    QFontMetrics fm(font);
    return fm.ascent();
  }

  static auto get_font_rendered_width(const std::string& input, const QFont font) -> int
  {
    QFontMetrics fm(font);
    return fm.horizontalAdvance(input.c_str());
  }

  static const char* get_font_name(Theme theme = Theme::Default)
  {
    switch (theme) {
    case Theme::Sketchy:
      return "Ink Free";
    case Theme::Default:
    default:
      return "Arial";
    }
  }

  //
  // Drawing Functions
  //

  static void draw_text(int x, int y, const std::string& text, QPainter& canvas, const int font_size = 12, Theme theme = Theme::Default)
  {
    canvas.save();

    QFont font(get_font_name(theme), font_size);
    int offset = get_font_rendered_height(font);

    canvas.setFont(font);
    canvas.drawText(x, y + offset, text.c_str());

    // restore original font
    canvas.restore();
  }

  static void draw_rectangle(QPoint top_left, QPoint bottom_right, QPainter& canvas, Theme theme)
  {
    switch (theme)
    {
    case Theme::Sketchy:
      // line from top_left.x to top_left.x + LANE_WIDTH
      draw_line(
        QPoint(top_left.x(), top_left.y() + (LayoutConstants::LANE_HEIGHT * 0.85) + random_skew(LayoutConstants::LANE_WIDTH, 0.0, 10.0)),
        QPoint(top_left.x() + LayoutConstants::LANE_WIDTH, top_left.y() + (LayoutConstants::LANE_HEIGHT * 0.85) + random_skew(LayoutConstants::LANE_WIDTH, -10.0, 0.0)),
        canvas,
        false,
        theme
      );
      break;
    case Theme::Default:
    default:
      canvas.drawRoundedRect(top_left.x(), top_left.y(), LayoutConstants::LANE_WIDTH, LayoutConstants::LANE_HEIGHT, 5, 5, Qt::SizeMode::AbsoluteSize);
      break;
    }
  }

  static void RenderingUtils::draw_line(QPoint from, QPoint to, QPainter& canvas, bool dashed = false, Theme theme = Theme::Default)
  {
    canvas.save();

    switch (theme) {
    case Theme::Sketchy:
      draw_sketchy_line(from, to, canvas, dashed);
      break;

    case Theme::Default:
    default:
      if (dashed)
      {
        canvas.setPen(Qt::PenStyle::DashLine);
      }
      canvas.drawLine(from, to);
      break;
    }

    canvas.restore();
  }

  static void draw_sketchy_line(QPoint from, QPoint to, QPainter& canvas, bool dashed = false)
  {
    QBrush brush(Qt::black, Qt::BrushStyle::SolidPattern);
    QPen pen(brush, 2);
    canvas.setPen(pen);
    canvas.setRenderHints(QPainter::Antialiasing);

    if (from.x() == to.x()) {
      // vertical line
      double line_length = abs(from.y() - to.y());
      double first_skew_point = 0.5 * line_length;
      double second_skew_point = 0.75 * line_length;

      QPainterPath myPath;
      myPath.moveTo(from);
      myPath.cubicTo(
        QPoint(from.x() + random_skew(line_length), from.y() + first_skew_point),
        QPoint(from.x() + random_skew(line_length), from.y() + second_skew_point),
        to
      );

      if (dashed)
      {
        set_dashed_pen(line_length, canvas);
      }
      canvas.drawPath(myPath);
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
        QPointF(from.x() + first_skew_point, from.y() + random_skew(line_length)),
        QPointF(from.x() + second_skeq_point, from.y() + random_skew(line_length)),
        to
      );

      if (dashed)
      {
        set_dashed_pen(line_length, canvas);
      }

      canvas.drawPath(myPath);
    }
  }

  static void set_dashed_pen(double line_length, QPainter& canvas)
  {
    QPen pen(canvas.pen());
    QVector<qreal> dashes;
    for (int i = 0; i <= line_length; i++)
    {
      int dash_len = random_dash_length(line_length, 10, 15);
      int gap_len = random_dash_length(line_length, 10, 15);
      dashes << dash_len << gap_len;

      i += dash_len + gap_len;
    }
    pen.setDashPattern(dashes);
    canvas.setPen(pen);
  }

  static double random_dash_length(double line_length, double min_skew = -10, double max_skew = 10) {
    static std::default_random_engine re{};
    using Dist = std::uniform_real_distribution<double>;
    static Dist uid{};

    return uid(re, Dist::param_type{ min_skew, max_skew }) * (0.5 * (line_length / 100.0));
  }

  static double random_skew(double line_length, double min_skew = -10, double max_skew = 10) {
    static std::default_random_engine re{};
    using Dist = std::uniform_real_distribution<double>;
    static Dist uid{};

    return uid(re, Dist::param_type{ min_skew, max_skew }) * (0.25 * (line_length / 100.0));
  }

  static void RenderingUtils::draw_arrowhead(QPoint point_at, QPainter& canvas, ArrowDirection direction, ArrowStyle filled, Theme theme = Theme::Default)
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
