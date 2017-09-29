#include  <stdexcept>
#include "link.h"

Link::Link(): L1(nullptr), L2(nullptr)
{
}

Link::Link(ALinkable *l1, ALinkable *l2)
{
    if (l1 == l2)
        std::runtime_error("L1 and L2 cannot be the same object!");
    L1 = l1;
    L2 = l2;
}
