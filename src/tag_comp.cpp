#include "api/tag_comp.h"

#include <utility>

namespace libnbt {

    bool NBTTagCompound::hasTag(const std::string& key) {
        return map.find(key) != map.end();
    }

    void NBTTagCompound::setTag(const std::string &key, NBTBase *tag) {
        if (hasTag(key)) {
            delete (map.at(key));
            map.at(key) = tag;
        } else {
            map.insert({key, tag});
        }
    }

    NBTBase *NBTTagCompound::getTag(const std::string &key) {
        return map.at(key);
    }

    void NBTTagCompound::read(std::istream &in) {
        clear();
        char child = -1;
        int16_t length = 0;
        in.get(child);
        while (child != 0 && !in.eof()) {
            NBTBase::read(in, (char *) &length, 2);
            std::string key = NBTBase::readString(in, length);
            NBTBase *tag = createNewTag((TAG_TYPE) child);
            tag->read(in);
            setTag(key, tag);
            in.get(child);
        }
    }

    void NBTTagCompound::write(std::ostream &out) {
        auto i = map.begin();
        for (; i != map.end(); i++) {
            out.put(i->second->type);
            auto l = (int16_t) i->first.size();
            NBTBase::write(out, (char *) &l, 2);
            out.write(i->first.c_str(), l);
            i->second->write(out);
            if (i->second->getType() == COMPOUND) {
                out.put(0);
            }
        }
    }

    void NBTTagCompound::clear() {
        auto i = map.begin();
        for (; i != map.end(); i++) {
            delete (i->second);
        }
        map.clear();
    }

    NBTTagCompound::NBTTagCompound() {
        this->type = COMPOUND;
    }

    NBTTagCompound::NBTTagCompound(std::string root) {
        this->type = COMPOUND;
        this->rootKey = std::move(root);
    }

    // TODO implement
    bool NBTTagCompound::check() {
        return true;
    }

    void NBTTagCompound::setRoot(std::string root) {
        this->rootKey = std::move(root);
    }

    std::string NBTTagCompound::getRoot() {
        return rootKey;
    }

    NBTTagCompound::~NBTTagCompound() {
        auto i = map.begin();
        for (; i != map.end(); i++) {
            delete (i->second);
        }
        map.clear();
    }
}
