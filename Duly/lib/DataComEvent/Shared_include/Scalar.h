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
        return buffer.Write(data);
    }

    size_t DeserializeFrom(Buffer &buffer) override
    {
        return buffer.Read(data);
    }

public:
    T &Data()
    {
        return data;
    }

    T const &Data() const
    {
        return data;
    }

private:
    T data;
};

template <>
class Scalar<QString> : public ISerializable
{
public:
    Scalar()
    {

    }

    Scalar(QString const &ref)
    {
        refreshSerial(ref);
    }

    Scalar(Scalar<QString> const &ref)
    {
        refreshSerial(ref.data);
    }

    Scalar<QString> &operator=(Scalar<QString> const &ref)
    {
        refreshSerial(ref.data);
        return *this;
    }

private:
    void refreshData() const
    {
        data.clear();
        for (Scalar<char> const &curr : serial.Data())
        {
            data.append(QChar(curr.Data()));
        }
    }

    void refreshSerial() const
    {
        serial.Data().clear();
        for (QChar const &curr : data)
        {
            serial.Data().push_back(curr.toLatin1());
        }
    }

    void refreshSerial(QString const &ref) const
    {
        data = ref;
        refreshSerial();
    }

public:
    size_t SerializeTo(Buffer &buff) const
    {
        refreshSerial();
        return serial.SerializeTo(buff);
    }

    size_t DeserializeFrom(Buffer &buff)
    {
        size_t size = serial.DeserializeFrom(buff);

        refreshData();
        return size;
    }

    size_t GetPackageSize() const
    {
        refreshSerial();
        return serial.GetPackageSize();
    }

    QString &Data()
    {
        refreshData();
        return data;
    }

    QString const &Data() const
    {
        refreshData();
        return data;
    }

private:
    mutable QString data;
    mutable List<Scalar<char>> serial;
};

#endif //SERIALIZER_SCALAR_H
