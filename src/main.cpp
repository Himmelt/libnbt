#include <iostream>
#include "api/tag_base.h"
#include "api/tag_comp.h"
#include "api/tag_data.h"

using namespace std;
using namespace libnbt;

int main() {
    ofstream file("out.dat", ios::binary);
    ifstream level("level", ios::binary);
    NBTTagCompound read("");
    NBTBase::readNbt(level, &read);
    read.setTag("int", new NBTTagInt(34));
    read.setTag("comp", new NBTTagCompound("child root"));
    NBTBase::writeNbt(file, &read);
    return 0;
}
