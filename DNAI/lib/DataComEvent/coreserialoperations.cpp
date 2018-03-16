#include "coreserialoperations.h"

BinaryStream    &operator <<(BinaryStream &stream, QString const &value)
{
    stream << value.toStdString();
    return stream;
}

BinaryStream    &operator >>(BinaryStream &stream, QString &value)
{
    uint32_t size;
    stream >> size;

    for (uint32_t i = 0; i < size; i++)
    {
        char c;

        stream >> c;
        value += c;
    }
    return stream;
}

template <typename EnumType>
void enum_serialize(BinaryStream &stream, EnumType value)
{
    stream << static_cast<int32_t>(value);
}

template <typename EnumType>
void enum_deserialize(BinaryStream &stream, EnumType &value)
{
    int32_t val;
    stream >> val;
    value = static_cast<EnumType>(val);
}

BinaryStream    &operator <<(BinaryStream &stream, PackageDataCom::ENTITY_CORE value)
{
    enum_serialize(stream, value);
    return stream;
}

BinaryStream    &operator >>(BinaryStream &stream, PackageDataCom::ENTITY_CORE &value)
{
    enum_deserialize(stream, value);
    return stream;
}

BinaryStream    &operator <<(BinaryStream &stream, PackageDataCom::VISIBILITYCORE value)
{
    enum_serialize(stream, value);
    return stream;
}

BinaryStream    &operator >>(BinaryStream &stream, PackageDataCom::VISIBILITYCORE &value)
{
    enum_deserialize(stream, value);
    return stream;
}
