#ifndef DNAI_MODELS_GUI_LINKABLEDATA_H
#define DNAI_MODELS_GUI_LINKABLEDATA_H

#include <QUuid>

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
					/*QString id;
					QString linkedId;*/
					QUuid id;
					QUuid linkedId;

					Linkable &operator=(const Linkable &link) = default;
					bool operator!=(const Linkable &link) const
					{
						return !(*this == link);
					}
					bool operator==(const Linkable &link) const
					{
						return (id == link.id && linkedId == link.linkedId);
					}
				};
			}
		}
	}
}

#endif //