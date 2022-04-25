//
// Created by Jason Ketterer on 4/12/22.
//
// To Do:
// Needs ConstIterator support to support const functions such as HasEdge()
//

#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include "vector.h"
#include "list.h"
#include "stack.h"
#include "queue.h"

template <typename T>
class Graph {
    typedef T Vertex;

public:
    explicit Graph(size_t n = 0);  // default constructor

    void SetVertexSize(size_t n);
    void AddEdge(Vertex from, Vertex to);
    bool HasEdge(Vertex from, Vertex to) const;
    size_t VertexSize() const { return n_; }
    size_t EdgeSize() const;
    size_t InDegree(Vertex v) const;
    size_t OutDegree(Vertex v) const;

    void dfsIter(Vertex src); // iterative version
    void dfs(Vertex src);  // recursive version
    void bfs(Vertex src);

    bool isPath(Vertex a, Vertex b) const;

    void readGraphFile(std::istream & is = std::cin);
    void Dump() const;

private:
    Vector< List<Vertex> > g_;
    size_t n_;

    // helper function for DFS
    ListIterator<T> findNextUnvisited(Vertex v, Vector<bool> & visited, Vector< ListIterator<T> > & adjListIterators);
};

#include "graph.cpp"

#endif //GRAPH_H
