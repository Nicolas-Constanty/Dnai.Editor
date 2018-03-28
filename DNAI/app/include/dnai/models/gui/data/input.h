#ifndef DNAI_MODELS_GUI_DATA_INPUT_H
#define DNAI_MODELS_GUI_DATA_INPUT_H

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
				struct Input : Variable, Linkable
				{
					QString name;
					Input &operator=(const Input &link) = default;
					bool operator!=(const Input &link) const
					{
						return !(*this == link);
					}
					bool operator==(const Input &link) const
					{
						return (name == link.name && Variable::operator==(link) && Linkable::operator==(link));
					}
				};
			}
		}
	}
}

#endif //DNAI_MODELS_GUI_DATA_INPUT_H