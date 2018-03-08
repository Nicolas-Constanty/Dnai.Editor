#include "dnai/models/variable.h"
#include "dnai/controllers/clientcontroller.h"

namespace dnai {
    namespace models {
		/*QList<QString> Variable::m_editableProperties = {};
        Variable::Variable(const qint32 uid, QString const &name, QString const &description, QVector2D const &position,
                           QString const &type, bool internal, int index, int listindex,
                           QObject *parent)
            : Common(uid, name, description, index, listindex, parent), Position(position), m_vartype(type), m_internal(internal)
        {
            m_type = ModelTypes::Variable;
        }

        QString Variable::varType() const
        {
            return m_vartype;
        }
        
        void Variable::setVarType(const QString &type)
        {
            m_vartype = type;
        }
        
        bool Variable::internal() const
        {
            return m_internal;
        }
        
        void Variable::setInternal(bool internal)
        {
            m_internal = internal;
        }

        void Variable::serialize(QJsonObject &obj) const
        {
            Common::serialize(obj);
            Position::serialize(obj);
            obj["type"] = m_type;
            obj["internal"] = m_internal;
        }

        void Variable::declare() const
        {
            controllers::ClientController::shared().sendDeclareEvent(PackageDataCom::ENTITYCORE::VARIABLE, 0, name(), PackageDataCom::VISIBILITYCORE::PUBLIC);
        }

	    const QList<QString>& Variable::editableProperties()
	    {
			if (m_editableProperties.empty())
                m_editableProperties += QList<QString>{ "type", "internal" } + Common::editableProperties() + Position::editableProperties();
            return m_editableProperties;
	    }

	    IClone *Variable::clone() const
        {
            return new Variable(uid(), name(), description(), position(), varType(), internal(), index(), listIndex());
        }*/

	    std::map<qint32, commands::EntityCommand*> VariableCore::initCommands() const
	    {
			auto map = EntityCore::initCommands();
			map[enums::core::COMMANDS::SET_VARIABLE_VALUE] = new commands::EntityCommand();
			map[enums::core::COMMANDS::GET_VARIABLE_VALUE] = new commands::EntityCommand();
			map[enums::core::COMMANDS::SET_CONTEXT_PARENT] = new commands::EntityCommand();
			return map;
	    }

	    std::map<qint32, commands::EntityCommand*> AttributeCore::initCommands() const
	    {
			auto map = EntityCore::initCommands();
			map[enums::core::ADD_CLASS_ATTRIBUTE] = new commands::EntityCommand();
			map[enums::core::RENAME_CLASS_ATTRIBUTE] = new commands::EntityCommand();
			map[enums::core::REMOVE_CLASS_ATTRIBUTE] = new commands::EntityCommand();
            return map;
	    }

	    EntityCore* Variable::coreModel() const
	    {
			return m_data;
	    }

	    void Variable::setCoreModel(EntityCore* model)
	    {
			if (model->entityType() == enums::core::ENTITY::DATA_TYPE)
			{
                if (model->id() == -1)
				{
					m_data = &m_dataCore.a;
				}
				else
				{
					m_data = &m_dataCore.v;
				}
			}
			else
				qDebug() << "BAD TYPE";
	    }
    }
}
