#include "parent.h"
#include "utils.h"
#include <sys/mman.h>
#include <unistd.h>


constexpr auto FIRST_SHM_NAME = "shared_memory_first"; // from parent to child1
constexpr auto SECOND_SHM_NAME = "shared_memory_second"; // from child2 to parent
constexpr auto THIRD_SHM_NAME = "third_shared_memory"; // from child1 to child2
constexpr auto FIRST_SEMAP = "first_semaphore";
constexpr auto SECOND_SEMAP = "second_semaphore";
constexpr auto THIRD_SEMAP = "third_semaphore";


std::vector<std::string> ParentRoutine(char const *pathToChild1, char const *pathToChild2,
                                       const std::vector<std::string> &input) {

    std::vector<std::string> output;

    int sfd1, semFd1;
    createShm(sfd1, semFd1, FIRST_SHM_NAME, FIRST_SEMAP);
    makeFtruncateShm(sfd1, semFd1);
    sem_t *sem1 = nullptr;
    makeMmap((void **) &sem1, PROT_WRITE | PROT_READ, MAP_SHARED, semFd1);
    sem_init(sem1, 1, 0);


    int sfd2, semFd2;
    createShm(sfd2, semFd2, SECOND_SHM_NAME, SECOND_SEMAP);
    makeFtruncateShm(sfd2, semFd2);
    sem_t *sem2 = nullptr;
    makeMmap((void **) &sem2, PROT_WRITE | PROT_READ, MAP_SHARED, semFd2);
    sem_init(sem2, 1, 0);


    int pid = fork();


    if (pid == 0) { // child1
        if (execl(pathToChild1, FIRST_SHM_NAME, FIRST_SEMAP,
                  THIRD_SHM_NAME, THIRD_SEMAP, nullptr) == -1) {
            GetExecError(pathToChild1);
        }
    } else if (pid == -1) {
        GetForkError();
    } else {
        char *ptr;
        makeMmap((void **) &ptr, PROT_READ | PROT_WRITE, MAP_SHARED, sfd1);
        for (const std::string &s: input) {
            sprintf((char *) ptr, "%s", s.c_str());
            ptr += s.size() + 1;
            sem_post(sem1);
        }
        sprintf((char *) ptr, "%s", "");
        sem_post(sem1);

        int sfd3, semFd3;
        createShm(sfd3, semFd3, THIRD_SHM_NAME, THIRD_SEMAP);
        makeFtruncateShm(sfd3, semFd3);
        sem_t *sem3 = nullptr;
        makeMmap((void **) &sem3, PROT_WRITE | PROT_READ, MAP_SHARED, semFd3);
        sem_init(sem3, 1, 0);


        pid = fork();

        if (pid == 0) { // child2
            if (execl(pathToChild2, THIRD_SHM_NAME, THIRD_SEMAP,
                      SECOND_SHM_NAME, SECOND_SEMAP, nullptr) == -1) {
                GetExecError(pathToChild2);
            }
        } else if (pid == -1) {
            GetForkError();
        } else { // parent
            char *ptr2;
            makeMmap((void **) &ptr2, PROT_READ | PROT_WRITE, MAP_SHARED, sfd2);

            while (true) {
                sem_wait(sem2);
                std::string s = std::string(ptr2);
                ptr2 += s.size() + 1;
                if (s.empty()) {
                    break;
                }
                output.push_back(s);
            }


            makeSemDestroy(sem1);
            makeMunmap(sem1);


            makeSemDestroy(sem2);
            makeMunmap(sem2);

            makeShmUnlink(FIRST_SHM_NAME);
            makeShmUnlink(SECOND_SHM_NAME);
            makeShmUnlink(FIRST_SEMAP);
            makeShmUnlink(SECOND_SEMAP);
        }
    }
    return output;
}