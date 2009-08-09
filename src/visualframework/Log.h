/*==============================================================================
    Dan Wilcox <danomatika@gmail.com>
==============================================================================*/
#ifndef LOG_H
#define LOG_H

#include <iostream>

#define LOG std::cout
#define LOG_DEBUG std::cout << "DEBUG: "
#define LOG_WARN std::cerr << "WARN: "
#define LOG_ERROR std::cerr << "ERROR: "

#endif // LOG_H
