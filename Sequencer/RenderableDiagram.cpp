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
#include "RenderableDiagram.h"

#include <numeric>

#include "qpainter.h"

#include "LayoutConstants.h"
#include "RenderableMetaData.h"
#include "RenderableParticipant.h"

#include "RendererFactory.h"

RenderableDiagram::RenderableDiagram(const Diagram& diagram, QPainter* canvas) : diagram_(diagram), canvas_(canvas) {
  initialise_renderables();
}

RenderableDiagram::~RenderableDiagram() {
  delete this->renderable_metadata_;
  for (auto renderable_participant : this->renderable_participants_) { delete renderable_participant; }
  for (auto renderable_interaction : this->renderable_interactions_) { delete renderable_interaction; }
}

void RenderableDiagram::draw() const {
  const auto meta_data = this->diagram_.get_meta_data();

  // Draw Header
  this->renderable_metadata_->draw();

  const auto header_y_offset = this->renderable_metadata_->calculate_height();

  // Draw all participants
  for (auto participant : this->renderable_participants_) {
    const int max_index = max_interaction_index();
    participant->draw(header_y_offset, max_index);
  }

  // Draw all interactions
  const auto interaction_y_offset = header_y_offset + LayoutConstants::LANE_HEIGHT + LayoutConstants::V_GAP;
  for (auto interaction : this->renderable_interactions_) { interaction->draw(interaction_y_offset); }
}

int RenderableDiagram::max_interaction_index() const {
  int max_index = this->diagram_.get_interactions().empty() ? 0 : this->diagram_.get_interactions().front().get_index();
  if (this->diagram_.get_interactions().size() >= 2) {
    std::list<Interaction> interactions = this->diagram_.get_interactions();
    max_index = std::max_element(interactions.begin(), interactions.end(),
                                 [](const Interaction& a, const Interaction& b) {
                                   return a.get_index() < b.get_index();
                                 })->get_index();
  }
  return max_index + 1;
}

void RenderableDiagram::calculate_diagram_size(int hxw[]) {
  const int header_width = this->renderable_metadata_->calculate_width();

  int participant_width = std::accumulate(this->renderable_participants_.begin(), this->renderable_participants_.end(),
                                          0,
                                          [](int acc_, const RenderableParticipant* rp) {
                                            return acc_ + rp->calculate_width();
                                          }
  );

  // get farthest right x of all interaction messages
  int rightmost_message_x = 0;
  for (auto renderable_interaction : this->renderable_interactions_) {
    if (renderable_interaction->get_rightmost_x() > rightmost_message_x) {
      rightmost_message_x = renderable_interaction->get_rightmost_x();
    }
  }

  const int diagram_width = std::max(std::max(rightmost_message_x, participant_width), header_width);

  const int max_height = (2 * LayoutConstants::DIAGRAM_MARGIN) +
    this->renderable_metadata_->calculate_height() +
    (this->renderable_participants_.empty() ? 0 : LayoutConstants::LANE_HEIGHT + LayoutConstants::V_GAP) +
    (this->renderable_interactions_.empty()
       ? 0
       : (this->max_interaction_index() + 1) * (LayoutConstants::INTERACTION_GAP + LayoutConstants::V_GAP));

  hxw[0] = max_height;
  hxw[1] = std::max(header_width, diagram_width);
}

void RenderableDiagram::initialise_renderables() {
  // Theme
  Renderer* renderer = RendererFactory::make_renderer(this->canvas_, this->diagram_.get_meta_data().get_theme());

  // MetaData
  this->renderable_metadata_ = new RenderableMetaData(this->diagram_.get_meta_data(), renderer);

  // Participants
  const auto participants = this->diagram_.get_participants();
  for (const auto& participant : participants) {
    this->renderable_participants_.emplace_back(new RenderableParticipant(participant, renderer));
  }

  // Interactions
  const auto interactions = this->diagram_.get_interactions();
  for (const auto& interaction : interactions) {
    this->renderable_interactions_.emplace_back(new RenderableInteraction(interaction, renderer));
  }
}
