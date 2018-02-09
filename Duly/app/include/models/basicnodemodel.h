#ifndef BASICNODEMODEL_H
#define BASICNODEMODEL_H

#include <QObject>
#include <QMap>
#include <QDebug>
#include <QDirIterator>
#include <QQmlComponent>

#include "dulyapp.h"
#include "qmlresources/instructionid.h"

namespace duly_gui {
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
    QQmlApplicationEngine *m_engine;

};
}
}

#endif // BASICNODEMODEL_H
