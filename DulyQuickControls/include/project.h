#ifndef PROJECT_H
#define PROJECT_H

#include <QString>
#include <QFile>
#include <QJsonObject>
#include "models/class.h"
#include "models/context.h"
#include "models/flow.h"
#include "models/function.h"
#include "models/input.h"
#include "models/output.h"
#include "models/node.h"
#include "models/variable.h"
#include "models/imodel.h"

namespace duly_gui {
    class Project: public models::Common, virtual public models::IModel
    {
    public:
        Project(const QString &, const QString &, QFile &);
        virtual ~Project();

    public:
        void save();

    private:
        QFile &m_file;

        QVector<models::Context*> m_contexts;
        QVector<models::Node*> m_nodes;

    public:
        QFile &file() const;

    private:
        models::Variable *createVariable(const QJsonObject &);
        models::Input *createInput(const QJsonObject &);
        models::Output *createOutput(const QJsonObject &);
        models::Flow *createFlow(const QJsonObject &);
        models::Function *createFunction(const QJsonObject &);
        models::Class *createClass(const QJsonObject &);
        models::Context *createContext(const QJsonObject &);
        models::Node *createNode(const QJsonObject &);


        // IModel interface
    public:
        virtual void serialize(QJsonObject &) const;

    public:
        void unserialize(const QJsonObject &);

    };
}

#endif // PROJECT_H
