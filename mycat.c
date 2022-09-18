#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *fd;
    int i, ch;
    if (argc == 1) {
        while (1) {
            if ((ch = getchar()) != EOF) {
                fputc(ch, stdout);
            } else { exit(0); }
        }
    }
    if (argc > 1) {
        for (i = 1; i < argc; i++) {
            fd = fopen(argv[i], "rb");
            while ((ch = fgetc(fd)) != EOF) {
                fputc(ch, stdout);
            }
            fclose(fd);
        }
    }
    return 0;
}