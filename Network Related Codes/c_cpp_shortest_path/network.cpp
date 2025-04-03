#include <bits/stdc++.h>
using namespace std;

vector<int> dijkstra(int V, unordered_map<int, vector<int>> &adj, int src, int target, vector<int> &parent) {
    vector<int> dist(V, INT_MAX); // Store shortest hop count
    queue<int> q;

    dist[src] = 0;
    q.push(src);
    parent[src] = -1; // Mark source's parent as -1

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        for (auto neighbor : adj[node]) {
            if (dist[node] + 1 < dist[neighbor]) {
                dist[neighbor] = dist[node] + 1;
                parent[neighbor] = node; // Store parent to reconstruct path
                q.push(neighbor);
            }
        }
    }
    return dist;
}

// Function to print the shortest path from source to target
void printPath(int target, vector<int> &parent) {
    vector<int> path;
    for (int v = target; v != -1; v = parent[v]) {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());

    cout << "Shortest path: ";
    for (int i = 0; i < path.size(); i++) {
        cout << path[i];
        if (i != path.size() - 1) cout << " -> ";
    }
    cout << endl;
}

int main() {
    int V = 10; // Number of nodes
    unordered_map<int, vector<int>> adj;

    // Creating the bidirectional graph
    vector<pair<int, int>> edges = {
        {0, 1}, // S ↔ V1
        {1, 2}, // V1 ↔ D4
        {2, 3}, {2, 6}, // D4 ↔ V3, D4 ↔ V2
        {3, 4}, // V3 ↔ V4
        {4, 5}, // V4 ↔ D5
        {6, 7}, {6, 8}, {6, 9} // V2 ↔ D1, D2, D3
        // {1, 8} //V1-D2
    };

    for (auto edge : edges) {
        adj[edge.first].push_back(edge.second);
        adj[edge.second].push_back(edge.first); // Since it's bidirectional
    }

    int src = 0;    // Source (S)
    int target = 8; // Destination (D2)

    vector<int> parent(V, -1); // Parent array for path reconstruction
    vector<int> shortest_hops = dijkstra(V, adj, src, target, parent);

    cout << "Shortest hop count from " << src << " to " << target << ": " << shortest_hops[target] << endl;
    
    printPath(target, parent); // Print the shortest path

    return 0;
}
