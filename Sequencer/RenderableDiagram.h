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
