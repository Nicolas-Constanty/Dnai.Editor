#ifndef PROJECT_OUTPUT_H
#define PROJECT_OUTPUT_H

#include "project/variable.h"
#include "project/identity.h"

namespace duly_gui {
    namespace project {
        class Output: public Variable, Identity
        {
        public:
            Output();
        };
    }
}

#endif // PROJECT_OUTPUT_H
