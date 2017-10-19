#ifndef PROJECT_NODE_H
#define PROJECT_NODE_H

#include <QVector>
#include <QVector2D>
#include "project/common.h"
#include "project/input.h"
#include "project/output.h"
#include "project/flow.h"

namespace duly_gui {
    namespace project {
    class Context;
    class Function;
        class Node: public Common
        {
        public:
            Node();
        private:
            Context *_context;
            Function *_function;
            QVector2D _position;
            QVector<Input> _inputs;
            QVector<Output> _outputs;
            Flow _flow_in;
            Flow _flow_out;
        };
    }
}

#endif // PROJECT_NODE_H
