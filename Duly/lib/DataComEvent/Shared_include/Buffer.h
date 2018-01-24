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
    void Write(T const &data)
    {
        if (index + sizeof(T) > buffSize)
            throw std::out_of_range("Trying to serialize data out of buffer range : " + std::string(typeid(T).name()));
        std::memcpy(buffer + index, &data, sizeof(T));
        index += sizeof(T);
    }

    template <typename T>
    void Read(T &data)
    {
        if (index + sizeof(T) > buffSize)
            throw std::out_of_range("Not enough data in buffer in order to read : " + std::string(typeid(T).name()));
        std::memcpy(&data, buffer + index, sizeof(T));
        index += sizeof(T);
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
