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

class RenderingUtils {
public:

  const enum class Theme {
    Default,
    Sketchy
  };

  const enum class ArrowDirection {
    Right,
    Left
  };

  const enum class ArrowStyle {
    Open,
    Closed
  };

  static auto get_font_rendered_height(const QFont font) -> int {
    QFontMetrics fm(font);
    return fm.ascent();
  }

  static auto get_font_rendered_width(const std::string& input, const QFont font) -> int {
    QFontMetrics fm(font);
    return fm.horizontalAdvance(input.c_str());
  }

  static void set_dashed_pen(double line_length, QPainter& canvas) {
    QPen pen(canvas.pen());
    QVector<qreal> dashes;
    for (int i = 0; i <= line_length; i++) {
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

    return uid(re, Dist::param_type{min_skew, max_skew}) * (0.5 * (line_length / 100.0));
  }

  static double random_skew(double line_length, double min_skew = -10, double max_skew = 10) {
    static std::default_random_engine re{};
    using Dist = std::uniform_real_distribution<double>;
    static Dist uid{};

    return uid(re, Dist::param_type{min_skew, max_skew}) * (0.25 * (line_length / 100.0));
  }
};
