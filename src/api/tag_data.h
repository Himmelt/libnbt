#ifndef LIBNBT_TAG_DATA_H
#define LIBNBT_TAG_DATA_H

#pragma once

#include "tag_base.h"

namespace libnbt {

    template<class T>
    class NBTTagData : public NBTBase {
    private:
        void setType() {
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

    protected:
        T _data;
        static uint8_t width;
    public:
        NBTTagData() { setType(); }

        explicit NBTTagData(T data) {
            setType();
            setData(data);
        }

        void setData(T data) {
            this->_data = data;
        }

        T getData() {
            return _data;
        }

        ~NBTTagData() override = default;

        void read(std::istream &in) override {
            NBTBase::read(in, (char *) &_data, width);
        }

        void write(std::ostream &out) override {
            NBTBase::write(out, (char *) &_data, width);
        }

        bool equals(NBTBase &tag) override {
            if (NBTBase::equals(tag)) {
                return this->_data == ((NBTTagData<T> &) tag)._data;
            }
            return false;
        }
    };

    template<typename T>
    uint8_t NBTTagData<T>::width = sizeof(T);

    typedef NBTTagData<int8_t> NBTTagByte;
    typedef NBTTagData<int16_t> NBTTagShort;
    typedef NBTTagData<int32_t> NBTTagInt;
    typedef NBTTagData<int64_t> NBTTagLong;
    typedef NBTTagData<float> NBTTagFloat;
    typedef NBTTagData<double> NBTTagDouble;

    class NBTTagString : public NBTTagData<std::string> {
    public:
        NBTTagString() = default;

        explicit NBTTagString(const std::string &data) : NBTTagData(data) {}

        void read(std::istream &in) override;

        void write(std::ostream &out) override;
    };
}

#endif //LIBNBT_TAG_DATA_H
