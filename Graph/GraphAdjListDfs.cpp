#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

struct edge
{
    int vertex;
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
    void addEdge(int u, int v)
    {
        if (V.find(u) == V.end() || V.find(v) == V.end())
        {
            cout << "Vertex does not exist" << endl;
            return;
        }
        edge *e = new edge();
        e->vertex = v;
        e->next = nullptr;
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
    vector<int> dfSearch(int source, int item)
    {
        unordered_set<int> seen;
        vector<int> path;
        reach(source, seen, path, item);
        return path;
    }
    bool reach(int source, unordered_set<int> &seen, vector<int> &path, int item)
    {
        path.push_back(source);
        if (source == item)
            return true;
        seen.insert(source);
        edge *temp = V[source].list;
        while (temp != nullptr)
        {
            if (seen.find(temp->vertex) == seen.end())
            {
                if (reach(temp->vertex, seen, path, item))
                    return true;
            }
            temp = temp->next;
        }
        path.pop_back();
        seen.erase(source);
        return false;
    }
};
int main()
{
    Graph g;
    g.addVertex(1);
    g.addVertex(2);
    g.addVertex(3);
    g.addVertex(4);
    g.addVertex(5);
    g.addVertex(6);
    g.addVertex(7);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    g.addEdge(3, 4);
    g.addEdge(3, 7);
    g.addEdge(4, 5);
    g.addEdge(4, 6);
    vector<int> path = g.dfSearch(1, 7);
    for (int i = 0; i < path.size(); i++)
    {
        cout << path[i] << " ";
    }
    return 0;
}