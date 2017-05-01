#include "stdafx.h"
#include "libnbt.h"

namespace libnbt {
    char NBTBase::getType() {
        return type;
    }
    bool NBTBase::equals(NBTBase * tag) {
        if (typeid(tag) == typeid(this)) {
            return this->type == tag->type;
        }
        return false;
    }
    bool NBTBase::has(const std::string key) {
        return false;
    }
    bool NBTBase::has(const std::string key, const char type) {
        return false;
    }
    NBTBase * NBTBase::get(const std::string key) {
        return nullptr;
    }
    NBTTagByte * NBTBase::get_byte(const std::string key) {
        if (has(key, TYPE_BYTE)) {
            // �����麯��a�����麯��b,ִ�е��������麯��b���Ǹ����麯��b
            return (NBTTagByte*)get(key);
        }
        return nullptr;
    }
}
