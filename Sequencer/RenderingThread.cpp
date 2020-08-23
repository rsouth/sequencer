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
#include "RenderingThread.h"

RenderingThread::RenderingThread(QObject* parent) : QThread(parent)
{
}

auto RenderingThread::render(RenderingJob rendering_job) -> void
{
	push(rendering_job);
	if (!isRunning())
	{
		qDebug() << " starting thread";
		start(LowPriority);
	}
}

auto RenderingThread::push(RenderingJob const& value) -> void
{
	{
		std::scoped_lock<std::mutex> lock(this->d_mutex);
		d_queue.push_front(value);
	}
	this->d_condition.notify_one();
}

auto RenderingThread::pop() -> RenderingJob
{
	std::unique_lock<std::mutex> lock(this->d_mutex);
	this->d_condition.wait(lock, [=] { return !this->d_queue.empty(); });
	auto rc(std::move(this->d_queue.back()));
	this->d_queue.pop_back();
	return rc;
}
