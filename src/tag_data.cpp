#include "api/tag_data.h"

namespace libnbt {

    void NBTTagString::read(std::istream &in) {
        int16_t length = 0;
        NBTBase::read(in, (char *) &length, 2);
        _data = NBTBase::readString(in, length);
    }

    void NBTTagString::write(std::ostream &out) {
        auto length = (int16_t) _data.size();
        NBTBase::write(out, (char *) &length, 2);
        out.write(_data.c_str(), length);
    }
}
