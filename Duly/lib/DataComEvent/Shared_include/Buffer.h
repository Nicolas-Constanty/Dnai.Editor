//
// Created by GasparQ on 20/01/2018.
//

#ifndef SERIALIZER_BUFFER_H
#define SERIALIZER_BUFFER_H

#include <cstdlib>
#include <cstring>
#include <typeinfo>

class Buffer
{
public:
    explicit Buffer(void *buff, size_t size) :
            buffer(static_cast<char *>(buff)),
            index(0),
            buffSize(size)
    {

    }

    ~Buffer()
    {

    }

public:
    template <typename T>
    size_t Write(T const &data)
    {
        if (index + sizeof(T) > buffSize)
            return 0;
        std::memcpy(buffer + index, &data, sizeof(T));
        index += sizeof(T);
        return sizeof(T);
    }

    template <typename T>
    size_t Read(T &data)
    {
        if (index + sizeof(T) > buffSize)
            return 0;
        std::memcpy(&data, buffer + index, sizeof(T));
        index += sizeof(T);
        return sizeof(T);
    }

    void *getData() const
    {
        return static_cast<void *>(buffer);
    }

    void resetIndex()
    {
        index = 0;
    }

private:
    char *buffer;
    size_t index;
    size_t buffSize;
};

#endif //SERIALIZER_BUFFER_H
