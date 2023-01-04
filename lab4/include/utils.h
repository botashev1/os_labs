#ifndef LAB2_UTILS_H
#define LAB2_UTILS_H

#include <iostream>
#include <semaphore.h>


void makeSharedMemoryOpen(int &sfd, std::string name, int oflag, mode_t mode);

void makeMmap(void **var, int prot, int flags, int fd);

void makeSemDestroy(sem_t *sem);

void makeMunmap(void *addr);

void makeShmUnlink(std::string name);

void createShm(int &sfd, int &semInFd, const std::string &shmName,
               const std::string &semap);

void makeFtruncateShm(int &sfd, int &semInFd);

void GetForkError();

void GetExecError(std::string const &executableFile);

#endif //LAB2_UTILS_H
