#include "utils.h"

void CreatePipe(int fd[]){
    if (pipe(fd) != 0){
        std::cout <<"Couldn't create pipe" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void GetForkError(){
    std::cout <<"fork error" << std::endl;
    exit(EXIT_FAILURE);
}

void GetExecError(std::string const &executable_file){
    std::cout << "Exec \"" << executable_file << "\" error." << std::endl;
}
