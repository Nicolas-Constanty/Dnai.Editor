#ifndef DNAI_MODELS_GUI_DATA_IOLINK
#define DNAI_MODELS_GUI_DATA_IOLINK
#include <QString>
#include <QUuid>

namespace dnai
{
	namespace models
	{
		namespace gui
		{
			namespace data
			{
				struct IoLink
				{
					QString inputName;
					QString outputName;

					QUuid inputUuid;
					QUuid outputUuid;

					IoLink &operator=(const IoLink &other) = default;
					bool operator!=(const IoLink& other) const
					{
						return !(*this == other);
					}
					bool operator==(const IoLink& other) const
					{
						return (
							inputName == other.inputName &&
							outputName == other.outputName &&
							inputUuid == other.inputUuid &&
							outputUuid == other.outputUuid
							);
					}
				};
			}
		}
	}
}

#endif //DNAI_MODELS_GUI_DATA_IOLINK