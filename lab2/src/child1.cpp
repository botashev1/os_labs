#include "utils.h"

int main() {
    size_t size;
    read(STDIN_FILENO, &size, sizeof(size));
    char s[size + 1];
    read(STDIN_FILENO, s, sizeof(char) * (size + 1));


    for (int i = 0; i < size; i++) {
        s[i] = toupper(s[i]);
    }
    write(STDOUT_FILENO, s, sizeof(char) * (size + 1));
    return 0;
}