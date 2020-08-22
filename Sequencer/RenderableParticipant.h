#pragma once

#include "Participant.h"
#include "RenderingUtils.h"

namespace cimg_library
{
	template <typename T>
	struct CImg;
}


class RenderableParticipant
{
public:
	RenderableParticipant(Participant participant, RenderingUtils* rendering_utils,
	                      cimg_library::CImg<unsigned char>* img);

	void draw(int header_y_offset, int total_interactions);
	int calculate_width();

private:

	Participant participant_;
	RenderingUtils* rendering_utils_;
	cimg_library::CImg<unsigned char>* img_;

	int get_participant_x();

	unsigned int font_height_ = 23;
};
