#include "bptree.h"
#include <vector>
#include <sys/time.h>

struct timeval curTime(void);
int cut(int length);
void printTreeCore(NODE *n);
void printTree(NODE *node);
NODE *findLeaf(NODE *node, int key);


NODE *allocLeaf(NODE *parent);
TEMP *makeTemp(void);
void insert(int key, DATA *data);
void insertIntoParent(NODE *leaf, int k, NODE *new_leaf);
void insertIntoNode(NODE *parent, NODE *left, int rskey, NODE *right);
void insertIntoTempLeaf(TEMP *temp_leaf, int key, DATA *data);
template <class LEAF>
LEAF *insertInLeaf(LEAF *leaf, int key, DATA *data);

TEMP *allocTempLeaf(NODE *node);
void erasenode(NODE *node);
void initRoot(void);
int interactive();


void 
initRoot(void) {
    Root = NULL;
}

struct timeval
curTime(void)
{
	struct timeval t;
	gettimeofday(&t, NULL);
	return t;
}

int cut(int length) {
    if (length % 2 == 0)
        return length / 2;
    else 
        return length / 2 + 1;
}

void
erasenode(NODE *leaf)
{   
    int i;
    for (i = 0; i < leaf->nkey; i++) {
        leaf->key[i] = 0;
        leaf->chi[i] = NULL;
    }
    leaf->chi[i] = NULL;
    leaf->nkey = 0;
}

NODE *
findLeaf(NODE *node, int key)
{
    int kid;

    if (node->isLeaf) return node;
    for (kid = 0; kid < node->nkey; kid++) {
        if (key < node->key[kid]) break;
    }
    return findLeaf(node->chi[kid], key);

}

NODE *
insertIntoNewRoot(NODE *left, int key, NODE *right)
{
    NODE *root;

    if (!(root = (NODE *)calloc(1, sizeof(NODE)))) ERR;
    root->isLeaf = false;
    root->key[0] = key;
    root->chi[0] = left;
    root->chi[1] = right;
    root->nkey++;
    root->parent = NULL;

    return root;
}

NODE *
makeNode(void)
{
    NODE *new_node;
    if (!(new_node = (NODE *)calloc(1, sizeof(NODE)))) ERR;
    new_node->isLeaf = false;
    new_node->nkey = 0;
    new_node->parent = NULL;
    // new_node->next = NULL;
    return new_node;
}

TEMP *
makeTemp(void) 
{
    TEMP *temp;
    if (!(temp = (TEMP *)calloc(1, sizeof(TEMP)))) ERR;
    temp->nkey = 0;

    return temp;
}

NODE *
makeLeaf(NODE *parent)
{
    NODE *node;
    if (!(node = (NODE *)calloc(1, sizeof(NODE)))) ERR;
    node->isLeaf = true;
    node->parent = parent;
    node->nkey = 0;

    return node;
}


NODE *
insertIntoLeaf(NODE *leaf, int key, DATA *data) 
{
    int i;
    if (key < leaf->key[0]) {
        for (i = leaf->nkey; i>0; i--) {
            leaf->chi[i] = leaf->chi[i-1];
            leaf->key[i] = leaf->key[i-1];
        }
        leaf->key[0] = key;
        leaf->chi[0] = (NODE *)data;
    }
    else {
        for (i = 0; i < leaf->nkey; i++) {
            if (key < leaf->key[i]) break;
        }
        for (int j = leaf->nkey; j > i; j--) {
            leaf->chi[j] = leaf->chi[j-1];
            leaf->key[j] = leaf->key[j-1];
        }
        leaf->key[i] = key;
        leaf->chi[i] = (NODE *)data;
    }
    leaf->nkey++;

    return leaf;
}

void
insertIntoTempLeaf(TEMP *temp_leaf, int key, DATA *data)
{
    int i;
    if (key < temp_leaf->key[0]) {
        for (i = temp_leaf->nkey; i > 0; i--) {
            temp_leaf->chi[i] = temp_leaf->chi[i-1];
            temp_leaf->key[i] = temp_leaf->key[i-1];
        }
        temp_leaf->key[0] = key;
        temp_leaf->chi[0] = (NODE *)data;
    }
    else {
        for (i = 0; i < temp_leaf->nkey; i++) {
            if (key < temp_leaf->key[i]) break;
        }
        for (int j = temp_leaf->nkey; j > i; j--) {
            temp_leaf->chi[j] = temp_leaf->chi[j-1];
            temp_leaf->key[j] = temp_leaf->key[j-1];
        }
        temp_leaf->key[i] = key;
        temp_leaf->chi[i] = (NODE *)data;
    }
	temp_leaf->nkey++;
}

void 
insertInLeafAfterSplitting(NODE *leaf, int key, DATA *data) 
{
    NODE *new_leaf;
    int i, j, split;

    new_leaf = makeLeaf(leaf->parent);

    TEMP *temp_leaf;
    temp_leaf = makeTemp();

    for (i = 0; i < (N-1); i++) {
        temp_leaf->chi[i] = leaf->chi[i];
        temp_leaf->key[i] = leaf->key[i];
        temp_leaf->nkey++;
    }
    temp_leaf->chi[i] = leaf->chi[i];

    insertIntoTempLeaf(temp_leaf, key, data);
    
    erasenode(leaf);
    
    for (int i = 0; i < N-1; i++) {
        leaf->chi[i] = temp_leaf->chi[i];
        leaf->key[i] = temp_leaf->key[i];
        leaf->nkey++;
    }
    
    for (i = split, j = 0; i < N; i++, j++) {
        new_leaf->chi[j] = temp_leaf->chi[i];
        new_leaf->key[j] = temp_leaf->key[i];
        new_leaf->nkey++;
    }

    new_leaf->chi[N-1] = leaf->chi[N-1];
    leaf->chi[N-1] = new_leaf;
    int rs_key = new_leaf->key[0];
    insertIntoParent(leaf, rs_key, new_leaf);
}

void
insertIntoNode(NODE *parent, NODE *left, int rskey, NODE *right)
{
    int lcid = 0;
    int rcid = 0;
    int i;

    for (i = 0; i < parent->nkey+1; i++) {
        if (parent->chi[i] == left) {
            lcid = i;
            rcid = i + 1;
            break;
        }
    }

    for (i = parent->nkey+1; i > rcid; i--) 
        parent->chi[i] = parent->chi[i-1];
    for (i = parent->nkey; i > lcid; i--) 
        parent->key[i] = parent->key[i-1];

    parent->key[lcid] = rskey;
    parent->chi[rcid] = right;
    parent->nkey++;
}

TEMP *
insertIntoTempNode(TEMP *temp, NODE *left, int rs_key, NODE *right)
{

}

void
insertIntoNodeAfterSplitting(NODE *old_node, int rs_key, NODE *right)
{   
    int i;
    TEMP *temp_node;

    temp_node = makeTemp();
    for (i = 0; i < (N-1); i++) {
        temp_node->chi[i] = old_node->chi[i];
        temp_node->key[i] = old_node->key[i];
        temp_node->nkey++;
    }
    temp_node->chi[i] = old_node->chi[i];

    temp_node = insertIntoTempNode(temp_node, old_node, rs_key, right);
}

void 
insertInTempParentNode(TEMP *temp, NODE *left_child, int right_small_key, NODE *right_child)
{
    int left_child_id = 0;
    int right_child_id = 0;
    int i;

    for (i = 0; i < temp->nkey; i++) {
        if (temp->chi[i] == left_child) {
            left_child_id = i;
            right_child_id = left_child_id + 1; 
            break;
        }
    }
}

void
insertIntoParent(NODE *left, int rskey, NODE *right)
{

    if (left == Root) {
        Root = insertIntoNewRoot(left, rskey, right);
        left->parent = Root;
        right->parent = Root;
        return;
    }

    NODE *parent;
    parent = left->parent;

    if (parent->nkey < (N-1)) {
        insertIntoNode(parent, left, rskey, right);
    }
    else {
        // insertIntoNodeAfterSplitting()
        TEMP temp_parent;
        //insertInTempParentNode(&temp_parent, left, rskey, right);
    }


}


int 
interactive()
{   
    int key;

    std::cout << "Key: ";
    std::cin >> key;

    return key;
}

void
insert(int key, DATA *data)
{
    NODE *leaf = NULL;

    if (Root == NULL) {
        leaf = makeLeaf(NULL);
        Root = leaf;
    }

    else {
        leaf = findLeaf(Root, key);
    }

    if (leaf->nkey < (N-1)) {
        insertIntoLeaf(leaf, key, data);
    }
    else {
        insertInLeafAfterSplitting(leaf, key, data);
    }
}

void
printTreeCore(NODE *n)
{
    printf("[");
    int i;
    for (i = 0; i < n->nkey; i++) {
        if (!n->isLeaf) printTreeCore(n->chi[i]);
        printf("%d", n->key[i]);
        if (i != n->nkey-1 && n->isLeaf) putchar(' ');
    }
    if (!n->isLeaf) printTreeCore(n->chi[n->nkey]);
    printf("]");
}

void 
printTree(NODE *node)
{
    printTreeCore(node);
    printf("\n"); fflush(stdout);
}


int
main(int argc, char *argv[])
{
  struct timeval begin, end;

	// 
	initRoot();

	printf("-----Insert-----\n");
	begin = curTime();
	while (true) {
			insert(interactive(), NULL);
		printTree(Root);
	}
	end = curTime();

	return 0;
}
