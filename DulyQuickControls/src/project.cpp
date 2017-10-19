#include "project.h"
#include <QDebug>

namespace duly_gui {
    Project::Project(const QString &name, const QString &path): _name(name), _path(path)
    {

    }

    Project::~Project()
    {

    }

    //Project *Project::create(const QString &name, const QString &path)
    //{
    //    qDebug() << name << " - " << path;
    //}

    //Project *Project::load(const QString &path)
    //{
    //    qDebug() << path;
    //}

    void    Project::save()
    {

    }
}
