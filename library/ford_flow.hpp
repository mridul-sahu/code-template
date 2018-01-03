#ifndef FORD_FLOW_HPP
#define FORD_FLOW_HPP

#include "my_def.hpp"

struct FordFlow {
    vector<vector<int>> input;

    FordFlow(const vector<vector<int>> &inp) : input(inp) {}

    bool bfs(int s, int t, vector<int> &parent) {
        vector<bool> visited(input.size(), false);
        queue<int> q;
        q.push(s);
        parent[s] = -1;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            visited[u] = true;
            for (int v = 0; v < input.size(); ++v) {
                if (!visited[v] && input[u][v] != 0) {
                    parent[v] = u;
                    q.push(v);
                    if (v == t)
                        return true;
                }
            }
        }
        return false;
    }

    int fordFulkerson(int s, int t) {
        vector<int> parent(input.size());
        int max_flow = 0;
        while (bfs(s, t, parent)) {
            int path_flow = numeric_limits<int>::max();

            for (int v = t; v != s; v = parent[v])
                path_flow = min(path_flow, input[parent[v]][v]);

            for (int v = t; v != s; v = parent[v]) {
                input[parent[v]][v] -= path_flow;
                input[v][parent[v]] += path_flow;
            }
            max_flow += path_flow;
        }
        return max_flow;
    }
};

#endif

