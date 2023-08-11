#include <iostream>
using namespace std;

template <class T>
class heap
{
    T *arr;
    int size;
    int capacity;

public:
    heap(int capacity)
    {
        arr = new T[capacity];
        size = 0;
    }
    ~heap()
    {
        delete[] arr;
    }
    void insert(T item)
    {
        if (size == capacity)
        {
            cout << "Heap is full" << endl;
            return;
        }
        arr[size] = item;
        if (size == 0)
        {
            size++;
            return;
        }
        heapifyUp(size, item);
        size++;
    }
    void heapifyUp(int index, T item)
    {
        if (index <= 0)
        {
            return;
        }
        int parent = (index - 1) / 2;
        if (arr[parent] < item)
        {
            T temp = arr[parent];
            arr[parent] = item;
            arr[index] = temp;
            heapifyUp(parent, item);
        }
        return;
    }
    T pop()
    {
        if (size == 0)
        {
            cout << "Heap is empty" << endl;
            return 0;
        }
        T temp = arr[0];
        arr[0] = arr[size - 1];
        size--;
        heapifyDown(0);
        return temp;
    }
    void heapifyDown(int index)
    {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        if (index >= size || left >= size || right >= size)
        {
            return;
        }
        if (arr[index] < arr[left] && arr[left] > arr[right])
        {
            swap(arr[index], arr[left]);
            heapifyDown(left);
            return;
        }
        if (arr[index] < arr[right] && arr[right] > arr[left])
        {
            swap(arr[index], arr[right]);
            heapifyDown(right);
        }
        return;
    }
    T peek()
    {
        if (size == 0)
        {
            cout << "Heap is empty" << endl;
            return T();
        }
        return arr[0];
    }
};
main()
{
    heap<int> h(10);
    h.insert(10);
    h.insert(8);
    h.insert(7);
    h.insert(91);
    h.pop();
    h.pop();
    h.pop();
    cout << h.peek();
}