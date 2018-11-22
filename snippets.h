#ifndef SNIPPETS_H
#define SNIPPETS_H

#include <vector>

#define ARR_SIZE 16
#define VERTICES 7 // set 7 for kruskal

class array {
public:
    int* arr;
    array();
    void selectionSort();
    void printArray();
    void bubbleSort();
    void mergeSort();
    int* arrayMerge(int*, int*, int);
    void printArrayMerge(int*, int);
};

class graph {
public:
    int** gr;
    int** mst; // minimal spanning tree
    graph();
    void floyd();
    void kruskal();
    void dijkstra(int, int);
    void fordBellman();


private:
    int kruskalCriteria(int**, int, int);
    void graphKruskal();
    void printGraph(int**);
};

#endif