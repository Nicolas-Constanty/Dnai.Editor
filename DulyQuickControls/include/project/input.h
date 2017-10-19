#ifndef PROJECT_INPUT_H
#define PROJECT_INPUT_H

#include "variable.h"
#include "link.h"

namespace duly_gui {
    namespace project {
        class Input: public Variable, Link
        {
        public:
            Input();
        };
    }
}

#endif // PROJECT_INPUT_H
