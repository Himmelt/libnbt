#include "stdafx.h"
#include "libnbt.h"

namespace libnbt {

    int NBT::s_compress(std::string &data) {
        uLongf src_size = data.size();
        uLongf des_size = compressBound(src_size);
        Bytef *des = new Bytef[des_size];
        int flag = compress(des, &des_size, (Bytef*)data.c_str(), src_size);
        data.assign((char*)des, des_size);
        delete[](des);
        return flag;
    }

    int NBT::s_uncompress(std::string &data) {
        uLongf src_size = data.size();
        uLongf des_size = 0x1000000;
        static Bytef des[0x1000000];
        int flag = uncompress(des, &des_size, (Bytef*)data.c_str(), src_size);
        data.assign((char*)des, des_size);
        return flag;
    }

}
