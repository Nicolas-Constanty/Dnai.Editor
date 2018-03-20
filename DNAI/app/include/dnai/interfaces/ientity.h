#ifndef DNAI_INTERFACES_IENTITY_H
#define DNAI_INTERFACES_IENTITY_H

#include <QString>

namespace dnai
{
	namespace interfaces
	{
		class IEntity
		{
		public:
			virtual ~IEntity() = default;
			virtual int index() const = 0;
			virtual bool setIndex(int index) = 0;

			virtual int listIndex() const = 0;
			virtual bool setListIndex(int listIndex) = 0;

			virtual bool expanded() const = 0;
			virtual bool setExpanded(bool exp) = 0;

			virtual const QString &description() const = 0;
			virtual bool setDescription(const QString& description) = 0;
		};
	}
}

#endif //DNAI_INTERFACES_IENTITY_H