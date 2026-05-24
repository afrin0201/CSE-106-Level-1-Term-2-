#ifndef ADJACENCY_LIST_GRAPH_H
#define ADJACENCY_LIST_GRAPH_H
#include "arrayList.h"
#include <iostream>
#include "GraphADT.h"
using namespace std;
class AdjacencyListGraph : public GraphADT
{
private:
    // TODO: Take necessary private members
    arrayList adjList[1000];
    bool isThere[1000];
    int ver;

public:
    AdjacencyListGraph()
    {
        ver = 0;
        for (int i = 0; i < 1000; i++)
            isThere[i] = false;
    }
    void AddNode(int v) override
    {
        if (isThere[v] == false)
        {
            ver++;
            isThere[v] = true;
        }
        // TODO: Add a new node v and resize the matrix if your current matrix is almost going to be full.
    }

    void AddEdge(int u, int v) override
    {
        // TODO: Add a new edge between the nodes u and v
        if (!CheckEdge(u,v))
       { adjList[u].insertItem(v);
        adjList[v].insertItem(u);}
    }

    bool CheckEdge(int u, int v) const override
    {
        // TODO: Check whether there is an edge between two nodes u and v
        for (int i = 0; i < adjList[u].getSize(); i++)
        {
            if (adjList[u].getItem(i) == v)
            {
                return true;
            }
        }
        return false;
    }

    void RemoveNode(int v) override
    {
        // TODO: Remove a node.
        while (adjList[v].getSize() > 0)
        {
            int neighbor = adjList[v].getItem(0); 
            RemoveEdge(v, neighbor);
        }

        isThere[v] = false;
    }

    void RemoveEdge(int u, int v) override
    {
        // TODO: remove an edge
        adjList[u].removeEdge(v);
        adjList[v].removeEdge(u);
    }

    bool CheckPath(int u, int v) const override
    {
        // TODO: Return true if there is a path between nodes u and v. Otherwise return false
        bool visited[1000] = {false};
        int queue[1000], front = 0, rear = 0;
        queue[rear++] = u;
        visited[u] = true;

        while (front < rear)
        {
            int current = queue[front++];

            if (current == v)
                return true;

            for (int i = 0; i < adjList[current].getSize(); i++)
            {
                int neighbor = adjList[current].getItem(i);
                if (!visited[neighbor])
                {
                    visited[neighbor] = true;
                    queue[rear++] = neighbor;
                }
            }
        }

        return false;
    }

    void FindShortestPath(int u, int v) const override
    {
        // TODO: Find the shortest path between the nodes u and v and print it.
        bool visited[1000] = {false};
        int parent[1000];
        for (int i = 0; i < 1000; i++)
            parent[i] = -1;

        int queue[1000], front = 0, rear = 0;
        queue[rear++] = u;
        visited[u] = true;

        while (front < rear)
        {
            int current = queue[front++];

            if (current == v)
                break;

            for (int i = 0; i < adjList[current].getSize(); i++)
            {
                int neighbor = adjList[current].getItem(i);
                if (!visited[neighbor])
                {
                    visited[neighbor] = true;
                    parent[neighbor] = current;
                    queue[rear++] = neighbor;
                }
            }
        }

        if (!visited[v])
        {
            cout << "No path found.\n";
            return;
        }
        int path[1000], idx = 0;
        for (int at = v; at != -1; at = parent[at])
        {
            path[idx++] = at;
        }
        cout<<"Shortest path: ";
        for (int i = idx - 1; i >= 0; i--)
        {
            cout << path[i];
            if (i != 0)
                cout << " ";
            }
            cout << endl;
    }

    int FindShortestPathLength(int u, int v) const override
    {
        bool visited[1000] = {false};
        int dist[1000] = {0};
        int queue[1000], front = 0, rear = 0;
        queue[rear++] = u;
        visited[u] = true;
        dist[u] = 0;

        while (front < rear)
        {
            int current = queue[front++];

            if (current == v)
                return dist[v];

            for (int i = 0; i < adjList[current].getSize(); i++)
            {
                int neighbor = adjList[current].getItem(i);
                if (!visited[neighbor])
                {
                    visited[neighbor] = true;
                    dist[neighbor] = dist[current] + 1;
                    queue[rear++] = neighbor;
                }
            }
        }
        // TODO: Return the shortest path length between nodes u and v if any such path exists. Otherwise return -1.
    }

    arrayList GetNeighbors(int u) const override
    {
        // TODO: Return the list of neighbors.
        return adjList[u];
    }
};

#endif // ADJACENCY_LIST_GRAPH_H
