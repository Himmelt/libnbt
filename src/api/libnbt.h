#ifndef LIBNBT_LIBNBT_H
#define LIBNBT_LIBNBT_H

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <typeinfo>
#include <unordered_map>

namespace libnbt {

    enum TAG_TYPE {
        END, BYTE, SHORT, INT, LONG, FLOAT, DOUBLE,
        BYTE_ARRAY, STRING, LIST, COMPOUND, INT_ARRAY
    };

    class NBTBase {
    protected:
        char type = 0;
    public:
        virtual void read(std::istream &in) = 0;

        virtual void write(std::ostream &out) = 0;

        virtual TAG_TYPE getType();

        virtual bool equals(NBTBase &tag);

        virtual ~NBTBase() = default;
    };

    class NBTTagEnd : public NBTBase {
    public:
        void read(std::istream &in) override {}

        ~NBTTagEnd() override = default;;

        void write(std::ostream &out) override {}
    };

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

        void read(std::istream &in) override;

        void write(std::ostream &out) override;

        bool equals(NBTBase &tag) override {
            if (NBTBase::equals(tag)) {
                return this->_data == ((NBTTagData<T> &) tag)._data;
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

    template<typename T>
    uint8_t NBTTagData<T>::width = sizeof(T);

    class NBTTagString : public NBTTagData<std::string> {
    public:
        NBTTagString() = default;

        explicit NBTTagString(const std::string &data) : NBTTagData(data) {}

        void read(std::istream &in) override;

        void write(std::ostream &out) override;
    };

    template<class T>
    class NBTTagVector : public NBTBase {
    protected:
        std::vector<T> array;
        static uint8_t width;
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

        void read(std::istream &in) override;

        void write(std::ostream &out) override;

        bool equals(NBTBase &tag) override {
            return NBTBase::equals(tag);
        }
    };

    typedef NBTTagVector<int8_t> NBTTagByteArray;
    typedef NBTTagVector<int32_t> NBTTagIntArray;

    template<typename T>
    uint8_t NBTTagVector<T>::width = sizeof(T);

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

    class NBTTagCompound : public NBTBase {
    private:
        std::unordered_map<std::string, NBTBase *> map;
        std::string rootKey = "";
    public:

        NBTTagCompound();

        explicit NBTTagCompound(std::string root);

        bool hasTag(const std::string &key);

        void setTag(const std::string &key, NBTBase *tag);

        NBTBase *getTag(const std::string &key);

        void read(std::istream &in) override;

        void write(std::ostream &out) override;

        void clear();

        bool check();

        void setRoot(std::string root);

        std::string getRoot();

        ~NBTTagCompound() override;
    };

    static const int32_t testEndian = 0x12345678;
    static const bool littleEndian = ((int8_t *) &testEndian)[0] == 0x78;

    static void readBytes(std::istream &in, char *data, uint8_t width) {
        if (width > 1 && littleEndian) {
            char t, *temp = new char[width];
            in.read(temp, width);
            for (int i = 0; i < width / 2; i++) {
                t = temp[i];
                temp[i] = temp[width - i - 1];
                temp[width - i - 1] = t;
            }
            memcpy(data, temp, width);
            delete[] temp;
        } else {
            in.read(data, width);
        }
    }

    static void writeBytes(std::ostream &out, const char *data, uint8_t width) {
        if (width > 1 && littleEndian) {
            char t, *temp = new char[width];
            memcpy(temp, data, width);
            for (int i = 0; i < width / 2; i++) {
                t = temp[i];
                temp[i] = temp[width - i - 1];
                temp[width - i - 1] = t;
            }
            out.write(temp, width);
            delete[] temp;
        } else {
            out.write(data, width);
        }
    }

    static std::string readString(std::istream &in, int16_t length) {
        std::string temp;
        temp.clear();
        char s;
        while (length--) {
            in.get(s);
            temp.push_back(s);
        }
        return temp;
    }

    static bool readNbt(std::istream &in, NBTTagCompound *compound) {
        char head = -1;
        char foot = -1;
        in.get(head);
        if (head == COMPOUND) {
            int16_t length = 0;
            readBytes(in, (char *) &length, 2);
            compound->setRoot(readString(in, length));
            compound->read(in);
            in.get(foot);
            return foot == END;
        }
        return false;
    }

    static void writeNbt(std::ostream &out, NBTTagCompound *compound) {
        out.put(COMPOUND);
        int16_t length = (int16_t) compound->getRoot().size();
        writeBytes(out, (char *) &length, 2);
        out.write(compound->getRoot().c_str(), length);
        compound->write(out);
        out.put(END);
    }

    static NBTBase *createNewTag(TAG_TYPE type) {
        switch (type) {
            case END:
                return new NBTTagEnd();
            case BYTE:
                return new NBTTagByte();
            case SHORT:
                return new NBTTagShort();
            case INT:
                return new NBTTagInt();
            case LONG:
                return new NBTTagLong();
            case FLOAT:
                return new NBTTagFloat();
            case DOUBLE:
                return new NBTTagDouble();
            case BYTE_ARRAY:
                return new NBTTagByteArray();
            case STRING:
                return new NBTTagString();
            case LIST:
                return new NBTTagList();
            case COMPOUND:
                return new NBTTagCompound();
            case INT_ARRAY:
                return new NBTTagIntArray();
            default:
                return new NBTTagEnd();
        }
    }
}

#endif //LIBNBT_LIBNBT_H
