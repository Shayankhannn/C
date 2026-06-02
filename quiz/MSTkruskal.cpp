/*
===========================================================
File: mst_kruskal.cpp

Homework 3: Minimum Spanning Tree (MST)

Objective:
This program computes the Minimum Spanning Tree (MST)
of a connected weighted undirected graph using Kruskal’s
algorithm.

Approach:
- Graph is represented using an edge list
- Edges are sorted by weight
- Union-Find structure is used to avoid cycles
- MST is built by selecting smallest valid edges
===========================================================
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/* ---------------- Edge Structure ---------------- */
struct Edge {
    int u, v;
    int weight;
};

/* ---------------- Graph Class ---------------- */
class Graph {

private:
    int V;
    vector<Edge> edges;

public:

    Graph(int vertices) {
        V = vertices;
    }

    /* Add edge (undirected graph) */
    void addEdge(int u, int v, int w) {
        edges.push_back({u, v, w});
    }

    /* Return all edges */
    vector<Edge> getEdges() {
        return edges;
    }

    int getVertices() {
        return V;
    }
};

/* ---------------- Union-Find ---------------- */
class DisjointSet {

private:
    vector<int> parent, rank;

public:

    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);

        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    void unite(int a, int b) {

        int rootA = find(a);
        int rootB = find(b);

        if (rootA != rootB) {

            if (rank[rootA] < rank[rootB])
                parent[rootA] = rootB;

            else if (rank[rootA] > rank[rootB])
                parent[rootB] = rootA;

            else {
                parent[rootB] = rootA;
                rank[rootA]++;
            }
        }
    }
};

/* ---------------- Kruskal MST ---------------- */
class MST {

public:

    static void kruskal(Graph &g) {

        vector<Edge> edges = g.getEdges();
        int V = g.getVertices();

        /* Sort edges by weight */
        sort(edges.begin(), edges.end(),
             [](Edge a, Edge b) {
                 return a.weight < b.weight;
             });

        DisjointSet ds(V);

        vector<Edge> mst;
        int totalCost = 0;

        for (int i = 0; i < edges.size(); i++) {

            int u = edges[i].u;
            int v = edges[i].v;
            int w = edges[i].weight;

            /* If including edge does NOT form cycle */
            if (ds.find(u) != ds.find(v)) {

                ds.unite(u, v);
                mst.push_back(edges[i]);
                totalCost += w;
            }
        }

        /* Output MST */
        cout << "\nMinimum Spanning Tree:\n";

        for (int i = 0; i < mst.size(); i++) {
            cout << mst[i].u << " - "
                 << mst[i].v << " : "
                 << mst[i].weight << "\n";
        }

        cout << "Total MST Cost = " << totalCost << "\n";
    }
};

/* ---------------- MAIN ---------------- */
int main() {

    int V, E;

    cout << "Enter number of vertices: ";
    cin >> V;

    Graph g(V);

    cout << "Enter number of edges: ";
    cin >> E;

    cout << "Enter edges (u v weight):\n";

    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g.addEdge(u, v, w);
    }

    MST::kruskal(g);

    return 0;
}