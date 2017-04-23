#include "stdafx.h"
#include "libnbt.h"

namespace libnbt {
    bool NBT::endian() {
        int32_t num = 0x12345678;
        return ((int8_t *)&num)[0] == 0x78;
    }
    int8_t NBT::read_byte(std::istream & in) {
        char temp;
        in.get(temp);
        return temp;
    }
    int16_t NBT::read_short(std::istream & in) {
        int16_t data;
        if (endian()) {
            char temp[2];
            in.get(temp[1]);
            in.get(temp[0]);
            memcpy(&data, temp, 2);
        } else {
            in.read((char*)&data, 2);
        }
        return data;
    }
    int32_t NBT::read_int(std::istream & in) {
        int32_t data;
        if (endian()) {
            char temp[4];
            in.get(temp[3]);
            in.get(temp[2]);
            in.get(temp[1]);
            in.get(temp[0]);
            memcpy(&data, temp, 4);
        } else {
            in.read((char*)&data, 4);
        }
        return data;
    }
    int64_t NBT::read_long(std::istream & in) {
        int64_t data;
        if (endian()) {
            char temp[8];
            in.get(temp[7]);
            in.get(temp[6]);
            in.get(temp[5]);
            in.get(temp[4]);
            in.get(temp[3]);
            in.get(temp[2]);
            in.get(temp[1]);
            in.get(temp[0]);
            memcpy(&data, temp, 8);
        } else {
            in.read((char*)&data, 8);
        }
        return data;
    }
    float_t NBT::read_float(std::istream & in) {
        float_t data;
        if (endian()) {
            char temp[4];
            in.get(temp[3]);
            in.get(temp[2]);
            in.get(temp[1]);
            in.get(temp[0]);
            memcpy(&data, temp, 4);
        } else {
            in.read((char*)&data, 4);
        }
        return data;
    }
    double_t NBT::read_double(std::istream & in) {
        double_t data;
        if (endian()) {
            char temp[8];
            in.get(temp[7]);
            in.get(temp[6]);
            in.get(temp[5]);
            in.get(temp[4]);
            in.get(temp[3]);
            in.get(temp[2]);
            in.get(temp[1]);
            in.get(temp[0]);
            memcpy(&data, temp, 8);
        } else {
            in.read((char*)&data, 8);
        }
        return data;
    }
    std::string NBT::read_string(std::istream & in, int16_t length) {
        char temp;
        std::string data;
        while (length--) {
            in.get(temp);
            data.push_back(temp);
        }
        return data;
    }
    void NBT::write(std::ostream & out, char data) {
        out.put(data);
    }
    void NBT::write(std::ostream & out, int8_t data) {
        out.put((char)data);
    }
    void NBT::write(std::ostream & out, int16_t data) {
        char temp[2];
        memcpy(temp, &data, 2);
        if (endian()) {
            out.put(temp[1]);
            out.put(temp[0]);
        } else {
            out.write(temp, 2);
        }
    }
    void NBT::write(std::ostream & out, int32_t data) {
        char temp[4];
        memcpy(temp, &data, 4);
        if (endian()) {
            out.put(temp[3]);
            out.put(temp[2]);
            out.put(temp[1]);
            out.put(temp[0]);
        } else {
            out.write(temp, 4);
        }
    }
    void NBT::write(std::ostream & out, int64_t data) {
        char temp[8];
        memcpy(temp, &data, 4);
        if (endian()) {
            out.put(temp[7]);
            out.put(temp[6]);
            out.put(temp[5]);
            out.put(temp[4]);
            out.put(temp[3]);
            out.put(temp[2]);
            out.put(temp[1]);
            out.put(temp[0]);
        } else {
            out.write(temp, 8);
        }
    }
    void NBT::write(std::ostream & out, float_t data) {
        char temp[4];
        memcpy(temp, &data, 4);
        if (endian()) {
            out.put(temp[3]);
            out.put(temp[2]);
            out.put(temp[1]);
            out.put(temp[0]);
        } else {
            out.write(temp, 4);
        }
    }
    void NBT::write(std::ostream & out, double_t data) {
        char temp[8];
        memcpy(temp, &data, 4);
        if (endian()) {
            out.put(temp[7]);
            out.put(temp[6]);
            out.put(temp[5]);
            out.put(temp[4]);
            out.put(temp[3]);
            out.put(temp[2]);
            out.put(temp[1]);
            out.put(temp[0]);
        } else {
            out.write(temp, 8);
        }
    }
    void NBT::write(std::ostream & out, std::string data) {
        out.write(data.c_str(), data.size());
    }
    NBTBase * NBT::create(char type) {
        switch (type) {
            case TYPE_BYTE:
                return new NBTTagByte();
            case TYPE_SHORT:
                return new NBTTagShort();
            case TYPE_INT:
                return new NBTTagInt();
            case TYPE_LONG:
                return new NBTTagLong();
            case TYPE_FLOAT:
                return new NBTTagFloat();
            case TYPE_DOUBLE:
                return new NBTTagDouble();
            case TYPE_BYTE_ARRAY:
                return new NBTTagByteArray();
            case TYPE_STRING:
                return new NBTTagString();
            case TYPE_LIST:
                return new NBTTagList();
            case TYPE_COMPOUND:
                return new NBTTagCompound();
            case TYPE_INT_ARRAY:
                return new NBTTagIntArray();
            default:
                return (NBTBase*)nullptr;
        }
    }
    void NBT::readNbt(std::istream & in, NBTBase * tag) {
        char head = TYPE_UNKNOWN, foot = TYPE_UNKNOWN;
        in.get(head);
        if (tag->getType() == TYPE_COMPOUND && head == TYPE_COMPOUND) {
            NBTTagCompound *compound = (NBTTagCompound *)tag;
            int16_t length = NBT::read_short(in);
            compound->root(NBT::read_string(in, length));
            compound->read(in);
        }
    }
    void NBT::writeNbt(std::ostream & out, NBTBase * tag) {
        if (tag->getType() == TYPE_COMPOUND) {
            out.put(TYPE_COMPOUND);
            NBTTagCompound *compound = (NBTTagCompound *)tag;
            int16_t length = (int16_t)compound->root().size();
            NBT::write(out, length);
            NBT::write(out, compound->root());
            tag->write(out);
            out.put(TYPE_END);
        }
    }
}
