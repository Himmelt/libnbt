#ifndef LIBNBT_TAG_H
#define LIBNBT_TAG_H

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <typeinfo>
#include <unordered_map>
#include "tag_type.h"

namespace libnbt {

    class NBTBase {
    private:
        virtual void read(std::istream in) = 0;

        virtual void write(std::ostream out) = 0;

    protected:
        TAG_TYPE type;

        static NBTBase *createNewByType(TAG_TYPE type);

    public:

        TAG_TYPE getType() { return type; };

        virtual bool equals(NBTBase *tag) {
            if (typeid(tag) != typeid(this)) {
                return false;
            } else {
                return this->type == tag->type;
            }
        }
    };


}

#endif //LIBNBT_TAG_H
