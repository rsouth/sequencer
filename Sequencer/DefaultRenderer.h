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

#include "Renderer.h"
#include "qpainter.h"

class DefaultRenderer : public Renderer {
public:

  explicit DefaultRenderer(QPainter* canvas) : Renderer(canvas) {
    title_font_ = QFont("Arial", 26);
    metadata_font_ = QFont("Arial", 10);
    header_font_ = QFont("Arial", 12);
    message_font_ = QFont("Arial", 10);
  }

  void draw_rectangle(QPoint top_left, QPoint bottom_right) override;

  void draw_line(QPoint from, QPoint to, bool dashed = false) override;
};
