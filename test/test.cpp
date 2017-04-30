#include <iostream>
#include "libnbt.h"
#include <fstream>

using namespace std;
using namespace libnbt;

int main() {
    ifstream mca("r.0.0.mca", ios::in | ios::binary);
    Region region;
    region.read(mca);
    ofstream out("r.0.1.mca", ios::out | ios::binary);
    region.write(out);
    return 0;
}
