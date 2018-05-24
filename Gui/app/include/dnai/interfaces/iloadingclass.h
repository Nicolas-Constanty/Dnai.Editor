#ifndef DNAI_INTERFACES_ILOADINGCLASS_H
#define DNAI_INTERFACES_ILOADINGCLASS_H

#include <queue>
#include <map>
#include <functional>

namespace dnai {
class App;
    namespace interfaces {
	    /**
         * \brief You can use this class in order to display the loading status or call a callback before, after each step or/and after all step
         */
        class ILoadingClass
        {
        public:
	        /**
             * \brief Possible status of ILoading class
             */
            enum Status {
                UNDEFINED = 0,
                RUNNING,
                READY
            };

	        /**
             * \brief Return the current status in percentage
             * \return float
             */
            float statusPercent() const
            {
                return  m_statusPercent;
            }

	        /**
             * \brief Return the current status
             * \return Status
             */
            Status status() const
            {
                return  m_status;
            }

	        /**
             * \brief Register a callback wich will be called before starting loading
             * \param func 
             */
            void registerBeforeStart(const std::function<void()>& func)
            {
                m_registeredEvents[Status::UNDEFINED].push(func);
            }
			/**
			* \brief Register a callback wich will be called after object was loaded
			* \param func
			*/
            void registerReady(const std::function<void()>& func)
            {
                m_registeredEvents[Status::READY].push(func);
            }
			/**
			* \brief Register a callback wich will be called each step of the loading. This function pass loading percentage at the callback function
			* \param func
			*/
            void registerUpdateStatus(const std::function<void(float)>& func)
            {
                m_registeredEvents[Status::RUNNING].emplace(std::bind(func, std::bind(&ILoadingClass::statusPercent, this)));
            }

        protected:
            ILoadingClass() : m_statusPercent(0), m_status(Status::UNDEFINED)
            {
            }
	        /**
             * \brief You need to implement this function in order to define the loading steps
             * \return 
             */
            virtual std::queue<std::function<void()>> init() = 0;

	        /**
             * \brief Execute all register callback of the current state
             */
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

	        /**
             * \brief Call this function in order to load the current object
             */
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
}


#endif // ILOADINGCLASS_H
