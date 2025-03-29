#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

int input[MAX_SIZE];
int heap_tree[MAX_SIZE];
int last_index = -1;

void swap(int *a, int *b){
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void insert_min_heap(int id_temp){
	int index;
	if(last_index >= MAX_SIZE -1){
		printf("The Heap is full!!!\n");
		exit(1);
	}
	else{
		heap_tree[++last_index] = id_temp;
		index = last_index;
		while(index>0){
			if(heap_tree[index] >= heap_tree[(index-1)/2])
				break;
			else{
				swap(&heap_tree[index], &heap_tree[(index-1)/2]);
				index = (index-1)/2;
			}
		}
	}
}

int delete_min_heap(){
	int parent, child;
	int item, temp;
	if(last_index < 0){
		printf("Heap is empty!!\n");
	}
	else{
		item = heap_tree[0];
		temp = heap_tree[last_index--];
		parent = 0;
		child = 1;
		while(child<=last_index){
			if((child<last_index)&&(heap_tree[child]>heap_tree[child + 1])){
				child++;
			}
			heap_tree[parent] = heap_tree[child];
			if(heap_tree[child]>temp){
				break;
			}
			parent = child;	child = (child+1)*2-1; 
		}
		heap_tree[parent] = temp;
		return item;
	}
}

int seperate(int first, int last){
	int i = first + 1, j = last;
	int pivot = first;
	
	while(i < j){
		for(;input[i]>input[pivot] && i<j; i++);
		for(;input[j]<input[pivot] && i<j; j--);
		if(i>=j)
			break;
		swap(&input[i], &input[j]);
		
	}
	if(input[pivot]>=input[j]){
		j--;
	}
	swap(&input[pivot], &input[j]);
	return j;
}

void Qsort(int first, int last){
	int pivot;
	if(first<last){
		pivot = seperate(first, last);
		Qsort(first, pivot-1);
		Qsort(pivot+1, last);
	}	
}

void Readfile(const char *filename){
	FILE *file;
	file = fopen(filename, "r");
	if(file == NULL){
		printf("file failed opening!!");
		exit(1);
	}
	int i = 0;
    while (fscanf(file, "%d", &input[i]) != EOF && i < MAX_SIZE) {
        i++;
    }
    fclose(file);
}

void insert_heap(){
	int i;
	for(i=0;i<MAX_SIZE;i++){
		insert_min_heap(input[i]);
	}
}

void OutputFile1(const char *filename){
	FILE *foutput1;
	foutput1 = fopen(filename, "w");
	while(last_index >= 0){
		int min = delete_min_heap();
		fprintf(foutput1, "%d\n", min);
	}
	fclose(foutput1);
}

void OutputFile2(const char *filename){
	FILE *foutput2;
	int i;
	foutput2 = fopen(filename, "w");
	for(i=0; i<MAX_SIZE; i++){
		fprintf(foutput2, "%d\n", input[i]);
	}
	fclose(foutput2);
}

int main(){
	Readfile("100numbers.txt");
	insert_heap();
	OutputFile1("ascending.txt");
	Qsort(0, MAX_SIZE-1);
	OutputFile2("descending.txt");
	return 0;
}
