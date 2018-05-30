#include "dnai/models/gui/flow.h"
#include "dnai/exceptions/notimplemented.h"
#include "dnai/exceptions/exceptionmanager.h"
#include "dnai/editor.h"

namespace dnai
{
	namespace models
	{
		namespace gui
		{
			void Flow::serialize(QJsonObject& obj) const
			{
                Q_UNUSED(obj)
				Editor::instance().notifyError("Flow serialize not implemented", []() {});
			}

			void Flow::_deserialize(const QJsonObject& obj)
			{
				Q_UNUSED(obj)
				Editor::instance().notifyError("Flow not _deserialize implemented", [](){});
			}

			const data::Flow& Flow::data() const
			{
				return m_data;
			}

			bool Flow::setData(const data::Flow& data)
			{
				if (m_data == data)
					return false;
				m_data = data;
				return true;
			}
		}
	}
}
