#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTICES 9
#define MAX_EDGES 11

struct Edge {
    int src, dest, weight;
};

struct Subset {
    int parent;
    int rank;
};

struct Graph {
    int num_vertices, num_edges;
    struct Edge edges[MAX_EDGES];
};

void swap(struct Edge *a, struct Edge *b) {
    struct Edge temp = *a;
    *a = *b;
    *b = temp;
}

int separate(struct Edge edges[], int first, int last) {
    int i = first + 1, j = last;
    struct Edge pivot = edges[first];

    while (i <= j) {
        while (i <= last && edges[i].weight <= pivot.weight)
            i++;
        while (edges[j].weight > pivot.weight)
            j--;
        if (i < j) {
            swap(&edges[i], &edges[j]);
        }
    }
    swap(&edges[first], &edges[j]);
    return j;
}

void Qsort(struct Edge edges[], int first, int last) {
    if (first < last) {
        int pivot = separate(edges, first, last);
        Qsort(edges, first, pivot - 1);
        Qsort(edges, pivot + 1, last);
    }
}

int find(struct Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

void Union(struct Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

void kruskalMST(struct Graph *graph) {
    int num_vertices = graph->num_vertices;
    int num_edges = graph->num_edges;
    struct Edge result[num_vertices];
    int v;
    int e = 0;
    int i = 0; 

    Qsort(graph->edges, 0, num_edges - 1);

    struct Subset *subsets = (struct Subset *)malloc(num_vertices * sizeof(struct Subset));

    for (v = 0; v < num_vertices; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    while (e < num_vertices - 1 && i < num_edges) {
        struct Edge next_edge = graph->edges[i++];
        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        // 找source和destination的爸爸，如果一樣就代表會循環，跳過他，如果不一樣就放在result然後輸出 
        if (x != y) {
            result[e++] = next_edge;
            Union(subsets, x, y);//鏈接兩個點，就是把他們納入一家人啦，然後根據他們的rank排序，誰才是爸爸 
        }
    }

    printf("Selected Path:\n");
    for (i = 0; i < e; ++i)
        printf("%c - %c\n", result[i].src + 'A', result[i].dest + 'A');

    free(subsets);
}

void readFile(char *filename, struct Graph *graph) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        exit(1);
    }

    char src, dest;
    int weight;
    int index = 0;

    while (fscanf(file, "%c %c %d\n", &src, &dest, &weight) != EOF) {
        graph->edges[index].src = src - 'A';
        graph->edges[index].dest = dest - 'A';
        graph->edges[index].weight = weight;
        index++;
    }

    fclose(file);

    graph->num_vertices = MAX_VERTICES;
    graph->num_edges = index;
}

int main(){
    struct Graph graph;
    char filename1[] = "graph1.txt";
    readFile(filename1, &graph);
    printf("%s:\n", filename1);
    kruskalMST(&graph);
    char filename2[] = "graph2.txt";
    readFile(filename2, &graph);
    printf("\n%s:\n", filename2);
    kruskalMST(&graph);
    return 0;
}
