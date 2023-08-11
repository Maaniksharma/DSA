#include <iostream>
using namespace std;
template <class T>
struct node
{
    T value;
    node<T> *next;
    node<T> *previous;
    node(T item) : value(item), next(nullptr), previous(nullptr) {}
};
template <class T>
class dlist
{
    int length;
    node<T> *head;
    node<T> *tail;

public:
    dlist()
    {
        head = tail = nullptr;
        length = 0;
    }

    ~dlist()
    {
        while (head != nullptr)
        {
            node<T> *temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
    }
    node<T> *createNode(T item)
    {
        node<T> *temp = new node<T>(item);
        length++;
        return temp;
    }
    node<T> *getAt(int indx) const
    {
        node<T> *curr = head;
        if (length == 0)
            throw runtime_error("List Is Empty");

        if (indx >= length)
            throw runtime_error("Index Out Of Range");
        else if (indx == length - 1)
            return tail;
        for (int i = 0; i < indx; i++)
        {
            curr = curr->next;
        }
        return curr;
    }
    T get(int indx) const
    {
        node<T> *curr = getAt(indx);
        return curr->value;
    }
    void traverse() const
    {
        node<T> *curr = head;
        for (int i = 0; i < length; i++)
        {
            cout << curr->value << " ";
            curr = curr->next;
        }
        cout << endl;
    }
    void append(T item)
    {
        node<T> *temp = createNode(item);
        if (length == 1)
        {
            head = tail = temp;
            return;
        }
        else
        {
            temp->previous = tail;
            tail->next = temp;
            tail = temp;
        }
    }
    void prepend(T item)
    {
        node<T> *temp = createNode(item);
        if (length == 1)
        {
            head = tail = temp;
            return;
        }
        head->previous = temp;
        temp->next = head;
        head = temp;
    }
    void insert(T item, int indx)
    {
        if (indx == 0)
        {
            prepend(item);
            return;
        }
        node<T> *curr;
        if (indx == length - 1)
        {
            curr = tail;
        }
        else
        {
            curr = getAt(indx);
        }
        node<T> *temp = createNode(item);
        temp->next = curr;
        temp->previous = curr->previous;
        (curr->previous)->next = temp;
        curr->previous = temp;
        return;
    }
    T removeAt(int index)
    {
        node<T> *temp = getAt(index);
        T item = temp->value;
        removePtr(temp);
        delete temp;
        return item;
    }
    void remove(T item)
    {
        for (node<T> *curr = head; curr != nullptr; curr = curr->next)
        {
            if (curr->value == item)
            {
                removePtr(curr);
                delete curr;
                return;
            }
        }
        throw runtime_error("Value Not Found");
    }
    void removePtr(node<T> *temp)
    {
        length--;
        if (temp == head)
        {
            head = head->next;
            return;
        }
        else if (temp == tail)
        {
            tail = tail->previous;
            return;
        }
        (temp->previous)->next = temp->next;
        (temp->next)->previous = temp->previous;
        return;
    }
};
int main()
{
    dlist<double> list;
    list.append(6.5);
    list.append(5.5);
    list.insert(6, 0);
    list.removeAt(1);
    list.traverse();
    float a = list.get(1);
    cout << a;
    return 0;
}