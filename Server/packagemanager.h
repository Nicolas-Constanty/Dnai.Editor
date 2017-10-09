#ifndef PACKAGEMANAGER_H
#define PACKAGEMANAGER_H

#include <QByteArray>

//class IPackage;

template<class T>
class PackageManager
{
private:
    //typedef void (T::*mfptr)(IPackage *);

public:
    PackageManager() {

    }

    void operator<<(QByteArray const &data) {
        m_data += data;
    }

    void compute() {

    }

private:
    QByteArray m_data;
};

#endif // PACKAGEMANAGER_H
