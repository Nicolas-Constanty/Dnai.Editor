#ifndef DNAI_MODELS_GUI_DATA_OUTPUT_H
#define DNAI_MODELS_GUI_DATA_OUTPUT_H

#include "variable.h"

namespace dnai
{
	namespace models
	{
		namespace gui
		{
			namespace data
			{
				struct Output : Variable
				{
					QString name;
				};
			}
		}
	}
}

#endif //DNAI_MODELS_GUI_DATA_OUTPUT_H