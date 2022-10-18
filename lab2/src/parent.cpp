#include "parent.h"


std::vector<std::string> ParentRoutine(char const *pathToChild1, char const *pathToChild2,
                                       const std::vector<std::string> &input){

    std::vector<std::string> output;

    int FirstPipe[2];
    CreatePipe(FirstPipe);
    int PipeBetweenChildren[2];
    CreatePipe(PipeBetweenChildren);

    int pid = fork();



    if (pid == 0) {

        close(FirstPipe[WRITE_END]);
        close(PipeBetweenChildren[READ_END]);

        dup2(FirstPipe[READ_END], STDIN_FILENO);
        dup2(PipeBetweenChildren[WRITE_END], STDOUT_FILENO);

        if (execl(pathToChild1, nullptr) == -1) {
            GetExecError(pathToChild1);
        }
        close(FirstPipe[READ_END]);
        close(FirstPipe[WRITE_END]);
    } else if (pid == -1) {
        GetForkError();
    } else {
        close(FirstPipe[READ_END]);
        for (const std::string & s : input) {
            std::string s_tmp = s + "\n";
            write(FirstPipe[WRITE_END], s_tmp.c_str(),  s_tmp.size());
        }
        close(FirstPipe[WRITE_END]);

        int SecondPipe[2];
        CreatePipe(SecondPipe);

        pid = fork();

        if (pid == 0) {
            close(SecondPipe[READ_END]);
            close(PipeBetweenChildren[WRITE_END]);

            dup2(PipeBetweenChildren[READ_END], STDIN_FILENO);
            dup2(SecondPipe[WRITE_END], STDOUT_FILENO);

            if (execl(pathToChild2, nullptr) == -1) {
                GetExecError(pathToChild2);
            }
            close(PipeBetweenChildren[READ_END]);
            close(SecondPipe[WRITE_END]);
        } else if (pid == -1) {
            GetForkError();
        } else {
            close(SecondPipe[WRITE_END]);
            close(PipeBetweenChildren[WRITE_END]);
            close(PipeBetweenChildren[READ_END]);

            while(wait(nullptr) > 0);

            for (int i = 0; i < input.size(); i++) {
                std::string res;
                char ch;
                while (read(SecondPipe[READ_END], &ch, 1) && ch != '\n'){
                    res += ch;
                }
                output.push_back(res);
            }
            close(SecondPipe[READ_END]);
        }
    }
    return output;
}