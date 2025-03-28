#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int p1, p2, weight;

    bool operator<(const Edge& e) const {
        return weight < e.weight;
    }
};

int find(int parent[], int i) {
    if (parent[i] == -1)
        return i;
    return find(parent, parent[i]);
}

void unionSets(int parent[], int x, int y) {
    int xroot = find(parent, x);
    int yroot = find(parent, y);

    if (xroot != yroot) {
        parent[xroot] = yroot;
    }
}

int kruskal(int n, vector<Edge>& edges, vector<Edge>& mstEdges) {
    sort(edges.begin(), edges.end());
    int parent[n];
    fill(parent, parent + n, -1);

    int mstCost = 0;
    int edgesUsed = 0;

    for (const Edge& edge : edges) {
        int u = edge.p1;
        int v = edge.p2;

        if (find(parent, u) != find(parent, v)) {
            mstCost += edge.weight;
            mstEdges.push_back(edge);
            edgesUsed++;
            unionSets(parent, u, v);
        }

        if (edgesUsed == n - 1)
            break;
    }

    return mstCost;
}

int prims(vector<Edge>& edges, int n, int start, vector<Edge>& mstEdges) {
    vector<bool> inMST(n, false);
    set<pair<int, int>> pq;  
    pq.insert({0, start});
    int mstCost = 0;
    int edgesUsed = 0;

    while (!pq.empty() && edgesUsed < n - 1) {
        int u = pq.begin()->second;
        int weight = pq.begin()->first;
        pq.erase(pq.begin());

        if (inMST[u]) continue;
        inMST[u] = true;
        mstCost += weight;

      
        for (const auto& edge : edges) {
            int v = (edge.p1 == u) ? edge.p2 : (edge.p2 == u) ? edge.p1 : -1;
            if (v != -1 && !inMST[v]) {
                pq.insert({edge.weight, v});
                mstEdges.push_back(edge);  
            }
        }
        edgesUsed++;
    }

    return mstCost;
}

int main() {
    int n, m;
    cout << "Enter number of offices (vertices): ";
    cin >> n;
    cout << "Enter number of possible phone lines (edges): ";
    cin >> m;

    vector<Edge> edges(m);

    cout << "Enter the edges (u, v, cost) where u and v are offices (0-indexed):\n";
    for (int i = 0; i < m; i++) {
        cin >> edges[i].p1 >> edges[i].p2 >> edges[i].weight;
    }

    int choice;
    cout << "Choose the algorithm to find MST:\n";
    cout << "1. Kruskal's Algorithm\n";
    cout << "2. Prim's Algorithm\n";
    cout << "Enter your choice (1 or 2): ";
    cin >> choice;

    if (choice == 1) {
        vector<Edge> mstEdges;
        int result = kruskal(n, edges, mstEdges);
        cout << "The minimum cost to connect all offices (Kruskal's) is: " << result << endl;
        cout << "The edges in the MST are:\n";
        for (const Edge& e : mstEdges) {
            cout << "(" << e.p1 << ", " << e.p2 << ", " << e.weight << ")\n";
        }
    } else if (choice == 2) {
        int start;
        cout << "Enter the starting office (vertex) for Prim's algorithm (0-indexed): ";
        cin >> start;

        vector<Edge> mstEdges;
        int mstCost = prims(edges, n, start, mstEdges);
        cout << "The minimum cost to connect all offices (Prim's) is: " << mstCost << endl;
        cout << "The edges in the MST are:\n";
        for (const Edge& e : mstEdges) {
            cout << "(" << e.p1 << ", " << e.p2 << ", " << e.weight << ")\n";
        }
    } else {
        cout << "Invalid choice!\n";
    }

    return 0;
}

