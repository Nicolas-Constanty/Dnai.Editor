#ifndef DNAI_MODELS_GUI_DATA_FLOW_H
#define DNAI_MODELS_GUI_DATA_FLOW_H

#include "dnai/models/gui/data/linkable.h"

namespace dnai
{
	namespace models
	{
		namespace gui
		{
			namespace data
			{
				struct Flow : Linkable
				{
					Flow &operator=(const Flow &link) = default;
					bool operator!=(const Flow &link) const
					{
						return !(*this == link);
					}
					bool operator==(const Flow &link) const
					{
						return Linkable::operator==(link);
					}
				};
			}
		}
	}
}

#endif //DNAI_MODELS_GUI_DATA_FLOW_H