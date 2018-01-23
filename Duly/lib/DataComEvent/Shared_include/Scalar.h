//
// Created by GasparQ on 20/01/2018.
//

#ifndef SERIALIZER_SCALAR_H
#define SERIALIZER_SCALAR_H

#include <QString>
#include "ISerializable.h"
#include "List.h"

template <typename T>
class Scalar : public ISerializable
{
public:
    Scalar()
    {

    }

    Scalar(Scalar const &ref) :
            data(ref.data)
    {

    }

    Scalar(const T &data) :
            data(data)
    {

    }

public:
    bool operator==(Scalar<T> const &ref) const
    {
        return ref.data == data;
    }

public:
    size_t GetPackageSize() const override
    {
        return sizeof(T);
    }

    size_t SerializeTo(Buffer &buffer) const override
    {
        buffer.Write(data);
        return GetPackageSize();
    }

    size_t DeserializeFrom(Buffer &buffer) override
    {
        buffer.Read(data);
        return GetPackageSize();
    }

public:
    T &Data()
    {
        return data;
    }

private:
    T data;
};

template <>
class Scalar<QString> : public List<Scalar<char>>
{
public:
    Scalar() : List()
    {

    }

    Scalar(QString const &ref)
    {
        for (QChar c : ref)
        {
            data.append(Scalar<char>(c.toLatin1()));
        }
    }
};

#endif //SERIALIZER_SCALAR_H
