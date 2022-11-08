#pragma once
#include <iostream>

#define DEBUG 1
#ifdef DEBUG
#define DEBUG_PRINT(x) (std::cout << (x) << std::endl)
#else
#define DEBUG_PRINT(x) ;
#endif