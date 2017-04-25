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
    void Region::read(std::istream & in) {
        size_t _seek = 0;
        for (int z = 0; z < 32; z++) {
            for (int x = 0; x < 32; x++) {
                in.seekg(4*x + 128*z);
                offset[x][z] = NBT::read_int(in);
                in.seekg(4*x + 128*z + 4096);
                timestamp[x][z] = NBT::read_int(in);
                in.seekg((offset[x][z]>>8)*4096);
                int32_t length = NBT::read_int(in);
                int8_t ztype = NBT::read_byte(in);
                char *zdata = new char[length];
                in.read(zdata,length);
                
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