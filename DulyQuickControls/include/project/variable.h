#ifndef PROJECT_VARIABLE_H
#define PROJECT_VARIABLE_H

#include <QString>
#include <QVariant>
#include "project/common.h"

namespace duly_gui {
    namespace project {
        class Variable: public Common
        {
        public:
            Variable();

        private:
            QString _name;
            QString _type;
            bool _internal;
            QVariant value;
        };
    }
}

#endif // PROJECT_VARIABLE_H
