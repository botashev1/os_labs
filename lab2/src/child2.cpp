#include "utils.h"


int main() {
    std::string s;
    while (getline(std::cin, s)) {
        int j = 0;
        char lastCh = '\0';
        for (int i = 0; i < s.size(); i++){
            if (lastCh != ' ' || s[i] != ' '){
                s[j] = s[i];
                j++;
            }
            lastCh = s[i];
        }
        for (int i = 0; i < j; i++) {
            std::cout << s[i];
        }
        std::cout << '\n';
    }
    return 0;
}