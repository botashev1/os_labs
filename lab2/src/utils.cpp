#include "utils.h"

void CreatePipe(int fd[]) {
    if (pipe(fd) != 0) {
        std::cout << "Couldn't create pipe" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void GetForkError() {
    std::cout << "fork error" << std::endl;
    exit(EXIT_FAILURE);
}

void MakeDup2(int oldFd, int newFd) {
    if (dup2(oldFd, newFd) == -1) {
        std::cout << "dup2 error" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void GetExecError(std::string const &executableFile) {
    std::cout << "Exec \"" << executableFile << "\" error." << std::endl;
}
