#include "stdafx.h"
#include "libnbt.h"

namespace libnbt {
    NBTTagCompound::NBTTagCompound() {
        this->_root = new std::string();
        this->map = new std::unordered_map<std::string, NBTBase *>();
    }
    NBTTagCompound::NBTTagCompound(std::string root) {
        this->_root = new std::string();
        this->map = new std::unordered_map<std::string, NBTBase *>();
        *this->_root = root;
    }
    NBTTagCompound::~NBTTagCompound() {
        clear();
        delete _root;
        delete map;
    }
    bool NBTTagCompound::has(const std::string key) {
        return map->find(key) != map->end();
    }
    void NBTTagCompound::set(std::string key, NBTBase * tag) {
        if (has(key)) {
            delete (map->at(key));
            map->at(key) = tag;
        } else {
            map->insert({ key, tag });
        }
    }
    NBTBase * NBTTagCompound::get(std::string key) {
        return map->at(key);
    }
    std::string NBTTagCompound::root() {
        return *_root;
    }
    void NBTTagCompound::root(std::string root) {
        *this->_root = root;
    }
    void NBTTagCompound::clear() {
        std::unordered_map<std::string, NBTBase *>::iterator i = map->begin();
        for (; i != map->end(); i++) {
            delete (i->second);
        }
        map->clear();
    }
    void NBTTagCompound::remove(std::string key) {
        if (has(key)) {
            map->erase(key);
        }
    }
    void NBTTagCompound::read(std::istream & in) {
        clear();
        char child = TYPE_UNKNOWN;
        int16_t length;
        std::string key;
        in.get(child);
        while (child != 0 && !in.eof()) {
            length = NBT::read_short(in);
            key = NBT::read_string(in, length);
            NBTBase *tag = NBT::create(child);
            tag->read(in);
            set(key, tag);
            in.get(child);
        }
    }
    void NBTTagCompound::write(std::ostream & out) {
        std::unordered_map<std::string, NBTBase *>::iterator i = map->begin();
        for (; i != map->end(); i++) {
            out.put(i->second->getType());
            int16_t length = (int16_t)i->first.size();
            NBT::write(out, length);
            NBT::write(out, i->first);
            i->second->write(out);
            if (i->second->getType() == TYPE_COMPOUND) {
                out.put(TYPE_END);
            }
        }
    }
    bool NBTTagCompound::equals(NBTBase * tag) {
        if (NBTBase::equals(tag)) {
            return false;
        }
        return false;
    }
}
