#include "api/libnbt.h"

namespace libnbt {

    TAG_TYPE NBTBase::getType() {
        return (TAG_TYPE) type;
    }

    bool NBTBase::equals(NBTBase &tag) {
        if (typeid(tag) == typeid(this)) {
            return this->type == tag.type;
        }
        return false;
    }

    template<class T>
    void NBTTagData<T>::read(std::istream &in) {
        readBytes(in, (char *) &_data, width);
    }

    template<class T>
    void NBTTagData<T>::write(std::ostream &out) {
        writeBytes(out, (const char *) &_data, width);
    }

    void NBTTagString::read(std::istream &in) {
        int16_t length = 0;
        readBytes(in, (char *) &length, 2);
        _data = readString(in, length);
    }

    void NBTTagString::write(std::ostream &out) {
        auto length = (int16_t) _data.size();
        writeBytes(out, (char *) &length, 2);
        out.write(_data.c_str(), length);
    }

    template<class T>
    void NBTTagVector<T>::read(std::istream &in) {
        int32_t size = 0;
        readBytes(in, (char *) &size, 4);
        clear();
        for (int i = 0; i < size; i++) {
            T temp;
            readBytes(in, (char *) &temp, width);
            array.push_back(temp);
        }
    }

    template<class T>
    void NBTTagVector<T>::write(std::ostream &out) {
        auto size = (int32_t) array.size();
        writeBytes(out, (char *) &size, 4);
        for (int i = 0; i < size; i++) {
            T temp = array[i];
            writeBytes(out, (char *) &temp, width);
        }
    }

    NBTTagList::NBTTagList(TAG_TYPE child) : NBTTagVector::NBTTagVector() {
        this->child = child;
    }

    TAG_TYPE NBTTagList::getListType() { return (TAG_TYPE) child; }

    void NBTTagList::read(std::istream &in) {
        in.get(child);
        int32_t size = 0;
        readBytes(in, (char *) &size, 4);
        clear();
        for (int i = 0; i < size; i++) {
            NBTBase *tag = createNewTag((TAG_TYPE) child);
            tag->read(in);
            array.push_back(tag);
        }
    }

    void NBTTagList::write(std::ostream &out) {
        auto size = (int32_t) array.size();
        out.put(child);
        writeBytes(out, (char *) &size, 4);
        for (int i = 0; i < size; i++) {
            array[i]->write(out);
        }
    }

    void NBTTagList::clear() {
        for (auto &i : array) {
            delete i;
        }
        array.clear();
    }

    bool NBTTagList::remove(size_t index) {
        if (index < array.size()) {
            delete (array[index]);
            array.erase(array.begin() + index);
            return true;
        }
        return false;
    }

    void NBTTagList::set(size_t index, NBTBase *data) {
        if (index >= 0 && index < array.size()) {
            delete (array[index]);
            array[index] = data;
        }
    }

    NBTTagList::~NBTTagList() {
        for (auto &i : array) {
            delete i;
        }
        array.clear();
    }

    bool NBTTagCompound::hasTag(const std::string &key) {
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

    std::set<std::string> NBTTagCompound::getKeys() {
        std::set<std::string> keys;
        for (auto & i : map) {
            keys.insert(i.first);
        }
        return keys;
    }

    void NBTTagCompound::read(std::istream &in) {
        clear();
        char child = -1;
        int16_t length = 0;
        in.get(child);
        while (child != 0 && !in.eof()) {
            readBytes(in, (char *) &length, 2);
            std::string key = readString(in, length);
            NBTBase *tag = createNewTag((TAG_TYPE) child);
            tag->read(in);
            setTag(key, tag);
            in.get(child);
        }
    }

    void NBTTagCompound::write(std::ostream &out) {
        auto i = map.begin();
        for (; i != map.end(); i++) {
            out.put(i->second->getType());
            auto size = (int16_t) i->first.size();
            writeBytes(out, (char *) &size, 2);
            out.write(i->first.c_str(), size);
            i->second->write(out);
            if (i->second->getType() == COMPOUND) {
                out.put(END);
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
