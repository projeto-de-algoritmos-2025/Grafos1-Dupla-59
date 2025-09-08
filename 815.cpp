#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int numBusesToDestination(vector<vector<int>>& routes, int source, int target) {
        if (source == target) return 0;

        // Mapeia parada -> rotas que passam por ela
        unordered_map<int, vector<int>> stopToRoutes;
        stopToRoutes.reserve(routes.size() * 2);

        for (int r = 0; r < (int)routes.size(); ++r) {
            for (int stop : routes[r]) {
                stopToRoutes[stop].push_back(r);
            }
        }

        // Se a source nem aparece, impossível
        if (!stopToRoutes.count(source)) return -1;

        // BFS
        queue<int> q;                // paradas
        q.push(source);

        unordered_set<int> visitedStops;
        visitedStops.insert(source);

        vector<char> visitedRoutes(routes.size(), 0);

        int buses = 0; // camadas da BFS = quantidade de ônibus tomados

        while (!q.empty()) {
            int sz = q.size();
            ++buses; // vamos pegar mais um ônibus nesta camada

            while (sz--) {
                int stop = q.front(); q.pop();

                // Para cada rota que passa por esta parada
                for (int r : stopToRoutes[stop]) {
                    if (visitedRoutes[r]) continue;
                    visitedRoutes[r] = 1;

                    // Expandimos todas as paradas dessa rota
                    for (int nextStop : routes[r]) {
                        if (nextStop == target) return buses;
                        if (!visitedStops.count(nextStop)) {
                            visitedStops.insert(nextStop);
                            q.push(nextStop);
                        }
                    }
                }
            }
        }

        return -1;
    }
};
