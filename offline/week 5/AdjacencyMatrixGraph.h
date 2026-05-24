#ifndef ADJACENCY_MATRIX_GRAPH_H
#define ADJACENCY_MATRIX_GRAPH_H
#include "GraphADT.h"
#include "iostream"

#include "queue.h"
#include "arrayList.h"
#include "stack.h"
using namespace std;

class AdjacencyMatrixGraph : public GraphADT
{
private:
    // TODO: Consider necessary private members as per your discretion
    int size;
    int **adjMat;
    int capacity;
    int adjArr[10000] = {0};
    int len;

    void clear()
    {

        for (int i = 0; i < size; ++i)
            delete[] adjMat[i];
        delete[] adjMat;
    }
    void resizeMatrix()
    {
        int **newAdj = new int *[capacity];
        // TODO: you need to resize your matrix when you will less data or more data
        for (int i = 0; i < capacity; i++)
        {
            newAdj[i] = new int[capacity];
        }
        for (int i = 0; i < capacity; i++)
        {

            for (int j = 0; j < capacity; j++)
            {
                
                {
                    newAdj[i][j] = 0;
                }
            }
        }
         for (int i = 0; i < size; i++)
        {

            for (int j = 0; j < size; j++)
            {
                
                {
                    newAdj[i][j] = adjMat[i][j];
                }
            }
        }
        clear();
        adjMat = newAdj;
    }
    int checkNode(int v) const
    {
        int index = -1;
        for (int i = 0; i < len; i++)
        {
            if (adjArr[i] == v)
            {
                return i;
            }
        }
        return index;
    }

public:
    AdjacencyMatrixGraph()
    {
        size = 0;
        len = 0;
        capacity = 2;
        adjMat = new int *[capacity];
        for (int i = 0; i < capacity; i++)
        {
            adjMat[i] = new int[capacity];
            for (int j = 0; j < capacity; j++)
            {
                adjMat[i][j] = 0;
            }
        }
    }
    void AddNode(int v) override
    {
        if (size > capacity / 2)
        {
            capacity *= 2;
            resizeMatrix();
        }
        if (checkNode(v) == -1)
        {
            adjArr[len++] = v;
            size++;
        }
        // TODO: Add a new node v and resize the matrix if your current matrix is almost going to be full.
    }

    void AddEdge(int u, int v) override
    {
        // TODO: Add a new edge between the nodes u and v
        if (checkNode(u) == -1)
           { AddNode(u);}
        if (checkNode(v) == -1)
        {    AddNode(v);}
        int ind1 = checkNode(u);
        int ind2 = checkNode(v);
        adjMat[ind1][ind2] = 1;
        adjMat[ind2][ind1] = 1;
    }

    bool CheckEdge(int u, int v) const override
    {
        // TODO: Check whether there is an edge between two nodes u and v
        int ind1 = checkNode(u);
        int ind2 = checkNode(v);
        if (ind1 == -1 || ind2 == -1)
            return false;
        return adjMat[ind1][ind2] == 1;
    }

    void RemoveNode(int v) override
    {
        // TODO: Remove a node.
        int indexOfNode = checkNode(v);
        if (size * 2 < capacity)
        {
            capacity /= 2;
            resizeMatrix();
        }
        for (int i = indexOfNode; i < len - 1; i++)
        {
            adjArr[i] = adjArr[i + 1];
        }
        len--;

        for (int i = indexOfNode; i < size - 1; i++)
        {
            for (int j = 0; j < size; j++)
            {
                adjMat[i][j] = adjMat[i + 1][j];
            }
        }

        for (int i = 0; i < size - 1; i++)
        {
            for (int j = indexOfNode; j < size - 1; j++)
            {
                adjMat[i][j] = adjMat[i][j + 1];
            }
        }

        size--;
    }

    void RemoveEdge(int u, int v) override
    {
        // TODO: remove an edge
        int ind1 = checkNode(u);
        int ind2 = checkNode(v);
        adjMat[ind1][ind2] = 0;
        adjMat[ind2][ind1] = 0;
    }

    bool CheckPath(int u, int v) const override
    {
        // TODO: Return true if there is a path between nodes u and v. Otherwise return false
        int ind1 = checkNode(u);
        int ind2 = checkNode(v);
        //cout<<ind1<<" "<<ind2<<endl;
        bool *visited = new bool[size];
        for (int i = 0; i < size; i++)
        {
            visited[i] = false;
        }
        ArrayQueue q;
        q.enqueue(ind1);
        visited[ind1] = true;
        while (!q.empty())
        {
            int curr = q.dequeue();
            if (curr == ind2)
            {
                delete[] visited;
                return true;
            }
            for (int i = 0; i < size; i++)
            {
                if (adjMat[curr][i] == 1 && !visited[i])
                {
                    q.enqueue(i);
                    visited[i] = true;
                }
            }
        }
        delete[] visited;
        return false;
    }

    void FindShortestPath(int u, int v) const override
    {
        // TODO: Return true if there is a path between nodes u and v. Otherwise return false
        ArrayStack s;
        int ind1 = checkNode(u);
        int ind2 = checkNode(v);
        bool *visited = new bool[size];
        int *parent = new int[size];
        for (int i = 0; i < size; i++)
        {
            visited[i] = false;
            parent[i] = -1;
        }
        ArrayQueue q;
        q.enqueue(ind1);
        visited[ind1] = true;
        bool found = false;
        while (!q.empty() && !found)
        {
            int curr = q.dequeue();
            for (int i = 0; i < size; i++)
            {
                if (adjMat[curr][i] && !visited[i])
                {
                    visited[i] = true;
                    parent[i] = curr;
                    q.enqueue(i);
                    if (i == ind2)
                    {
                        found = true;
                        break;
                    }
                }
            }
        }
        if (found)
        {
            int temp = ind2;
            while (temp != -1)
            {
                s.push(adjArr[temp]);
                temp = parent[temp];
            }
        }

        delete[] visited;
        delete[] parent;
        cout << "Shortest path: ";
        // TODO: Find the shortest path between the nodes u and v and print it.
        s.print();
        cout << endl;
    }

    int FindShortestPathLength(int u, int v) const override
    {
        ArrayStack s;
        int ind1 = checkNode(u);
        int ind2 = checkNode(v);
        bool *visited = new bool[size];
        int *parent = new int[size];
        for (int i = 0; i < size; i++)
        {
            visited[i] = false;
            parent[i] = -1;
        }
        ArrayQueue q;
        int count = 0;
        q.enqueue(ind1);
        visited[ind1] = true;
        bool found = false;
        while (!q.empty() && !found)
        {
            int curr = q.dequeue();
            for (int i = 0; i < size; i++)
            {
                if (adjMat[curr][i] && !visited[i])
                {
                    visited[i] = true;
                    parent[i] = curr;
                    q.enqueue(i);
                    if (i == ind2)
                    {
                        found = true;
                        break;
                    }
                }
            }
            if (found)
            {
                int temp = ind2;
                while (temp != -1)
                {
                    count++;
                    temp = parent[temp];
                }
            }
        }

        delete[] visited;
        delete[] parent;
        return count - 1;
        // TODO: Return the shortest path length between nodes u and v if any such path exists. Otherwise return -1.
    }
    arrayList GetNeighbors(int u) const override
    {
        // TODO return a list of neighbors of node u
        arrayList a;
        int ind = checkNode(u);
        for (int i = 0; i < size; i++)
        {
            if (adjMat[ind][i] == 1)
            {
                a.insertItem(adjArr[i]);
            }
        }
        return a;
    }
    ~AdjacencyMatrixGraph()
    {
        clear();
    }
};

#endif // ADJACENCY_MATRIX_GRAPH_H
