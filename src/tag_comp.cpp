#include "api/tag_comp.h"

namespace libnbt {

    bool NBTTagCompound::hasTag(const std::string key) {
        return map.find(key) != map.end();
    }

    void NBTTagCompound::setTag(std::string key, NBTBase *tag) {
        if (hasTag(key)) {
            map.at(key) = tag;
        } else {
            map.insert({key, tag});
        }
    }

    NBTBase *NBTTagCompound::getTag(std::string key) {
        return map.at(key);
    }

    void NBTTagCompound::read(std::istream &in) {
        clear();
        in.get(type);
        int16_t length = 0;
        in.read((char *) &length, 2);
        for (int i = 0; i < length; i++) {
            char temp = 0;
            in.read(&temp, 1);
            root.push_back(temp);
        }
        char child = 0;
        in.get(child);
        switch ((TAG_TYPE) child) {
            case END:
            case BYTE:
            case SHORT:
            default: {
            }
        }
    }

    void NBTTagCompound::write(std::ostream &out) {
        out.put(type);
        int16_t length = (int16_t) root.size();
        out.write((char *) &length, 2);
        out.write(root.c_str(), length);
        std::unordered_map<std::string, NBTBase *>::iterator i = map.begin();
        for (; i != map.end(); i++) {
            out.put(i->second->type);
            int16_t l = (int16_t) i->first.size();
            out.write((char *) &l, 2);
            out.write(i->first.c_str(), l);
            i->second->write(out);
        }
    }

    void NBTTagCompound::clear() {
        std::unordered_map<std::string, NBTBase *>::iterator i = map.begin();
        for (; i != map.end(); i++) {
            delete (i->second);
        }
        map.clear();
    }

    NBTTagCompound::NBTTagCompound() {
        this->type = COMPOUND;
    }

    NBTTagCompound::NBTTagCompound(std::string root) {
        this->root = root;
    }

    bool NBTTagCompound::check() {
        return true;
    }

}
