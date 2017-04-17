#ifndef LIBNBT_TAG_DATA_H
#define LIBNBT_TAG_DATA_H

#include "tag_base.h"

namespace libnbt {

    template<class T>
    class NBTTagData : public NBTBase {
    private:
        T data;

        uint8_t width;

        void read(std::istream in) override {
        }

        void write(std::ostream out) override {}

    public:
        NBTTagData(T data) {
            this->data = data;
        }

        void setData(T data) {
            this->data = data;
            if (typeid(T) == typeid(int8_t)) {
                type = BYTE;
            }
            if (typeid(T) == typeid(int16_t)) {
                type = SHORT;
            }
            if (typeid(T) == typeid(int32_t)) {
                type = INT;
            }
            if (typeid(T) == typeid(int64_t)) {
                type = LONG;
            }
            if (typeid(T) == typeid(float)) {
                type = FLOAT;
            }
            if (typeid(T) == typeid(double)) {
                type = DOUBLE;
            }
            if (typeid(T) == typeid(std::string)) {
                type = STRING;
            }
        }

        T getData() {
            return data;
        }
    };
}

#endif //LIBNBT_TAG_DATA_H
