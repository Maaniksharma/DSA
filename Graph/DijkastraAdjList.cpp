#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
using namespace std;

struct edge
{
    int vertex;
    int weight;
    edge *next;
};
struct vertex
{
    int value;
    edge *list;
};
class Graph
{
    unordered_map<int, vertex> V;
    int size;

public:
    Graph()
    {
        size = 0;
    }
    ~Graph()
    {
        for (auto &v : V)
        {
            edge *temp = v.second.list;
            while (temp != nullptr)
            {
                edge *next = temp->next;
                delete temp;
                temp = next;
            }
        }
    }
    void addVertex(int value)
    {
        if (V.find(value) == V.end())
        {
            vertex *temp = new vertex();
            temp->value = value;
            temp->list = nullptr;
            V[value] = *temp;
            size++;
        }
        else
        {
            cout << "Vertex Alredy Present" << endl;
        }
    }
    void addEdge(int u, int v, int weight)
    {
        if (V.find(u) == V.end() || V.find(v) == V.end())
        {
            cout << "Vertex does not exist" << endl;
            return;
        }
        edge *e = new edge();
        e->vertex = v;
        e->next = nullptr;
        e->weight = weight;
        edge *temp = V[u].list;
        if (temp == nullptr)
        {
            V[u].list = e;
        }
        else
        {
            while (temp->next != nullptr)
            {
                temp = temp->next;
            }
            temp->next = e;
        }
    }
    std::pair<unordered_map<int, int> *, unordered_map<int, int> *> dijkastra(int source)
    {
        unordered_map<int, int> *distance = new unordered_map<int, int>();
        unordered_map<int, int> *previous = new unordered_map<int, int>();
        unordered_set<int> visited;
        for (auto &v : V)
        {
            (*previous)[v.first] = -1;
            (*distance)[v.first] = 1000;
            visited.insert(v.first);
        }
        (*distance)[source] = 0;
        while (!visited.empty())
        {
            int u = getLowUnvisit((*distance), visited);
            visited.erase(u);
            edge *temp = V[u].list;
            while (temp != nullptr)
            {
                if ((*distance)[temp->vertex] > (*distance)[u] + temp->weight)
                {
                    (*distance)[temp->vertex] = (*distance)[u] + temp->weight;
                    (*previous)[temp->vertex] = u;
                }
                temp = temp->next;
            }
        }
        return std::make_pair(distance, previous);
    }
    int *getPath(unordered_map<int, int> &previous, int source, int destination)
    {
        int *path = new int[size + 2];
        int i = 0;
        int u = destination;
        while (u != source)
        {
            path[i++] = u;
            u = previous[u];
        }
        path[i] = source;
        std::reverse(path, path + i + 1);
        i++;
        for (; i < size + 2; i++)
        {
            path[i] = -1;
        }
        return path;
    }
    int getLowUnvisit(unordered_map<int, int> &distance, unordered_set<int> &visited)
    {
        int min = 1000;
        int minVertex = -1;
        for (const auto &v : visited)
        {
            if (distance[v] < min)
            {
                min = distance[v];
                minVertex = v;
            }
        }
        return minVertex;
    }
    void printGraph()
    {
        for (const auto &v : V)
        {
            cout << v.first << "->";
            edge *temp = v.second.list;
            while (temp != nullptr)
            {
                cout << temp->vertex << "(" << temp->weight << ")"
                     << "->";
                temp = temp->next;
            }
            cout << "NULL" << endl;
        }
    }
};
main()
{
    Graph g;
    g.addVertex(1);
    g.addVertex(2);
    g.addVertex(3);
    g.addVertex(4);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 5);
    g.addEdge(2, 3, 1);
    g.addEdge(2, 4, 2);
    g.addEdge(3, 4, 1);
    g.printGraph();
    int source = 1;
    int destination = 4;
    std::pair<unordered_map<int, int> *, unordered_map<int, int> *> result = g.dijkastra(1);
    unordered_map<int, int> *distance = result.first;
    unordered_map<int, int> *previous = result.second;
    cout << "Algorithm executed" << endl;
    int *path = g.getPath(*previous, source, destination);
    if (path == nullptr)
    {
        cout << "No path found from source to destination" << endl;
    }
    else
    {
        cout << "Path from " << source << " to " << destination << ": ";
        for (int i = 0; path[i] != -1; i++)
        {
            cout << path[i] << " ";
        }
        cout << endl;
    }
    cout << "Distances From " << source << endl;
    for (const auto &v : *distance)
    {
        cout << v.first << "->" << v.second << endl;
    }

    delete distance;
    delete previous;
    delete[] path;
}