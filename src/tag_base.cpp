#include "api/tag_base.h"
#include "api/tag_data.h"
#include "api/tag_vector.h"
#include "api/tag_comp.h"

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

    NBTBase *NBTBase::createNewTag(TAG_TYPE type) {
        switch (type) {
            case END:
                return new NBTTagEnd();
            case BYTE:
                return new NBTTagByte();
            case SHORT:
                return new NBTTagShort();
            case INT:
                return new NBTTagInt();
            case LONG:
                return new NBTTagLong();
            case FLOAT:
                return new NBTTagFloat();
            case DOUBLE:
                return new NBTTagDouble();
            case BYTE_ARRAY:
                return new NBTTagByteArray();
            case STRING:
                return new NBTTagString();
            case LIST:
                return new NBTTagList();
            case COMPOUND:
                return new NBTTagCompound();
            case INT_ARRAY:
                return new NBTTagIntArray();
            default:
                return new NBTTagEnd();
        }
    }

    void NBTBase::read(std::istream &in, char *data, uint8_t width) {
        if (width > 1 && littleEndian()) {
            char t, *temp = new char[width];
            in.read(temp, width);
            for (int i = 0; i < width / 2; i++) {
                t = temp[i];
                temp[i] = temp[width - i - 1];
                temp[width - i - 1] = t;
            }
            memcpy(data, temp, width);
            delete[](temp);
        } else {
            in.read(data, width);
        }
    }

    void NBTBase::write(std::ostream &out, const char *data, uint8_t width) {
        if (width > 1 && littleEndian()) {
            char t, *temp = new char[width];
            memcpy(temp, data, width);
            for (int i = 0; i < width / 2; i++) {
                t = temp[i];
                temp[i] = temp[width - i - 1];
                temp[width - i - 1] = t;
            }
            out.write(temp, width);
            delete[](temp);
        } else {
            out.write(data, width);
        }
    }

    std::string NBTBase::readString(std::istream &in, int16_t length) {
        std::string temp;
        temp.clear();
        char s;
        while (length--) {
            in.get(s);
            temp.push_back(s);
        }
        return temp;
    }

    bool NBTBase::readNbt(std::istream &in, NBTBase *tag) {
        char head = -1;
        char foot = -1;
        in.get(head);
        if (tag->getType() == COMPOUND && head == COMPOUND) {
            auto *compound = (NBTTagCompound *) tag;
            int16_t length = 0;
            NBTBase::read(in, (char *) &length, 2);
            compound->setRoot(NBTBase::readString(in, length));
            compound->read(in);
            in.get(foot);
            return foot == END;
        }
        return false;
    }

    bool NBTBase::writeNbt(std::ostream &out, NBTBase *tag) {
        if (tag->getType() == COMPOUND) {
            out.put(COMPOUND);
            auto *compound = (NBTTagCompound *) tag;
            int16_t length = (int16_t) compound->getRoot().size();
            NBTBase::write(out, (char *) &length, 2);
            out.write(compound->getRoot().c_str(), length);
            tag->write(out);
            out.put(0);
            return true;
        }
        return false;
    }

    NBTBase::~NBTBase() = default;
}
