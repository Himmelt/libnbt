#include "api/tag_data.h"

namespace libnbt {

    void NBTTagString::read(std::istream &in) {
        int16_t length = 0;
        in.read((char *) &length, 2);
        data.clear();
        for (int i = 0; i < length; i++) {
            char temp = 0;
            in.read(&temp, 1);
            data.push_back(temp);
        }
    }

    void NBTTagString::write(std::ostream &out) {
        int16_t length = (int16_t) data.size();
        out.write((char *) &length, 2);
        out.write(data.c_str(), length);
    }
}
