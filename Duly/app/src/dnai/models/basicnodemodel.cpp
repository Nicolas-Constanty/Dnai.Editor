#include "dnai/models/basicnodemodel.h"

namespace dnai {
namespace models {
BasicNodeModel::BasicNodeModel(QObject *parent) : QObject(parent)
{
    m_engine = static_cast<dnai::DulyApp *>(dnai::DulyApp::instance())->engine();
    loadCurrentModel();
}

void BasicNodeModel::loadCurrentModel()
{
    setQmlPaths(":/resources/Nodes");
    instantiateComponents();

}

void BasicNodeModel::instantiateComponents()
{

}

void BasicNodeModel::instantiateComponent(const QString &path)
{
    if (m_engine)
    {
        const auto component = new QQmlComponent(m_engine, path);
        qmlresources::QInstructionID::Instruction_ID idx = static_cast<qmlresources::QInstructionID::Instruction_ID>(component->property("instruction_id").toInt());
        m_components[idx] << component;
    }
    else {
        qWarning() << "Engine must be initialize before calling instantiateComponent(const QString &path)";
    }
}

void BasicNodeModel::setQmlPaths(const QString &path)
{
    QDirIterator it(path, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        QString filename = it.fileName();
        if (it.fileInfo().isFile()
                && filename != "NodeModel.qml"
                && filename != "UnaryOperatorModel.qml"
                && filename != "BinaryOperatorModel.qml"
                && filename != "LogicalNodeModel.qml")
        {
            m_qmlpaths[it.fileInfo().dir().dirName()] << it.filePath();
        }
        it.next();
    }
}
}
}
