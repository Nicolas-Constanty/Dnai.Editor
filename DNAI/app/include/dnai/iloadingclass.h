#ifndef ILOADINGCLASS_H
#define ILOADINGCLASS_H

#include <queue>
#include <map>
#include <functional>
#include <QDebug>

namespace dnai {
class App;
class ILoadingClass
{
public:
    enum Status {
        UNDEFINED = 0,
        RUNNING,
        READY
    };

	float statusPercent() const
	{
		return  m_statusPercent;
	}

	Status status() const
	{
		return  m_status;
	}

	void registerBeforeStart(const std::function<void()>& func)
	{
		m_registeredEvents[Status::UNDEFINED].push(func);
	}

	void registerReady(const std::function<void()>& func)
	{
		m_registeredEvents[Status::READY].push(func);
	}

	void registerUpdateStatus(const std::function<void(float)>& func)
    {
        m_registeredEvents[Status::RUNNING].emplace(std::bind(func, std::bind(&ILoadingClass::statusPercent, this)));
	}

protected:
    ILoadingClass() : m_statusPercent(0), m_status(Status::UNDEFINED)
	{
	}
    virtual std::queue<std::function<void()>> init() = 0;

	void execAllEvent()
	{
		auto events = m_registeredEvents[m_status];
		while (!events.empty())
		{
			events.back()();
			events.pop();
		}
	}

public:
	virtual ~ILoadingClass() = default;

    void load()
    {
		auto funcs = init();
		const auto count = funcs.size();
        auto i = 0.f;
		execAllEvent();
		m_status = Status::RUNNING;
		execAllEvent();
		while (!funcs.empty())
        {
			funcs.front()();
			funcs.pop();
			++i;
			m_statusPercent = i / count;
			execAllEvent();
		}
		m_status = Status::READY;
		execAllEvent();
	}

private:
    float m_statusPercent;
    Status m_status;
    std::map<Status, std::queue<std::function<void()>>> m_registeredEvents;
};
}


#endif // ILOADINGCLASS_H
