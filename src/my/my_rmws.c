#include "my.h"
// Removes any whitespace within a username *Put in my library
void my_rmws(char *name) {
    int count = 0;
    int length = my_strlen(name);

    for (int i = 0; i < length; i++) {
        // If the current character is not whitespace, write it to name[count]
        if (!(name[i] == ' ' || name[i] == '\t' || name[i] == '\n')) {
            name[count] = name[i];
            count++;
        }
    }

    name[count] = '\0';
}