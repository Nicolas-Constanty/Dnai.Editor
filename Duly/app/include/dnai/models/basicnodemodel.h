#ifndef BASICNODEMODEL_H
#define BASICNODEMODEL_H

#include <QObject>
#include <QMap>
#include <QDebug>
#include <QDirIterator>
#include <QQmlComponent>

#include "dnai/dulyapp.h"
#include "dnai/qmlresources/instructionid.h"

namespace dnai {
namespace models {
class BasicNodeModel : public QObject
{
    Q_OBJECT
public:
    BasicNodeModel(QObject *parent = nullptr);

private:
    void loadCurrentModel();
    void instantiateComponents();
    void instantiateComponent(const QString &path);
    void setQmlPaths(const QString &path);

private:
    QMap<QString, QStringList> m_qmlpaths;
    QMap<qmlresources::QInstructionID::Instruction_ID, QList<QQmlComponent *>> m_components;
};
}
}

#endif // BASICNODEMODEL_H
