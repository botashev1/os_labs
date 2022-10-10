#include "parent.h"


std::string ParentRoutine(char const * const pathToChild1, char const * const pathToChild2, std::string &s) {
    int parentPipe[2];
    createPipe(parentPipe);

    int pid = fork();

    if (pid == 0) {
        dup2(parentPipe[READ_END], STDIN_FILENO);
        dup2(parentPipe[WRITE_END], STDOUT_FILENO);


        if (execl(pathToChild1, pathToChild2, nullptr) == -1) {
            Get_exec_error(pathToChild1);
        }
        close(parentPipe[READ_END]);
        close(parentPipe[WRITE_END]);
    }
    else if(pid == -1){
        Get_fork_error();
    }
    else {
        size_t size = s.size();
        write(parentPipe[WRITE_END], &size, sizeof(size));
        write(parentPipe[WRITE_END], s.c_str(), sizeof(char) * (size + 1));
        close(parentPipe[WRITE_END]);

        wait(nullptr);
        size_t new_size;
        read(parentPipe[READ_END], &new_size, sizeof(new_size));

        char new_s[new_size+1];
        read(parentPipe[READ_END], new_s, sizeof(char) * (new_size + 1));
        close(parentPipe[READ_END]);
        return new_s;
    }
}