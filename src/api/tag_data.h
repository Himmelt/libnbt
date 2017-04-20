#ifndef LIBNBT_TAG_DATA_H
#define LIBNBT_TAG_DATA_H

#pragma once

#include "tag_base.h"

namespace libnbt {

    template<class T>
    class NBTTagData : public NBTBase {
    protected:
        T data;
    public:
        NBTTagData() {}

        NBTTagData(T data) {
            setData(data);
        }

        void setData(T data) {
            this->data = data;
            if (typeid(T) == typeid(int8_t)) {
                type = BYTE;
            } else if (typeid(T) == typeid(int16_t)) {
                type = SHORT;
            } else if (typeid(T) == typeid(int32_t)) {
                type = INT;
            } else if (typeid(T) == typeid(int64_t)) {
                type = LONG;
            } else if (typeid(T) == typeid(float)) {
                type = FLOAT;
            } else if (typeid(T) == typeid(double)) {
                type = DOUBLE;
            } else if (typeid(T) == typeid(std::string)) {
                type = STRING;
            } else {
                type = END;
            }
        }

        T getData() {
            return data;
        }

        void read(std::istream &in) override {
            in.read((char *) &data, sizeof(T));
        }

        void write(std::ostream &out) override {
            out.write((char *) &data, sizeof(T));
        }

        bool equals(NBTBase &tag) override {
            if (NBTBase::equals(tag)) {
                return this->data == ((NBTTagData<T> &) tag).data;
            }
            return false;
        }
    };

    typedef NBTTagData<int8_t> NBTTagByte;
    typedef NBTTagData<int16_t> NBTTagShort;
    typedef NBTTagData<int32_t> NBTTagInt;
    typedef NBTTagData<int64_t> NBTTagLong;
    typedef NBTTagData<float> NBTTagFloat;
    typedef NBTTagData<double> NBTTagDouble;

    class NBTTagString : public NBTTagData<std::string> {
    public:
        NBTTagString() {}

        NBTTagString(const std::string &data) : NBTTagData(data) {}

        void read(std::istream &in) override;

        void write(std::ostream &out) override;
    };
}

#endif //LIBNBT_TAG_DATA_H
