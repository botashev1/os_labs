#ifndef LAB2_UTILS_H
#define LAB2_UTILS_H

#include <iostream>
#include <semaphore.h>


void makeSharedMemoryOpen(int &sfd, std::string name, int oflag, mode_t mode);

void makeMmap(void **var, int prot, int flags, int fd);

void makeSemDestroy(sem_t *sem);

void makeMunmap(void *addr);

void makeShmUnlink(std::string name);

void createShm(int &sfd, int &semInFd, int &semOutFd, const std::string &shmName,
               const std::string &semaphoreInputName, const std::string &semaphoreOutputName);

void makeFtruncateShm(int &sfd, int &semInFd, int &semOutFd);

void GetForkError();

void GetExecError(std::string const &executableFile);

#endif //LAB2_UTILS_H
