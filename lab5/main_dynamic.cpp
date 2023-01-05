#include <array>
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <dlfcn.h>
#include <string>
#include <vector>


int main() {
    const std::vector <std::string> LIB = {"./libd1_dynamic.so", "./libd2_dynamic.so"};
    const std::vector <std::string> FUNC_NAME = {"primeCount", "sort"};
    int curlib = 0;
    int (*primeCount)(int a, int b);
    std::vector <int> (*sort)(std::vector <int>array, int low, int high);
    void* handle = dlopen(LIB[curlib].c_str(), RTLD_LAZY);
    if (handle == nullptr) {
        std::cout << "Fail dlopen\n";
        return EXIT_FAILURE;
    }
    primeCount = ((int (*)(int, int)) dlsym(handle, FUNC_NAME[0].c_str()));
    sort = (std::vector <int>(*)(std::vector <int>, int, int))dlsym(handle, FUNC_NAME[1].c_str());
    int command;
    while (std::cin >> command) {
        if (command == 1) {
            int a, b;
            std::cin >> a >> b;
            if (a > b){
                std::cout << R"("a" have to be less or equal then "b"\n)";
            }
            else{
                std::cout << primeCount(a, b) << "\n";
            }
        } else if (command == 2) {
            int n;
            std::cin >> n;
            std::vector <int>arr(n);
            for (int i = 0; i < n; i++){
                std::cin >> arr[i];
            }
            sort(arr, 0, n);

            for (int i = 0; i < n; i++){
                std::cout << arr[i] << " ";
            }
            std::cout << "\n";
        } else if (command == 0) {
            dlclose(handle);
            curlib ^= 1;
            void* handle = dlopen(LIB[curlib].c_str(), RTLD_LAZY);
            if (handle == nullptr) {
                std::cout << "Fail dlopen\n";
                return EXIT_FAILURE;
            }
            primeCount = ((int (*)(int, int)) dlsym(handle, FUNC_NAME[0].c_str()));
            sort = (std::vector <int>(*)(std::vector <int>, int, int))dlsym(handle, FUNC_NAME[1].c_str());
        } else {
            std::cout << "you have to enter 0, 1 or 2" << std::endl;
        }
    }
    dlclose(handle);
}