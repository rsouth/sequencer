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

#include "Diagram.h"
#include "RenderableInteraction.h"
#include "RenderableMetaData.h"
#include "RenderableParticipant.h"

#include "RenderingUtils.h"

#include "qpainter.h"

class RenderableDiagram {
public:
  RenderableDiagram(const Diagram& diagram, QPainter* img);

  ~RenderableDiagram();

  void draw() const;

  auto calculate_diagram_size(int hxw[]) -> void;

private:
  Diagram diagram_;
  QPainter* canvas_;

  int max_interaction_index() const;

  auto initialise_renderables() -> void;

  // Renderables
  RenderableMetaData* renderable_metadata_; // = RenderableMetaData();
  std::list<RenderableParticipant*> renderable_participants_ = std::list<RenderableParticipant*>();
  std::list<RenderableInteraction*> renderable_interactions_ = std::list<RenderableInteraction*>();
};
