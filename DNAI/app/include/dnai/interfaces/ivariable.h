#ifndef DNAI_INTERFACES_IVARIABLE_H
#define DNAI_INTERFACES_IVARIABLE_H
#include <qisenum.h>

class QJsonObject;

namespace dnai
{
	namespace interfaces
	{
		class IVariable
		{
		public:
			virtual ~IVariable() = default;
			virtual qint32 varType() const = 0;
			virtual bool setVarType(qint32 id) = 0;

			virtual const QJsonObject &value() const = 0;
			virtual bool setValue(const QJsonObject &value) = 0;
		};
	}
}

#endif //DNAI_INTERFACES_IVARIABLE_H