#include <iostream>

using namespace std;

struct record {
  int key;
};

void fixheap(record a[], int left, int right) {
  record x = a[left];
  int i, j;
  for (i = left, j = 2 * i + 1; j <= right; i = j, j = 2 * i + 1) {
    if (j < right && a[j + 1].key > a[j].key) j++;
    if (x.key >= a[j].key) break;

    a[i] = a[j];
  }
  a[i] = x;

  cout << "[ ";
  for(int i = 0; i <= right; i++) cout << a[i].key << " ";
  cout << "]\n";  
}
void heapSort(record a[], int n) {
  if (n > 1) {
    for (int left = n / 2 - 1; left >= 0; left--) {
      fixheap(a, left, n - 1);
    }
    swap(a[0], a[n - 1]);

    for (int right = n - 2; right >= 1; right--) {
      fixheap(a, 0, right);
      swap(a[0], a[right]);
    }
  }
}

int main() {
  record a[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  heapSort(a, sizeof(a) / sizeof(record));

  return 0;
}