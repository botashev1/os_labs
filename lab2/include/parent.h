#ifndef LAB2_PARENT_H
#define LAB2_PARENT_H

#include <sys/wait.h>
#include <iostream>
#include "utils.h"
#include <fstream>
#include <vector>

std::vector <std::string> ParentRoutine(char const *pathToChild1, char const *pathToChild2,
                                        std::vector <std::string> &input);

#endif //LAB2_PARENT_H
