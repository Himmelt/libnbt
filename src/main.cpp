#include <iostream>
#include "api/tag_base.h"
#include "api/tag_comp.h"

using namespace std;
using namespace libnbt;

int main() {

    cout << "main" << endl;

    ofstream file("out.dat", ios::binary);
    NBTTagCompound compound;
    compound.hasTag("test");
    cout << NBTBase::isBigEndian() << endl;
    return 0;
}
