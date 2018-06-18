#ifndef DNAI_RANDOM_UTILS_H
#define DNAI_RANDOM_UTILS_H

#include <QString>
#include <QUuid>

namespace dnai
{
    namespace utils
    {
        QString getRandomString(int size);

        QUuid generateUid();
    }
}

#endif // DNAI_RANDOM_UTILS_H
