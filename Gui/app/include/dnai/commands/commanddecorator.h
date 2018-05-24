#ifndef COMMANDDECORATOR_H
#define COMMANDDECORATOR_H

#include "command.h"

namespace dnai {
    namespace commands {
        class CommandDecorator : public interfaces::ICommand
        {
        protected:
            interfaces::ICommand *m_decoratedCommand;

        public:
	        /**
             * \brief Allow to add new comportement feature on the decoratedCommand
             * \param decoratedCommand 
             */
            explicit CommandDecorator(interfaces::ICommand *decoratedCommand);
        };
    }
}

#endif // COMMANDDECORATOR_H
