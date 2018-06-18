#ifndef ACOMMAND_H
#define ACOMMAND_H

#include "icommand.h"

class ACommand : ICommand
{
public:
    void clone() override;
};

#endif // ACOMMAND_H
