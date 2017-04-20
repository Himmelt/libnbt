#ifndef LIBNBT_TAG_BASE_H
#define LIBNBT_TAG_BASE_H

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <typeinfo>
#include "tag_data.h"
#include "tag_vector.h"
#include "tag_comp.h"

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

        static NBTBase *createNewTag(TAG_TYPE type) {
            switch (type) {
                case END:
                    return new NBTTagEnd();
                case BYTE:
                    return new NBTTagByte();
                case SHORT:
                    return new NBTTagShort();
                case INT:
                    return new NBTTagInt();
                case LONG:
                    return new NBTTagLong();
                case FLOAT:
                    return new NBTTagFloat();
                case DOUBLE:
                    return new NBTTagDouble();
                case BYTE_ARRAY:
                    return new NBTTagByteArray();
                case STRING:
                    return new NBTTagString();
                case LIST:
                    return new NBTTagList();
                case COMPOUND:
                    return new NBTTagCompound();
                case INT_ARRAY:
                    return new NBTTagIntArray();
                default:
                    return new NBTTagEnd();
            }
        }
    };

    class NBTTagEnd : public NBTBase {
    public:
        void read(std::istream &in) override {}

        void write(std::ostream &out) override {}
    };

}

#endif //LIBNBT_TAG_BASE_H
