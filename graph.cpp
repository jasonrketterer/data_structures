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