#ifndef DNAI_CORE_RESOURCEHANDLER_H
#define DNAI_CORE_RESOURCEHANDLER_H

#include <QObject>

#include "entitymanager.h"

namespace dnai
{
    namespace gcore
    {
        class ResourceHandler : public QObject
        {
            Q_OBJECT

        public:
            virtual ~ResourceHandler() = default;

        public:
            Q_INVOKABLE void setDirectory(QString directory);
            Q_INVOKABLE QString copyResource(QUrl filePath);
            Q_INVOKABLE bool deleteResource(QString value);

        private:
            QList<QString> m_projectResources;
        };
    }
}

#endif // DNAI_CORE_RESOURCEHANDLER_H
