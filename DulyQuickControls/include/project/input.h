#ifndef PROJECT_INPUT_H
#define PROJECT_INPUT_H

#include "project/variable.h"
#include "project/identity.h"

namespace duly_gui {
    namespace project {
        class Input: public Variable, Identity
        {
        public:
            Input();
        };
    }
}

#endif // PROJECT_INPUT_H
