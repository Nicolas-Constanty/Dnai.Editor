#ifndef PROJECT_OUTPUT_H
#define PROJECT_OUTPUT_H

#include "variable.h"
#include "link.h"

namespace duly_gui {
    namespace project {
        class Output: public Variable, Link
        {
        public:
            Output();
        };
    }
}

#endif // PROJECT_OUTPUT_H
