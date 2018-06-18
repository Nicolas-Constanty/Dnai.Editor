#ifndef DNAI_CORE_GLOBALHANDLER_H
#define DNAI_CORE_GLOBALHANDLER_H

#include <QObject>

#include "entitymanager.h"

namespace dnai
{
    namespace gcore
    {
        class GlobalHandler : public QObject
        {
            Q_OBJECT

        public:
            GlobalHandler() = default;
            ~GlobalHandler() = default;

        public:
            void setup();

        public:
            Q_INVOKABLE void save(QString const &path);
            Q_INVOKABLE void load(QString const &path);

        signals:
            void saved(QString const &path);
            void saveError(QString const &path, QString const &msg);
            void loaded(QString const &path);
            void loadError(QString const &path, QString const &msg);

        private:
            void onSaved(QString const &path);
            void onSaveError(QString const &path, QString const &msg);

            void onLoaded(QString const &path);
            void onLoadError(QString const &path, QString const &msg);
        };
    }
}

#endif // DNAI_CORE_GLOBALHANDLER_H
