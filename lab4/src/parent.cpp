#include "parent.h"
#include "utils.h"
#include <sys/mman.h>
#include <unistd.h>


constexpr auto FIRST_SHM_NAME = "shared_memory_first";
constexpr auto SECOND_SHM_NAME = "shared_memory_second";
constexpr auto THIRD_SHM_NAME = "third_shared_memory";
constexpr auto FIRST_SEMAPHORE_INPUT_NAME = "first_semaphore_input";
constexpr auto FIRST_SEMAPHORE_OUTPUT_NAME = "first_semaphore_output";
constexpr auto SECOND_SEMAPHORE_INPUT_NAME = "second_semaphore_input";
constexpr auto SECOND_SEMAPHORE_OUTPUT_NAME = "second_semaphore_output";
constexpr auto THIRD_SEMAPHORE_INPUT_NAME = "third_semaphore_input";
constexpr auto THIRD_SEMAPHORE_OUTPUT_NAME = "third_semaphore_output";


std::vector<std::string> ParentRoutine(char const *pathToChild1, char const *pathToChild2,
                                       const std::vector<std::string> &input) {

    std::vector<std::string> output;

//    int firstPipe[2];
//    CreatePipe(firstPipe);
//    int pipeBetweenChildren[2];
//    CreatePipe(pipeBetweenChildren);

    /* shared memory file descriptor */
    int sfd1, semInFd1, semOutFd1;
    createShm(sfd1, semInFd1, semOutFd1, FIRST_SHM_NAME, FIRST_SEMAPHORE_INPUT_NAME, FIRST_SEMAPHORE_OUTPUT_NAME);
    makeFtruncateShm(sfd1, semInFd1, semOutFd1);
    sem_t *semInput1 = nullptr, *semOutput1 = nullptr;
    makeMmap((void **) &semInput1, PROT_WRITE | PROT_READ, MAP_SHARED, semInFd1);
    makeMmap((void **) &semOutput1, PROT_WRITE | PROT_READ, MAP_SHARED, semOutFd1);
    sem_init(semInput1, 1, 0);
    sem_init(semOutput1, 1, 0);


    int sfd2, semInFd2, semOutFd2;
    createShm(sfd2, semInFd2, semOutFd2, SECOND_SHM_NAME, SECOND_SEMAPHORE_INPUT_NAME, SECOND_SEMAPHORE_OUTPUT_NAME);
    makeFtruncateShm(sfd2, semInFd2, semOutFd2);
    sem_t *semInput2 = nullptr, *semOutput2 = nullptr;
    makeMmap((void **) &semInput2, PROT_WRITE | PROT_READ, MAP_SHARED, semInFd2);
    makeMmap((void **) &semOutput2, PROT_WRITE | PROT_READ, MAP_SHARED, semOutFd2);
    sem_init(semInput2, 1, 0);
    sem_init(semOutput2, 1, 0);


    int pid = fork();


    if (pid == 0) {
        if (execl(pathToChild1, FIRST_SHM_NAME, FIRST_SEMAPHORE_INPUT_NAME,
                  THIRD_SHM_NAME, THIRD_SEMAPHORE_INPUT_NAME, nullptr) == -1) {
            GetExecError(pathToChild1);
        }
    } else if (pid == -1) {
        GetForkError();
    } else {
        char *ptr;
        makeMmap((void **) &ptr, PROT_READ | PROT_WRITE, MAP_SHARED, sfd1);
        for (const std::string &s: input) {
            sprintf((char *) ptr, "%s\n", s.c_str());
            sem_post(semInput1);
        }

        int sfd3, semInFd3, semOutFd3;
        createShm(sfd3, semInFd3, semOutFd3, THIRD_SHM_NAME, THIRD_SEMAPHORE_INPUT_NAME, THIRD_SEMAPHORE_OUTPUT_NAME);
        makeFtruncateShm(sfd3, semInFd3, semOutFd3);
        sem_t *semInput3 = nullptr, *semOutput3 = nullptr;
        makeMmap((void **) &semInput3, PROT_WRITE | PROT_READ, MAP_SHARED, semInFd3);
        makeMmap((void **) &semOutput3, PROT_WRITE | PROT_READ, MAP_SHARED, semOutFd3);
        sem_init(semInput3, 1, 0);
        sem_init(semOutput3, 1, 0);


        pid = fork();

        if (pid == 0) {
            if (execl(pathToChild2, THIRD_SHM_NAME, THIRD_SEMAPHORE_INPUT_NAME,
                      SECOND_SHM_NAME, SECOND_SEMAPHORE_INPUT_NAME, nullptr) == -1) {
                GetExecError(pathToChild2);
            }
        } else if (pid == -1) {
            GetForkError();
        } else {
            char *ptr2;
            makeMmap((void **) &ptr2, PROT_READ | PROT_WRITE, MAP_SHARED, sfd2);

            while (true) {
                sem_wait(semInput2);
                std::string s = std::string(ptr2);
                if (s.empty()) {
                    break;
                }
                output.push_back(s);
            }


            makeSemDestroy(semInput1);
            makeMunmap(semInput1);

            makeSemDestroy(semOutput1);
            makeMunmap(semOutput1);

            makeSemDestroy(semInput2);
            makeMunmap(semInput2);

            makeSemDestroy(semOutput2);
            makeMunmap(semOutput2);

            makeShmUnlink(FIRST_SHM_NAME);
            makeShmUnlink(SECOND_SHM_NAME);
            makeShmUnlink(FIRST_SEMAPHORE_INPUT_NAME);
            makeShmUnlink(FIRST_SEMAPHORE_OUTPUT_NAME);
            makeShmUnlink(SECOND_SEMAPHORE_INPUT_NAME);
            makeShmUnlink(SECOND_SEMAPHORE_OUTPUT_NAME);
        }
    }
    return output;
}