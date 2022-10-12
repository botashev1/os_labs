#include "include/parent.h"
#include <vector>

int main() {
    std::vector <std::string> input;
    int n;
    std::cout << "Enter count string:\n";
    std::cin >> n;
    std::cout << "Enter strings:\n";
    std::string s;
    getline(std::cin, s);
    for (int i = 0; i < n; i++) {
        getline(std::cin, s);
        input.push_back(s);
    }
    std::vector <std::string> output = ParentRoutine(getenv("child1"), getenv("child2"), input);

    for (auto &res : output){
        std::cout << res << std::endl;
    }
    return 0;
}
