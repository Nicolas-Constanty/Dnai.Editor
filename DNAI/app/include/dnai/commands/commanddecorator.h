#ifndef COMMANDDECORATOR_H
#define COMMANDDECORATOR_H

#include "command.h"

namespace dnai {
    namespace commands {
        class CommandDecorator : public ICommand
        {
        protected:
            ICommand *m_decoratedCommand;

        public:
            explicit CommandDecorator(ICommand *decoratedCommand);
        };
    }
}

#endif // COMMANDDECORATOR_H
