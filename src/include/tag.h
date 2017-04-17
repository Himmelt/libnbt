#ifndef LIBNBT_TAG_H
#define LIBNBT_TAG_H

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <typeinfo>
#include <unordered_map>

namespace libnbt {

    using namespace std;
    using namespace __gnu_cxx;

    enum TAG_TYPE {
        END, BYTE, SHORT, INT, LONG, FLOAT, DOUBLE,
        BYTE_ARRAY, STRING, LIST, COMPOUND, INT_ARRAY
    };

    class NBTBase {
    private:
        virtual void write(uint8_t *data)=0;

        virtual void read(uint8_t *data, int depth)=0;

        virtual void write2(ostream stream)=0;


    public:
        virtual string toString()=0;

        virtual TAG_TYPE getType()=0;

        virtual NBTBase *copy()=0;

        virtual bool hasNoTags() { return false; }

        virtual bool equals(NBTBase *tag);

    protected:
        static NBTBase *createNewByType(uint8_t id);

        virtual string getString() { return this->toString(); }
    };

    class NBTTagEnd : public NBTBase {
    public:
        string toString() override;

        TAG_TYPE getType() override;

        NBTBase *copy() override;

        bool hasNoTags() override;

        bool equals(NBTBase *tag) override;

    protected:
        string getString() override;

    private:
        void write(uint8_t *data) override;

        void read(uint8_t *data, int depth) override;

    };

    template<class T>
    class NBTTagData : public NBTBase {
    public:
        NBTTagData() {}

        NBTTagData(T data) {
            this->data = data;
        }

        void setData(T data) {
            this->data = data;
        }

        T getData() {
            return data;
        }

    private:
        T data;
    };

    class NBTTagByte2 : public NBTTagData<uint8_t> {
    public:
        TAG_TYPE getType() override {
            return BYTE;
        }

    };

    class NBTTagByte : public NBTBase {
    public:
        NBTTagByte() {}

        NBTTagByte(uint8_t data) { this->data = data; }

        void setByte(uint8_t data) { this->data = data; }

        string toString() override;

        TAG_TYPE getType() override;

        NBTBase *copy() override;

        bool equals(NBTBase *tag) override;

        bool hasNoTags() override;

    protected:
        string getString() override;

    private:
        uint8_t data;

        void write(uint8_t *data) override;

        void read(uint8_t *data, int depth) override;

        void write2(ostream stream) override;

    };

    class NBTTagShort : public NBTBase {
    public:
        NBTTagShort() {}

        NBTTagShort(int16_t data) { this->data = data; }

        string toString() override;

        TAG_TYPE getType() override;

        NBTBase *copy() override;

        bool hasNoTags() override;

        bool equals(NBTBase *tag) override;

    protected:
        string getString() override;

    private:
        int16_t data;

        void write(uint8_t *data) override;

        void read(uint8_t *data, int depth) override;

    };

    class NBTTagInt : public NBTBase {
    public:
        string toString() override;

        TAG_TYPE getType() override;

        NBTBase *copy() override;

        bool hasNoTags() override;

        bool equals(NBTBase *tag) override;

    protected:
        string getString() override;

    private:
        void write(uint8_t *data) override;

        void read(uint8_t *data, int depth) override;

    };

    class NBTTagLong : public NBTBase {
    public:
        string toString() override;

        TAG_TYPE getType() override;

        NBTBase *copy() override;

        bool hasNoTags() override;

        bool equals(NBTBase *tag) override;

    protected:
        string getString() override;

    private:
        void write(uint8_t *data) override;

        void read(uint8_t *data, int depth) override;

    };

    class NBTTagFloat : public NBTBase {
    public:
        string toString() override;

        TAG_TYPE getType() override;

        NBTBase *copy() override;

        bool hasNoTags() override;

        bool equals(NBTBase *tag) override;

    protected:
        string getString() override;

    private:
        void write(uint8_t *data) override;

        void read(uint8_t *data, int depth) override;

    };

    class NBTTagDouble : public NBTBase {
    public:
        string toString() override;

        TAG_TYPE getType() override;

        NBTBase *copy() override;

        bool hasNoTags() override;

        bool equals(NBTBase *tag) override;

    protected:
        string getString() override;

    private:
        void write(uint8_t *data) override;

        void read(uint8_t *data, int depth) override;

    };

    class NBTTagByteArray : public NBTBase {
    public:
        string toString() override;

        TAG_TYPE getType() override;

        NBTBase *copy() override;

        bool hasNoTags() override;

        bool equals(NBTBase *tag) override;

    protected:
        string getString() override;

    private:
        void write(uint8_t *data) override;

        void read(uint8_t *data, int depth) override;

    };

    class NBTTagString : public NBTBase {
    public:
        string toString() override;

        TAG_TYPE getType() override;

        NBTBase *copy() override;

        bool hasNoTags() override;

        bool equals(NBTBase *tag) override;

    protected:
        string getString() override;

    private:
        void write(uint8_t *data) override;

        void read(uint8_t *data, int depth) override;

    };

    class NBTTagList : public NBTBase {
    public:
        string toString() override;

        TAG_TYPE getType() override;

        NBTBase *copy() override;

        bool hasNoTags() override;

        bool equals(NBTBase *tag) override;

    protected:
        string getString() override;

    private:
        void write(uint8_t *data) override;

        void read(uint8_t *data, int depth) override;

    };

    class NBTTagCompound : public NBTBase {
    public:
        NBTTagCompound() {}

        string toString() override;

        TAG_TYPE getType() override;

        NBTBase *copy() override;

        size_t getSize();

        void setTag(string key, NBTBase *value);

        NBTBase *getTag(string key);

        TAG_TYPE getTagId(string key);

        bool hasKey(string key);

        bool hasKey(string key, uint8_t type);

        void setByte(string key, uint8_t value);

        void setShort(string key, int16_t value);

        void setInteger(string key, int32_t value);

        void setLong(string key, int64_t value);

        void setFloat(string key, float value);

        void setDouble(string key, double value);

        void setString(string key, string value);

        void setByteArray(string key, vector<string> *value);

        void setIntArray(string key, vector<int> *value);

        void setBoolean(string key, bool value);

        bool hasNoTags() override;

        bool equals(NBTBase *tag) override;

    protected:
        string getString() override;

    private:
        unordered_map<string, NBTBase *> tagMap;

        void write(uint8_t *data) override;

        void read(uint8_t *data, int depth) override;

    };

    class NBTTagIntArray : public NBTBase {
    public:
        string toString() override;

        TAG_TYPE getType() override;

        NBTBase *copy() override;

        bool hasNoTags() override;

        bool equals(NBTBase *tag) override;

    protected:
        string getString() override;

    private:
        void write(uint8_t *data) override;

        void read(uint8_t *data, int depth) override;

    };
}

#endif //LIBNBT_TAG_H
