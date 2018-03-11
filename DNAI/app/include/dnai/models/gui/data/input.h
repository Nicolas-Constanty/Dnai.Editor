#ifndef DNAI_MODELS_GUI_DATA_INPUT_H
#define DNAI_MODELS_GUI_DATA_INPUT_H

#include "variable.h"

namespace dnai
{
	namespace models
	{
		namespace gui
		{
			namespace data
			{
				struct Input : Variable
				{
					QString name;
				};
			}
		}
	}
}

#endif //DNAI_MODELS_GUI_DATA_INPUT_H