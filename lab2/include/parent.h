#ifndef LAB2_PARENT_H
#define LAB2_PARENT_H

#include <sys/wait.h>
#include <iostream>
#include "utils.h"
#include <fstream>

std::string ParentRoutine(char const * const pathToChild1, char const * const pathToChild2, std::string &s);

#endif //LAB2_PARENT_H
