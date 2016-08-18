/*******************************************************************************
 * Created by Himmelt on 2016/8/18.
 * Copyright (c) 2015-2016. Himmelt All rights reserved.
 * https://opensource.org/licenses/MIT
 ******************************************************************************/
#include "../include/nbt.h"

namespace libnbt {
    NBT::NBT() {
    }

    NBT::NBT(std::string filename) {
        open(filename);
        seek = buff;
    }

    NBT::~NBT() {
    }

    void libnbt::NBT::open(std::string filename) {
        infile.open(filename, std::ios::binary);
        std::filebuf *filebuf = infile.rdbuf();
        long size = (long) filebuf->pubseekoff(0, std::ios::end, std::ios::in);
        if (size <= 0) {
            std::cout << "Read File Error!!" << std::endl;
        } else {
            filebuf->pubseekpos(0, std::ios::in);
            NBT::size = size;
            buff = new int8_t[size];
            filebuf->sgetn((char *) buff, size);
        }
        infile.close();
    }

    int8_t libnbt::NBT::readByte() {
        if (size > 0 && seek - buff <= size) {
            return seek++[0];
        } else {
            return 0;
        }
    }

    int16_t libnbt::NBT::readShort() {
        int16_t data = readByte();
        data = (data << 8) | readByte();
        return data;
    }

    int32_t libnbt::NBT::readInt() {
        int32_t data = readShort();
        data = (data << 16) | readShort();
        return data;
    }

    int64_t libnbt::NBT::readLong() {
        int64_t data = readInt();
        data = (data << 32) | readInt();
        return data;
    }

    float libnbt::NBT::readFloat() {
        int32_t temp = readInt();
        float data = 0;
        memcpy(&data, &temp, 4);
        return data;
    }

    double libnbt::NBT::readDouble() {
        int64_t temp = readLong();
        double data = 0;
        memcpy(&data, &temp, 8);
        return data;
    }

    int8_t *libnbt::NBT::readByteArray(int n) {
        int8_t *buff = seek;
        seek = seek + n;
        return buff;
    }

    int32_t *libnbt::NBT::readIntArray(int n) {
        int32_t *buff = (int32_t *) seek;
        seek = seek + 4 * n;
        return buff;
    }

    std::string NBT::readString(int n) {
        int8_t *buff = nullptr;
        buff = new int8_t[n + 1];
        for (int i = 0; i < n; i++) {
            buff[i] = readByte();
        }
        buff[n] = 0;
        std::string data = (char *) buff;
        delete buff;
        return data;
    }

    libnbt::TagCompound *libnbt::NBT::prase(std::string key, bool isList, TagType listType) {
        TagCompound * compound = new TagCompound(key, isList, listType);

        while (seek - buff <= size) {
            int8_t type = readByte();
            int length = readShort();
            std::string key = readString(length);

            switch (type) {
                case 0x01:
                case 0x02:
                case 0x03:
                case 0x04:
                case 0x05:
                case 0x06:
                    compound->appendValue(new TagData(key, (DataType) type));
                    break;
                case 0x07:
                case 0x08:
                case 0x0B:
                    compound->appendValue(new TagArray(key, (DataType) type, size)
                default:
                    break;
            }
        }
        return compound;
    }
}
