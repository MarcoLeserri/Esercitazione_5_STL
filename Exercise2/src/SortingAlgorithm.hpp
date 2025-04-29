#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

namespace SortLibrary {
template<typename T>
concept Sortable = requires(T& t) {
    {t < t} -> std::convertible_to<bool>;
};

// BubbleSort
template<Sortable T>
void BubbleSort(vector<T>& v)
{
    const unsigned int n = v.size();

    for (unsigned int i = 0; i < n - 1; i++) {
        for (unsigned int j = i +1; j < n ; j++) {
            if (v[j] < v[i]) {
                T tmp = v[j];
                v[j] = v[i];
                v[i] = tmp;
            }
        }
    }
}
// mantenere la proprietà dell'heap
template<Sortable T>
void heapify(vector<T>& v, int n, int i)
{
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && v[l] > v[largest])
        largest = l;

    if (r < n && v[r] > v[largest])
        largest = r;

    if (largest != i)
    {
        T tmp = v[i];
        v[i] = v[largest];
        v[largest] = tmp;

        heapify(v, n, largest);
    }
}

// HeapSort
template<Sortable T>
void HeapSort(vector<T>& v)
{
    const unsigned int n = v.size();

    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(v, n, i);
    }

    for (int i = n - 1; i > 0; i--) {
        T tmp = v[0];
        v[0] = v[i];
        v[i] = tmp;

        heapify(v, i, 0);
    }
}


}



