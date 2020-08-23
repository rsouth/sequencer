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
