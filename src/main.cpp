#include <iostream>
#include "api/tag_base.h"
#include "api/tag_data.h"
#include "api/tag_vector.h"

using namespace std;
using namespace libnbt;

int main() {

    ofstream file("out.dat", ios::binary);
    NBTTagString tagString("Himmelt");
    tagString.write(file);
    NBTTagIntArray array;
    array.put('a');
    array.put('b');
    array.put('c');
    array.put('d');
    array.put(255);
    array.set(4, 0xfafa);
    array.set(2, 0);
    cout << array.get(0) << endl;
    array.write(file);
    return 0;
}
