#include <QJsonArray>

#include "dnai/models/function.h"
#include "dnai/controllers/clientcontroller.h"

namespace dnai {
    namespace models {
		QList<QString> Function::m_editableProperties = {};
        Function::Function(const qint32 uid, QString const &name, QString const &description, QVector2D const &position, int index, int listindex, QObject *parent)
            : Common(uid, name, description, index, listindex, parent), Position(position)
        {
            m_type = ModelTypes::Function;
        }
        
        QList<Variable*> Function::variables() const
        {
            return m_variables;
        }
        
        QList<Input*> Function::inputs() const
        {
            return m_inputs;
        }

        QList<Output*> Function::outputs() const
        {
            return m_outputs;
        }

        QList<Node*> Function::nodes() const
        {
            return m_nodes;
        }

        void Function::addVariable(Variable *model)
        {
            m_variables.push_back(model);
        }

        void Function::addInput(Input *model)
        {
            m_inputs.push_back(model);
        }

        void Function::addOutput(Output *model)
        {
            m_outputs.push_back(model);
        }

        void Function::addNode(Node *model)
        {
            m_nodes.push_back(model);
        }

        void Function::removeVariable(Variable *model)
        {
            m_variables.removeOne(model);
        }

        void Function::removeInput(Input *model)
        {
            m_inputs.removeOne(model);
        }

        void Function::removeOutput(Output *model)
        {
            m_outputs.removeOne(model);
        }

        void Function::removeNode(Node *model)
        {
            m_nodes.removeOne(model);
        }

        void Function::serialize(QJsonObject &obj) const
        {
            Common::serialize(obj);
            Position::serialize(obj);

            QJsonArray variables;
            foreach (const Variable *variable, m_variables) {
                QJsonObject var;
                variable->serialize(var);
                variables.append(var);
            }

            QJsonArray inputs;
            foreach (const Input *input, m_inputs) {
                QJsonObject var;
                input->serialize(var);
                inputs.append(var);
            }

            QJsonArray outputs;
            foreach (const Output *output, m_outputs) {
                QJsonObject var;
                output->serialize(var);
                outputs.append(var);
            }

            QJsonArray nodes;
            foreach (const Node *node, m_nodes) {
                QJsonObject var;
                node->serialize(var);
                nodes.append(var);
            }

            obj["variables"] = variables;
            obj["inputs"] = inputs;
            obj["outputs"] = outputs;
            obj["nodes"] = nodes;
        }

        void Function::declare() const
        {
            controllers::ClientController::shared().sendDeclareEvent(PackageDataCom::ENTITYCORE::FUNCTION, 0, name(), PackageDataCom::VISIBILITYCORE::PUBLIC);
        }

	    const QList<QString>& Function::editableProperties()
	    {
			if (m_editableProperties.empty())
				m_editableProperties += Common::m_editableProperties + Position::m_editableProperties;
			return m_editableProperties;
	    }

	    IClone *Function::clone() const
        {
            return new Function(uid(), name(), description(), position(), index(), listIndex());
        }
    }
}
