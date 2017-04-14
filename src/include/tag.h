#ifndef LIBNBT_TAG_H
#define LIBNBT_TAG_H

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <typeinfo>
#include <map>

namespace libnbt {

    using namespace std;

    enum NBT_TYPES {
        END, BYTE, SHORT, INT, LONG, FLOAT, DOUBLE,
        BYTE_ARRAY, STRING, LIST, COMPOUND, INT_ARRAY
    };

    class NBTBase {
    private:
        virtual void write(uint8_t *data)=0;

        virtual void read(uint8_t *data, int depth)=0;

    public:
        virtual string toString()=0;

        virtual uint8_t getId()=0;

        virtual NBTBase *copy()=0;

        bool hasNoTags() { return false; }

        virtual bool equals(NBTBase *tag);

    protected:
        static NBTBase *createNewByType(uint8_t id);

        string getString() { return this->toString(); }
    };

    class NBTTagEnd : public NBTBase {
    public:
        string toString() override;

        uint8_t getId() override;

        NBTBase *copy() override;

    private:
        void write(uint8_t *data) override;

        void read(uint8_t *data, int depth) override;

    };

    class NBTTagByte : public NBTBase {
    public:
        string toString() override;

        uint8_t getId() override;

        NBTBase *copy() override;

        NBTTagByte(uint8_t data) { this->data = data; }

        bool equals(NBTBase *tag) override;

    private:
        uint8_t data;

        void write(uint8_t *data) override;

        void read(uint8_t *data, int depth) override;

    };

    class NBTTagShort : public NBTBase {
    public:
        string toString() override;

        uint8_t getId() override;

        NBTBase *copy() override;

    private:
        void write(uint8_t *data) override;

        void read(uint8_t *data, int depth) override;

    };

    class NBTTagInt : public NBTBase {
    public:
        string toString() override;

        uint8_t getId() override;

        NBTBase *copy() override;

    private:
        void write(uint8_t *data) override;

        void read(uint8_t *data, int depth) override;

    };

    class NBTTagLong : public NBTBase {
    public:
        string toString() override;

        uint8_t getId() override;

        NBTBase *copy() override;

    private:
        void write(uint8_t *data) override;

        void read(uint8_t *data, int depth) override;

    };

    class NBTTagFloat : public NBTBase {
    public:
        string toString() override;

        uint8_t getId() override;

        NBTBase *copy() override;

    private:
        void write(uint8_t *data) override;

        void read(uint8_t *data, int depth) override;

    };

    class NBTTagDouble : public NBTBase {
    public:
        string toString() override;

        uint8_t getId() override;

        NBTBase *copy() override;

    private:
        void write(uint8_t *data) override;

        void read(uint8_t *data, int depth) override;

    };

    class NBTTagByteArray : public NBTBase {
    public:
        string toString() override;

        uint8_t getId() override;

        NBTBase *copy() override;

    private:
        void write(uint8_t *data) override;

        void read(uint8_t *data, int depth) override;

    };

    class NBTTagString : public NBTBase {
    public:
        string toString() override;

        uint8_t getId() override;

        NBTBase *copy() override;

    private:
        void write(uint8_t *data) override;

        void read(uint8_t *data, int depth) override;

    };

    class NBTTagList : public NBTBase {
    public:
        string toString() override;

        uint8_t getId() override;

        NBTBase *copy() override;

    private:
        void write(uint8_t *data) override;

        void read(uint8_t *data, int depth) override;

    };

    class NBTTagCompound : public NBTBase {
    public:
        string toString() override;

        uint8_t getId() override;

        NBTBase *copy() override;

        size_t getSize();

        void setTag(string key, NBTBase *value);

    private:
        map<string, NBTBase *> tagMap;

        void write(uint8_t *data) override;

        void read(uint8_t *data, int depth) override;

    };

    class NBTTagIntArray : public NBTBase {
    public:
        string toString() override;

        uint8_t getId() override;

        NBTBase *copy() override;

    private:
        void write(uint8_t *data) override;

        void read(uint8_t *data, int depth) override;

    };
}

#endif //LIBNBT_TAG_H
