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
		class IController
		{
		public:
			virtual QList<QQuickItem*> views() const = 0;
			virtual QQuickItem *createView() = 0;

		protected:
			virtual commands::ICommand *createCommand() = 0;
		};
		template <class T>
		class AController : public IController, public models::IClone
		{
		public:
			explicit AController(const QString& view): m_createCommand(nullptr)
			{
                m_viewPath = view;
			}

			virtual ~AController() = default;

		public:
			T *model() const
			{
				return m_model;
			}

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
				m_createCommand = createCommand();
				commands::CommandManager::Instance()->exec(m_createCommand);
				if (m_model)
					delete m_model;
				m_model = model;
			}

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
