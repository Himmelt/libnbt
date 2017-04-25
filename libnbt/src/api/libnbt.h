#ifndef LIBNBT_H
#define LIBNBT_H

#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <unordered_map>

#ifdef LIBNBT_EXPORTS
#define LIBNBT_API __declspec(dllexport)
#else
#define LIBNBT_API __declspec(dllimport)
#endif

#define TYPE_END          0
#define TYPE_BYTE         1
#define TYPE_SHORT        2
#define TYPE_INT          3
#define TYPE_LONG         4
#define TYPE_FLOAT        5
#define TYPE_DOUBLE       6
#define TYPE_BYTE_ARRAY   7
#define TYPE_STRING       8
#define TYPE_LIST         9
#define TYPE_COMPOUND    10
#define TYPE_INT_ARRAY   11
#define TYPE_UNKNOWN     -1

namespace libnbt {

    class LIBNBT_API NBTBase {
    protected:
        char type = TYPE_UNKNOWN;
    public:
        virtual char getType();
        virtual bool equals(NBTBase *tag);
        virtual void read(std::istream &in) = 0;
        virtual void write(std::ostream &out) = 0;
    };

    class LIBNBT_API NBTTagByte : public NBTBase {
    private:
        int8_t data = 0;
        static const int8_t width = 1;
    public:
        NBTTagByte();
        NBTTagByte(int8_t data);
        void set(int8_t data);
        int8_t get();
        void read(std::istream &in) override;
        void write(std::ostream &out) override;
        bool equals(NBTBase *tag) override;
    };

    class LIBNBT_API NBTTagShort : public NBTBase {
    private:
        int16_t data = 0;
        static const int8_t width = 2;
    public:
        NBTTagShort();
        NBTTagShort(int16_t data);
        void set(int16_t data);
        int16_t get();
        void read(std::istream &in) override;
        void write(std::ostream &out) override;
        bool equals(NBTBase *tag) override;
    };

    class LIBNBT_API NBTTagInt : public NBTBase {
    private:
        int32_t data = 0;
        static const int8_t width = 4;
    public:
        NBTTagInt();
        NBTTagInt(int32_t data);
        void set(int32_t data);
        int32_t get();
        void read(std::istream &in) override;
        void write(std::ostream &out) override;
        bool equals(NBTBase *tag) override;
    };

    class LIBNBT_API NBTTagLong : public NBTBase {
    private:
        int64_t data = 0;
        static const int8_t width = 8;
    public:
        NBTTagLong();
        NBTTagLong(int64_t data);
        void set(int64_t data);
        int64_t get();
        void read(std::istream &in) override;
        void write(std::ostream &out) override;
        bool equals(NBTBase *tag) override;
    };

    class LIBNBT_API NBTTagFloat : public NBTBase {
    private:
        float_t data = 0.0;
        static const int8_t width = 4;
    public:
        NBTTagFloat();
        NBTTagFloat(float_t data);
        void set(float_t data);
        float_t get();
        void read(std::istream &in) override;
        void write(std::ostream &out) override;
        bool equals(NBTBase *tag) override;
    };

    class LIBNBT_API NBTTagDouble : public NBTBase {
    private:
        double_t data = 0.0;
        static const int8_t width = 8;
    public:
        NBTTagDouble();
        NBTTagDouble(double_t data);
        void set(double_t data);
        double_t get();
        void read(std::istream &in) override;
        void write(std::ostream &out) override;
        bool equals(NBTBase *tag) override;
    };

    class LIBNBT_API NBTTagString : public NBTBase {
    private:
        std::string *data;
    public:
        NBTTagString();
        NBTTagString(std::string data);
        ~NBTTagString();
        void set(std::string data);
        std::string get();
        void read(std::istream &in) override;
        void write(std::ostream &out) override;
        bool equals(NBTBase *tag) override;
    };

    class LIBNBT_API NBTTagByteArray : public NBTBase {
    private:
        std::vector<int8_t> *array;
        static const int8_t width = 1;
    public:
        NBTTagByteArray();
        ~NBTTagByteArray();
        void put(int8_t data);
        void set(size_t index, int8_t data);
        int8_t get(size_t index);
        size_t size();
        void clear();
        void remove(size_t index);
        void read(std::istream &in) override;
        void write(std::ostream &out)override;
        bool equals(NBTBase *tag) override;
    };

    class LIBNBT_API NBTTagIntArray : public NBTBase {
    private:
        std::vector<int32_t> *array;
        static const int8_t width = 4;
    public:
        NBTTagIntArray();
        ~NBTTagIntArray();
        void put(int32_t data);
        void set(size_t index, int32_t data);
        int32_t get(size_t index);
        size_t size();
        void clear();
        void remove(size_t index);
        void read(std::istream &in) override;
        void write(std::ostream &out) override;
        bool equals(NBTBase *tag) override;
    };

    class LIBNBT_API NBTTagList :public NBTBase {
    private:
        char _child = TYPE_UNKNOWN;
        std::vector<NBTBase*> *list;
    public:
        NBTTagList();
        NBTTagList(char child);
        ~NBTTagList();
        void put(NBTBase* tag);
        void set(size_t index, NBTBase *tag);
        NBTBase* get(size_t index);
        char child();
        void clear();
        void remove(size_t index);
        void read(std::istream &in) override;
        void write(std::ostream &out) override;
        bool equals(NBTBase *tag) override;
    };

    class LIBNBT_API NBTTagCompound : public NBTBase {
    private:
        std::string *_root;
        std::unordered_map<std::string, NBTBase *> *map;
    public:
        NBTTagCompound();
        NBTTagCompound(std::string root);
        ~NBTTagCompound();
        bool has(const std::string key);
        void set(std::string key, NBTBase *tag);
        NBTBase *get(std::string key);
        std::string root();
        void root(std::string root);
        void clear();
        void remove(std::string key);
        void read(std::istream &in) override;
        void write(std::ostream &out) override;
        bool equals(NBTBase *tag) override;
    };

    class LIBNBT_API NBT {
    public:
        static bool endian();
        static int8_t read_byte(std::istream &in);
        static int16_t read_short(std::istream &in);
        static int32_t read_int(std::istream &in);
        static int64_t read_long(std::istream &in);
        static float_t read_float(std::istream &in);
        static double_t read_double(std::istream &in);
        static std::string read_string(std::istream &in, int16_t length);
        static void write(std::ostream &out, char data);
        static void write(std::ostream &out, int8_t data);
        static void write(std::ostream &out, int16_t data);
        static void write(std::ostream &out, int32_t data);
        static void write(std::ostream &out, int64_t data);
        static void write(std::ostream &out, float_t data);
        static void write(std::ostream &out, double_t data);
        static void write(std::ostream &out, std::string data);
        static NBTBase *create(char type);
        static void readNbt(std::istream &in, NBTBase *tag);
        static void writeNbt(std::ostream &out, NBTBase *tag);
    };

    class Pos {
    public:
        int x, y;
    };

    class LIBNBT_API Chunk {
    private:
        bool _empty = true;
        NBTTagCompound *level;
    public:
        bool is_empty();
        void set_empty();
    };

    class LIBNBT_API Region {
    private:
        int32_t offset[1024]={0};
        int32_t timestamp[1024]={0};
        Chunk chunks[32][32];
    public:
        Region();
        ~Region();
        bool hasChunk(int x, int z);
        void setChunk(int x, int z, Chunk chunk);
        Chunk &getChunk(Pos pos);
        size_t get_entry(int x,int z);
        void set_entry(int x,int z);
        int32_t get_timestamp(int x,int z);
        void set_timestamp(int x,int z);
        void clear();
        void remove(Pos pos);
        void read(std::istream &in);
        void write(std::ostream &out);
    };
    class ByteStream{
    private:
        char* byte;
        size_t length;
        size_t seek_r,seek_w;
    public:
        void copy(const char *byte,size_t length){
            delete[](byte);
            this->length = length;
            this->seek_r = 0;
            this->seek_w = 0;
            this->byte = new char[length];
            memcpy(byte,this->byte,length);
        }
    };
}

#endif //LIBNBT_H
