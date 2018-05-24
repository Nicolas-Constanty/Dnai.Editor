#ifndef DNAI_ENUMS_GUITYPES_H
#define DNAI_ENUMS_GUITYPES_H
#include <qisenum.h>

namespace dnai
{
	namespace enums
	{
		/**
		 * \brief List of available type for gui model
		 */
		enum GUI_TYPE : qint32
		{
			UNDEFINED = -1,
			PROJECT,
			CONTEXT,
			CLASS,
			FUNCTION,
			VARIABLE,
			FLOW,
			INPUT,
			OUTPUT
		};
	}
}

#endif //DNAI_ENUMS_GUITYPES_H