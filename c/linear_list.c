#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLINE 1024

struct list {   
    struct list *next; // 次のノードに繋げるためのポインタ
    char *name; // データを入れるためのメンバ
};

int main() {
    char input[MAXLINE];
    char *ret; // fgetsの値を受け取る
    char *s; // strchrのinputの'\n'のアドレスを受け取る変数
    int len; // 文字の長さを数える

    // listを表す変数(線形リスト型)
    struct list head; // リストの先頭を定義 
    struct list *ndPtr; // 新規確保用    
    struct list *ndLast; // 現在の末尾のリストのポインタ
    struct list *ndPrev; // 末尾直前のポインタ

    head.next = NULL; // headの初期化

    for(;;) {
        ret = fgets(input, MAXLINE, stdin);
        // fgetsの返り値がNULLならば終了
        if(ret == NULL){
            break;
        }

        s = strchr(input, '\n');
        // 終端文字を'\n'からkara'\0'に置き換える
        if(s != NULL) {
            *s = '\0'; 
        }

        len = strlen(input); // inputの長さを受け取る

        /*----- ノードのメモリ割り当て -----*/

        // list構造体の容量のメモリをmallocで割り当て,それを指すポインタndPtrに代入
        ndPtr = malloc(sizeof(struct list)); 
        if (ndPtr == NULL) {
            printf("メモリが確保できません\n");
            exit(EXIT_FAILURE);
        } 
        // 文字の長さ分の記憶領域を確保しndPtr->nameに代入 
        ndPtr->name = malloc(sizeof(char)*len+1);
        if (ndPtr == NULL) {
            printf("メモリが確保できません\n");
            exit(EXIT_FAILURE);
        } else {
            strcpy(ndPtr->name, input);

            // printf("%s\n", ndPtr->name);

            // 次の要素は末尾と分かるように分かるようにNULLを代入
            ndPtr->next = NULL;
        }

        /*----- リスト先頭へのノード追加(連結) -----*/

        // 最初は先頭が末尾のポインタになる
        ndPrev = &head;

        // for文で,リストを最初からチェックし, next が NULL である要素まで移動
        for(ndLast = head.next; ndLast != NULL; ndLast = ndLast->next){               
            ndPrev = ndLast;
        }

        // リストを連結する
        ndPrev->next = ndPtr;
    }

    /*--------- データ内容の表示 ------------*/
    // list構造体型ポインタ ndPtr が指す所から始まる線形リストのデータ内容を
    // next が NULLになるまで全て表示

    for(struct list *ndPtr = head.next; ndPtr != NULL; ndPtr = ndPtr->next) {
        printf("%s\n", ndPtr->name);
    }
    

    /*--------- 開放 -----------*/

    // 次のリストのポインタ
    struct list *nextPtr;

    // 削除対象のポインタ
    struct list *del;

    nextPtr = head.next;

    // NULLになるまでループ 

    while(nextPtr) {
        // 削除対象のポインタを保存
        del = nextPtr;
        // 次のリストのポインタを取得する
        nextPtr = nextPtr->next;

        free(del->name);
        free(del);
    }
}
