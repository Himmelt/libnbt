#include "stdafx.h"
#include "libnbt.h"

namespace libnbt {

    Region::Region() {
        for (int x = 0; x < 32; x++) {
            for (int z = 0; z < 32; z++) {
                chunks[x][z] = &empty_chunk;
            }
        }
    }
    void Region::write(std::ostream & out) {
        for (int x = 0; x < 32; x++) {
            for (int z = 0; z < 32; z++) {
                //offset[x][z]=
            }
        }
    }

}