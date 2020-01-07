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

        explicit NBTTagCompound(std::string root);

        bool hasTag(const std::string& key);

        void setTag(const std::string& key, NBTBase *tag);

        NBTBase *getTag(const std::string& key);

        void read(std::istream &in) override;

        void write(std::ostream &out) override;

        void clear();

        bool check();

        void setRoot(std::string root);

        std::string getRoot();

        ~NBTTagCompound() override;
    };
}

#endif //LIBNBT_TAG_COMP_H
