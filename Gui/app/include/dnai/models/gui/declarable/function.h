#ifndef DNAI_MODELS_GUI_DECLARABLE_FUNCTION_H
#define DNAI_MODELS_GUI_DECLARABLE_FUNCTION_H

#include <QObject>
#include <QAbstractListModel>
#include <QVariant>

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
				class FunctionInputs : public QAbstractListModel
				{
					Q_OBJECT
					
				public:
					FunctionInputs(QObject *parent = nullptr) : QAbstractListModel(parent), m_list(nullptr)
					{
					}
					enum Roles {
						Name = Qt::UserRole + 1,
						Type
					};
					explicit FunctionInputs(QList<models::gui::Input*> *);
					int rowCount(const QModelIndex& parent) const override;
					QVariant data(const QModelIndex& index, int role) const override;
					void add(const QString &name, qint32 varType);
					void moveUp(int index);
					void moveDown(int index);
					void remove(const QString &name);
					bool setData(const QModelIndex& index, const QVariant& value, int role) override;
					bool setData(int index, const QVariant& value, int role);

				private:
					QList<models::gui::Input*> *m_list;
					QHash<int, QByteArray> roleNames() const override;

				};

				class FunctionOutputs : public QAbstractListModel
				{
					Q_OBJECT
					
				public:
					FunctionOutputs(QObject *parent = nullptr) : QAbstractListModel(parent), m_list(nullptr)
					{
					}
					enum Roles {
						Name = Qt::UserRole + 1,
						Type
					};
					explicit FunctionOutputs(QList<models::gui::Output*> *);
					int rowCount(const QModelIndex& parent) const override;
					QVariant data(const QModelIndex& index, int role) const override;
					void add(const QString &name, qint32 varType);
					void moveUp(int index);
					void moveDown(int index);
					void remove(const QString &name);

					bool setData(const QModelIndex& index, const QVariant& value, int role) override;
					bool setData(int index, const QVariant& value, int role);

				private:
					QList<models::gui::Output*> *m_list;
					QHash<int, QByteArray> roleNames() const override;

				};
				class Function : public QObject, public interfaces::IInstruction, public Entity<data::Function, Function>
                {
					Q_OBJECT
					Q_PROPERTY(FunctionInputs *inputModels READ inputModels WRITE setInputModels NOTIFY inputModelsChanged)
					Q_PROPERTY(FunctionOutputs *outputModels READ outputModels WRITE setOutputModels NOTIFY outputModelsChanged)
				public:
					explicit Function(QObject *parent = nullptr);
					//Implementation of ISerializable
					void serialize(QJsonObject& obj) const override;
				protected:
					void _deserialize(const QJsonObject& obj) override;

				public:
					//Implementation of IInstruction
					const QList<models::gui::Input*> &inputs() const override;
					bool setInputs(const QList<models::gui::Input*>& inputs) override;
					const QList<models::gui::Output*> &outputs() const override;
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

					Q_INVOKABLE void updateInputName(int index, const QString &name);
					Q_INVOKABLE void updateInputVarType(int index, qint32 varType);

					Q_INVOKABLE void updateOutputName(int index, const QString &name);
					Q_INVOKABLE void updateOutputVarType(int index, qint32 varType);

					FunctionInputs *inputModels() const;
					FunctionOutputs *outputModels() const;
					void setInputModels(FunctionInputs* inputs);
					void setOutputModels(FunctionOutputs* outputs);

				signals:
					void inputModelsChanged(FunctionInputs* inputs);
					void outputModelsChanged(FunctionOutputs* outputs);

				private:
					FunctionInputs *m_finputs;
					FunctionOutputs *m_foutputs;
				};
			}
		}
	}
}

#endif //DNAI_MODELS_GUI_DECLARABLE_FUNCTION_H
