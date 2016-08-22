/*******************************************************************************
 * Created by Himmelt on 2016/8/18.
 * Copyright (c) 2015-2016. Himmelt All rights reserved.
 * https://opensource.org/licenses/MIT
 ******************************************************************************/

#include <iostream>
#include "include/nbt.h"

using namespace std;
using namespace libnbt;

int main() {

    NBT nbt("level.dat");
    nbt.print();
    cout << "=======================================" << endl;
    TagCompound *compound = nbt.prase();
    cout << compound << endl;
    return 0;

}