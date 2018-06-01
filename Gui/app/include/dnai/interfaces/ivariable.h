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
			virtual quint32 varType() const = 0;
			virtual bool setVarType(quint32 id) = 0;

			virtual const QString &value() const = 0;
			virtual bool setValue(const QString &value) = 0;
		};
	}
}

#endif //DNAI_INTERFACES_IVARIABLE_H