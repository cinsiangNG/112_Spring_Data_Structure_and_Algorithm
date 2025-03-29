#include<stdio.h>
#include<stdlib.h>

typedef struct dlistnode
{
	struct dlistnode *left; 
	int data; 
	struct dlistnode *right; 
} Dnode;

Dnode *FirstNode=NULL;
int Score[10]={32,90,27,55,43,10,86,61,3,77};

int InsertAfter(Dnode *p, int value)
{
	Dnode* NewNode;
    NewNode = (Dnode*)malloc(sizeof(Dnode));
    if(NewNode == NULL)
        return 0;
    
    NewNode->data = value;
    if(FirstNode == NULL || FirstNode->data >= value){
        NewNode->left = NULL;
        NewNode->right = FirstNode;
        if(FirstNode != NULL)
            FirstNode->left = NewNode;
        FirstNode = NewNode;
    }
    else{
        Dnode *p = FirstNode;
        while(p->right != NULL && p->right->data < value){
            p = p->right;
        }
        NewNode->left = p;
        NewNode->right = p->right;
        if(p->right != NULL)
            p->right->left = NewNode;
        p->right = NewNode;
    }
    return 1;
}

int DeleteNode(Dnode *p)
{
	if(p == NULL)
		return 0;
	
	p -> left -> right = p -> right;
	p -> right -> left = p -> left;
	free(p);
	return 1;
}

void PrintResult()
{
	Dnode *p;
	for(p=FirstNode;p;p=p->right)
	{
		printf("%d ", p->data);
	}
	printf("\n");
}

int main()
{
	int i;
	Dnode *currentNode = NULL;
	for(i=0;i<10;i++){ //Insert nodes from Score array
		InsertAfter(currentNode, Score[i]);
		if(currentNode == NULL){
			currentNode = FirstNode;
		}
		else{
			currentNode = currentNode -> right;
		}
	}
	PrintResult();
	currentNode = FirstNode;
	for(i=0; i<4; i++){ //Delete the 5th node in the link list
		currentNode = currentNode -> right;
	}
	DeleteNode(currentNode);
	PrintResult();
	while(currentNode){ //Delete the node with value 86 in the link list
		if(currentNode -> data == 86){
			DeleteNode(currentNode);
		}
		currentNode = currentNode->right;
	}
	PrintResult();
	return(0);
}

