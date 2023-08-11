#include <iostream>
using namespace std;

template <class T>
int partition(int low, int high, T *arr)
{
    T pivot = arr[high];
    int indx = low;
    for (int i = low; i < high; i++)
    {
        if (arr[i] < pivot)
        {
            T temp = arr[indx];
            arr[indx] = arr[i];
            arr[i] = temp;
            indx++;
        }
    }
    arr[high] = arr[indx];
    arr[indx] = pivot;
    return indx;
}
template <class T>
void qs(int low, int high, T *arr)
{
    if (low >= high)
    {
        return;
    }
    int indx = partition(low, high, arr);
    qs(low, indx - 1, arr);
    qs(indx + 1, high, arr);
}
int main()
{
    int a[20] = {7, 6, 5, 5, 4, 3, 2};
    cout << "Before Sorting:";
    for (int i = 0; i < 6; i++)
        cout << a[i] << ",";
    qs(0, 5, a);
    cout << "\nAfter Sorting:";
    for (int i = 0; i < 6; i++)
        cout << a[i] << ",";
    cout << endl;
    return 0;
}
