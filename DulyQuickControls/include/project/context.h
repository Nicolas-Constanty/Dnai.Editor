#ifndef PROJECT_CONTEXT_H
#define PROJECT_CONTEXT_H

#include <QVector>
#include "project/common.h"
#include "project/variable.h"
#include "project/function.h"

namespace duly_gui {
    namespace project {
        class Context: public Common
        {
        public:
            Context();

        private:
            QVector<Context> contexts;
            QVector<Variable> _variables;
            QVector<Function> _functions;
        };
    }
}

#endif // PROJECT_CONTEXT_H
