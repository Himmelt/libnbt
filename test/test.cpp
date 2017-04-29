#include <iostream>
#include "libnbt.h"
#include <fstream>

using namespace std;
using namespace libnbt;

int main() {
    fstream mca("r.0.0.mca", ios::in | ios::binary);
    cout << mca.is_open() << endl;
    Region region;
    region.read(mca);

    return 0;
}
