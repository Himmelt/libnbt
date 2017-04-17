#ifndef LIBNBT_TAG_TYPE_H
#define LIBNBT_TAG_TYPE_H

#pragma once

namespace libnbt {
    enum TAG_TYPE {
        END, BYTE, SHORT, INT, LONG, FLOAT, DOUBLE,
        BYTE_ARRAY, STRING, LIST, COMPOUND, INT_ARRAY
    };
}

#endif //LIBNBT_TAG_TYPE_H
