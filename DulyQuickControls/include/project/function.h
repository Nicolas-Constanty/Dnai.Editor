#ifndef PROJECT_FUNCTION_H
#define PROJECT_FUNCTION_H

#include <QVector>
#include "project/common.h"
#include "project/variable.h"
#include "project/input.h"
#include "project/output.h"
#include "project/node.h"

namespace duly_gui {
    namespace project {
        class Function: public Common
        {
        public:
            Function();

        private:
            QVector<Variable> _variables;
            QVector<Input> _inputs;
            QVector<Output> _outputs;
            QVector<Node> _nodes;
        };
    }
}

#endif // PROJECT_FUNCTION_H
