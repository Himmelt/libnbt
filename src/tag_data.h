#ifndef LIBNBT_TAG_DATA_H
#define LIBNBT_TAG_DATA_H

#include "tag_base.h"

namespace libnbt {

    template<class T>
    class NBTTagData : public NBTBase {
    private:
        T data;

        uint8_t width;

    public:
        NBTTagData(T data) {
            setData(data);
        }

        void setData(T data) {
            this->data = data;
            std::cout << "TYPE:" << typeid(T).name() << "|-|" << typeid(int8_t).name() << std::endl;
            if (typeid(T) == typeid(int8_t)) {
                type = BYTE;
                width = 1;
            } else if (typeid(T) == typeid(int16_t)) {
                type = SHORT;
                width = 2;
            } else if (typeid(T) == typeid(int32_t)) {
                type = INT;
                width = 4;
            } else if (typeid(T) == typeid(int64_t)) {
                type = LONG;
                width = 8;
            } else if (typeid(T) == typeid(float)) {
                type = FLOAT;
                width = 4;
            } else if (typeid(T) == typeid(double)) {
                type = DOUBLE;
                width = 8;
            } else if (typeid(T) == typeid(std::string)) {
                type = STRING;
                width = 0;
            } else {
                type = END;
                width = 0;
            }
            std::cout << type << "|" << (unsigned short) width << std::endl;
        }

        T getData() {
            return data;
        }

        void read(std::istream &in) override {
            in.read((char *) &data, width);
        }

        void write(std::ostream &out) override {
            std::cout << "width:" << (unsigned short) width << std::endl;
            char *p = (char *) &data;
            std::cout << (unsigned short) p[0] << "-" << (unsigned short) p[1] << std::endl;
            out.write((char *) &data, width);
        }
    };
}

#endif //LIBNBT_TAG_DATA_H
