/*******************************************************************************
 * Created by Himmelt on 2016/8/18.
 * Copyright (c) 2015-2016. Himmelt All rights reserved.
 * https://opensource.org/licenses/MIT
 ******************************************************************************/

#include <iostream>
#include <fstream>
#include "include/nbt.h"

using namespace std;
using namespace libnbt;

int main() {

    fstream file("out.db", ios::out | ios::binary);

    file.write("SSSS", 4);

    int16_t a = 1000;

    char *p = (char *) (&a);

    file.write(p + 1, 1).write(p, 1);

//    NBT nbt("level.dat");
//
//    TagCompound *compound = nbt.prase();

    return 0;

}