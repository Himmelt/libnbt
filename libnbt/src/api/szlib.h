#ifndef SZLIB_H
#define SZLIB_H

#pragma once

#include <iostream>
#include "zlib.h"

int s_compress(std::string &data);

int s_uncompress(std::string &data);

#endif // !SZLIB_H
