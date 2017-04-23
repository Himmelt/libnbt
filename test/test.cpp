#include <iostream>
#include "libnbt.h"

using namespace std;
int main() {
    cout << "main" << endl;
    cout << libnbt::NBT::endian() << endl;
    return 0;
}
