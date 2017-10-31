#ifndef PACKAGEMANAGER_H
#define PACKAGEMANAGER_H

#include <QByteArray>
#include <map>
#include <functional>
#include <QObject>

class PackageManager : public QObject
{
    Q_OBJECT

public:
    PackageManager() : QObject(0) {

    }

    void registerEvent(std::function<void(void*, unsigned int)>,
                       int id);

    void operator<<(QByteArray const &data) {
        m_data += data;
    }

    void compute();

private:
    QByteArray m_data;
    std::map<int, std::function<void(void*, unsigned int)> > m_events;
};

#endif // PACKAGEMANAGER_H
