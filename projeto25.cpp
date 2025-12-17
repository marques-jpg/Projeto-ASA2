#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int N; 
    if (!(cin >> N)) return 0;
    int M; cin >> M;
    int m1, m2; cin >> m1 >> m2;
    int K; cin >> K;
    vector<vector<int>> adj(N + 1);
    vector<int> indeg(N + 1, 0);
    for (int i = 0; i < K; ++i) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        ++indeg[b];
    }

    queue<int> q;
    for (int i = 1; i <= N; ++i) if (indeg[i] == 0) q.push(i);
    vector<int> topo;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        topo.push_back(u);
        for (int v : adj[u]) {
            if (--indeg[v] == 0) q.push(v);
        }
    }
    if ((int)topo.size() != N) {
        return 0;
    }

    vector<vector<pair<int,int>>> truckPairs(M + 1);

    vector<unsigned long long> ways(N + 1);
    vector<int> waysMod(N + 1);
    vector<char> hasPath(N + 1);

    for (int src = 1; src <= N; ++src) {
        fill(ways.begin(), ways.end(), 0);
        fill(waysMod.begin(), waysMod.end(), 0);
        fill(hasPath.begin(), hasPath.end(), 0);
        ways[src] = 1;
        waysMod[src] = 1;
        hasPath[src] = 1;

        for (int u : topo) {
            if (!hasPath[u]) continue;
            for (int v : adj[u]) {
                ways[v] += ways[u];
                waysMod[v] = (waysMod[v] + waysMod[u]) % M;
                hasPath[v] = 1;
            }
        }

        for (int dst = 1; dst <= N; ++dst) {
            if (dst == src) continue;
            if (!hasPath[dst]) continue;
            int truck = 1 + waysMod[dst] % M;
            truckPairs[truck].push_back({src, dst});
        }
    }

    for (int t = 1; t <= M; ++t) {
        auto &v = truckPairs[t];
        sort(v.begin(), v.end());
    }

    for (int t = m1; t <= m2; ++t) {
        cout << 'C' << t;
        for (const auto &p : truckPairs[t]) {
            cout << ' ' << p.first << ',' << p.second;
        }
        cout << '\n';
    }

    return 0;
}
