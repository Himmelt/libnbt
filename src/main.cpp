#include <iostream>
#include "tag_base.h"
#include "tag_data.h"


using namespace std;
using namespace libnbt;

typedef NBTTagData<int8_t> NBTTagByte;
typedef NBTTagData<int16_t> NBTTagShort;

int main() {

    ofstream file("out.dat", ios::binary);
    NBTTagByte tag(64);
    NBTTagShort s(125);
    tag.write(cout);
    s.write(cout);
    tag.write(file);
    s.write(file);
    return 0;
}
