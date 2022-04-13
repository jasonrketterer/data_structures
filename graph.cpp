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
void Graph<T>::AddEdge(Vertex from, Vertex to) {
    g_[from].PushBack(to);
}

template <typename T>
bool Graph<T>::HasEdge(Vertex from, Vertex to) {
    for(ListIterator<T> i = g_[from].Begin(); i != g_[from].End(); ++i)
        if(*i == to)
            return true;
    return false;
}

template <typename T>
size_t Graph<T>::EdgeSize() {
    size_t edges = 0;
    for(size_t v = 0; v < n_; ++v)
        edges += g_[v].Size();
    return edges;
}

template <typename T>
size_t Graph<T>::InDegree(Vertex v) {
    size_t indeg = 0;
    for(Vertex n = 0; n < VertexSize(); ++n) {
        for(ListIterator<T> i = g_[n].Begin(); i != g_[n].End(); ++i) {
            if(*i == v)
                ++indeg;
        }
    }
    return indeg;
}

template <typename T>
size_t Graph<T>::OutDegree(Vertex v) {
    return g_[v].Size();
}


// expects to read the number of vertices first and then the edges in format 'from to to to ...'
// on a new line for each vertex
template <typename T>
void Graph<T>::readGraphFile(std::istream & is) {
    int n, to , from;
    std::cin >> n;
    SetVertexSize(n);
    while(is >> to) {
        //std::cout << to << ' ';
        while(is.peek() != '\n') {
            is >> from;
            AddEdge(to, from);
            //std::cout << from << ' ';
        }
        //std::cout << std::endl;
    }
}

template <typename T>
void Graph<T>::Dump() const {
    if(n_ != 0) {
        for (Vertex i = 0; i < n_; ++i) {
            std::cout << "[" << i << "]: ";
            g_[i].Display(std::cout);
        }
    }
}