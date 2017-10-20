#ifndef PROJECT_H
#define PROJECT_H

#include <QString>
#include <QJsonObject>
#include "models/class.h"
#include "models/context.h"
#include "models/flow.h"
#include "models/function.h"
#include "models/input.h"
#include "models/output.h"
#include "models/node.h"
#include "models/variable.h"

namespace duly_gui {
    class Project
    {
    public:
        Project(const QString &, const QString &);
        virtual ~Project();

    public:
        void save();

    private:
        QString m_name;
        QString m_path;

    public:
        const QString &name() const;
        void setName(const QString &name);

        const QString &path() const;
        void setPath(const QString &path);

    private:

        models::Variable *createVariable(const QJsonObject &);
        models::Input *createInput(const QJsonObject &);
        models::Output *createOutput(const QJsonObject &);
        models::Flow *createFlow(const QJsonObject &);
        models::Function *createFunction(const QJsonObject &);
        models::Class *createClass(const QJsonObject &);
        models::Context *createContext(const QJsonObject &);
        models::Node *createNode(const QJsonObject &);
    };
}

#endif // PROJECT_H
