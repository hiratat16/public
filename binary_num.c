#include <stdio.h>
#define KETA 4

int main() {
    int i,j;
    char x[KETA + 1], y[KETA + 1], op, ans[KETA + 1];
    char cb; // count of bytes

    /* 入力例 */
    // 足し算)0001 + 0101 
    // 引き算)1000 - 0111
    printf("計算式 : ");
    scanf("%s %c %s", x, &op, y);

    cb = '0';
    j = 0;
    switch (op) {
        case '+':
            for (i = KETA - 1; i >= 0; i--) {
                if (x[i] == '0' && y[i] == '0') {
                    ans[j] = cb;
                    cb = '0';
                } else if (x[i] == '1' && y[i] == '1') {
                    ans[j] = cb;
                    cb = '1';
                } else {
                    if (cb == '1') {
                        ans[j] = '0';
                    } else {
                        ans[j] = '1';
                    }
                }
                j++;
            }
            if (cb == '1')
                ans[j++] = cb;
            break;
        case '-':
            for (i = KETA - 1; i >= 0; i--) {
                if (x[i] == '1' && y[i] == '0') {
                    if (cb == '0') {
                        ans[j] = '1';
                    }
                    else {
                        ans[j] = '0';
                        cb = '0';
                    }
                } else if (x[i] == '0' && y[i] == '1') {
                    if (cb == '0') {
                        ans[j] = '1';
                        cb = '1';
                    } else {
                        ans[j] = '0';
                    }
                } else {
                    ans[j] = cb;
                }
                j++;
            }
            break;
    } 
    printf("答え : ");
    for (i = j - 1; i >= 0; i--) {
        printf("%c", ans[i]);
    }
    printf("\n");
    return 0;
    
}