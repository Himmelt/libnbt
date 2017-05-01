#include "stdafx.h"
#include "libnbt.h"

namespace libnbt {

    Region::Region() {
        map = new std::unordered_map<int, NBTTagCompound*>();
    }

    Region::~Region() {
        delete(map);
    }

    bool Region::has(int x, int z) {
        return map->find(x + 32 * z) != map->end();
    }

    NBTTagCompound * Region::get(int x, int z) {
        return map->at(x + 32 * z);
    }

    void Region::cls_entities(int x, int z) {
        if (has(x, z)) {
            NBTTagList *list = (NBTTagList *)((NBTTagCompound*)get(x, z)->get("Level"))->get("Entities");
        }
    }

    void Region::read(std::istream & in) {
        NBT::LOG() << "Start Read Region !" << std::endl;
        in.read(offset, 0x1000);
        in.read(timestamp, 0x1000);
        for (int z = 0; z < 32; z++) {
            for (int x = 0; x < 32; x++) {
                in.seekg(4 * x + 128 * z);
                int32_t off_set = NBT::read_int(in) >> 8;
                if (off_set >= 2) {
                    in.seekg(off_set * 0x1000);
                    int32_t length = NBT::read_int(in) - 1;
                    int8_t ztype = NBT::read_byte(in);
                    std::string nbt = NBT::read_string(in, length);
                    int flag = NBT::s_uncompress(nbt);
                    if (flag == Z_OK) {
                        std::istringstream stream;
                        stream.str(nbt);
                        stream.seekg(0);
                        NBTTagCompound *tag = new NBTTagCompound();
                        NBT::readNbt(stream, tag);
                        if (tag->size() > 0) {
                            map->insert({ x + 32 * z, tag });
                        }
                    } else {
                        NBT::LOG() << "Read Err:" << flag << std::endl;
                    }
                }
            }
        }
        NBT::LOG() << "Finish Read Region !" << std::endl;
    }

    void Region::write(std::ostream & out) {
        NBT::LOG() << "Start Write Region !" << std::endl;
        std::ostringstream nbt;
        int32_t entry = 2;
        for (int z = 0; z < 32; z++) {
            for (int x = 0; x < 32; x++) {
                if (has(x, z)) {
                    nbt.str("");
                    NBT::writeNbt(nbt, map->at(x + 32 * z));
                    std::string data = nbt.str();
                    NBT::s_compress(data);
                    int32_t length = data.size() + 1;
                    int8_t sec_size = (int8_t)ceil((length + 4) / 4096.0);
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
        out.seekp(0x1000);
        out.write(timestamp, 0x1000);
        out.seekp(entry * 0x1000 - 1);
        out.put(0);
        NBT::LOG() << "Finish Write Region !" << std::endl;
    }

}
