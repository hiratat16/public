#include <stdio.h>

int main(void) {
    int i, j, cnt;
    char input[1001], last[2];

    printf("圧縮前の文字列 : ");
    scanf("%s", input);
    printf("圧縮後の文字列 : ");
    last[0] = input[0];
    last[1] = input[1];
    cnt = 1;

    for (i = 2; input[i] != '\0'; i += 2) {
        if (last[0] != input[i] || last[1] != input[i + 1]) {
            if (cnt <= 2) {
                for (j = 0; j < cnt; j++) {
                    printf("%c%c", last[0], last[1]);
                }
            } else {
                printf("*%d%c%c", cnt, last[0], last[1]);
            }
            last[0] = input[i];
            last[1] = input[i + 1];
            cnt = 0;
        }
        cnt++;
    }
    if(cnt <= 2) {
        for (j = 0; j < cnt; j++) {
            printf("%c%c", last[0], last[1]);
        }
    } else {
        printf("%d%c%c", cnt , last[0], last[1]);
    }
    printf("\n");
    return 0;
    
}