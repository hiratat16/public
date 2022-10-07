#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#define NBYTE 512 //読み込むバイト数
#define MAX_FILES (2) //読み込むファイル数

int main(int argc, char *argv[]){

    char buf[MAX_FILES][NBYTE]; //読み込むデータの記憶場所
    char buf2[20]; //snprintf(,,"differ at byre %d")使うなら20は必要
    int file_count = 0;
    int fd; //ファイル識別子
    int i;
    ssize_t count[MAX_FILES], wcount; //読み書きするバイト数
    memset(buf, '\0', sizeof(buf)); //MAX_FILES * NBYTEでもOK

    for(int i=1; i<argc; i++){ //引数がないとき, つまりargcが1の時は実行されない
        fd = open(argv[i], O_RDONLY); //読み込み専用でファイルを開く
        if(fd == -1){
            perror(argv[i]);
            continue; //ファイルのオープンに失敗したら次の引数で指定されたファイルの処理に進む
        }
        count[file_count] = read(fd, buf[file_count], NBYTE); //読み込んだバイト数

        close(fd);

        // if(count[file_count]<0) count[file_count] = 0;
        // file_count++;
        // if(file_count >= MAX_FILES) break;
        if(count[file_count]<0){
            count[file_count] = 0;

        }
        file_count++;
        if(file_count >= MAX_FILES){
            break;
        }
    }   

    //比較
    for(i=0; i < NBYTE; i++){
        if(buf[0][i]!=buf[1][i]){
            //ストップした場所が, 不一致箇所
            break;//異なる文字が出てきたらストップ
        }
            //サイズのチェック
        if(i>=count[0]) break;
        if(i>=count[1]) break;

    }

    if((i!=count[0])||(i!=count[1])){
        wcount = snprintf(buf2, sizeof(buf2), "differ at byre %d\n", i+1);
        if(wcount > 0){
            if(wcount >= sizeof(buf2)){
                wcount = sizeof(buf2);
            }
            wcount = write(1, buf2, wcount);
            if(wcount == -1){//書き込みに失敗した時のエラー表示
                perror("write error");
            }
        }
    }
    exit(0);
}