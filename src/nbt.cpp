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

    void NBT::open(std::string filename) {

        std::filebuf filebuf;
        filebuf.open(filename, std::ios::in | std::ios::binary);

        if (filebuf.is_open()) {
            std::cout << "open" << std::endl;
            char head[4];
            filebuf.sgetn(head, 2);
            // gzip header ?
            printf("head:%x,%x", head[0], head[1] & 0xff);
            if ((head[0] & 0xff) == 0x1f && (head[1] & 0xff) == 0x8b) {
                std::cout << "gzip" << std::endl;
                filebuf.pubseekoff(-4, std::ios::end);
                filebuf.pubsetbuf(head, 4);
                size = (head[3] & 0xff | size) << 8;
                size = (head[2] & 0xff | size) << 8;
                size = (head[1] & 0xff | size) << 8;
                size = head[0] & 0xff | size;
                gzFile gzfile = gzopen(filename.c_str(), "rb");
                if (gztell(gzfile) >= 0) {
                    buff = new int8_t[size];
                    int code = gzread(gzfile, buff, size);
                    if (code <= 0) {
                        std::cout << "code:" << code << std::endl;
                        std::cout << "uncompress gzip failed!" << std::endl;
                    } else {
                        std::cout << "uncompress gzip success!" << std::endl;
                    }
                } else {
                    std::cout << "read gzip failed!" << std::endl;
                }
                gzclose(gzfile);
            } else {
                size = (unsigned int) filebuf.pubseekoff(0, std::ios::end, std::ios::in);
                if (size <= 0) {
                    std::cout << "read file failed!" << std::endl;
                } else {
                    buff = new int8_t[size];
                    filebuf.pubseekpos(0, std::ios::in);
                    filebuf.sgetn((char *) buff, size);
                    std::cout << "read file success!" << std::endl;
                }
            }
        } else {
            std::cout << "read file error!" << std::endl;
        }
        filebuf.close();
    }

    int8_t NBT::readByte() {
        if (size > 0 && seek - buff <= size) {
            return seek++[0];
        } else {
            return 0;
        }
    }

    int16_t NBT::readShort() {
        int16_t data = readByte();
        data = (data << 8) | readByte();
        return data;
    }

    int32_t NBT::readInt() {
        int32_t data = readShort();
        data = (data << 16) | readShort();
        return data;
    }

    int64_t NBT::readLong() {
        int64_t data = readInt();
        data = (data << 32) | readInt();
        return data;
    }

    float NBT::readFloat() {
        int32_t temp = readInt();
        float data = 0;
        memcpy(&data, &temp, 4);
        return data;
    }

    double NBT::readDouble() {
        int64_t temp = readLong();
        double data = 0;
        memcpy(&data, &temp, 8);
        return data;
    }

    int8_t *NBT::readByteArray(int n) {
        int8_t *buff = seek;
        seek = seek + n;
        return buff;
    }

    int32_t *NBT::readIntArray(int n) {
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

    TagCompound *NBT::prase(std::string key) {

        TagCompound *compound = new TagCompound(key);

        while (seek - buff <= size) {
            TagType type = (TagType) readByte();
            switch (type) {
                case TagType::TypeEnd: {
                    return compound;
                }
                case TagType::TypeByte: {
                    int length = readShort();
                    std::string nextKey = readString(length);
                    TagByte *tag = new TagByte(nextKey);
                    tag->setValue(readByte());
                    compound->appendValue(tag);
                    break;
                }
                case TagType::TypeShort: {
                    int length = readShort();
                    std::string nextKey = readString(length);
                    TagShort *tag = new TagShort(nextKey);
                    tag->setValue(readShort());
                    compound->appendValue(tag);
                    break;
                }
                case TagType::TypeInt: {
                    int length = readShort();
                    std::string nextKey = readString(length);
                    TagInt *tag = new TagInt(nextKey);
                    tag->setValue(readInt());
                    compound->appendValue(tag);
                    break;
                }
                case TagType::TypeLong: {
                    int length = readShort();
                    std::string nextKey = readString(length);
                    TagLong *tag = new TagLong(nextKey);
                    tag->setValue(readLong());
                    compound->appendValue(tag);
                }
                case TagType::TypeFloat: {
                    int length = readShort();
                    std::string nextKey = readString(length);
                    TagLong *tag = new TagLong(nextKey);
                    tag->setValue(readLong());
                    compound->appendValue(tag);
                    break;
                }
                case TagType::TypeDouble: {
                    int length = readShort();
                    std::string nextKey = readString(length);
                    TagDouble *tag = new TagDouble(nextKey);
                    tag->setValue(readDouble());
                    compound->appendValue(tag);
                    break;
                }
                case TagType::TypeByteArray: {
                    int length = readShort();
                    std::string nextKey = readString(length);
                    int size = readInt();
                    TagByteArray *tag = new TagByteArray(nextKey, size);
                    tag->setValue(readByteArray(size));
                    compound->appendValue(tag);
                    break;
                }
                case TagType::TypeIntArray: {
                    int length = readShort();
                    std::string nextKey = readString(length);
                    int size = readInt();
                    TagIntArray *tag = new TagIntArray(nextKey, size);
                    tag->setValue(readIntArray(size));
                    compound->appendValue(tag);
                    break;
                }
                case TagType::TypeString: {
                    int length = readShort();
                    std::string nextKey = readString(length);
                    int size = readShort();
                    TagString *tag = new TagString(nextKey);
                    tag->setValue(readString(size));
                    compound->appendValue(tag);
                    break;
                }
                case TagType::TypeList: {
                    int length = readShort();
                    std::string nextKey = readString(length);
                    TagType listType = (TagType) readByte();
                    int size = readShort();
                    TagList *tag = prase(nextKey, size, listType);
                    compound->appendValue(tag);
                    break;
                }
                case TagType::TypeCompound: {
                    int length = readShort();
                    std::string nextKey = readString(length);
                    TagCompound *tag = prase(nextKey);
                    compound->appendValue(tag);
                    break;
                }
            }
        }
        return compound;
    }

    TagList *NBT::prase(std::string key, int size, TagType listType) {
        TagList *tagList = new TagList(key, listType);
        switch (listType) {
            case TagType::TypeEnd: {
                std::cout << "Maybe Something Error!!" << std::endl;
                break;
            }
            case TagType::TypeByte: {
                for (int i = 0; i < size; i++) {
                    TagByte *tag = new TagByte("list");
                    tag->setValue(readByte());
                    tagList->appendValue(tag);
                }
                break;
            }
            case TagType::TypeShort: {
                for (int i = 0; i < size; i++) {
                    TagShort *tag = new TagShort("list");
                    tag->setValue(readShort());
                    tagList->appendValue(tag);
                }
                break;
            }
            case TagType::TypeInt: {
                for (int i = 0; i < size; i++) {
                    TagInt *tag = new TagInt("list");
                    tag->setValue(readInt());
                    tagList->appendValue(tag);
                }
                break;
            }
            case TagType::TypeLong: {
                for (int i = 0; i < size; i++) {
                    TagLong *tag = new TagLong("list");
                    tag->setValue(readLong());
                    tagList->appendValue(tag);
                }
                break;
            }
            case TagType::TypeFloat: {
                for (int i = 0; i < size; i++) {
                    TagFloat *tag = new TagFloat("list");
                    tag->setValue(readFloat());
                    tagList->appendValue(tag);
                }
                break;
            }
            case TagType::TypeDouble: {
                for (int i = 0; i < size; i++) {
                    TagDouble *tag = new TagDouble("list");
                    tag->setValue(readDouble());
                    tagList->appendValue(tag);
                }
                break;
            }
            case TagType::TypeByteArray: {
                for (int i = 0; i < size; i++) {
                    int arraySize = readInt();
                    TagByteArray *tag = new TagByteArray("list", arraySize);
                    tag->setValue(readByteArray(arraySize));
                    tagList->appendValue(tag);
                }
                break;
            }
            case TagType::TypeIntArray: {
                for (int i = 0; i < size; i++) {
                    int arraySize = readInt();
                    TagIntArray *tag = new TagIntArray("list", arraySize);
                    tag->setValue(readIntArray(arraySize));
                    tagList->appendValue(tag);
                }
                break;
            }
            case TagType::TypeString: {
                for (int i = 0; i < size; i++) {
                    int length = readShort();
                    TagString *tag = new TagString("list");
                    tag->setValue(readString(length));
                    tagList->appendValue(tag);
                }
                break;
            }
            case TagType::TypeList: {
                for (int i = 0; i < size; i++) {
                    TagType type = (TagType) readByte();
                    int listSize = readInt();
                    TagList *tag = prase("list", listSize, type);
                    tagList->appendValue(tag);
                }
                break;
            }
            case TagType::TypeCompound: {
                for (int i = 0; i < size; i++) {
                    TagCompound *tag = prase("compound");
                    tagList->appendValue(tag);
                }
                break;
            }
        }
        return tagList;
    }

    NBT::NBT(int8_t *buff, unsigned int size) {
        NBT::buff = NBT::seek = buff;
        NBT::size = size;
    }
}
