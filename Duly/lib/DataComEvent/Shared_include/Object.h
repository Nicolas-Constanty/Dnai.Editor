//
// Created by GasparQ on 20/01/2018.
//

#ifndef SERIALIZER_OBJECT_H
#define SERIALIZER_OBJECT_H

#include <tuple>
#include "ISerializable.h"

template <typename ... AttrTypes>
class Object : public ISerializable
{
public:
    using DataType = std::tuple<AttrTypes...>;

private:
    template <size_t ... idxs>
    using SeqT = std::integer_sequence<size_t, idxs...>;

    std::make_index_sequence<sizeof...(AttrTypes)> _seq;

public:
    Object()
    {

    }

    Object(Object<AttrTypes...> const &ref) :
        data(ref.data)
    {

    }

    Object(AttrTypes const & ... attrs) :
            data(attrs...)
    {

    }

public:
    Object &operator=(DataType const &ref)
    {
        data = ref;
        return *this;
    }

    bool operator==(Object<AttrTypes...> const &ref) const
    {
        return data == ref.data;
    }

public:
    DataType &Data()
    {
        return data;
    }

    DataType const &Data() const
    {
        return data;
    }

    template <size_t fieldIndex>
    typename std::tuple_element<fieldIndex, DataType>::type &Field()
    {
        return std::get<fieldIndex>(data);
    }

private:
    size_t getSumOf(std::initializer_list<size_t> const &sizes) const
    {
        size_t toret = 0;

        for (size_t curr : sizes)
            toret += curr;
        return toret;
    }

    template <size_t ... idxs>
    size_t _GetPackageSize(SeqT<idxs...>) const
    {
        return getSumOf({std::get<idxs>(data).GetPackageSize()...});
    }

    template <size_t ... idxs>
    size_t _SerializeTo(Buffer &buff, SeqT<idxs...>) const
    {
        return getSumOf({std::get<idxs>(data).SerializeTo(buff)...});
    }

    template <size_t ... idxs>
    size_t _DeserializeFrom(Buffer &buff, SeqT<idxs...>)
    {
        return getSumOf({std::get<idxs>(data).DeserializeFrom(buff)...});
    }

public:
    size_t GetPackageSize() const override
    {
        return _GetPackageSize(_seq);
    }

    size_t SerializeTo(Buffer &buff) const override
    {
        return _SerializeTo(buff, _seq);
    }

    size_t DeserializeFrom(Buffer &buff) override
    {
        return _DeserializeFrom(buff, _seq);
    }

private:
    DataType data;
};

#endif //SERIALIZER_OBJECT_H
