#include "stdafx.h"
#include "libnbt.h"

namespace libnbt {

    std::ofstream& NBT::LOG() {
        static char time[28] = { 0 };
        static std::time_t result;
        static std::ofstream logfile("libnbt.log", std::ios::app | std::ios::out);
        result = std::time(nullptr);
        ctime_s(time, 28, &result);
        for (int i = 0; i < 28; i++) {
            if (time[i] == 10) {
                time[i] = ':';
            }
        }
        logfile << time << " ";
        return logfile;
    }

}
