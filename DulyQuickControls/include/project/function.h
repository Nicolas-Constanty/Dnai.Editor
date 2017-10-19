#ifndef PROJECT_FUNCTION_H
#define PROJECT_FUNCTION_H

#include <QVector>
#include "common.h"
#include "variable.h"
#include "input.h"
#include "output.h"
#include "node.h"

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
