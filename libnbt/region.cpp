#include "stdafx.h"
#include "libnbt.h"

namespace libnbt {
    Region::Region() {
        map = new std::unordered_map<int, NBTTagCompound*>();
    }
    Region::~Region() {
        delete(map);
    }
    void Region::read(std::istream & in) {
        in.read(offset, 0x1000);
        in.read(timestamp, 0x1000);
        for (int z = 0; z < 32; z++) {
            for (int x = 0; x < 32; x++) {
                in.seekg(4 * x + 128 * z);
                int32_t off_set = NBT::read_int(in) >> 8;
                //std::cout << "x:" << x << ",z:" << z << ",off:" << off_set << std::endl;
                if (off_set >= 2) {
                    in.seekg(off_set * 0x1000);
                    int32_t length = NBT::read_int(in) - 1;
                    //std::cout << x<<","<<z << "   section:" << off_set << "   length:" << length << std::endl;
                    if (length > 1) {
                        int8_t ztype = NBT::read_byte(in);
                        std::string nbt = NBT::read_string(in, length);
                        std::cout << x << "," << z << " sec:" << off_set << " l:" << length << " n:" << nbt.size();
                        int flag = s_uncompress(nbt);
                        if (flag == Z_OK) {
                            std::cout << " u:" << nbt.size() << std::endl;
                            if (nbt.size() > 2) {
                                std::istringstream stream(nbt);
                                NBTTagCompound *tag = new NBTTagCompound();
                                NBT::readNbt(stream, tag);
                                map->insert({ x + 32 * z, tag });
                                //std::cout << map->size() << std::endl;
                            }
                        } else {
                            std::cout << "ERR:" << flag << std::endl;
                        }
                    }
                }
            }
        }
    }

    void Region::write(std::ostream & out) {
        std::ostringstream nbt;
        int32_t entry = 2;
        for (int x = 0; x < 32; x++) {
            for (int z = 0; z < 32; z++) {
                if (has(x, z)) {
                    nbt.str("");
                    NBT::writeNbt(nbt, map->at(x + 32 * z));
                    std::string data = nbt.str();
                    s_compress(data);
                    int32_t length = data.size() + 1;
                    int8_t sec_size = ceil((length + 4) / 4096.0);
                    // 定位到(x,z)的offset入口
                    out.seekp(x * 4 + z * 128);
                    // 计算偏移值和区段数量
                    int32_t temp = entry << 8 | sec_size;
                    // 写偏移值和区段数
                    NBT::write(out, temp);
                    // 根据偏移定位到数据入口
                    out.seekp(entry * 0x1000);
                    // 写数据长度和压缩类型
                    NBT::write(out, length);
                    out.put(2);
                    // 写数据
                    NBT::write(out, data);
                    // 计算新的数据入口
                    entry += sec_size;
                }
            }
        }
        //out.seekp(0x1000);
        //out.write(timestamp, 0x1000);
        out.seekp(entry * 0x1000 - 1);
        std::cout << std::hex << entry * 0x1000 - 1 << std::endl;
        out.put(0);
    }

}
