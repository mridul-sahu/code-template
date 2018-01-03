#ifndef DISJOINT_SET_HPP
#define DISJOINT_SET_HPP

#include "my_def.hpp"

struct UnionFind {
    vector<int> parent; // parent[root] is the negative of the size.
    explicit UnionFind(int n) : parent(n, -1) {}

    bool unite(int u, int v) {
        u = root(u);
        v = root(v);
        if (u == v) return false;
        if (parent[u] > parent[v]) swap(u, v);
        parent[u] += parent[v];
        parent[v] = u;
        return true;
    }

    bool find(int u, int v) { return root(u) == root(v); }

    int root(int u) { return parent[u] < 0 ? u : parent[u] = root(parent[u]); }

    int size(int u) { return -parent[root(u)]; }
};

#endif
