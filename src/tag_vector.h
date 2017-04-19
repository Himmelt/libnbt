#ifndef LIBNBT_TAG_VECTOR_H
#define LIBNBT_TAG_VECTOR_H

#pragma once

#include "tag_base.h"
#include <vector>

namespace libnbt {
    template<class T>
    class NBTTagVector : public NBTBase {
    protected:
        std::vector<T> array;

    public:
        NBTTagVector() {
            if (typeid(T) == typeid(int8_t)) {
                type = BYTE_ARRAY;
            } else if (typeid(T) == typeid(int16_t)) {
                type = INT_ARRAY;
            } else {
                type = LIST;
            }
        }

        void read(std::istream &in) override {

        }

        void write(std::ostream &out) override {

        }

        bool equals(NBTBase &tag) override {
            return NBTBase::equals(tag);
        }

    };

    typedef NBTTagVector<int8_t> NBTTagByteArray;
    typedef NBTTagVector<int16_t> NBTTagIntArray;

    class NBTTagList : public NBTTagVector<NBTBase *> {
    private:
        TAG_TYPE child;
    public:
        NBTTagList(TAG_TYPE child) : NBTTagVector() {
            this->child = child;
        }

        TAG_TYPE getListType() { return child; }

        void read(std::istream &in) override {
            NBTTagVector::read(in);
        }

        void write(std::ostream &out) override {
            NBTTagVector::write(out);
        }

    };
}

#endif //LIBNBT_TAG_VECTOR_H
