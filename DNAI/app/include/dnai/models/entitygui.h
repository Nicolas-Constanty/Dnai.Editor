#ifndef DNAI_MODELS_ENTITYGUI_H
#define DNAI_MODELS_ENTITYGUI_H
#include <QString>
#include <QObject>
#include "ientity.h"

namespace dnai
{
	namespace models
	{
		struct EntityGuiData
		{
			int index;
			int listIndex;
			QString description;

			EntityGuiData& operator=(const EntityGuiData& other) = default;
			bool operator!=(const EntityGuiData& other) const;
			bool operator==(const EntityGuiData& other) const;
		};

		class EntityGUI : public IEntity<EntityGuiData>
		{
			//IEntity implementation
		public:
			const EntityGuiData &data() const override;
			bool setData(const EntityGuiData& data) override;

			int index() const;
			bool setIndex(int index);

			int listIndex() const;
			bool setListIndex(int listIndex);

			const QString &description() const;
			bool setDescription(const QString& description);

		private:
			EntityGuiData m_data;
		};
	}
}

#endif //DNAI_MODELS_ENTITYGUI_H