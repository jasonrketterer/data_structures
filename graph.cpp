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
bool Graph<T>::HasEdge(Vertex from, Vertex to) const {
    for(ConstListIterator<T> i = g_[from].Begin(); i != g_[from].End(); ++i)
        if(*i == to)
            return true;
    return false;
}

template <typename T>
size_t Graph<T>::EdgeSize() const {
    size_t edges = 0;
    for(size_t v = 0; v < n_; ++v)
        edges += g_[v].Size();
    return edges;
}

template <typename T>
size_t Graph<T>::InDegree(Vertex v) const {
    size_t indeg = 0;
    for(Vertex n = 0; n < VertexSize(); ++n) {
        for(ConstListIterator<T> i = g_[n].Begin(); i != g_[n].End(); ++i) {
            if(*i == v)
                ++indeg;
        }
    }
    return indeg;
}

template <typename T>
size_t Graph<T>::OutDegree(Vertex v) const {
    return g_[v].Size();
}

// Iterative version of Depth First Search
template <typename T>
void Graph<T>::dfsIter(Vertex src) {
    Stack<T> stk;
    Vector<bool> visited(VertexSize(), false);
    Vector< ListIterator<T> > adjListIterators(VertexSize());

    // adjListIterators will be an array of Iterators for each vertex adjacency list
    // that will find the next unvisited vertex in the list.  This will allow us to
    // traverse each list only one time, help keeping runtime O(|V| + |E|)

    // initialize adjListIterators
    for(Vertex v = 0; v < VertexSize(); ++v)
        adjListIterators[v] = g_[v].Begin();

    Vertex top;
    ListIterator<T> nuv;

    stk.Push(src);
    while(!stk.Empty()) {
        top = stk.Top();
        if(!visited[top]) {
            visited[top] = true;
            std::cout << top << ' ';
        }
        nuv = findNextUnvisited(top, visited, adjListIterators);
        if(nuv != g_[top].End()) {
            stk.Push(*nuv);
        }
        else { // no more neighbors to visit
            stk.Pop();
        }
    }
    std::cout << std::endl;
}

template <typename T>
ListIterator<T> Graph<T>::findNextUnvisited(Vertex v, Vector<bool> & visited, Vector< ListIterator<T> > & adjListIterators) {
    while(adjListIterators[v] != g_[v].End() && visited[*adjListIterators[v]])
        ++adjListIterators[v];
    return adjListIterators[v];
}

template <typename T>
void Graph<T>::dfs(Vertex src) {
    static Vector<bool> visited(VertexSize(), false);

    if(!visited[src]) {
        std::cout << src << ' ';
        visited[src] = true;
    }
    ListIterator<T> i;
    for(i = g_[src].Begin(); i != g_[src].End(); ++i)
        if(!visited[*i])
            dfs(*i);
}

template <typename T>
void Graph<T>::bfs(Vertex src) {
    Vector<bool> visited(VertexSize(), false);
    Queue<T> q;

    q.Push(src);
    Vertex front; ListIterator<T> i;
    while(!q.Empty()) {
        front = q.Front();
        q.Pop();
        visited[front] = true;
        std::cout << front << ' ';
        for(i = g_[front].Begin(); i != g_[front].End(); ++i) {
            if (!visited[*i])
                q.Push(*i);
            visited[*i] = true;
        }
    }
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