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
