#include <stdio.h>
#include <stdlib.h>
struct Node {
    int key;
    int value;
};

const int capacity = 20;
int size = 0;

// ポインタのアドレス (ポインタのリスト, アドレスのリスト)
// HashNode **arr; は struct HashNode *arr[]; と書くことも可能
// → arr (array = アレー = 配列) の中に, hashdata(へのアドレス) を並べて格納する
struct Node **arr;
struct Node *dummy;

/* -------------------- INSERT -------------------- */
void insert(int key, int V) {
    // 初期化
    // key と value を1組分 (struct HashNode 1個分) 保存するスペースを確保
    struct Node *new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->key = key;
    new_node->value = V;

    // hash 関数を適用して見つける
    // 指定された key の index
    int hashIndex = key % capacity;

    // 既に nodeindex に node がある場合は, 空の index が見つかるまで探す.
    while (arr[hashIndex] != NULL
            && arr[hashIndex]->key != key
            && arr[hashIndex]->key != -1) {
                // HashIndex を継続的に更新し, 線形探索を実行
                hashIndex++;
                hashIndex %= capacity;
    }

    // 新しいノードを挿入する場合
    // サイズを1増やす
    if (arr[hashIndex] == NULL || arr[hashIndex]->key == -1) {
        size++;
    }
    // main 関数で作成した arr (アドレスを20個分格納したスペース) の 
    // arr[hashIndex] に key と value を入れる.
    arr[hashIndex] = new_node;
}

/* -------------------- DELETE -------------------- */
int delete (int key) {

    int hashIndex = key % capacity;

    while (arr[hashIndex] != NULL) {
        if (arr[hashIndex]->key == key) {
            arr[hashIndex] = dummy;
            size--;
            return -1;
        }
        // arr[hashIndex]->key == key ではない場合, key が見つかるまで線形探索を行う
        hashIndex++;
        hashIndex %= capacity;
    }
    return 0;
}

/* -------------------- FIND -------------------- */
int Find(int key) {
    /// hash function (Division Method) を適用して見つける
    // 指定された key の index
    int hashIndex = (key % capacity);

    int counter = 0;

    // 指定された key を持つ node を見つける
    while (arr[hashIndex] != NULL) {

        int counter = 0;
        // counter が capacity より大きい場合
        if (counter++  > capacity) {
            break;
        }

        // node が見つかった場合, その値を返す
        if (arr[hashIndex]->key == key) {
            return arr[hashIndex]->value;
        }
        // if arr[HashIndex]-> != key 
        // HashIndex を継続的に更新し, 線形探索を実行
        hashIndex++;
        hashIndex %= capacity;
    }
    // 見つからなかった場合
    return -1;
}


int main() {

    /* -------------------- PreProcessing -------------------- */
    // アドレス (だけ) を20個格納するスペースを確保
    arr = (struct Node**)malloc(sizeof(struct Node*)*capacity);

    // 初期化
    for (int i = 0; i < capacity; i++) {
        arr[i] = NULL;
    }

    dummy = (struct Node*)malloc(sizeof(struct Node));

    dummy->key = -1;
    dummy->value = -1;

    /* -------------------- INSERT -------------------- */
    insert(1, 5);
    insert(2, 15);
    insert(3, 20);
    insert(4, 7);
    insert(5, 12);
    insert(6, 1);
    insert(7, 11);
    insert(8, 88);
    insert(9, 22);
    insert(10, 67);

    printf("-------------------- FIND --------------------\n");
    printf("Please inupt the key you want to search.\n");
    printf("(Ex.) key: 5\n");
    printf("key: ");
    int FKey;
    scanf("%d", &FKey);
    
    if (Find(FKey) != -1) {
        printf("Value of Key %d = %d\n", FKey, Find(FKey));
    }
    else {
        printf("Key %d does not exists\n", FKey);
    }
    printf("\n");

    printf("-------------------- DELETE --------------------\n"); 
    printf("Please inupt the key you want to delete.\n");
    printf("(Ex.) key: 7\n");
    printf("key: ");
    int DKey;
    scanf("%d", &DKey);
    
    if (delete(DKey) == -1) {
        printf("Node value of key %d is deleted successfully\n", DKey);
    }
    else {
        printf("Key does not exists\n");
    }

    return 0;
}