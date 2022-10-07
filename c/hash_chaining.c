/* Hash */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
/* リスト: ハッシュテーブルの定義 */
/* プログラムを簡単にするために, キーを文字列, 値を整数(int)に限定する. */

/*---------- 連結リスト ----------*/
// key: key
// value: 値
// next: 次の list への pointer
// 連結リストの終端はNULL
typedef struct Node{
    char *key;
    int value;
    struct Node *next;
} Node;

/*---------- hash table ----------*/
// size: hash table
// count: data 数
// table: hash table の本体
typedef struct {
    int size, count;
    Node **table;
} HashTable;

/*---------- ノードの生成と廃棄 ----------*/
// ノードの生成
Node *MakeNode(const char *key, int val, Node *next) {
    // ListNode本体の領域を確保する.
    Node *lp = malloc(sizeof(Node));
    if (lp != NULL) {
        // 文字列 key の領域を取得
        lp->key = malloc(strlen(key) + 1);
        if (lp->key == NULL) {
            free(lp);
            return NULL;
        }
        // 取得した文字列をコピー
        strcpy(lp->key, key);
        lp->value = val;
        lp->next = next;
    }
    return lp;
}

// ノードの廃棄
void DeleteNode(Node *lp) {
    // NULLになるまで list をたどる, 
    while (lp != NULL) {
        Node *xs = lp->next;
        // 文字列の領域を free(key) で解放
        free(lp->key);
        // listnode本体を free(cp) で解放
        free(lp);
        lp = xs;
    }
}

/*---------- ハッシュ表の生成と廃棄 ----------*/
// 大きさが size のハッシュ表を作成する
// リターン型は構造体
HashTable *MakeHashTable(int size) {
    // 最初にHashTable本体の領域を取得
    HashTable *ht = malloc(sizeof(HashTable));
    if (ht != NULL) {
        ht->size = size;
        ht->count = 0;
        // 次に ハッシュ表の領域を取得
        // ListNode ではなく ListNode * を指定
        ht->table = malloc(sizeof(Node *) * size);
        if (ht->table == NULL) {
            free(ht);
            return NULL;
        }
        // 初期化
        for (int i = 0; i < size; i++) ht->table[i] = NULL;
    }
    return ht;
}

// ハッシュ表の廃棄
void DeleteHashTable(HashTable *ht) {
    for (int i = 0; i < ht->size; i++) {
        // DeleteNode で table に格納されている連結リストを廃棄
        DeleteNode(ht->table[i]);
    }
    // free(ht) で HashTable 本体を解放する
    free(ht);
}

/*---------- ハッシュ関数の作成 ----------*/
// hash 値を計算する関数
// (適当な関数だが, ハッシュ法は十分機能する)
int HashFunc(HashTable *ht, const char *key) {
    unsigned int value = 0;
    for (; *key != '\0'; key++) {
        // value を 3bit 左シフトして, そこに *key を加算
        value = (value << 3) + *key;
    }
    return value % ht->size;
}

/*---------- データの探索 ----------*/
// 作業用関数
Node *SearchNode(HashTable *ht, const char *key, int hval) {
    Node *lp = ht->table[hval];
    // hash table ht->[hval] から キー　key と等しいセルを線形探索する
    for (; lp != NULL; lp = lp->next) {
        if (strcmp (lp->key, key) == 0) {
            return lp;
        } 
    }
    // 見つかればNULLを返す
    return NULL;
}

// hash table ht から キー key を探索してその値を返す
// 見つからない場合は *err にfalase をセットして 0 を返す
int SearchHash(HashTable *ht, const char *key, bool *err) {
    // HashFunc で hash 値を求める
    Node *lp = SearchNode(ht, key, HashFunc(ht, key));
    if (lp != NULL) {
        // 見つけた場合
        *err = true;
        return lp->value;
    }
    // 見つからない場合
    *err = false;
    return 0;
}

/*---------- データの挿入 ----------*/
// hash table ht にキー key と値 val を追加する
// 既存の key は値を書き換えて false を返す. 新しいキーは true を返す
bool InsertHash(HashTable *ht, const char *key, int val) {
    int hval = HashFunc(ht, key);
    // SerachNode で key と等しい list を見つける
    Node *lp = SearchNode(ht, key, hval);
    // 見つからない場合
    if (lp == NULL) {
        // セルを作って連結リストの先頭に追加
        ht->table[hval] = MakeNode(key, val, ht->table[hval]);
        ht->count++;
        return true;
    // 見つけた場合
    } else {
        // 書き換える
        lp->value = val;
        return false;
    }
}

/*---------- データの削除 ----------*/
// ハッシュ表 ht から キー key とその値を削除する 
// 削除できた場合は true を返す. キーが見つからない場合は false を返す
bool DeleteHash(HashTable *ht, const char *key) {
    // HashFunc で hash 値を求める
    int hval = HashFunc(ht, key);
    // hash table から 先頭の list を取り出す
    Node *lp = ht->table[hval];
    // 線形探索
    if (lp != NULL) {
        // lp->key と key が等しい場合
        if (strcmp(lp->key, key) == 0) {
            // 先頭データを削除
            // hash_table[hval]の値を lp->next に書き換える
            ht->table[hval] = lp->next;
            ht->count--;
            free(lp->key);
            free(lp);
            return true;
        // lp->key と key が等しくない場合
        } else {
            // 連結リストをたどって key を探索
            for (; lp->next != NULL; lp = lp->next) {
                // 見つけた場合
                if (strcmp(lp->next->key, key) ==  0) {
                    Node *del = lp->next;
                    // lp->next の値を lp->next->next に書き換えて list を削除
                    lp->next = lp->next->next;
                    ht->count--;
                    // 削除した list を解放
                    free(del->key);
                    free(del);
                    return true;
                }
            }
        }
    }
    // 空の場合(lp==NULL)
    return false;
}

// hash は空かどうか
bool IsEmptyHash(HashTable *ht) {
    return ht->count == 0;
}

// 要素数を返す
int LengthHash(HashTable *ht) {
    return ht->count;
}

// hashを空にする
void ClearHash(HashTable *ht) {
    ht->count = 0;
    for (int i = 0; i < ht->size; i++) {
        DeleteNode(ht->table[i]);
        ht->table[i] = NULL;
    }
}

void test1(void) {
    char buff[8][12];
    HashTable *ht = MakeHashTable(5);
    bool err;
    printf("-- %d, %d --\n", IsEmptyHash(ht), LengthHash(ht));
    printf("----- insert -----\n");
    for (int i = 0; i < 8; i++) {
        sprintf(buff[i], "%d", rand() % 10 + 1);
        printf("%s, %d\n", buff[i], InsertHash(ht, buff[i], i));
    }
    printf("-- %d, %d --\n", IsEmptyHash(ht), LengthHash(ht));
    printf("----- search -----\n");
    for (int i = 0; i < 8; i++) {;
        printf("%s, %d\n", buff[i], SearchHash(ht, buff[i], &err));
    }
    printf("----- delete -----\n");
    for (int i = 0; i < 8; i++) {;
        printf("%s, %d\n", buff[i], DeleteHash(ht, buff[i]));
        int x = SearchHash(ht, buff[i], &err);
        printf("%s, %d %d\n", buff[i], x, err);
    }
    printf("-- %d, %d --\n", IsEmptyHash(ht), LengthHash(ht));
    printf("----- delete hash -----\n");
    DeleteHashTable(ht);
}

int main(void) {
    test1();
    return 0;
}