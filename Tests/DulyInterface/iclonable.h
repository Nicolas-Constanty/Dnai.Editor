#ifndef ICLONABLE_H
#define ICLONABLE_H

class IClonable
{
public:
    virtual IClonable *clone() const = 0;
};

#endif // ICLONABLE_H
