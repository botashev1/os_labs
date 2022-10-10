#include "child1.h"


int main(const int argc, const char *argv[]) {
    if (argc != 1){
        exit(EXIT_FAILURE);
    }


    size_t size;
    read(STDIN_FILENO, &size, sizeof(size));
    char s[size + 1];
    read(STDIN_FILENO, s, sizeof(char) * (size + 1));


    for (int i = 0; i < size; i++) {
        s[i] = toupper(s[i]);
    }



    int childPipe[2];
    createPipe(childPipe);

    int pid = fork();

    if (pid == 0) {
        close(STDIN_FILENO);
        dup2(childPipe[READ_END], STDIN_FILENO);
        close(STDOUT_FILENO);
        dup2(childPipe[WRITE_END], STDOUT_FILENO);


        auto pathToChild2 = (argv[0]);

        if (execl(pathToChild2, "a", nullptr) == -1) {
            Get_exec_error(pathToChild2);
        }
        close(childPipe[READ_END]);
        close(childPipe[WRITE_END]);
    }
    else if (pid == -1){
        Get_fork_error();
    }
    else {

        write(childPipe[WRITE_END], &size, sizeof(size));
        write(childPipe[WRITE_END], s, sizeof(char) * (size + 1));

        wait(nullptr);
        size_t new_size;
        read(childPipe[READ_END], &new_size, sizeof(new_size));
        char res[new_size + 1];
        read(childPipe[READ_END], res, sizeof(char) * (new_size + 1));


        close(childPipe[READ_END]);
        write(STDOUT_FILENO, &new_size, sizeof(new_size));
        write(STDOUT_FILENO, res, sizeof(char) * (new_size + 1));
        close(childPipe[WRITE_END]);
    }

    return 0;
}