#include <iostream>
#include "api/tag_base.h"
#include "api/tag_comp.h"

using namespace std;
using namespace libnbt;

int main() {

    ofstream file("out.dat", ios::binary);
    NBTTagCompound compound;
    compound.hasTag("test");
    return 0;
}
