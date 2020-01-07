#ifndef LIBNBT_TAG_BASE_H
#define LIBNBT_TAG_BASE_H

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <typeinfo>

namespace libnbt {

    static const int32_t testEndian = 0x12345678;
    static const bool littleEndian = ((int8_t *) &testEndian)[0] == 0x78;

    enum TAG_TYPE {
        END, BYTE, SHORT, INT, LONG, FLOAT, DOUBLE,
        BYTE_ARRAY, STRING, LIST, COMPOUND, INT_ARRAY
    };

    class NBTBase {
    public:
        char type = 0;

        virtual void read(std::istream &in) = 0;

        virtual void write(std::ostream &out) = 0;

        virtual TAG_TYPE getType();

        virtual bool equals(NBTBase &tag);

        static NBTBase *createNewTag(TAG_TYPE type);

        static void read(std::istream &in, char *data, uint8_t width);

        static void write(std::ostream &out, const char *data, uint8_t width);

        static std::string readString(std::istream &in, int16_t length);

        static bool readNbt(std::istream &in, NBTBase *tag);

        static bool writeNbt(std::ostream &out, NBTBase *tag);

        virtual ~NBTBase();
    };

    class NBTTagEnd : public NBTBase {
    public:
        void read(std::istream &in) override {}

        ~NBTTagEnd() override = default;

        void write(std::ostream &out) override {}
    };
}

#endif //LIBNBT_TAG_BASE_H
