#ifndef DNAI_INTERFACES_IPROJECT_H
#define DNAI_INTERFACES_IPROJECT_H

#include <QFileInfo>
#include "isavable.h"
#include "iserializable.h"

namespace dnai
{
	namespace interfaces
	{
		class IProject : public ISavable, public ISerializable
		{
		public:
			virtual ~IProject() = default;
			virtual void load(const QString &path) = 0;
			virtual void close() = 0;
			virtual const QString &version() const = 0;
			virtual void setVersion(const QString &version) = 0;
			virtual const QString &fileName() const = 0;
			virtual void setFileName(const QString &name) = 0;
			virtual const QString &name() const = 0;
			virtual void setName(const QString &name) = 0;
			virtual const QString &description() const = 0;
			virtual void setDescription(const QString &desc) = 0;
			virtual const QJsonObject &jsonData() const = 0;
		};
	}
}



#endif //DNAI_INTERFACES_IPROJECT_H