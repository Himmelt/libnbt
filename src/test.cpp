#include <iostream>
#include "api/libnbt.h"

using namespace std;
using namespace libnbt;

int main() {
    ofstream file("out.dat", ios::binary);
    ifstream level("level", ios::binary);
    NBTTagCompound read("");
    libnbt::readNbt(level, &read);
    read.setTag("set_int", new NBTTagInt(666));
    read.setTag("set_long", new NBTTagLong(6667896));
    read.setTag("set_string", new NBTTagString("test string hello !"));
    read.setTag("set_comp", new NBTTagCompound("child root"));
    libnbt::writeNbt(file, &read);
    return 0;
}
