#include "include/parent.h"

int main() {
    std::string s;
    getline(std::cin, s);
    std::cout << ParentRoutine(getenv("child1"), getenv("child2"), s) << std::endl;
    return 0;
}
