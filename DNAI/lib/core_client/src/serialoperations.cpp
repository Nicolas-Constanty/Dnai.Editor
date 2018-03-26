#include "serialoperations.h"

BinaryStream    &operator <<(BinaryStream &stream, QString const &value)
{
    stream << value.toStdString();
    return stream;
}

BinaryStream    &operator >>(BinaryStream &stream, QString &value)
{
    quint32 size;
    stream >> size;

    for (uint32_t i = 0; i < size; i++)
    {
        char c;

        stream >> c;
        value += c;
    }
    return stream;
}

JSONStream      &operator <<(JSONStream &stream, QString const &value)
{
    stream.Write('"');
    for (QChar const &curr : value)
    {
        stream << curr.toLatin1();
    }
    stream.Write('"');
    return stream;
}

JSONStream      &operator >>(JSONStream &stream, QString &value)
{
    stream.ignore(1);
    while (stream.nextCharacter() != '"')
    {
        char c;
        stream >> c;
        value += QChar(c);
    }
    stream.ignore(1);
    return stream;
}

template <typename EnumType, typename Stream>
void enum_serialize(Stream &stream, EnumType value)
{
    stream << static_cast<int32_t>(value);
}

template <typename EnumType, typename Stream>
void enum_deserialize(Stream &stream, EnumType &value)
{
    int32_t val;
    stream >> val;
    value = static_cast<EnumType>(val);
}

BinaryStream    &operator <<(BinaryStream &stream, core::ENTITY value)
{
    enum_serialize(stream, value);
    return stream;
}

BinaryStream    &operator >>(BinaryStream &stream, core::ENTITY &value)
{
    enum_deserialize(stream, value);
    return stream;
}

JSONStream      &operator <<(JSONStream &stream, core::ENTITY value)
{
    enum_serialize(stream, value);
    return stream;
}

JSONStream      &operator >>(JSONStream &stream, core::ENTITY &value)
{
    enum_deserialize(stream, value);
    return stream;
}

BinaryStream    &operator <<(BinaryStream &stream, core::VISIBILITY value)
{
    enum_serialize(stream, value);
    return stream;
}

BinaryStream    &operator >>(BinaryStream &stream, core::VISIBILITY &value)
{
    enum_deserialize(stream, value);
    return stream;
}

JSONStream      &operator <<(JSONStream &stream, core::VISIBILITY value)
{
    enum_serialize(stream, value);
    return stream;
}

JSONStream      &operator >>(JSONStream &stream, core::VISIBILITY &value)
{
    enum_deserialize(stream, value);
    return stream;
}
