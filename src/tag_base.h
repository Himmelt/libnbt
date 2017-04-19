#ifndef LIBNBT_TAG_H
#define LIBNBT_TAG_H

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <typeinfo>

namespace libnbt {
    enum TAG_TYPE {
        END, BYTE, SHORT, INT, LONG, FLOAT, DOUBLE,
        BYTE_ARRAY, STRING, LIST, COMPOUND, INT_ARRAY
    };

    class NBTBase {
    protected:
        TAG_TYPE type = END;
    public:
        virtual void read(std::istream &in)=0;

        virtual void write(std::ostream &out)=0;

        virtual TAG_TYPE getType() { return type; }

        virtual bool equals(NBTBase &tag) {
            if (typeid(tag) == typeid(this)) {
                return this->type == tag.type;
            }
            return false;
        }
    };

    class NBTTagEnd : public NBTBase {
    public:
        void read(std::istream &in) override {}

        void write(std::ostream &out) override {}

    };

}

#endif //LIBNBT_TAG_H
