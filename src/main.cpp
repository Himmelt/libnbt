#include <iostream>
#include "tag_base.h"
#include "tag_data.h"
#include "tag_vector.h"

using namespace std;
using namespace libnbt;

int main() {

    ofstream file("out.dat", ios::binary);
    NBTTagString tagString("Himmelt");
    tagString.write(file);
    NBTTagByteArray byteArray;
    byteArray.put('a');
    byteArray.put('b');
    byteArray.put('c');
    byteArray.put('d');
    byteArray.set(4, 3);
    byteArray.set(2, 'a');
    std::vector<int8_t> a = byteArray.get();
    cout << byteArray.get(0) << endl;
    byteArray.write(file);
    return 0;
}
