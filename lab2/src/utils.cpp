#include "utils.h"

void createPipe(int fd[]){
    if (pipe(fd) != 0){
        std::cout <<"Couldn't create pipe" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void Get_fork_error(){
    std::cout <<"fork error" << std::endl;
    exit(EXIT_FAILURE);
}

void Get_exec_error(std::string const &executable_file){
    std::cout << "Exec \"" << executable_file << "\" error." << std::endl;
}
