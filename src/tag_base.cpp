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

    bool NBTBase::BigEndian = isBigEndian();

    bool NBTBase::isBigEndian() {
        int32_t num = 0x12345678;
        return ((int8_t *) &num)[0] == 0x12;
    }

}
