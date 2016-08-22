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
        std::cout << "buff point @ open:" << static_cast<const void *>(buff) << std::endl;
        seek = buff;
        std::cout << "seek point @ open:" << static_cast<const void *>(seek) << std::endl;
    }

    NBT::NBT(int8_t *buff, unsigned int size) {
        NBT::buff = NBT::seek = buff;
        NBT::size = size;
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
            printf("head:%x,%x\n", head[0], head[1] & 0xff);
            if ((head[0] & 0xff) == 0x1f && (head[1] & 0xff) == 0x8b) {
                std::cout << "gzip" << std::endl;
                filebuf.pubseekoff(-4, std::ios::end);
                filebuf.sgetn(head, 4);
                size = (head[3] & 0xff | size) << 8;
                size = (head[2] & 0xff | size) << 8;
                size = (head[1] & 0xff | size) << 8;
                size = head[0] & 0xff | size;

                printf("i size:%x,%x,%x,%x\n", head[3] & 0xff, head[2] & 0xff, head[1] & 0xff, head[0] & 0xff);

                gzFile gzfile = gzopen(filename.c_str(), "rb");
                if (gztell(gzfile) >= 0) {
                    buff = new int8_t[size];
                    int code = gzread(gzfile, buff, size);
                    if (code <= 0) {
                        std::cout << "code:" << code << std::endl;
                        std::cout << "uncompress gzip failed!" << std::endl;
                    } else {
                        std::cout << "return size(Byte):" << code << std::endl;
                        std::cout << "uncompress gzip success!" << std::endl;
                        std::cout << "buff point:" << static_cast<const void *>(buff) << std::endl;
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
        return seek++[0];
    }

    int16_t NBT::readShort() {
        int16_t data = 0;
        char temp[2] = {seek[1], seek[0]};
        memcpy(&data, temp, 2);
        seek += 2;
        return data;
    }

    int32_t NBT::readInt() {
        int32_t data = 0;
        char temp[4] = {seek[3], seek[2], seek[1], seek[0]};
        memcpy(&data, temp, 4);
        seek += 4;
        return data;
    }

    int64_t NBT::readLong() {
        int64_t data = 0;
        char temp[8] = {seek[7], seek[6], seek[5], seek[4], seek[3], seek[2], seek[1], seek[0]};
        memcpy(&data, temp, 8);
        seek = seek + 8;
        return data;
    }

    float NBT::readFloat() {
        float data = 0;
        char temp[4] = {seek[3], seek[2], seek[1], seek[0]};
        memcpy(&data, temp, 4);
        seek += 4;
        return data;
    }

    double NBT::readDouble() {
        double data = 0;
        char temp[8] = {seek[7], seek[6], seek[5], seek[4], seek[3], seek[2], seek[1], seek[0]};
        memcpy(&data, temp, 8);
        seek += 8;
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
        if (n <= 0) return "";
        char *buff = new char[n + 1];
        memcpy(buff, seek, (size_t) n);
        buff[n] = 0;
        std::string data = buff;
        delete buff;
        seek += n;
        return data;
    }

    TagCompound *NBT::prase() {
        TagType rootType = (TagType) readByte();
        if (rootType != TagType::TypeCompound) {
            return nullptr;
        }
        int rootKeySize = readShort();
        std::cout << "rootKeySize:" << rootKeySize << " , seek-position:" << (NBT::seek - NBT::buff) << std::endl;
        return prase(readString(rootKeySize), false);
    }

    TagCompound *NBT::prase(std::string key, bool _inlist) {

        TagCompound *compound = new TagCompound(key);

        compound->setInlist(_inlist);

        while ((unsigned int) (seek - buff) < size) {
            TagType type = (TagType) readByte();
            printf("%d-%lu-", type, seek - buff);
            std::cout << "type@Comp:" << type << "<<" << std::endl;
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
                    int length = (int) readShort();
                    std::string nextKey = readString(length);
                    std::cout << "len:" << length << ",nextKey:" << nextKey << std::endl;
                    TagLong *tag = new TagLong(nextKey);
                    tag->setValue(readLong());
                    std::cout << "set value:" << tag->getValue() << std::endl;
                    compound->appendValue(tag);
                    break;
                }
                case TagType::TypeFloat: {
                    int length = readShort();
                    printf("float length:%d\n", length);
                    std::string nextKey = readString(length);
                    TagFloat *tag = new TagFloat(nextKey);
                    tag->setValue(readFloat());
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
                    int size = readInt();
                    TagList *tag = prase(nextKey, size, listType, false);
                    compound->appendValue(tag);
                    break;
                }
                case TagType::TypeCompound: {
                    int length = readShort();
                    std::string nextKey = readString(length);
                    TagCompound *tag = prase(nextKey, false);
                    compound->appendValue(tag);
                    break;
                }
            }
        }
        return compound;
    }

    TagList *NBT::prase(std::string key, int size, TagType listType, bool _inlist) {

        TagList *tagList = new TagList(key, listType);

        tagList->setInlist(_inlist);

        switch (listType) {
            case TagType::TypeEnd: {
                std::cout << "Maybe Something Error!!" << std::endl;
                break;
            }
            case TagType::TypeByte: {
                for (int i = 0; i < size; i++) {
                    TagByte *tag = new TagByte(true);
                    tag->setValue(readByte());
                    tagList->appendValue(tag);
                }
                break;
            }
            case TagType::TypeShort: {
                for (int i = 0; i < size; i++) {
                    TagShort *tag = new TagShort(true);
                    tag->setValue(readShort());
                    tagList->appendValue(tag);
                }
                break;
            }
            case TagType::TypeInt: {
                for (int i = 0; i < size; i++) {
                    TagInt *tag = new TagInt(true);
                    tag->setValue(readInt());
                    tagList->appendValue(tag);
                }
                break;
            }
            case TagType::TypeLong: {
                for (int i = 0; i < size; i++) {
                    TagLong *tag = new TagLong(true);
                    tag->setValue(readLong());
                    tagList->appendValue(tag);
                }
                break;
            }
            case TagType::TypeFloat: {
                for (int i = 0; i < size; i++) {
                    TagFloat *tag = new TagFloat(true);
                    tag->setValue(readFloat());
                    tagList->appendValue(tag);
                }
                break;
            }
            case TagType::TypeDouble: {
                for (int i = 0; i < size; i++) {
                    TagDouble *tag = new TagDouble(true);
                    tag->setValue(readDouble());
                    tagList->appendValue(tag);
                }
                break;
            }
            case TagType::TypeByteArray: {
                for (int i = 0; i < size; i++) {
                    int arraySize = readInt();
                    TagByteArray *tag = new TagByteArray(true, arraySize);
                    tag->setValue(readByteArray(arraySize));
                    tagList->appendValue(tag);
                }
                break;
            }
            case TagType::TypeIntArray: {
                for (int i = 0; i < size; i++) {
                    int arraySize = readInt();
                    TagIntArray *tag = new TagIntArray(true, arraySize);
                    tag->setValue(readIntArray(arraySize));
                    tagList->appendValue(tag);
                }
                break;
            }
            case TagType::TypeString: {
                for (int i = 0; i < size; i++) {
                    int length = readShort();
                    TagString *tag = new TagString(true);
                    tag->setValue(readString(length));
                    tagList->appendValue(tag);
                }
                break;
            }
            case TagType::TypeList: {
                for (int i = 0; i < size; i++) {
                    TagType type = (TagType) readByte();
                    int listSize = readInt();
                    TagList *tag = prase("list", listSize, type, true);
                    tagList->appendValue(tag);
                }
                break;
            }
            case TagType::TypeCompound: {
                for (int i = 0; i < size; i++) {
                    TagCompound *tag = prase("compound", true);
                    tagList->appendValue(tag);
                }
                break;
            }
        }
        return tagList;
    }

    void NBT::print() {
        for (int i = 0; i < NBT::size; i++) {
            std::cout << (0xff & NBT::buff[i]) << " ";
        }
    }

}
