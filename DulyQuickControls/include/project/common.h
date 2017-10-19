#ifndef PROJECT_COMMON_H
#define PROJECT_COMMON_H

#include <QString>

namespace duly_gui {
    namespace project {
        class Common
        {
        public:
            Common(QString const &, QString const &);

        private:
            QString _name;
            QString _description;
        };
    }
}

#endif // PROJECT_COMMON_H
