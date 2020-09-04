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

#include "MetaData.h"
#include "RenderingUtils.h"

#include "qpainter.h"

class RenderableMetaData
{
public:
  RenderableMetaData(const MetaData& meta_data, QPainter* img);

  auto draw(RenderingUtils::Theme theme) const -> void;
  auto calculate_height() const -> int;
  auto calculate_width() const -> int;

private:
  MetaData meta_data_ = MetaData();
  QPainter* img_ = nullptr;

  // \param font_height_ Height of the text font(exact match for 13, 23, 53, 103, interpolated otherwise).
  const int title_font_height_ = 16;
  const int text_font_height_ = 8;
};
