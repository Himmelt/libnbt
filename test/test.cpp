#include <iostream>
#include "libnbt.h"
#include <fstream>

using namespace std;
using namespace libnbt;

int main() {
    ofstream file("out.dat", ios::binary);
    ifstream level("level", ios::binary);
    cout << "main" << endl;
    NBTTagCompound *comp = (NBTTagCompound*)NBT::create(TYPE_COMPOUND);
    comp->set("key", new NBTTagString("string"));
    NBT::writeNbt(file, comp);
    cout << libnbt::NBT::endian() << endl;
    NBT::readNbt(level,comp);
    cout << "s" << endl;
    delete comp;
    return 0;
}
