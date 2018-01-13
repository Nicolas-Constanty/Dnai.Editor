#include <iostream>
#include "headercommunication.h"
#include "packagemanager.h"
#include <qdebug.h>

void PackageManager::registerEvent(std::function<void(void*, unsigned int)> event,
                                   int id) {
    m_events[id] = event;
}

void PackageManager::compute() {
    HeaderCommunication *header = NULL;
  //  qDebug() << m_data;

  //  qDebug() << "enter";

    while (m_data.size() >= (int)sizeof(HeaderCommunication)) {
        header = (HeaderCommunication *)(m_data.data());

        qDebug() << "id: " << header->id;
        qDebug() << "packageSize: " << header->packageSize;
        qDebug() << "sizeMAX" << m_data.size();

      //  std::cout << header->packageSize << std::endl;
      //  std::cout << header->id << std::endl;
    //    qDebug() << "size: " << m_data.size() << " >= " <<  (sizeof(HeaderCommunication) + header->packageSize);

        if (header->magicNumber != MAGIC_NUMBER) {
            m_data = QByteArray();
        }
        else if (header->magicNumber == MAGIC_NUMBER
                && m_data.size() >= (int)(sizeof(HeaderCommunication) + header->packageSize)) {
            std::map<int, std::function<void(void*, unsigned int)> >::iterator it;
            if ((it = m_events.find(header->id)) != m_events.end()) {
                  it->second(((void *)(m_data.constData() + sizeof(HeaderCommunication))), header->packageSize);
            //      qDebug() << "ENTER";
            }
            std::cout << "sizeof(HeaderCommunication) + header->packageSize == " << sizeof(HeaderCommunication) + header->packageSize << std::endl;
            m_data.remove(0, sizeof(HeaderCommunication) + header->packageSize);
            std::cout << "SIZE: " << m_data.count() << std::endl;
            //qDebug() << "ENTER and remove";
        } else {
            //qDebug() << "OUT";
            break;
        }

    }
    //qDebug() << "out";
}
