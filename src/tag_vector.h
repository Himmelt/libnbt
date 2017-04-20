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

        void put(T data) {
            array.push_back(data);
        }

        void set(size_t index, T data) {
            if (index < array.size()) array[index] = data;
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

        bool remove(size_t index) {
            if (index < array.size()) {
                array.erase(array.begin() + index);
                return true;
            }
            return false;
        }

        void read(std::istream &in) override {
            int32_t size = 0;
            int8_t width = sizeof(T);
            in.read((char *) &size, 4);
            array.clear();
            for (int i = 0; i < size; i++) {
                T temp;
                in.read((char *) &temp, width);
                array.push_back(temp);
            }
        }

        void write(std::ostream &out) override {
            int32_t size = (int32_t) array.size();
            int8_t width = sizeof(T);
            out.write((char *) &size, 4);
            for (int i = 0; i < size; i++) {
                T temp = array[i];
                out.write((char *) &temp, width);
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
        char child;
    public:
        NBTTagList() {}

        NBTTagList(TAG_TYPE child) : NBTTagVector() {
            this->child = child;
        }

        TAG_TYPE getListType() { return (TAG_TYPE) child; }

        void read(std::istream &in) override {
            in.get(child);
            int32_t size = 0;
            in.read((char *) &size, 4);
            for (int i = 0; i < size; i++) {
                NBTBase *tag = createNewTag(child);
                tag->read(in);
                array.push_back(tag);
            }
        }

        void write(std::ostream &out) override {
            int32_t size = (int32_t) array.size();
            out.put(child);
            out.write((char *) &size, 4);
            for (int i = 0; i < size; i++) {
                array[i]->write(out);
            }
        }
    };
}

#endif //LIBNBT_TAG_VECTOR_H
