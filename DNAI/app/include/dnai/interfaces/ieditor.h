#ifndef DNAI_INTERFACES_IEDITOR_H
#define DNAI_INTERFACES_IEDITOR_H

#include <QList>
#include "icommand.h"
#include "isingleton.h"
#include "iviewzone.h"
#include "isavable.h"
#include "isolution.h"

namespace dnai
{
	namespace interfaces
	{
		template<class T>
		class IEditor : public ISingleton<T>, public ISavable
		{
		protected:
			IEditor() = default;

		public:
			IEditor(IEditor const&) = delete;             // Copy construct
			IEditor(IEditor&&) = delete;                  // Move construct
			IEditor& operator=(IEditor const&) = delete;  // Copy assign
			IEditor& operator=(IEditor &&) = delete;      // Move assign
			virtual ~IEditor() = default;
			virtual const QString &version() const = 0;
			virtual void setVersion(const QString &version) = 0;
			virtual void restoreViewState(const QJsonObject &obj) = 0;
			virtual void saveViewState() = 0;
			virtual void openSolution(const QString &filename) = 0;
			virtual void closeSolution() = 0;
			virtual const QList<ICommand *> &getActions() const = 0;
			virtual const QObject &getSelection() const = 0;
			virtual const QList<QObject *> &getSelections() const = 0;
			virtual const QList<IViewZone *> &getViews() const = 0;
			virtual const IViewZone &getSelectedView() const = 0;
			virtual const ISolution &getSolution() const = 0;
		};
	}
}


#endif DNAI_INTERFACES_IEDITOR_H