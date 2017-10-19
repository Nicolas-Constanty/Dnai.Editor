#ifndef PROJECT_LINK_H
#define PROJECT_LINK_H

#include <QString>

namespace duly_gui {
    namespace project {
        class Link
        {
        public:
            Link();

        private:
            QString _uid;
            QString _linked_uid;
        };
    }
}

#endif // PROJECT_LINK_H
