#include "stdafx.h"
#include "libnbt.h"

namespace libnbt {
    NBTTagCompound::NBTTagCompound() {
        this->type = TYPE_COMPOUND;
        this->_root = new std::string();
        this->map = new std::unordered_map<std::string, NBTBase *>();
    }
    NBTTagCompound::NBTTagCompound(std::string root) {
        this->type = TYPE_COMPOUND;
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
    bool NBTTagCompound::has(const std::string key, const char type) {
        return has(key) && get(key)->getType() == type;
    }
    void NBTTagCompound::set(std::string key, NBTBase * tag) {
        if (has(key)) {
            delete (map->at(key));
            map->at(key) = tag;
        } else {
            map->insert({ key, tag });
        }
    }
    NBTBase * NBTTagCompound::get(const std::string key) {
        return map->at(key);
    }
    int NBTTagCompound::size() {
        return map->size();
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
        while (child != TYPE_END && !in.eof()) {
            if (child < 0 || child >11) {
                NBT::LOG() << "Error Tag:" << child << std::endl;
            }
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
        }
        out.put(TYPE_END);
    }
    bool NBTTagCompound::equals(NBTBase * tag) {
        if (NBTBase::equals(tag)) {
            return false;
        }
        return false;
    }
}
