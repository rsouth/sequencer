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

#include "qpixmap.h"
#include "qpainter.h"


#include "Diagram.h"
#include "DiagramParser.h"
#include "RenderableDiagram.h"


const QPixmap RenderingJob::do_render_diagram(const std::string& input) const
{
	const auto diagram = DiagramParser::parse(input);
	
	QPixmap* temp_pixmap = new QPixmap(1000, 1000);
	QPainter* temp_painter = new QPainter(temp_pixmap);

	RenderableDiagram renderable_diagram(diagram, temp_painter);
	int hxw[2];
	renderable_diagram.calculate_diagram_size(hxw);


	QPixmap* pix = new QPixmap(hxw[0], hxw[1]);
	QPainter* paint = new QPainter(pix);
	RenderableDiagram renderable(diagram, paint);

#ifdef NDEBUG
	// fill white for release build
	QColor background(Qt::GlobalColor::white);
#else
	// fill grey for debug build
	QColor background(Qt::GlobalColor::lightGray);
#endif

	paint->fillRect(pix->rect(), Qt::BrushStyle::SolidPattern);

	pix->fill(background);

	renderable.draw();

	return *pix;
}
