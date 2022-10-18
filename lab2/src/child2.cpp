#include "utils.h"


int main() {
    std::string old_string;
    while (getline(std::cin, old_string)) {
        std::string new_string;
        char last_ch = '\0';
        for (char ch: old_string) {
            if (ch == ' ' && last_ch != ' ') {
                new_string += ch;
            } else if (ch != ' ') {
                new_string += ch;
            }
            last_ch = ch;
        }
        std::cout << new_string << '\n';
    }
    return 0;
}