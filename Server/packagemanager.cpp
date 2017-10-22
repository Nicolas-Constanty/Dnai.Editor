#include <iostream>
#include "headercommunication.h"
#include "packagemanager.h"

void PackageManager::registerEvent(std::function<void(void*, unsigned int)> event,
                                   int id) {
    m_events[id] = event;
}

void PackageManager::compute() {
    HeaderCommunication *header = NULL;

    if (m_data.size() >= sizeof(HeaderCommunication)) {
        header = (HeaderCommunication *)(m_data.data());
        std::cout << header->magicNumber << std::endl;
        std::cout << header->packageSize << std::endl;
        std::cout << header->id << std::endl;

        if (header->magicNumber == MAGIC_NUMBER && m_data.size() >= (sizeof(HeaderCommunication) + header->packageSize)) {
            std::map<int, std::function<void(void*, unsigned int)> >::iterator it;
            if ((it = m_events.find(header->id)) != m_events.end()) {
                  it->second(((void *)(m_data.constData() + sizeof(HeaderCommunication))), header->packageSize);
            }
            m_data.remove(0, sizeof(HeaderCommunication) + header->packageSize);
        }

    }
}
