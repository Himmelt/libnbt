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
    using namespace std;

    class NBT {
    private:
        int8_t *buff = nullptr;
        int8_t *seek = nullptr;
        size_t size = 0;
        TagComp *tag = nullptr;

        int8_t read8();

        int16_t read16();

        int32_t read32();

        int64_t read64();

        float readfl();

        double readbl();

        string readstr(int n);

        void open(string filename);

        TagComp *prase(string _key, Type _type, Type _ltype, int32_t _lsize, bool _inlist);

    public:

        //NBT();

        NBT(string filename);

        NBT(int8_t *_buff, size_t _size);

        void printbuff();

        void printjson();

        void write(string filename, bool isGzip);

        TagComp *prase();
    };
}

#endif //LIBNBT_NBT_H
