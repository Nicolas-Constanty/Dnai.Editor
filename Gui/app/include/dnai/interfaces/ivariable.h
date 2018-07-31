#ifndef DNAI_INTERFACES_IVARIABLE_H
#define DNAI_INTERFACES_IVARIABLE_H

#include <qisenum.h>
#include <QUuid>

class QJsonObject;

namespace dnai
{
	namespace interfaces
    {
		class IVariable
		{
		public:
			virtual ~IVariable() = default;
            virtual QUuid varType() const = 0;
            virtual bool setVarType(QUuid const &id) = 0;

			virtual const QString &value() const = 0;
			virtual bool setValue(const QString &value) = 0;
		};
	}
}

#endif //DNAI_INTERFACES_IVARIABLE_H
