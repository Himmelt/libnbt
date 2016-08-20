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
    public:
        NBT();

        NBT(std::string filename);

        NBT(int8_t *buff, unsigned int size);

        ~NBT();

        void open(std::string filename);

        int8_t readByte();

        int16_t readShort();

        int32_t readInt();

        int64_t readLong();

        float readFloat();

        double readDouble();

        int8_t *readByteArray(int n);

        int32_t *readIntArray(int n);

        std::string readString(int n);

        TagCompound *prase(std::string key);

        TagList *prase(std::string key, int size, TagType listType);
    };

#pragma clang diagnostic pop
}

#endif //LIBNBT_NBT_H
