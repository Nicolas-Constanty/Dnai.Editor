#ifndef MAP_H
#define MAP_H

#include <QMap>
#include "ISerializable.h"

template <typename Key, typename Value>
class Map : public ISerializable
{
public:
    Map()
    {

    }

    Map(Map<Key, Value> const &ref) :
        data(ref.data)
    {

    }

    Map(QMap<Key, Value> const &ref) :
        data{ref}
    {

    }

public:
    Map<Key, Value> &operator=(Map const &ref)
    {
        data = ref.data;
    }

    QMap<Key, Value> &Data()
    {
        return data;
    }

public:
    size_t SerializeTo(Buffer &buff) const
    {
        size_t written = buff.Write(static_cast<uint32_t>(data.count()));

        if (written == 0)
            return 0;

        for (auto const &element : data)
        {
            size_t s;

            if ((s = element.key().SerializeTo(buff)) == 0)
                return written;

            written += s;

            if ((s = element.value().SerializeTo(buff)) == 0)
                return written;

            written += s;
        }
        return written;
    }

    size_t DeserializeFrom(Buffer &buff)
    {
        uint32_t count;
        size_t read = buff.Read(count);

        if (read == 0)
            return 0;

        for (uint32_t i = 0; i < count; i++)
        {
            Key k;
            Value v;
            size_t s;

            if ((s = k.DeserializeFrom(buff)) == 0)
                return read;

            read += s;

            if ((s = v.DeserializeFrom(buff)) == 0)
                return read;

            read += s;

            data[k] = v;
        }
        return read;
    }

    size_t GetPackageSize() const
    {
        size_t pckgSize = sizeof(uint32_t);

        for (auto const &element : data)
        {
            pckgSize += element.key().GetPackageSize();
            pckgSize += element.value().GetPackageSize();
        }
        return pckgSize;
    }

private:
    QMap<Key, Value> data;
};

#endif // MAP_H
