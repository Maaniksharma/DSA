#include <iostream>
using namespace std;

template <class T>
struct node
{
    T value;
    node<T> *previous;
    node(T item) : value(item), previous(nullptr) {}
};

template <class T>
class stack
{
    int length;
    node<T> *head;

public:
    stack()
    {
        length = 0;
        head = NULL;
    }

    T peek()
    {
        if (head != NULL)
        {
            return head->value;
        }
        cout << "Stack is Empty" << endl;
        return T();
    }

    void push(T item)
    {
        node<T> *temp = new node<T>(item);
        temp->previous = head;
        head = temp;
        length++;
    }

    T pop()
    {
        if (head != NULL)
        {
            node<T> *temp = head;
            head = head->previous;
            temp->previous = NULL;
            T value = temp->value;
            delete temp;
            length--;
            return value;
        }
        throw runtime_error("Underflow: Stack is Empty");
    }
};

int main()
{
    stack<int> A;
    A.push(101);
    A.push(100);
    A.push(109);
    A.push(109);

    int a = A.pop();
    cout << "Returned Item: " << a << endl;

    a = A.pop();
    cout << "Returned Item: " << a << endl;

    a = A.pop();
    cout << "Returned Item: " << a << endl;

    a = A.pop();
    cout << "Returned Item: " << a << endl;
    stack<string> s;
    s.push("manik");
    s.push("manik");
    s.push("manik");
    s.push("manik");
    s.push("manik");
    s.push("manik");
    string so = s.pop();
    cout << "char:" << so;
}
