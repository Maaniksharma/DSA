#include <iostream>
using namespace std;

template <class T>
struct node
{
    T value;
    node<T> *next;
    node(T item) : value(item), next(nullptr) {}
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
        head = tail = NULL;
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
        if (head != NULL)
        {
            return head->value;
        }
        cout << "Queue is Empty" << endl;
        return T();
    }
    void enqueue(T item)
    {
        node<T> *temp = new node<T>(item);
        if (head == NULL)
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
        if (head != NULL)
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
main()
{
    queue<int> q;
    // q.enqueue(10);
    // q.enqueue(8);
    // q.enqueue(6);
    // q.enqueue(9);
    // q.enqueue(10);
    // q.enqueue(7);
    // int a = q.dequeue();
    // a = q.dequeue();
    // a = q.dequeue();
    // a = q.dequeue();
    // a = q.dequeue();
    // a = q.dequeue();
    // a = q.dequeue();
    bool a = q.isEmpty();
    cout << "Returned Value:" << a << endl;
}