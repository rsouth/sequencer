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

	auto render(RenderingJob rendering_job) -> void;

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
