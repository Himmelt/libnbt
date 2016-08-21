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

    TagByte tag("byte");
    tag.setValue('S');
    cout << &tag << endl;

    return 0;
}