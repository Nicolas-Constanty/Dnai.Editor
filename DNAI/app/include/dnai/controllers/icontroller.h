#ifndef ICONTROLLER_H
#define ICONTROLLER_H

#include "dnai/app.h"
#include "dnai/commands/icommand.h"
#include "replies.h"
#include "dnai/commands/commandmanager.h"

namespace dnai
{
	namespace controllers
	{
		template <class T>
		class IController
		{
		public:
			explicit IController(const QString& view): m_createCommand(nullptr)
			{
                m_viewPath = view;
			}

			virtual ~IController()
			{
			}

		public:
			T *model() const
			{
				return m_model;
			}

			QList<QQuickItem*> views() const
			{
				return m_views;
			}

			void addViewToCurrentContext()
			{
				m_views.append(createView());
			}

            virtual void asyncCreate(T* model)
			{
				commands::CommandManager::Instance()->exec(m_createCommand);
				if (m_model)
					delete m_model;
				m_model = model;
			}

			virtual QQuickItem *createView() = 0;

		protected:
			T *m_model;
			commands::ICommand *m_createCommand;
			QList<QQuickItem *> m_views;
			QString m_viewPath;

		protected:
			virtual bool create(Reply::EntityDeclared const &reply) = 0;

		};
	}
}

#endif
