#ifndef LINK_H
#define LINK_H

#include "ilinkable.h"

class Link
{
public:

    ALinkable *L1;
    ALinkable *L2;

public:
    Link(ALinkable *l1, ALinkable *l2);

private:
    Link();
};

#endif // LINK_H
