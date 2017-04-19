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
        NBTTagString(const std::string &data) : NBTTagData(data) {}

        void read(std::istream &in) override {
            int16_t length = 0;
            in.read(((char *) &length), 2);
            char *temp = new char[length + 1];
            in.read(temp, length);
            data.assign(temp, (size_t) length);
            delete (temp);
        }

        void write(std::ostream &out) override {
            int16_t length = (int16_t) data.size();
            out.write(((char *) &length), 2);
            out.write(data.c_str(), length);
        }
    };
}

#endif //LIBNBT_TAG_DATA_H
