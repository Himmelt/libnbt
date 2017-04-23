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
}
