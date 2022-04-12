//
// Created by Jason Ketterer on 4/12/22.
//

#include "graph.h"

template <typename T>
Graph<T>::Graph(size_t n) : n_(n), g_{n} {;}

template <typename T>
void Graph<T>::SetVertexSize(size_t n) {
    g_.SetSize(n);
    n_ = n;
}

// expects to read the number of vertices first and then the edges in format 'from to to to ...'
// on a new line for each vertex
template <typename T>
void Graph<T>::readGraphFile(std::istream & is) {
    int n, to , from;
    std::cin >> n;
    SetVertexSize(n);
    while(is >> to) {
        std::cout << to << ' ';
        while(is.peek() != '\n') {
            is >> from;
            std::cout << from << ' ';
        }
        std::cout << std::endl;
    }
}

template <typename T>
void Graph<T>::Dump() const {
    if(n_ != 0) {
        for (Vertex i = 0; i < n_; ++i) {
            std::cout << "[" << i << "]: ";
            g_[i].Display(std::cout);
            std::cout << std::endl;
        }
    }
}