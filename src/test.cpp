#include <iostream>
#include "api/libnbt.h"

using namespace std;
using namespace libnbt;

int main() {
    ofstream file("out.dat", ios::binary);
    ifstream level("level", ios::binary);
    NBTTagCompound read("");
    libnbt::readNbt(level, &read);
    read.setTag("int", new NBTTagInt(34));
    read.setTag("comp", new NBTTagCompound("child root"));
    libnbt::writeNbt(file, &read);
    return 0;
}
