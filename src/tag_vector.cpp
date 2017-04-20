#include "api/tag_vector.h"

namespace libnbt {

    NBTTagList::NBTTagList(TAG_TYPE child) : NBTTagVector::NBTTagVector() {
        this->child = child;
    }

    TAG_TYPE NBTTagList::getListType() { return (TAG_TYPE) child; }

    void NBTTagList::read(std::istream &in) {
        in.get(child);
        int32_t size = 0;
        in.read((char *) &size, 4);
        for (int i = 0; i < size; i++) {
            NBTBase *tag = createNewTag((TAG_TYPE) child);
            tag->read(in);
            array.push_back(tag);
        }
    }

    void NBTTagList::write(std::ostream &out) {
        int32_t size = (int32_t) array.size();
        out.put(child);
        out.write((char *) &size, 4);
        for (int i = 0; i < size; i++) {
            array[i]->write(out);
        }
    }

}