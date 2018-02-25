#ifndef ICONTROLLER_H
#define ICONTROLLER_H

#include "dnai/app.h"
#include "dnai/commands/icommand.h"
#include "dnai/commands/commandmanager.h"

namespace dnai
{
	namespace controllers
	{
		class IController
		{
		public:
			virtual ~IController() = default;
			virtual QList<QQuickItem*> views() const = 0;
			virtual QQuickItem *createView() = 0;

		protected:
			virtual commands::ICommand *createCommand() = 0;
		};
        template <class T, class U = void>
		class AController : public IController, public models::IClone
		{
            using Fun = typename std::conditional<std::is_void<void>::value, void *, U>::type;
		public:
			explicit AController(const QString& view): m_createCommand(nullptr)
			{
                m_viewPath = view;
			}

			explicit AController(const AController& controller)
			{
				*this = controller;
			}

			AController& operator=(const AController& other)
			{
				if (&other == this)
					return *this;
				this->m_model = other.model();
//				this->m_createCommand = other.createCommand();
				this->m_viewPath = other.path();
				this->m_views = other.views();
				return *this;
			}

			virtual ~AController() = default;

		public:
			T *model() const
			{
				return m_model;
			}

			void setModel(T *m)
			{
				if (m == m_model) return;
				m_model = m;
			}

			const QString &path() const { return m_viewPath;  }

			QList<QQuickItem*> views() const override
			{
				return m_views;
			}

			void addViewToCurrentContext()
			{
				m_views.append(createView());
			}

            virtual void asyncCreate(T* model)
			{
                if (model == nullptr)
                    return;
				m_createCommand = createCommand();
				commands::CommandManager::Instance()->exec(m_createCommand);
				if (m_model)
					delete m_model;
				m_model = model;
			}

            virtual bool create(Fun)
        	{
                addViewToCurrentContext();
                return false;
            }

		protected:
			T *m_model;
			commands::ICommand *m_createCommand;
			QList<QQuickItem *> m_views;
			QString m_viewPath;
		};
	}
}

#endif
