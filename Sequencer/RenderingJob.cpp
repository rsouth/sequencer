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
	img.fill(222); // 255 for white...

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
