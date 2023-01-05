#include <iostream>
#include "signature.h"


int main() {
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
            int arr[n];
            for (int i = 0; i < n; i++){
                std::cin >> arr[i];
            }
            sort(arr, 0, n);

            for (int i = 0; i < n; i++){
                std::cout << arr[i] << " ";
            }
            std::cout << "\n";
        } else {
            std::cout << "you have to enter 1 or 2" << std::endl;
        }
    }
}