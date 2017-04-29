#ifndef SZLIB_H
#define SZLIB_H

#pragma once

#include <iostream>
#include "zlib.h"

int s_uncompress(std::iostream &in, size_t size, std::iostream &out);

#endif // !SZLIB_H
