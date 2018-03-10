#ifndef MODEL_VARIABLE_H
#define MODEL_VARIABLE_H

//#include "dnai/models/common.h"
//#include "dnai/models/position.h"
#include "entity.h"

namespace dnai {
	namespace models {
//class Variable: public Common, public Position, virtual public IModel
//{
//public:
//	Variable(qint32 uid, QString const& name, QString const& description, QVector2D const& position, QString const& type,
//	         bool internal, int index, int listindex, QObject* parent = nullptr);
//	virtual ~Variable() = default;
//
//private:
//    QString m_vartype;
//    bool m_internal;
//    //            QVariant value;
//
//public:
//    QString varType() const;
//    void setVarType(const QString &type);
//
//    bool internal() const;
//    void setInternal(bool internal);
//
//
//    // IModel interface
//public:
//	void serialize(QJsonObject &) const override;
//	void declare() const override;
//	const QList<QString>& editableProperties() override;
//
//    // IClone interface
//private:
//    IClone *clone() const override;
//protected:
//	static QList<QString> m_editableProperties;
//
//};
		class VariableCore : public EntityCore
		{
		public:
			std::map<qint32, commands::EntityCommand*> initCommands() const override;
		};

		class AttributeCore : public EntityCore
		{
		public:
			std::map<qint32, commands::EntityCommand*> initCommands() const override;
		};

		union VariableCoreUnion
		{
			VariableCore v;
			AttributeCore a;
            ~VariableCoreUnion() {}
        };
		class Variable : public Entity
		{
		public:
            ~Variable() = default;

			EntityCore* coreModel() const override;
			void setCoreModel(EntityCore* model) override;
		private:
			VariableCoreUnion m_dataCore;
			EntityCore * m_data = nullptr;
		};
	}
}

#endif // MODEL_VARIABLE_H
