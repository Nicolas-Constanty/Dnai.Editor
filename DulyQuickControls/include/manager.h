#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include "project.h"

namespace duly_gui {
    class Manager: public QObject
    {
        Q_OBJECT
    public:
        Manager(QObject *parent = 0);
        virtual ~Manager();

        static const QString project_extension;

    private:
        Project *m_project;

    public:
        Q_INVOKABLE void createProject(const QString &, const QString &, const QString &);
        Q_INVOKABLE void loadProject(const QString &);
    };
}

#endif // MANAGER_H
