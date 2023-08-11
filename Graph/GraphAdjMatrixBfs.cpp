#include <iostream>
using namespace std;

template <class T>
struct node
{
    T value;
    node<T> *next;
    node(T v) : value(v), next(nullptr) {}
};
template <class T>
class queue
{
    node<T> *head;
    node<T> *tail;
    int length;

public:
    queue()
    {
        head = tail = nullptr;
        length = 0;
    }
    bool isEmpty()
    {
        if (head == nullptr)
            return true;
        else
            false;
    }
    T peek()
    {
        if (head != nullptr)
        {
            return head->value;
        }
        cout << "Queue is Empty" << endl;
        return T();
    }
    void enqueue(T item)
    {
        node<T> *temp = new node<T>(item);
        if (head == nullptr)
        {
            head = temp;
            tail = temp;
        }
        else
        {
            tail->next = temp;
            tail = temp;
        }
    }
    T dequeue()
    {
        if (head != nullptr)
        {
            node<T> *temp = head;
            head = head->next;
            T Value = temp->value;
            delete temp;
            return Value;
        }
        else
            throw runtime_error("Underflow: Queue is Empty");
    }
};
class Graph
{
    int **adjMatrix;
    int length;

public:
    Graph(int n)
    {
        length = n;
        adjMatrix = new int *[n];
        for (int i = 0; i < n; i++)
        {
            adjMatrix[i] = new int[n];
            for (int j = 0; j < n; j++)
            {
                adjMatrix[i][j] = 0;
            }
        }
    }
    ~Graph()
    {
        for (int i = 0; i < length; i++)
        {
            delete[] adjMatrix[i];
        }
        delete[] adjMatrix;
    }
    void addEdge(int u, int v)
    {
        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1;
    }
    void printAdjMatrix()
    {
        for (int i = 0; i < length; i++)
        {
            for (int j = 0; j < length; j++)
            {
                cout << adjMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }
    int *bfSearch(int source, int item)
    {
        queue<int> q;
        q.enqueue(source);
        int seen[length] = {0};
        int prev[length] = {-1};
        seen[source] = 1;
        while (!q.isEmpty())
        {
            int u = q.dequeue();
            for (int v = 0; v < length; v++)
            {
                if (adjMatrix[u][v] == 1 && seen[v] == 0)
                {
                    q.enqueue(v);
                    seen[v] = 1;
                    prev[v] = u;
                    if (v == item)
                        break;
                }
            }
        }
        int *path = new int[length];
        int k = 0;
        while (prev[item] != -1)
        {
            item = prev[item];
            path[k++] = item;
        }
        for (int i = 0; i < k / 2; i++)
        {
            int temp = path[i];
            path[i] = path[k - i - 1];
            path[k - i - 1] = temp;
        }
        path[k] = -1;
        return path;
    }
};
main()
{
    Graph g(6);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 3);
    g.addEdge(2, 4);
    g.addEdge(3, 5);
    g.addEdge(4, 5);
    g.printAdjMatrix();
    int *path = g.bfSearch(0, 5);
    for (int i = 0; path[i] != -1; i++)
    {
        cout << path[i] << " ";
    }
    delete[] path;
    cout << endl;
}
