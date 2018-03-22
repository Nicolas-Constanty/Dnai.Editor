#ifndef DNAI_MODELS_GUI_LINKABLEDATA_H
#define DNAI_MODELS_GUI_LINKABLEDATA_H
#include <QString>

namespace dnai
{
	namespace models
	{
		namespace gui
		{
			namespace data
			{
				struct Linkable
				{
					QString in;
					QString out;

					Linkable &operator=(const Linkable &link) = default;
					bool operator!=(const Linkable &link) const
					{
						return !(*this == link);
					}
					bool operator==(const Linkable &link) const
					{
						return (in == link.in && out == link.out);
					}
				};
			}
		}
	}
}

#endif //