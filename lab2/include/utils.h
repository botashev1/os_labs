#ifndef LAB2_UTILS_H
#define LAB2_UTILS_H

#include <sys/wait.h>
#include <iostream>


enum PipeEnd {
    READ_END,
    WRITE_END
};

void createPipe(int fd[]);
void Get_fork_error();
void Get_exec_error(std::string const &executable_file);

#endif //LAB2_UTILS_H
