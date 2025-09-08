#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        // Grafo (não direcionado)
        vector<vector<int>> g(n);
        g.reserve(n);
        for (auto &e : connections) {
            int a = e[0], b = e[1];
            g[a].push_back(b);
            g[b].push_back(a);
        }

        vector<int> disc(n, -1);   // tempo de descoberta (dfs time) de cada nó
        vector<int> low(n, 0);     // menor tempo alcançável a partir do nó (incluindo back-edges)
        vector<vector<int>> bridges;
        bridges.reserve(connections.size());

        int time = 0;

        function<void(int,int)> dfs = [&](int u, int parent) {
            disc[u] = low[u] = time++;
            for (int v : g[u]) {
                if (v == parent) continue;              // ignora aresta para o pai
                if (disc[v] == -1) {                    // árvore de DFS
                    dfs(v, u);
                    low[u] = min(low[u], low[v]);
                    // Se o menor alcançável de v é maior que o discovery de u,
                    // não há back-edge fechando ciclo acima de u -> (u,v) é ponte
                    if (low[v] > disc[u]) {
                        bridges.push_back({u, v});
                    }
                } else {
                    // back-edge
                    low[u] = min(low[u], disc[v]);
                }
            }
        };

        // O grafo pode não ser estritamente conexo em instâncias gerais;
        // o enunciado diz que é alcançável, mas varremos por segurança.
        for (int i = 0; i < n; ++i) {
            if (disc[i] == -1) dfs(i, -1);
        }

        return bridges;
    }
};
