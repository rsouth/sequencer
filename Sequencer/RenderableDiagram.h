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


namespace cimg_library
{
	template <typename T>
	struct CImg;
}

class RenderableDiagram
{
public:
	RenderableDiagram(const Diagram& diagram, cimg_library::CImg<unsigned char>* img);

	~RenderableDiagram();

	auto draw() -> void;
	auto max_interaction_index() -> int;
	auto calculate_diagram_size(int hxw[]) -> void;

private:
	Diagram diagram_;
	RenderingUtils* rendering_utils_ = new RenderingUtils();
	cimg_library::CImg<unsigned char>* img_;

	auto initialise_renderables() -> void;

	// Renderables
	RenderableMetaData* renderable_metadata_; // = RenderableMetaData();
	std::list<RenderableParticipant*> renderable_participants_ = std::list<RenderableParticipant*>();
	std::list<RenderableInteraction*> renderable_interactions_ = std::list<RenderableInteraction*>();
};
