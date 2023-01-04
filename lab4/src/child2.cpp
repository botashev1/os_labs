#include "utils.h"
#include <fstream>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>


int main(int argc, char *argv[]) {
    if (argc != 4) {
        std::cout << "Invalid arguments 2.\n";
        exit(EXIT_FAILURE);
    }

    int readFd, semInFd;
    makeSharedMemoryOpen(readFd, argv[0], O_CREAT | O_RDWR, S_IRWXU);
    makeSharedMemoryOpen(semInFd, argv[01], O_CREAT | O_RDWR, S_IRWXU);

    int writeFd, semOutFd;
    makeSharedMemoryOpen(readFd, argv[2], O_CREAT | O_RDWR, S_IRWXU);
    makeSharedMemoryOpen(semInFd, argv[3], O_CREAT | O_RDWR, S_IRWXU);


    char *input, *output;
    sem_t *semInput, *semOutput;
    makeMmap((void **) &input, PROT_READ | PROT_WRITE, MAP_SHARED, readFd);
    makeMmap((void **) &output, PROT_READ | PROT_WRITE, MAP_SHARED, writeFd);
    makeMmap((void **) &semInput, PROT_READ | PROT_WRITE, MAP_SHARED, semInFd);
    makeMmap((void **) &semOutput, PROT_READ | PROT_WRITE, MAP_SHARED, semOutFd);


    while (true) {
        sem_wait(semInput);
        std::string s = std::string(input);
        if (s.empty()) {
            break;
        }
        int j = 0;
        char lastCh = '\0';
        for (size_t i = 0; i < s.size(); i++){
            if (lastCh != ' ' || s[i] != ' '){
                s[j] = s[i];
                j++;
            }
            lastCh = s[i];
        }

        std::string res;
        for (int i = 0; i < j; i++) {
            res += s[i];
        }

        sprintf((char *) output, "%s\n", res.c_str());
        sem_post(semOutput);
    }


    makeMunmap(input);
    makeMunmap(output);
    makeMunmap(semInput);
    makeMunmap(semOutput);
    return 0;
}