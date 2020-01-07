#include "api/tag_vector.h"

namespace libnbt {

    NBTTagList::NBTTagList(TAG_TYPE child) : NBTTagVector::NBTTagVector() {
        this->child = child;
    }

    TAG_TYPE NBTTagList::getListType() { return (TAG_TYPE) child; }

    void NBTTagList::read(std::istream &in) {
        in.get(child);
        int32_t size = 0;
        NBTBase::read(in, (char *) &size, 4);
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
        NBTBase::write(out, (char *) &size, 4);
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
}