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

#include "RenderingUtils.h"
#include "Renderer.h"
#include "DefaultRenderer.h"
#include "SketchyRenderer.h"

class RendererFactory {
public:

  static Renderer* make_renderer(QPainter* canvas, const RenderingUtils::Theme theme) {
    switch (theme) {
    case RenderingUtils::Theme::Sketchy:
      return new SketchyRenderer(canvas);
    case RenderingUtils::Theme::Default:
    default:
      return new DefaultRenderer(canvas);
    }
  }
};
