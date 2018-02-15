//
// Created by GasparQ on 20/01/2018.
//

#ifndef SERIALIZER_LIST_H
#define SERIALIZER_LIST_H

#include <QVector>

#include "ISerializable.h"

template <class Stored>
class List : public ISerializable
{
public:
    List()
    {

    }

    List(List const &ref) :
        data(ref.data)
    {

    }

    template <size_t size>
    explicit List(Stored const (&ref)[size]) :
            data{ref}
    {

    }

    List(std::initializer_list<Stored> const& ref) :
            data{ref}
    {

    }

public:
    bool operator==(List<Stored> const &ref) const
    {
        return ref.data == data;
    }

public:
    QVector<Stored> &Data()
    {
        return data;
    }

    QVector<Stored> const &Data() const
    {
        return data;
    }

public:
    size_t GetPackageSize() const override
    {
        size_t toret = sizeof(uint32_t);

        for (Stored const &curr : data)
        {
            toret += curr.GetPackageSize();
        }
        return toret;
    }

    size_t SerializeTo(Buffer &buff) const override
    {
        size_t size = buff.Write(static_cast<uint32_t >(data.size()));

        if (size == 0)
            return size;

        for (Stored const &curr : data)
        {
            size_t s = curr.SerializeTo(buff);

            if (s == 0)
                return size;

            size += s;
        }
        return size;
    }

    size_t DeserializeFrom(Buffer &buff) override
    {
        uint32_t cnt;
        size_t size = buff.Read(cnt);

        if (size == 0)
            return size;

        for (uint32_t i = 0; i < cnt; i++)
        {
            data.append(Stored());

            size_t s = data.back().DeserializeFrom(buff);

            if (s == 0)
                return size;

            size += s;
        }
        return size;
    }

private:
    QVector<Stored> data;
};

#endif //SERIALIZER_LIST_H
