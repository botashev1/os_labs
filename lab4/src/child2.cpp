#include "utils.h"
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
    makeSharedMemoryOpen(writeFd, argv[2], O_CREAT | O_RDWR, S_IRWXU);
    makeSharedMemoryOpen(semOutFd, argv[3], O_CREAT | O_RDWR, S_IRWXU);


    char *input, *output;
    sem_t *semInput, *semOutput;
    makeMmap((void **) &input, PROT_READ | PROT_WRITE, MAP_SHARED, readFd);
    makeMmap((void **) &output, PROT_READ | PROT_WRITE, MAP_SHARED, writeFd);
    makeMmap((void **) &semInput, PROT_READ | PROT_WRITE, MAP_SHARED, semInFd);
    makeMmap((void **) &semOutput, PROT_READ | PROT_WRITE, MAP_SHARED, semOutFd);



    char *ptr = input;


    while (true) {
        sem_wait(semInput);
        std::string s = std::string(ptr);
        ptr = ptr + s.size() + 1;
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

        sprintf((char *) output, "%s", res.c_str());
        sem_post(semOutput);
    }

    sprintf((char *) output, "%s", "");
    sem_post(semOutput);

    makeMunmap(input);
    makeMunmap(output);
    makeMunmap(semInput);
    makeMunmap(semOutput);
    return 0;
}