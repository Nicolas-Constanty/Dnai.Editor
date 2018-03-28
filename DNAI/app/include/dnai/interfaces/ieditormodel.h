#ifndef DNAI_INTERFACES_IEDITORMODEL_H
#define DNAI_INTERFACES_IEDITORMODEL_H

#include <QAbstractItemModel>
#include "iserializable.h"

namespace dnai
{
	namespace interfaces
	{
		class IEditorModel : public QAbstractItemModel, public ISerializable
		{
			virtual ~IEditorModel() = default;
		};
	}
}

#endif //DNAI_INTERFACES_EDITOR_H