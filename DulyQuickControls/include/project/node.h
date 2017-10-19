#ifndef PROJECT_NODE_H
#define PROJECT_NODE_H

#include <QVector>
#include <QVector2D>
#include "common.h"
#include "input.h"
#include "output.h"
#include "context.h"
#include "function.h"
#include "flow.h"

namespace duly_gui {
    namespace project {
        class Node: public Common
        {
        public:
            Node();
        private:
            Context *_context;
            Function *_function;
            QVector2D<int>  _position;
            QVector<Input> _inputs;
            QVector<Output> _outputs;
            Flow _flow_in;
            Flow _flow_out;
        };
    }
}

#endif // PROJECT_NODE_H
