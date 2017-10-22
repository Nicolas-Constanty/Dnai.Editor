#ifndef PACKAGEMANAGER_H
#define PACKAGEMANAGER_H

#include <QByteArray>
#include <map>
#include <functional>

class PackageManager
{

private:
    /*class FunctionInfo {
    public:
        FunctionInfo(std::function<void(void*)> func, unsigned int size) : func(func), size(size) {}
        FunctionInfo(FunctionInfo const &other) {
            *this = other;
        }
        FunctionInfo &operator=(FunctionInfo const &other) {
            func = other.func;
            size = other.size;
            return *this;
        }

        std::function<void(void*)> func;
        unsigned int size;
    };*/

public:
    PackageManager() {

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
