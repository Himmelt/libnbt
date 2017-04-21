#include <iostream>
#include "api/tag_base.h"
#include "api/tag_comp.h"
#include "api/tag_data.h"

using namespace std;
using namespace libnbt;

int main() {
    ofstream file("out.dat", ios::binary);
    NBTTagCompound compound("rootKey");
    compound.setTag("int", new NBTTagInt(34));
    compound.write(file);
    compound.setTag("int", new NBTTagString("override tag int"));
    compound.write(file);
    compound.clear();
    cout << compound.hasTag("int") << endl;
    return 0;
}
