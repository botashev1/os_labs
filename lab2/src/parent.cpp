#include "parent.h"

std::vector<std::string> ParentRoutine(char const *pathToChild1, char const *pathToChild2,
                                       std::vector<std::string> &input) {

    std::vector<std::string> output;

    for (const std::string &s: input) {
        int FirstPipe[2];
        CreatePipe(FirstPipe);

        int pid = fork();

        if (pid == 0) {
            dup2(FirstPipe[READ_END], STDIN_FILENO);
            dup2(FirstPipe[WRITE_END], STDOUT_FILENO);


            if (execl(pathToChild1, nullptr) == -1) {
                GetExecError(pathToChild1);
            }
            close(FirstPipe[READ_END]);
            close(FirstPipe[WRITE_END]);
        } else if (pid == -1) {
            GetForkError();
        } else {
            size_t size = s.size();
            write(FirstPipe[WRITE_END], &size, sizeof(size));
            write(FirstPipe[WRITE_END], s.c_str(), sizeof(char) * (size + 1));
            close(FirstPipe[WRITE_END]);

            wait(nullptr);

            char upper_s[size + 1];
            read(FirstPipe[READ_END], upper_s, sizeof(char) * (size + 1));
            close(FirstPipe[READ_END]);

            int SecondPipe[2];
            CreatePipe(SecondPipe);

            pid = fork();

            if (pid == 0) {
                dup2(SecondPipe[READ_END], STDIN_FILENO);
                dup2(SecondPipe[WRITE_END], STDOUT_FILENO);

                if (execl(pathToChild2, nullptr) == -1) {
                    GetExecError(pathToChild2);
                }
                close(SecondPipe[READ_END]);
                close(SecondPipe[WRITE_END]);
            } else if (pid == -1) {
                GetForkError();
            } else {

                write(SecondPipe[WRITE_END], &size, sizeof(size));
                write(SecondPipe[WRITE_END], upper_s, sizeof(char) * (size + 1));

                wait(nullptr);
                size_t new_size;
                read(SecondPipe[READ_END], &new_size, sizeof(new_size));
                char res[new_size + 1];
                read(SecondPipe[READ_END], res, sizeof(char) * (new_size + 1));
                close(SecondPipe[READ_END]);
                close(SecondPipe[WRITE_END]);
                output.push_back(res);
            }
        }
    }
    return output;
}