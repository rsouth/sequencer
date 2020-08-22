#pragma once

#include <qpixmap.h>

#include "CImg.h"


class RenderingJob
{
public:

	RenderingJob(QObject*, std::string input_text) : input_text_(input_text) { }

	/* call render_diagram when thread runs */
	QPixmap render_diagram()
	{
		return do_render_diagram(input_text_);
	}


signals:
	void update_gui_diagram(QPixmap& image_data);

private:
	std::string input_text_;

	static auto convert_cimg_to_qimage(cimg_library::CImg<unsigned char>* img) -> QImage;

	auto do_render_diagram(std::string input) -> QPixmap;
};
