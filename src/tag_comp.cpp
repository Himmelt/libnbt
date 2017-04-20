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

    }

    void NBTTagCompound::write(std::ostream &out) {

    }

    void NBTTagCompound::clear() {
        std::unordered_map<std::string, NBTBase *>::iterator i = map.begin();
        for (; i != map.end(); i++) {
            delete (i->second);
        }
        map.clear();
    }

}
