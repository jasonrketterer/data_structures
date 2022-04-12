//
// Created by Jason Ketterer on 4/12/22.
//

#ifndef GRAPH_H
#define GRAPH_H

#include "vector.h"
#include "list.h"

template <typename T>
class Graph {
    typedef T Vertex;

public:
    explicit Graph(size_t n = 0);  // default constructor

    void SetVertexSize(size_t n);
    //void AddEdge(Vertex from, Vertex to);
    //bool HasEdge(Vertex from, Vertex to) const;
    //size_t VertexSize() const;
    //size_t EdgeSize() const;
    //size_t InDegree(Vertex v) const;
    //size_t OutDegree(Vertex v) const;

    void Dump() const;

private:
    Vector< List<Vertex> > g_;
    size_t n_;
};

#include "graph.cpp"

#endif //GRAPH_H
