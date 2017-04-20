#include <iostream>
#include "api/tag_base.h"
#include "api/tag_data.h"
#include "api/tag_vector.h"

using namespace std;
using namespace libnbt;

int main() {

    ofstream file("out.dat", ios::binary);
    NBTTagList list(BYTE);
    list.put(new NBTTagByte(64));
    list.put(new NBTTagByte(65));
    list.put(new NBTTagByte(66));
    list.remove(1);
    list.set(1, new NBTTagByte(78));
    list.write(file);
    return 0;
}
