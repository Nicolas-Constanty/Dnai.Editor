#ifndef ICOMMAND_H
#define ICOMMAND_H

//#include "iclonable.h"

class ICommand
{
public:
	virtual ~ICommand() = default;
	virtual void Execute() const = 0;
    virtual void UnExcute() const = 0;
};

#endif // ICOMMAND_H
