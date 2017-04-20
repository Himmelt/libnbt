#ifndef LIBNBT_TAG_BASE_H
#define LIBNBT_TAG_BASE_H

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
        char type = 0;
    public:
        virtual void read(std::istream &in)=0;

        virtual void write(std::ostream &out)=0;

        virtual TAG_TYPE getType();

        virtual bool equals(NBTBase &tag);

        static NBTBase *createNewTag(TAG_TYPE type);
    };

    class NBTTagEnd : public NBTBase {
    public:
        void read(std::istream &in) override {}

        void write(std::ostream &out) override {}
    };

}

#endif //LIBNBT_TAG_BASE_H
