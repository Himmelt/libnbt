#include "stdafx.h"
#include "libnbt.h"

namespace libnbt {

    void Region::read(std::iostream & in) {
        in.read(offset, 4096);
        in.read(timestamp, 4096);
        for (int z = 0; z < 32; z++) {
            for (int x = 0; x < 32; x++) {
                in.seekg(getoff(x, z));
                int32_t length = NBT::read_int(in);
                int8_t ztype = NBT::read_byte(in);
                s_uncompress(in, length, nbt);
                NBT::readNbt(nbt, &chunks[x][z]);
            }
        }
    }

    void Region::write(std::iostream & out) {
        for (int x = 0; x < 32; x++) {
            for (int z = 0; z < 32; z++) {

            }
        }
    }

}
