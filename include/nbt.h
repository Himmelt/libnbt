/*******************************************************************************
 * Created by Himmelt on 2016/8/18.
 * Copyright (c) 2015-2016. Himmelt All rights reserved.
 * https://opensource.org/licenses/MIT
 ******************************************************************************/
#ifndef LIBNBT_NBT_H
#define LIBNBT_NBT_H

#pragma once

#include <iostream>
#include <fstream>
#include <zlib.h>
#include "tag.h"

namespace libnbt {

    class NBT {
    private:
        int8_t *buff = nullptr;
        int8_t *seek = nullptr;
        unsigned int size = 0;

        Tag *tag = nullptr;

    public:
        NBT();

        NBT(std::string filename);

        NBT(int8_t *buff, unsigned int size);

        ~NBT();

        void print();

        void open(std::string filename);

        void write(std::string filename, bool isGzip);

        int8_t readByte();

        int16_t readShort();

        int32_t readInt();

        int64_t readLong();

        float readFloat();

        double readDouble();

        int8_t *readByteArray(int n);

        int32_t *readIntArray(int n);

        std::string readString(int n);

        TagCompound *prase();

        TagCompound *prase(std::string key, bool _inlist);

        TagList *prase(std::string key, int size, TagType listType, bool _inlist);
    };

}

#endif //LIBNBT_NBT_H
