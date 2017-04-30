#include <iostream>
#include "libnbt.h"
#include <fstream>

using namespace std;
using namespace libnbt;

int main() {
    ifstream in("r.0.0.mca", ios::in | ios::binary);
    ofstream out("r.0.1.mca", ios::out | ios::binary);
    Region region;
    region.read(in);
    region.write(out);
    return 0;
}
