#include "include/parent.h"
#include <vector>

int main() {
    std::vector <std::string> input;

    std::string s;
    while (getline(std::cin, s)) {
        input.push_back(s);
    }

    std::vector <std::string> output = ParentRoutine("child1", "child2", input);

    for (const auto &res : output){
        std::cout << res << std::endl;
    }
    return 0;
}
