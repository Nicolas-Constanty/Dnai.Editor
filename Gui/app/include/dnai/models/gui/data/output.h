#ifndef DNAI_MODELS_GUI_DATA_OUTPUT_H
#define DNAI_MODELS_GUI_DATA_OUTPUT_H

#include "variable.h"
#include "linkable.h"

namespace dnai
{
	namespace models
	{
		namespace gui
		{
			namespace data
			{
				struct Output : Variable, Linkable
				{
                    QString name;
                    Output &operator=(const Output &link) = default;
					bool operator!=(const Output &link) const
					{
						return !(*this == link);
                    }
					bool operator==(const Output &link) const
					{
						return (name == link.name && Variable::operator==(link) && Linkable::operator==(link));
					}
				};
			}
		}
	}
}

#endif //DNAI_MODELS_GUI_DATA_OUTPUT_H
