#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int data;
    struct Node* left;
    struct Node* right;
    struct Node* p; 
}Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void treeInsert(Node** root, Node* z) {
    Node* y = NULL;
    Node* x = *root;
    while (x != NULL) {
        y = x;
        if (z->data < x->data) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    z->p = y;
    if (y == NULL) {
        *root = z;
    } else if (z->data < y->data) {
        y->left = z;
    } else {
        y->right = z;
    }
}

//void printLevels(Node* root, int level) {
//    if (root == NULL) {
//        return;
//    }
//    printf("Node %d is at level %d\n", root->data, level);
//    printLevels(root->left, level + 1);
//    printLevels(root->right, level + 1);
//}

void printBST(Node* root){
	if(root == NULL){
		return;
	}
	printBST(root -> left);
	printf("%d ", root->data);
	printBST(root -> right);
}
int sumOfLevels(Node* root, int level) {
    if (root == NULL) {
        return 0;
    }
    return level + sumOfLevels(root->left, level + 1) + sumOfLevels(root->right, level + 1);
}

int countNodes(Node* root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + countNodes(root->left) + countNodes(root->right);
}

float averageLevel(Node* root, int n) {
    int totalLevels = sumOfLevels(root, n);
    int totalNodes = countNodes(root);
    return (float)totalLevels / totalNodes;
}

Node* Readfile(const char *filename) {
    FILE *file;
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file!!!\n");
        exit(1);
    }
    Node* root = NULL;
    int num;
    
    while (fscanf(file, "%d", &num) != EOF) {
        Node* newNode = createNode(num);
        treeInsert(&root, newNode);
//        printf("%d ", num);
    }
    fclose(file);
    return root;
}

int main() {
    Node* root = Readfile("100numbers.txt");
    printf("Binary Search Tree in ascending order: \n");
    printBST(root);
//    printf("Level of each node:\n");
//    printLevels(root, 1);
    printf("\n\nSum of levels: %d\n", sumOfLevels(root, 0));
    printf("Number of nodes: %d\n", countNodes(root));
    printf("Average level of nodes: %.2f\n", averageLevel(root, 0));
    return 0;
}

