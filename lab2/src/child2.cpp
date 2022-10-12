#include "utils.h"
#include <fstream>

int main() {
    size_t old_size;
    read(STDIN_FILENO, &old_size, sizeof(old_size));

    char old_string[old_size + 1];
    read(STDIN_FILENO, old_string, sizeof(char) * (old_size + 1));


    char new_string[old_size + 1];
    int j = 0;
    char last_ch = '\0';
    for (int i = 0; i < old_size; i++) {
        if (old_string[i] == ' ' && last_ch != ' ') {
            new_string[j] = old_string[i];
            j++;
            last_ch = old_string[i];
        } else if (old_string[i] != ' ') {
            new_string[j] = old_string[i];
            j++;
            last_ch = old_string[i];
        }
    }
    new_string[j] = '\0';
    size_t new_size = j;


    write(STDOUT_FILENO, &new_size, sizeof(new_size));
    write(STDOUT_FILENO, new_string, sizeof(char) * (new_size + 1));


    return 0;
}