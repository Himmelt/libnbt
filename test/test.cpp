#include <iostream>
#include "libnbt.h"
#include <fstream>

using namespace std;
using namespace libnbt;

int main() {
    ifstream test("test.dat", ios::in | ios::binary);
    ofstream test2("test1.dat", ios::out | ios::binary);
    ofstream test3("test2.dat", ios::out | ios::binary);
    string str = NBT::read_string(test, 0xb3);
    NBT::s_uncompress(str);
    cout << "size" << str.size() << endl;
    NBT::write(test2, str);
    NBT::s_compress(str);
    NBT::write(test3, str);
    ifstream mca("r.0.0.mca", ios::in | ios::binary);
    Region region;
    region.read(mca);
    ofstream out("r.0.1.mca", ios::out | ios::binary);
    region.write(out);
    //ifstream in("050stream.dat", ios::in | ios::binary);
    //NBTTagCompound comp;
    //NBT::readNbt(in, &comp);
    return 0;
}
