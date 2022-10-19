#ifndef LAB2_UTILS_H
#define LAB2_UTILS_H

#include <sys/wait.h>
#include <iostream>


enum PipeEnd {
    READ_END,
    WRITE_END
};

void CreatePipe(int fd[]);
void GetForkError();
void MakeDup2(int oldFd, int newFd);
void GetExecError(std::string const &executableFile);

#endif //LAB2_UTILS_H
