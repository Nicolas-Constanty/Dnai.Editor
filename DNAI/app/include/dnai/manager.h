#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include "project.h"
//#include "models/treemodel.h"
//#include "models/treeitem.h"
#include "models/user.h"
//#include "models/declarationmodel.h"
#include "models/basicnodemodel.h"
#include "views/layout.h"
#include "api.h"
#include "session.h"
#include "dnai/viewshandler.h"

namespace dnai {
	class App;
    class Manager: public QObject
    {
        Q_OBJECT
        Q_PROPERTY(dnai::Session *session READ session CONSTANT)
        Q_PROPERTY(dnai::ViewsHandler *views READ views CONSTANT)
        Q_PROPERTY(dnai::Project *project READ project WRITE setProject NOTIFY projectChanged)
    public:
	    explicit Manager(QObject *parent = 0);
        virtual ~Manager();

        Project *project() const;
		void setProject(Project *p);

        static const QString project_extension;

    private:
        void createTreeModel(Project *project);
        Project *m_project;

	signals:
		void projectChanged(Project *p);

    public:
//        Q_INVOKABLE void createProject(const QString &, const QString &, const QString &);
//        Q_INVOKABLE QJsonObject loadProjectData(const QString &);
//        Q_INVOKABLE void openProject(const QString &);
//        Q_INVOKABLE void openProject(Project *);
	    Q_INVOKABLE void setAppViewLayout(dnai::views::Layout* l) const;
		Q_INVOKABLE void createNode(QObject *nodeModel);
        Q_INVOKABLE bool isMac();

    public:
        Session *session() const;
        ViewsHandler *views() const;

    private:
		ViewsHandler *m_viewsHandler;
    };
    }

#endif // MANAGER_H
