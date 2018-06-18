#include "dnai/utils/random_utils.h"

namespace dnai
{
    namespace utils
    {
        QString getRandomString(int size)
        {
            const QString possibleCharacters(" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~");

            QString randomString;
            for (auto i = 0; i< size; ++i)
            {
                auto index = qrand() % possibleCharacters.length();
                auto nextChar = possibleCharacters.at(index);
                randomString.append(nextChar);
            }
            return randomString;
        }

        QUuid generateUid()
        {
            return QUuid::createUuidV5(QUuid::createUuid(), getRandomString(128));
        }
    }
}
