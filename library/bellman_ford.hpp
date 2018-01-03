#ifndef BELLMAN_FORD_HPP
#define BELLMAN_FORD_HPP

#include "my_def.hpp"

struct Bellman {
    struct node {
        int d = numeric_limits<int>::max();
        int p = -1;
    };
    vector<node> nodes;
    vector<vector<int>> input;

    explicit Bellman(const vector<vector<int>> &inp) {
        input = inp;
        nodes = vector<node>(input.size());
    }

    bool bellmanFord(int s) {
        nodes[s].d = 0;
        for (int i = 1; i < input.size(); ++i) {
            for (int i = 0; i < input.size(); ++i) {
                for (int j = 0; j < input[i].size(); ++j) {
                    if (i != j && input[i][j] != 0 && nodes[i].d != numeric_limits<int>::max()) {
                        if (nodes[j].d > nodes[i].d + input[i][j]) {
                            nodes[j].d = nodes[i].d + input[i][j];
                            nodes[j].p = i;
                        }
                    }
                }
            }
        }
        for (int i = 0; i < input.size(); ++i) {
            for (int j = 0; j < input[i].size(); ++j) {
                if (i != j && input[i][j] != 0) {
                    if (nodes[j].d > nodes[i].d + input[i][j]) {
                        return false;
                    }
                }
            }
        }
        return true;
    }
};

#endif

