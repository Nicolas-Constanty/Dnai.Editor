#include <QDirIterator>

#include "dnai/app.h"
#include "dnai/models/basicnodemodel.h"

namespace dnai {
namespace models {
	BasicNodeModel::BasicNodeModel(QObject *parent) : QAbstractListModel(parent)
    {
        loadCurrentModel();
    }

	int BasicNodeModel::rowCount(const QModelIndex&) const
	{
		return m_nodes.count();
	}

	QVariant BasicNodeModel::data(const QModelIndex& index, int role) const
	{
        if (role == NodeCategories::NODE_MODELS)
            return QVariant::fromValue(m_nodes.values().at(index.row()));
		if (role == NodeCategories::NAME)
            return QVariant::fromValue(m_nodes.keys().at(index.row()));
		return QVariant();
	}

	QObject* BasicNodeModel::createNode(enums::QInstructionID::Instruction_ID nodeId) const
	{
        return m_components[nodeId]->create();
    }

    BasicNodeModel::~BasicNodeModel()
    {
        auto map = m_nodes.toStdMap();
        map.erase(map.begin(), map.end());
        qDebug() << "~" << "BasicNodeModel";
    }

	QHash<int, QByteArray> BasicNodeModel::roleNames() const
	{
		QHash<int, QByteArray> roles;
		roles[NodeCategories::NODE_MODELS] = "nodeModels";
        roles[NodeCategories::NAME] = "name";
		return roles;
	}

	void BasicNodeModel::loadCurrentModel()
{
    setQmlPaths(":/resources/Nodes");
    instantiateComponents();

}

void BasicNodeModel::instantiateComponents()
{
    QMap<QString, QStringList>::const_iterator qmlpath = m_qmlpaths.constBegin();
    while (qmlpath != m_qmlpaths.constEnd()) {
        for (const auto& node : qmlpath.value())
        {
            instantiateComponent(qmlpath.key(), "qrc" + node);
        }
		++qmlpath;
    }
}

void BasicNodeModel::instantiateComponent(const QString &category, const QString &path)
{
    const auto component = new QQmlComponent(App::getEngineInstance(), QUrl(path));
	if (!m_nodes.contains(category))
		m_nodes[category] = new ListNode();
	const auto obj = component->create();
    *m_nodes[category] << obj;
	m_components[static_cast<dnai::enums::QInstructionID::Instruction_ID>(obj->property("instruction_id").toInt())] = component;
}

void BasicNodeModel::setQmlPaths(const QString &path)
{
    QDirIterator it(path, QDirIterator::Subdirectories);
    while (it.hasNext()) {
	    const auto filename = it.fileName();
        if (it.fileInfo().isFile()
                && filename != "NodeModel.qml"
                && filename != "UnaryOperatorModel.qml"
                && filename != "BinaryOperatorModel.qml"
                && filename != "LogicalNodeModel.qml")
        {
			if (it.fileInfo().dir().dirName() == "Logical")
				m_qmlpaths["BinaryOperator" + it.fileInfo().dir().dirName()] << it.filePath();
			else
				m_qmlpaths[it.fileInfo().dir().dirName()] << it.filePath();
        }
        it.next();
    }
}
}
}
