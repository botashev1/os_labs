#include "utils.h"
#include <sys/mman.h>
#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>


void makeSharedMemoryOpen(int &sfd, std::string name, int oflag, mode_t mode) {
    if ((sfd = shm_open(name.c_str(), oflag, mode)) == -1) {
        std::cout << "Shm_open error" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void makeMmap(void **var, int prot, int flags, int fd) {
    *var = mmap(nullptr, getpagesize(), prot, flags, fd, 0);
    if (var == MAP_FAILED) {
        std::cout << "Mmap error" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void makeSemDestroy(sem_t *sem) {
    if (sem_destroy(sem) == -1) {
        std::cout << "Sem_destroy error" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void makeMunmap(void *addr) {
    if (munmap(addr, getpagesize()) == -1) {
        std::cout << "Munmap error" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void makeShmUnlink(std::string name) {
    if (shm_unlink(name.c_str()) == -1) {
        std::cout << "Shm_unlink error" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void createShm(int &sfd, int &semInFd, const std::string &shmName,
               const std::string &semap) {
    makeSharedMemoryOpen(sfd, shmName, O_CREAT | O_RDWR, S_IRWXU);
    makeSharedMemoryOpen(semInFd, semap, O_CREAT | O_RDWR, S_IRWXU);
}

void makeFtruncateShm(int &sfd, int &semInFd){
    ftruncate(sfd, getpagesize());
    ftruncate(semInFd, getpagesize());
}

void GetForkError() {
    std::cout << "fork error" << std::endl;
    exit(EXIT_FAILURE);
}

void GetExecError(std::string const &executableFile) {
    std::cout << "Exec \"" << executableFile << "\" error." << std::endl;
}
