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
        uint8_t width = sizeof(T);
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

        void put(T data) {
            array.push_back(data);
        }

        virtual void set(size_t index, T data) {
            if (index < array.size()) {
                array[index] = data;
            }
        }

        size_t size() {
            return array.size();
        }

        T get(size_t index) {
            return array[index];
        }

        std::vector<T> get() {
            return array;
        }

        virtual bool remove(size_t index) {
            if (index < array.size()) {
                array.erase(array.begin() + index);
                return true;
            }
            return false;
        }

        virtual void clear() {
            array.clear();
        }

        void read(std::istream &in) override {
            int32_t size = 0;
            NBTBase::read(in, (char *) &size, 4);
            clear();
            for (int i = 0; i < size; i++) {
                T temp;
                NBTBase::read(in, (char *) &temp, width);
                array.push_back(temp);
            }
        }

        void write(std::ostream &out) override {
            auto size = (int32_t) array.size();
            NBTBase::write(out, (char *) &size, 4);
            for (int i = 0; i < size; i++) {
                T temp = array[i];
                NBTBase::write(out, (char *) &temp, width);
            }
        }

        bool equals(NBTBase &tag) override {
            return NBTBase::equals(tag);
        }

    };

    typedef NBTTagVector<int8_t> NBTTagByteArray;
    typedef NBTTagVector<int32_t> NBTTagIntArray;

    class NBTTagList : public NBTTagVector<NBTBase *> {
    private:
        char child = 0;
    public:
        NBTTagList() = default;

        explicit NBTTagList(TAG_TYPE child);

        TAG_TYPE getListType();

        void read(std::istream &in) override;

        void write(std::ostream &out) override;

        void clear() override;

        bool remove(size_t index) override;

        void set(size_t index, NBTBase *data) override;

        ~NBTTagList() override;
    };
}

#endif //LIBNBT_TAG_VECTOR_H
