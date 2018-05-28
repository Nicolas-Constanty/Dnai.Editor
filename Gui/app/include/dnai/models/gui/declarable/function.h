#ifndef DNAI_MODELS_GUI_DECLARABLE_FUNCTION_H
#define DNAI_MODELS_GUI_DECLARABLE_FUNCTION_H

#include <QObject>
#include <QAbstractListModel>

#include "dnai/interfaces/ientity.h"
#include "dnai/interfaces/iinstruction.h"
#include "dnai/models/gui/data/function.h"

namespace dnai
{
	namespace models
	{
		namespace gui
		{
			namespace declarable
			{
				class Function : public QObject, public interfaces::IInstruction, public Entity<data::Function, Function>
                {
					Q_OBJECT
					Q_PROPERTY(QList<models::gui::Input*> inputs READ inputs WRITE setInputs NOTIFY inputsChanged)
					Q_PROPERTY(QList<models::gui::Output*> outputs READ outputs WRITE setOutputs NOTIFY outputsChanged)

				public:
					explicit Function(QObject *parent = nullptr);
					//Implementation of ISerializable
					void serialize(QJsonObject& obj) const override;
				protected:
					void _deserialize(const QJsonObject& obj) override;

				public:
					//Implementation of IInstruction
					QList<models::gui::Input*> inputs() const override;
					bool setInputs(const QList<models::gui::Input*>& inputs) override;
					QList<models::gui::Output*> outputs() const override;
					bool setOutputs(const QList<models::gui::Output*>& outputs) override;
					models::gui::Flow* flowIn() const override;
					bool setFlowIn(models::gui::Flow* flow) override;
					models::gui::Flow* flowOut() const override;
					bool setFlowOut(models::gui::Flow* flow) override;

					Q_INVOKABLE void addInput(const QString &name, qint32 varType);
					Q_INVOKABLE void addOutput(const QString &name, qint32 varType);
					Q_INVOKABLE void removeInput(const QString &name);
					Q_INVOKABLE void removeOutput(const QString &name);

					Q_INVOKABLE void moveInputUp(int index);
					Q_INVOKABLE void moveOutputUp(int index);

					Q_INVOKABLE void moveInputDown(int index);
					Q_INVOKABLE void moveOutputDown(int index);


				signals:
					void inputsChanged(const QList<models::gui::Input*>& inputs);
					void outputsChanged(const QList<models::gui::Output*>& outputs);

				};
			}
		}
	}
}

#endif //DNAI_MODELS_GUI_DECLARABLE_FUNCTION_H
