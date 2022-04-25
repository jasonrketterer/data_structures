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
    Vertex front;
    ListIterator<T> i;
    while(!q.Empty()) {
        front = q.Front();
        q.Pop();
        visited[front] = true;
        std::cout << front << ' ';
        for(i = g_[front].Begin(); i != g_[front].End(); ++i) {
            if (!visited[*i]) {
                q.Push(*i);
                visited[*i] = true;
            }
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
            std::cout << '\n';
        }
    }
}

// uses bidirectional BFS to determine if a path exists between a and b
template<typename T>
bool Graph<T>::isPath(Vertex a, Vertex b) const {
    if( a == b) return true;

    Vector<bool> visited_a(VertexSize(), false);
    Vector<bool> visited_b(VertexSize(), false);
    List<Vertex> q_a, q_b;

    q_a.PushFront(a);
    q_b.PushFront(b);
    Vertex front_a, front_b;
    ConstListIterator<Vertex> i, j;
    while(!q_a.Empty() && !q_b.Empty()) {
        front_a = q_a.Front();
        front_b = q_b.Front();
        visited_a[front_a] = true;
        visited_b[front_b] = true;
        q_a.PopFront(); q_b.PopFront();

        // add a's children for curr vertex at front of q
        for(i = g_[front_a].Begin(); i != g_[front_a].End(); ++i) {
            if(!visited_a[*i]) {
                visited_a[*i] = true;
                q_a.PushBack(*i);
            }
        }
        // add b's children for current vertex, checking along the way if any of them equal
    }
}
