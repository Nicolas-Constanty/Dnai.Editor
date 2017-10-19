#ifndef PROJECT_IDENTITY_H
#define PROJECT_IDENTITY_H

#include <QString>

namespace duly_gui {
    namespace project {
        class Identity
        {
        public:
            Identity();

        private:
            QString _uid;
            QString _linked_uid;
        };
    }
}

#endif // PROJECT_IDENTITY_H
