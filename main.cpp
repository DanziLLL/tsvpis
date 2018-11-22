#include <iostream>
#include <chrono>
#include "snippets.h"

int main() {
    int option;
    std::cout << "1 for selection sort" << std::endl;
    std::cout << "2 for bubble sort" << std::endl;
    std::cout << "3 for non-recursive merge sort" << std::endl;
    std::cout << "4 for Floyd-Warshall algorithm" << std::endl;
    std::cout << "5 for Kruskal algorithm ## SET VERTICES = 7 in snippets.h! ##" << std::endl;
    std::cout << "6 for Ford-Bellman algorithm" << std::endl;

    std::cin >> option;
    switch(option) {
        case 1: {
            array *a = new array;
            auto start = std::chrono::steady_clock::now();
            a->selectionSort();
            auto end = std::chrono::steady_clock::now();
            std::cout << "Running time: " << std::chrono::duration <double, std::milli> (end - start).count() << " ms" << std::endl;
            break;
        }
        case 2: {
            array *a = new array;
            auto start = std::chrono::steady_clock::now();
            a->bubbleSort();
            auto end = std::chrono::steady_clock::now();
            std::cout << "Running time: " << std::chrono::duration <double, std::milli> (end - start).count() << " ms" << std::endl;
            break;
        }
        case 3: {
            array *a = new array;
            auto start = std::chrono::steady_clock::now();
            a->mergeSort();
            auto end = std::chrono::steady_clock::now();
            std::cout << "Running time: " << std::chrono::duration <double, std::milli> (end - start).count() << " ms" << std::endl;
            break;
        }
        case 4: {
            graph *g = new graph;
            auto start = std::chrono::steady_clock::now();
            g->floyd();
            auto end = std::chrono::steady_clock::now();
            std::cout << "Running time: " << std::chrono::duration <double, std::milli> (end - start).count() << " ms" << std::endl;
            break;
        }
        case 5: {
            graph *g = new graph;
            auto start = std::chrono::steady_clock::now();
            g->kruskal();
            auto end = std::chrono::steady_clock::now();
            std::cout << "Running time: " << std::chrono::duration <double, std::milli> (end - start).count() << " ms" << std::endl;
            break;
        }
        case 6: {
            graph *g = new graph;
            auto start = std::chrono::steady_clock::now();
            g->fordBellman();
            auto end = std::chrono::steady_clock::now();
            std::cout << "Running time: " << std::chrono::duration <double, std::milli> (end - start).count() << " ms" << std::endl;
            break;
        }
        default: {
            return 0;
        }
    }
    return 0;
}

