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
        std::string rootKey = "";
    public:

        NBTTagCompound();

        NBTTagCompound(std::string rootKey);

        bool hasTag(const std::string key);

        void setTag(std::string key, NBTBase *tag);

        NBTBase *getTag(std::string key);

        void read(std::istream &in) override;

        void write(std::ostream &out) override;

        void clear();

        bool check();

        void setRoot(std::string rootKey);

        std::string getRoot();
    };
}

#endif //LIBNBT_TAG_COMP_H
