#ifndef LIBNBT_TAG_COMP_H
#define LIBNBT_TAG_COMP_H

#pragma once

#include "tag_base.h"
#include <string>
#include <unordered_map>

namespace libnbt {

    class NBTTagCompound : public NBTBase {
    private:
        std::unordered_map<std::string, NBTBase *> map;

    public:

        bool hasTag(const std::string key) {
            return map.find(key) != map.end();
        }

        void setTag(std::string key, NBTBase *tag) {
            if (hasTag(key)) {
                map.at(key) = tag;
            } else {
                map.insert({key, tag});
            }
        }

        NBTBase *getTag(std::string key) {
            return map.at(key);
        }

        void read(std::istream &in) override {

        }

        void write(std::ostream &out) override {

        }

    };
}

#endif //LIBNBT_TAG_COMP_H
