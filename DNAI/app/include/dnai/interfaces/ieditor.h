#ifndef DNAI_INTERFACES_IEDITOR_H
#define DNAI_INTERFACES_IEDITOR_H

#include "icommand.h"
#include "iviewzone.h"
#include "isavable.h"
#include "isolution.h"

namespace dnai
{
	namespace interfaces
	{
		class IEditor : public ISavable
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
			virtual const QList<ICommand *> &actions() const = 0;
			virtual const QObject &selection() const = 0;
			virtual const QList<QObject *> &selections() const = 0;
			virtual const QList<IViewZone *> &views() const = 0;
			virtual const IViewZone &selectedView() const = 0;
			virtual ISolution *solution() const = 0;
		};
	}
}


#endif DNAI_INTERFACES_IEDITOR_H