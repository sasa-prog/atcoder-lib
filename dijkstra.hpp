#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Edge {
    int to;

    ll cost;
};

using Graph = vector<vector<Edge>>;
using Pair = pair<ll, int>;

void dijkstra(const Graph& graph, vector<ll>& distances, int start) {
    priority_queue<Pair, vector<Pair>, greater<Pair>> q;
    q.emplace((distances[start] = 0), start);

    while (!q.empty()) {
        const ll dist = q.top().first;
        const int from = q.top().second;
        q.pop();

        if (distances[from] < dist) {
            continue;
        }

        for (const auto& edge: graph[from]) {
            const ll d = (distances[from] + edge.cost);
            if (d < distances[edge.to]) {
                q.emplace((distances[edge.to] = d), edge.to);
            }
        }
    }
}
