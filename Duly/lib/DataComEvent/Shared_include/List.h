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
        uint32_t size = 0;

        buff.Write(static_cast<uint32_t >(data.size()));

        size = sizeof(size);
        for (Stored const &curr : data)
        {
            size += curr.SerializeTo(buff);
        }
        return size;
    }

    size_t DeserializeFrom(Buffer &buff) override
    {
        uint32_t cnt;
        uint32_t size = sizeof(cnt);

        buff.Read(cnt);
        for (uint32_t i = 0; i < cnt; i++)
        {
            data.append(Stored());
            size += data.back().DeserializeFrom(buff);
        }
        return size;
    }

protected:
    QVector<Stored> data;
};

#endif //SERIALIZER_LIST_H
