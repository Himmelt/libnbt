#include "szlib.h"
#include "stdafx.h"

int s_compress(std::string &data) {
    uLongf src_size = data.size();
    uLongf des_size = compressBound(src_size);
    Bytef *des = new Bytef[des_size];
    int flag = compress(des, &des_size, (Bytef*)data.c_str(), src_size);
    data.assign((char*)des, des_size);
    delete[](des);
    return flag;
}

int s_uncompress(std::string &data) {
    uLongf src_size = data.size();
    uLongf des_size = src_size;
    Bytef *des = new Bytef[des_size];
    int flag = uncompress(des, &des_size, (Bytef*)data.c_str(), src_size);
    //&& des_size < 10 * src_size
    while (flag == Z_BUF_ERROR ) {
        delete[](des);
        des_size = des_size + src_size;
        des = new Bytef[des_size];
        flag = uncompress(des, &des_size, (Bytef*)data.c_str(), src_size);
    }
    data.assign((char*)des, des_size);
    delete[](des);
    return flag;
}
