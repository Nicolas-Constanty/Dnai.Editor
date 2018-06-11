#ifndef DNAI_MODELS_GUI_DATA_FLOWLINK_H
#define DNAI_MODELS_GUI_DATA_FLOWLINK_H
#include <QUuid>

namespace dnai
{
	namespace models
	{
		namespace gui
		{
			namespace data
			{
				struct FlowLink
				{
					QUuid from;
					QUuid to;
					quint32 outIndex;

					FlowLink &operator=(const FlowLink &other) = default;
					bool operator!=(const FlowLink& other) const
					{
						return !(*this == other);
					}
					bool operator==(const FlowLink& other) const
					{
						return (
							from == other.from &&
							to == other.to &&
							outIndex == other.outIndex
							);
					}
				};
			}
		}
	}
}

#endif //DNAI_MODELS_GUI_DATA_FLOWLINK_H