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

#include "qpainter.h"
#include "RenderingUtils.h"

class Renderer {
public:

  Renderer(QPainter* canvas) : canvas_(canvas) { }

  //
  // Drawing functions
  //

  virtual void draw_rectangle(QPoint top_left, QPoint bottom_right) = 0;

  virtual void draw_line(QPoint from, QPoint to, bool dashed = false) = 0;

  virtual void draw_text(int x, int y, const std::string& text, QFont font);

  virtual void draw_arrowhead(QPoint point_at, RenderingUtils::ArrowDirection direction,
                              RenderingUtils::ArrowStyle filled);

  //
  // Fonts
  //

  QFont get_title_font() { return title_font_; }

  QFont get_metadata_font() { return metadata_font_; }

  QFont get_header_font() { return header_font_; }

  QFont get_message_font() { return message_font_; }

protected:

  QPainter* canvas_;

  QFont title_font_;
  QFont metadata_font_;
  QFont header_font_;
  QFont message_font_;
};
