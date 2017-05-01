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
            // 父类虚函数a调用虚函数b,执行的是子类虚函数b还是父类虚函数b
            return (NBTTagByte*)get(key);
        }
        return nullptr;
    }
}
