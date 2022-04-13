//
// Created by Jason Ketterer on 4/12/22.
//
// To Do:
// Needs ConstIterator support to support const functions such as HasEdge()
//

#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <fstream>
#include "vector.h"
#include "list.h"

template <typename T>
class Graph {
    typedef T Vertex;

public:
    explicit Graph(size_t n = 0);  // default constructor

    void SetVertexSize(size_t n);
    void AddEdge(Vertex from, Vertex to);
    bool HasEdge(Vertex from, Vertex to);
    size_t VertexSize() const { return n_; }
    size_t EdgeSize();
    size_t InDegree(Vertex v);
    size_t OutDegree(Vertex v);

    void readGraphFile(std::istream & is = std::cin);
    void Dump() const;

private:
    Vector< List<Vertex> > g_;
    size_t n_;
};

#include "graph.cpp"

#endif //GRAPH_H
