#include <stdio.h>
#define COLS 12
#define ROWS 6
#define LENG 80

int main(void) {
    char tbl[ROWS][COLS] = {
        {'A','B','C','D','E','F','G','H','I','J','K','L'},
        {'M','N','O','P','Q','R','S','T','U','V','W','X'},
        {'Y','Z','a','b','c','d','e','f','g','h','i','j'},
        {'k','l','m','n','o','p','q','r','s','t','u','v'},
        {'w','x','y','z','_','0'}
    };

    char cvt[ROWS][COLS] = {
        {'U','B','t','w','N','2','j','z','R','G','-','X'},
        {')','9','F','f','o','D','d','0','e','c',',','O'},
        {'3','Q','J','S',':','7','8','a','Z','q','W','r'},
        {'C','s','m','h','g','"','L','Y','4','x','6','5'},
        {'1','A','u','(','T','i','p','V','H','y','v','1'},
        {'k',';','n','M','`','E','.','k','b','_','P'}
    };

    char instr[LENG + 1], encstr[LENG + 1];
    int i, j, col, row;
    int ofsCol, ofsRow, cnvCol, cnvRow;
    char ch;
    // 標準入力から,行補正値,列補正値,暗号化前文字列を順に入力する
    printf("行補正値(0 - %d) : ", ROWS - 1);
    scanf("%d", &ofsRow);
    printf("列補正値(0 - %d) : ", COLS - 1);
    scanf("%d", &ofsCol);
    printf("暗号化前文字列(%d文字まで) : ", LENG);
    scanf("%s", instr);

    /*---------- 暗号化 ----------*/
    i = 0; // 暗号化前文字列を走査するための添字
    j = 0;
    // 暗号化前文字列の文字を先頭から末尾まで順に1文字ずつ取り出して,
    // 変更前テーブル内の一致する文字位置(行, 列)を求める.
    while (instr[i] != '\0') {
        ch = '\0';
        for (row = 0; row < ROWS && ch == '\0'; row++) {
            for (col = 0; col < COLS && ch == '\0'; col++) {
                // 一致する文字がある場合は,求めた文字位置の行を行補正値で,
                // 列を列補正値で補正し,補正後の位置にある変換後テーブルの文字を求めて
                // 暗号化後文字列に追加する.
                if (instr[i] == tbl[row][col]) {
                    cnvRow = (row + ofsRow) % ROWS;
                    // printf("cnvRow=%d\n", cnvRow);
                    cnvCol = (col + ofsCol) % COLS;
                    // printf("cnvCol=%d\n", cnvCol);
                    ch = cvt[cnvRow][cnvCol];
                    // printf("ch=%c\n", ch);
                }
            }
        }
        // 一致する文字がない場合は,不正な文字としてその文字を標準出力に表示する.
        if (ch == '\0') {
            printf("不正な文字 : %c\n", instr[i]);
        } 
        // 一致する文字がある場合は,求めた文字位置の行を行補正値で,列を列補正値で補正し,
        // 補正後の位置にある変換後テーブルの文字を求めて,暗号化後文字列に追加する
        else {
            encstr[j++] = ch;
        }
        // 走査位置を次の文字に移動
        // 文字列の末尾に格納されている'\0'が見つかるまで行う
        i++;
    }
    // 暗号化前文字列を暗号化後文字列を標準出力に表示する
    // 文字列encstrを正しく表示するために,末尾に終端文字を加える
    encstr[j] = '\0';
    printf("暗号化前文字列 : %s\n", instr);
    printf("暗号化後文字列 : %s\n", encstr);

    return 0;
}