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
#include "RenderingJob.h"

#include <qpixmap.h>


#include "CImg.h"
#include "Diagram.h"
#include "DiagramParser.h"
#include "RenderableDiagram.h"

using namespace cimg_library;

QPixmap RenderingJob::do_render_diagram(const std::string input)
{
	const auto diagram = DiagramParser::parse(input);

	const auto diagram_width = 1000;
	const auto diagram_height = 1000;

	// draw something, anything :)
	CImg<unsigned char> img(diagram_width, diagram_height, 1, 3);
	CImg<unsigned char>* i = &img;

	// create renderable version of the diagram
	auto renderable_diagram = RenderableDiagram(diagram, i);

	// resize the CImg to fit the diagram
	int hxw[2];
	renderable_diagram.calculate_diagram_size(hxw);

	img.resize(hxw[1], hxw[0], 1, 3);
#ifdef NDEBUG
	// fill white for release build
	img.fill(255);
#else
	// fill grey for debug build
	img.fill(222);
#endif
	

	// draw the diagram to the CImg
	renderable_diagram.draw();

	// put the CImg data in to QImage for the UI
	const QImage image = convert_cimg_to_qimage(i);

	return QPixmap::fromImage(image);
}


auto RenderingJob::convert_cimg_to_qimage(CImg<unsigned char>* img) -> QImage
{
	const auto h = img->height();
	const auto w = img->width();
	QImage image(w, h, QImage::Format_RGB32);

	for (auto y = 0; y < h; y++)
	{
		for (auto x = 0; x < w; x++)
		{
			QColor color(*img->data(x, y, 0, 0), *img->data(x, y, 0, 1), *img->data(x, y, 0, 2));
			image.setPixel(x, y, color.rgb());
		}
	}
	return image;
}
