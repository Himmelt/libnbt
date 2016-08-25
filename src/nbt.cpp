/*******************************************************************************
 * Created by Himmelt on 2016/8/18.
 * Copyright (c) 2015-2016. Himmelt All rights reserved.
 * https://opensource.org/licenses/MIT
 ******************************************************************************/
#include "../include/nbt.h"

namespace libnbt {
    //NBT::NBT()
    //{
    //    buff = seek = nullptr;
    //    tag = nullptr;
    //    size = 0;
    //}
    NBT::NBT(string filename) {
        open(filename);
        seek = buff;
        tag = prase();
    }

    NBT::NBT(int8_t *_buff, size_t _size) {
        seek = buff = _buff;
        size = _size;
    }

    TagComp *NBT::prase() {
        if (read8() != 0x0a) {
            return nullptr;
        }
        return prase(readstr(read16()), Type::Comp, Type::End, 1, false);
    }

    int8_t NBT::read8() {
        //printf("SEEK:%u\n", seek);
        return seek++[0];
    }

    int16_t NBT::read16() {
        int16_t data = 0;
        char temp[2] = {seek[1], seek[0]};
        memcpy(&data, temp, 2);
        seek += 2;
        return data;
    }

    int32_t NBT::read32() {
        int32_t data = 0;
        char temp[4] = {seek[3], seek[2], seek[1], seek[0]};
        memcpy(&data, temp, 4);
        seek += 4;
        return data;
    }

    int64_t NBT::read64() {
        int64_t data = 0;
        char temp[8] = {seek[7], seek[6], seek[5], seek[4], seek[3], seek[2], seek[1], seek[0]};
        memcpy(&data, temp, 8);
        seek = seek + 8;
        return data;
    }

    float NBT::readfl() {
        float data = 0;
        char temp[4] = {seek[3], seek[2], seek[1], seek[0]};
        memcpy(&data, temp, 4);
        seek += 4;
        return data;
    }

    double NBT::readbl() {
        double data = 0;
        char temp[8] = {seek[7], seek[6], seek[5], seek[4], seek[3], seek[2], seek[1], seek[0]};
        memcpy(&data, temp, 8);
        seek += 8;
        return data;
    }

    string NBT::readstr(int n) {
        string data = "";
        while (n--) {
            data.push_back(read8());
        }
        return data;
    }

    void NBT::open(string filename) {
        filebuf filebuf;
        filebuf.open(filename, ios::in | ios::binary);

        if (filebuf.is_open()) {
            cout << "open" << endl;
            char head[4];
            filebuf.sgetn(head, 2);
            // gzip header ?
            printf("head:%02x,%02x\n", head[0], head[1] & 0xff);
            if ((head[0] & 0xff) == 0x1f && (head[1] & 0xff) == 0x8b) {
                cout << "gzip" << endl;
                filebuf.pubseekoff(-4, ios::end);
                filebuf.sgetn(head, 4);
                size = (head[3] & 0xff | size) << 8;
                size = (head[2] & 0xff | size) << 8;
                size = (head[1] & 0xff | size) << 8;
                size = head[0] & 0xff | size;

                printf("i size:%02x,%02x,%02x,%02x\n", head[3] & 0xff, head[2] & 0xff, head[1] & 0xff, head[0] & 0xff);


                gzFile gzfile = gzopen(filename.c_str(), "rb");

                if (gztell(gzfile) >= 0) {

                    cout << "size:" << size << endl;
                    printf(",,,%u,,,", size);

                    buff = new int8_t[size];
                    int code = gzread(gzfile, buff, (unsigned int) size);
                    if (code <= 0) {
                        cout << "code:" << code << endl;
                        cout << "uncompress gzip failed!" << endl;
                    } else {
                        cout << "return size(Byte):" << code << endl;
                        cout << "uncompress gzip success!" << endl;
                        cout << "buff point:" << static_cast<const void *>(buff) << endl;
                    }
                } else {
                    cout << "read gzip failed!" << endl;
                }
                gzclose(gzfile);
            } else {
                size = (unsigned int) filebuf.pubseekoff(0, ios::end, ios::in);
                if (size <= 0) {
                    cout << "read file failed!" << endl;
                } else {
                    buff = new int8_t[size];
                    filebuf.pubseekpos(0, ios::in);
                    filebuf.sgetn((char *) buff, size);
                    cout << "read file success!" << endl;
                }
            }
        } else {
            cout << "read file error!" << endl;
        }
        filebuf.close();
    }

    TagComp *NBT::prase(string _key, Type _type, Type _ltype, int32_t _lsize, bool _inlist) {

        TagComp *comp = nullptr;
        string nKey = "";
        bool islist = _type == Type::List;

        if (!islist && _inlist) comp = new TagComp();
        if (!islist && !_inlist) comp = new TagComp(_key);
        if (islist && _inlist) comp = new TagComp(_ltype);
        if (islist && !_inlist) comp = new TagComp(_key, _ltype);

        while ((size_t) (seek - buff) < size) {

            printf("==========================================\n");

            if (!islist) {
                _ltype = (Type) read8();
                if (_ltype != Type::End) {
                    cout << "SEEK:" << seek - buff << "|Type:" << _ltype;
                    int16_t len = read16();
                    nKey = readstr(len);
                    cout << "|Len:" << len << "|KEY:" << nKey << endl;
                }
            }

            switch (_ltype) {
                case Type::End:
                    return comp;
                case Type::Byte: {
                    while (_lsize--) {
                        TagByte *tag = islist ? new TagByte() : new TagByte(nKey);
                        tag->setVal(read8());
                        comp->addVal(tag);
                    }
                    break;
                }
                case Type::Short: {
                    while (_lsize--) {
                        TagShort *tag = islist ? new TagShort() : new TagShort(nKey);
                        tag->setVal(read16());
                        comp->addVal(tag);
                    }
                    break;
                }
                case Type::Int: {
                    while (_lsize--) {
                        TagInt *tag = islist ? new TagInt() : new TagInt(nKey);
                        tag->setVal(read32());
                        comp->addVal(tag);
                    }
                    break;
                }
                case Type::Long: {
                    while (_lsize--) {
                        TagLong *tag = islist ? new TagLong() : new TagLong(nKey);
                        tag->setVal(read64());
                        comp->addVal(tag);
                    }
                    break;
                }
                case Type::Float: {
                    while (_lsize--) {
                        TagFloat *tag = islist ? new TagFloat() : new TagFloat(nKey);
                        tag->setVal(readfl());
                        comp->addVal(tag);
                    }
                    break;
                }
                case Type::Double: {
                    while (_lsize--) {
                        TagDouble *tag = islist ? new TagDouble() : new TagDouble(nKey);
                        tag->setVal(readbl());
                        comp->addVal(tag);
                    }
                    break;
                }
                case Type::String: {
                    ///////////////////////////////
                    while (_lsize--) {
                        TagString *tag = islist ? new TagString() : new TagString(nKey);
                        int16_t size = read16();
                        tag->setVal(readstr(size));
                        comp->addVal(tag);
                    }
                    break;
                }
                case Type::BytA: {
                    while (_lsize--) {
                        TagBytA *tag = islist ? new TagBytA() : new TagBytA(nKey);
                        int32_t size = read32();
                        vector<int8_t> val;
                        while (size--) val.push_back(read8());
                        tag->setVal(val);
                        comp->addVal(tag);
                    }
                    break;
                }
                case Type::IntA: {
                    while (_lsize--) {
                        TagIntA *tag = islist ? new TagIntA() : new TagIntA(nKey);
                        int32_t size = read32();
                        vector<int32_t> val;
                        while (size--) val.push_back(read32());
                        tag->setVal(val);
                        comp->addVal(tag);
                    }
                    break;
                }

                case Type::List: {
                    while (_lsize--) {
                        Type ltype = (Type) read8();
                        int32_t size = read32();
                        TagComp *tag = prase(nKey, Type::List, ltype, size, islist);
                        comp->addVal(tag);
                    }
                    break;
                }
                case Type::Comp: {
                    while (_lsize--) {
                        TagComp *tag = prase(nKey, Type::Comp, Type::End, 1, islist);
                        comp->addVal(tag);
                    }
                    break;
                }
            }
            if (islist)return comp;
            else _lsize = 1;
        }
        return comp;
    }

    void NBT::printbuff() {
        for (size_t i = 0; i < size; i++) {
            printf("%02x ", 0xff & buff[i]);
        }
        printf("\n");
    }

    void NBT::printjson() {
        cout << "=====================json===============================" << endl;
        cout << "{" << tag << "}" << endl;
        cout << "=====================json===============================" << endl;
    }

    void NBT::write(string filename, bool isGzip) {

    }

}
