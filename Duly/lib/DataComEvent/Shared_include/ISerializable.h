//
// Created by GasparQ on 20/01/2018.
//

#ifndef SERIALIZER_ISERIALIZABLE_H
#define SERIALIZER_ISERIALIZABLE_H

#include <cstdio>
#include "Buffer.h"

class ISerializable
{
public:
    virtual ~ISerializable() = default;

public:
    virtual size_t GetPackageSize() const = 0;
    virtual size_t SerializeTo(Buffer &buff) const = 0;
    virtual size_t DeserializeFrom(Buffer &buff) = 0;
};

#endif //SERIALIZER_ISERIALIZABLE_H
