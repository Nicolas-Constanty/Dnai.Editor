#ifndef DNAI_INTERFACES_IEDITORACTION_H
#define DNAI_INTERFACES_IEDITORACTION_H
#include <QString>
#include <utility>
#include "icommand.h"
#include "ieditormodel.h"

namespace dnai
{
	namespace interfaces
	{
		class IEditorAction
		{
		public:
			virtual ~IEditorAction() = default;
			virtual void run() = 0;
		};
	}
}

#endif //DNAI_INTERFACES_IEDITORACTION_H