#include "snippets.h"
#include <random>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <climits>

array::array() {
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0, 1024);
    this->arr = new int[ARR_SIZE];
    for (int i = 0; i < ARR_SIZE; i++) {
        this->arr[i] = distribution(generator);
    }
}

void array::printArray() {
    for (int k = 0; k < ARR_SIZE; k++) {
        std::cout << k << ":" << this->arr[k] << std::endl;
    }
}

void array::printArrayMerge(int* array, int size) {
    for (int k = 0; k < size; k++) {
        std::cout << std::setw(6) << array[k];
    }
}

int* array::arrayMerge(int* arrA, int* arrB, int size) {
    int idxA = 0, idxB = 0, i = 0;
    std::cout << "Merging arrays: " << std::endl << "a[";
    this->printArrayMerge(arrA, size);
    std::cout << ']' << std::endl << "b[";
    this->printArrayMerge(arrB, size);
    std::cout << ']' << std::endl;
    bool AisEmpty = false, BisEmpty = false;
    int *res = new int[size * 2];
    for (i = 0; i < size * 2; i++) {
        if (AisEmpty || BisEmpty) {
            if (AisEmpty) {
                res[i] = arrB[idxB];
                idxB++;
                continue;
            }
            if (BisEmpty) {
                res[i] = arrA[idxA];
                idxA++;
                continue;
            }
        }
        if (arrA[idxA] < arrB[idxB]) {
            res[i] = arrA[idxA];
            if (idxA < size) {
                idxA++;
            }
            if (idxA == size){
                AisEmpty = true;
            }
            continue;
        }
        if (arrB[idxB] < arrA[idxA]) {
            res[i] = arrB[idxB];
            if (idxB < size) {
                idxB++;
            }
            if (idxB == size){
                BisEmpty = true;
            }
            continue;
        }
    }
    return res;
}

void array::selectionSort() {
    int position = 0;
    for (int i = 0; i < ARR_SIZE; i++) {
        int minpos = -1;
        int min = INT_MAX;
        for (int j = position; j < ARR_SIZE; j++) {
            if (this->arr[j] < min) {
                minpos = j;
                min = this->arr[j];
            }
        }
        if (minpos != -1) {
            std::swap(this->arr[position], this->arr[minpos]);
        }
        position++;
    }
    //printArray(arr);
    return;
}

void array::bubbleSort() {
    bool isSwapped;
    for (int i = 0; i < ARR_SIZE - 1; i++) {
        isSwapped = false;
        for (int j = 0; j < ARR_SIZE - i - 1; j++) {
            if (this->arr[j] > this->arr[j + 1]) {
                std::swap(this->arr[j], this->arr[j + 1]);
                isSwapped = true;
            }
        }
        if (!isSwapped) {
            break;
        }
    }
    //printArray(arr);
}

void array::mergeSort() { // works only if ARR_SIZE is a power of 2
    int iters = int(log2(ARR_SIZE));
    this->printArray();
    int ***gdom = new int**[iters]; // BEHOLD THE GREAT DUMP OF MEMORY
    for (int i = 0; i < iters; i++) { // tricky memory allocation for 3d array
        gdom[i] = new int*[int(pow(2, iters - i - 1))];
        for (int j = 0; j < int(pow(2, iters - i - 1)); j++) {
            gdom[i][j] = new int[int(pow(2, i + 1))];
        }
    }
    for (int i = 0; i < int(pow(2, iters - 1)); i++) { // base array init
        if (this->arr[2 * i] <= this->arr[2 * i + 1]) { // taking care of initial 2-elements arrays sorting
            gdom[0][i][0] = this->arr[2 * i];
            gdom[0][i][1] = this->arr[2 * i + 1];
        }
        else {
            gdom[0][i][0] = this->arr[2 * i + 1];
            gdom[0][i][1] = this->arr[2 * i];
        }
    }
    for (int i = 1; i < iters; i++) {
        std::cout << "Size = " << int(pow(2, i)) << std::endl;
        for (int j = 0; j < int(pow(2, iters - i - 1)); j++) {
            gdom[i][j] = arrayMerge(gdom[i - 1][2 * j], gdom[i - 1][2 * j + 1], int(pow(2, i)));
        }
    }
    this->printArrayMerge(gdom[iters - 1][0], ARR_SIZE);
    std::cout << std::endl;
}

graph::graph() {
    mst = nullptr;
    std::default_random_engine rng;
    std::uniform_int_distribution<int> dWGT(2, 100);
    std::uniform_int_distribution<int> dVTX(1, VERTICES - 2);
    int shortestPath[int(log2(VERTICES))];
    shortestPath[0] = 0;
    shortestPath[int(log2(VERTICES)) - 1] = VERTICES - 1;
    this->gr = new int*[VERTICES];
    for (int i = 0; i < VERTICES; i++) {
        this->gr[i] = new int[VERTICES];
    }
    for (int i = 0; i < VERTICES; i++) {
        for (int j = 0; j < VERTICES; j++) {
            this->gr[i][j] = 0; // no graph vertices connections
        }
    }
    for (int l = 0; l < VERTICES; l++) {
        for (int i = 0; i < VERTICES; i++) {
            if (this->gr[l][i] == 0) {
                this->gr[l][i] = dWGT(rng);
                this->gr[i][l] = this->gr[l][i];
            }
            else {
                continue;
            }
        }
    }
    for (int i = 0; i < VERTICES; i++) {
        this->gr[i][i] = 0;
    }
    /*
     * generating shortest path in graph
     * n = log2(VERTICES) vertices with weight sum = log2(VERTICES)
     */
    for (int i = 1; i < int(log2(VERTICES)) - 1; i++) {
        shortestPath[i] = dVTX(rng);
    }
    for (int k = 0; k < int(log2(VERTICES)) - 1; k++) {
        this->gr[shortestPath[k]][shortestPath[k + 1]] = 1;
        this->gr[shortestPath[k + 1]][shortestPath[k]] = 1;
    }

}

void graph::printGraph(int **gr) {
    std::cout.setf(std::ios::fixed);
    for (int i = 0; i < VERTICES; i++) {
        for (int j = 0; j < VERTICES; j++) {
            std::cout << std::setw(10) << gr[i][j]; // << '\t';
        }
        std::cout << std::endl;
    }
}

void graph::floyd() {
    this->printGraph(this->gr);
    std::cout << std::endl;
    for (int i = 0; i < VERTICES; i++) {
        for (int j = 0; j < VERTICES; j++) {
            for (int k = 0; k < VERTICES; k++) {
                this->gr[j][k] = std::min(this->gr[j][k], this->gr[j][i] + this->gr[i][k]);
            }
        }
    }
    this->printGraph(this->gr);
}

int graph::kruskalCriteria(int** conn, int v1, int v2) { // TODO: rewrite
    int v1connX = -1, v2connX = -1;
    int v1connY = -1, v2connY = -1;
    int free = 0;
    for (int i = 0; i < VERTICES; i++) {
        if (conn[i][0] == -1) {
            free = i;
            break;
        }
        for (int j = 0; j < VERTICES; j++) {
            if (conn[i][j] == v1) {
                v1connX = i;
                v1connY = j;
            }
            if (conn[i][j] == v2) {
                v2connX = i;
                v2connY = j;
            }
        }
        if (v1connX != -1 && v2connX != -1) {
            break;
        }
    }
    if (v1connX == v2connX && v1connX == -1) {
        conn[free][0] = v1;
        conn[free][1] = v2;
        return 0;
    }
    if (v1connX == v2connX) {
        return -1;
    }
    if (v1connX != v2connX) {
        if (v1connX != -1 && v2connX == -1) {
            conn[v1connX][v1connY + 1] = v2;
            return 0;
        }
        if (v1connX == -1 && v2connX != -1) {
            conn[v2connX][v2connY + 1] = v1;
            return 0;
        }
        if (v1connX == -1 && v2connX == -1) {
            conn[free][0] = v1;
            conn[free][1] = v2;
            return 0;
        }
        if (v1connX != -1 && v2connX !=  -1) {
            int i = 0;
            while (conn[v2connX][i] != 0){
                conn[v1connX][v1connY + i + 1] = conn[v2connX][i];
                conn[v2connX][i] = 0;
                i++;
            }
            return 0;
        }
    }
    return -3;
}

void graph::kruskal() {
    this->graphKruskal();
    int ret = 0;
    int edgesInMST = 0;
    int** conn = new int*[VERTICES];
    this->mst = new int*[VERTICES];
    for (int i = 0; i < VERTICES; i++) {
        this->mst[i] = new int[VERTICES];
        conn[i] = new int[VERTICES];
    }
    for (int i = 0; i < VERTICES; i++) {
        for (int j = 0; j < VERTICES; j++) {
            this->mst[i][j] = 0;
            conn[i][j] = -1;
        }
    }
    int v1 = 0, v2 = 0;
    std::vector<std::pair<int, std::pair<int, int>>> edges; // edge weight, id vert1, id vert2
    for (int i = 0; i < VERTICES; i++) {
        for (int j = 0; j < VERTICES; j++) {
            if (this->gr[i][j] != 0 && std::find(edges.begin(), edges.end(),
                    std::pair<int, std::pair<int,int>>(this->gr[i][j], std::pair<int,int>(j,i))) == edges.end()) {
                edges.push_back(std::pair<int, std::pair<int,int>>(this->gr[i][j], std::pair<int,int>(i,j)));
            }
        }
    }
    std::sort(edges.begin(), edges.end()); // sorting edges by weight
    for (int i = 0; i < edges.size(); i++) {
        if (edgesInMST == VERTICES - 1) {
            break;
        }
        v1 = edges[i].second.first;
        v2 = edges[i].second.second;
        if (v1 == v2) {
            continue;
        }
        std::cout << "Checking edge " << v1 + 1 << "-" << v2 + 1 << std::endl;
        ret = this->kruskalCriteria(conn, v1, v2);
        if (ret == 0) {
            this->mst[v1][v2] = edges[i].first;
            this->mst[v2][v1] = edges[i].first;
            std::cout << "OK" << std::endl;
            edgesInMST++;
        }
        else if (ret == -1) {
            std::cout << "It will make a cycle :(" << std::endl;
        }
        else if (ret == -2) {
            std::cout << "Broken edge!";
        }
    }
    printGraph(this->mst);
}

void graph::dijkstra(int start, int end) {
    // int
}

void graph::graphKruskal() {
    this->gr = new int*[7];
    for (int i = 0; i < 7; i++) {
        this->gr[i] = new  int[7];
    }
    for (int j = 0; j < 7; j++) {
        for (int i = 0; i < 7; i++) {
            this->gr[i][j] = 0;
        }
    }
    // please god forgive me
    gr[0][5] = 23;
    gr[0][6] = 1;
    gr[0][1] = 20;
    gr[1][0] = 20;
    gr[1][6] = 4;
    gr[1][2] = 5;
    gr[2][1] = 5;
    gr[2][6] = 9;
    gr[2][3] = 3;
    gr[3][2] = 3;
    gr[3][6] = 16;
    gr[3][4] = 17;
    gr[4][3] = 17;
    gr[4][6] = 25;
    gr[4][5] = 28;
    gr[5][4] = 28;
    gr[5][6] = 36;
    gr[5][0] = 23;
    gr[6][0] = 1;
    gr[6][1] = 4;
    gr[6][2] = 9;
    gr[6][3] = 16;
    gr[6][4] = 25;
    gr[6][5] = 36;
}

void graph::fordBellman() {
    std::vector<std::pair<int, std::pair<int, int>>> edges; // edge weight, id vert1, id vert2
    for (int i = 0; i < VERTICES; i++) {
        for (int j = 0; j < VERTICES; j++) {
            if (this->gr[i][j] != 0 && std::find(edges.begin(), edges.end(),
                                                 std::pair<int, std::pair<int,int>>(this->gr[i][j], std::pair<int,int>(j,i))) == edges.end()) {
                edges.push_back(std::pair<int, std::pair<int,int>>(this->gr[i][j], std::pair<int,int>(i,j)));
            }
        }
    }
    bool changed = true;
    int *wgt = new int[VERTICES];
    for (int k = 0; k < VERTICES; k++) {
        wgt[k] = INT_MAX;
    }
    wgt[0] = 0;
    while (changed) {
        changed = false;
        for (int i = 0; i < edges.size(); i++) {
            if (wgt[edges[i].second.second] > wgt[edges[i].second.first] + edges[i].first) {
                wgt[edges[i].second.second] = wgt[edges[i].second.first] + edges[i].first;
                changed = true;
            }
        }
    }
    for (int l = 0; l < VERTICES; l++) {
        std::cout << l  << ": " << wgt[l] << std::endl;
    }
}
