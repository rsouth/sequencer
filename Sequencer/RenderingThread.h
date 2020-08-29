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

#include <mutex>
#include <qaccessible.h>
#include <qthread.h>
#include <queue>

#include "RenderingJob.h"

class RenderingThread final : public QThread
{
Q_OBJECT

public:
	explicit RenderingThread(QObject* parent = nullptr);

	auto render(const RenderingJob& rendering_job) -> void;

	auto push(RenderingJob const& value) -> void;

	auto pop() -> RenderingJob;

signals:
	void render_completed(const QPixmap& image);

protected:
	void run() override
	{
		while (!isInterruptionRequested())
		{
			auto job = pop();
			emit render_completed(job.render_diagram());
		}
	}

private:
	std::mutex d_mutex;
	std::condition_variable d_condition;
	std::deque<RenderingJob> d_queue;
};
