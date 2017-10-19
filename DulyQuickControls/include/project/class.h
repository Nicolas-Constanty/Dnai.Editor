#ifndef PROJECT_CLASS_H
#define PROJECT_CLASS_H

#include <QVector>
#include "project/common.h"
#include "project/variable.h"
#include "project/function.h"

namespace duly_gui {
    namespace project {
        class Class: public Common
        {
        public:
            Class();

        private:
            QVector<Variable> _attributes;
            QVector<Function> _methods;
            QVector<Variable> _variables;
            QVector<Function> _functions;
        };
    }
}


#endif // PROJECT_CLASS_H
