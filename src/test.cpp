#include <iostream>
#include <fstream>
#include "api/libnbt.h"

using namespace std;
using namespace libnbt;

int main() {
    ofstream outFile("out.dat", ios::binary);
    ifstream inFile("servers.dat", ios::binary);
    NBTTagCompound tag;
    libnbt::readNbt(inFile, &tag);
    for (const auto &key:tag.getKeys()) {
        cout << key << endl;
    }
    NBTBase *base = tag.getTag("servers");
    if (base->getType() == LIST) {
        auto *list = dynamic_cast<NBTTagList *>(base);
        for (int i = 0; i < list->size(); ++i) {
            auto *comp = dynamic_cast<NBTTagCompound *>(list->get(i));
            cout << dynamic_cast<NBTTagString *>(comp->getTag("ip"))->getData() << endl;
        }
    }
    tag.setTag("set_int", new NBTTagInt(666));
    tag.setTag("set_long", new NBTTagLong(6667896));
    tag.setTag("set_string", new NBTTagString("test string hello !"));
    tag.setTag("set_comp", new NBTTagCompound("child root"));
    libnbt::writeNbt(outFile, &tag);
    return 0;
}
