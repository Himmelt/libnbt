#include "szlib.h"
#include "stdafx.h"

int s_uncompress(std::iostream &in, size_t size, std::iostream &out) {
    Bytef *src = new Bytef[size];
    Bytef *des = new Bytef[size];
    uLongf src_size = size;
    uLongf des_size = size;
    in.read((char*)src, size);
    int flag = uncompress(des, &des_size, src, src_size);
    while (flag == Z_BUF_ERROR && des_size < 10 * src_size) {
        delete[](des);
        des_size = des_size + src_size;
        des = new Bytef[des_size];
        flag = uncompress(des, &des_size, src, src_size);
    }
    out.write((char*)des, des_size);
    out.flush();
    delete[](src);
    delete[](des);
    return flag;
}
