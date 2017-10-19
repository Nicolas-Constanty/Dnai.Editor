#include "manager.h"
#include <QDebug>

namespace duly_gui {
    Manager::Manager(QObject *parent): QObject(parent)
    {

    }

    Manager::~Manager()
    {

    }

    void Manager::createProject(const QString &name, const QString &path)
    {
        qDebug() << name << " - " << path;
    }

    void Manager::loadProject(const QString &path)
    {
        qDebug() << path;
    }
}
