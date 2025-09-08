#include <stdbool.h>
#include <stdio.h>

#define SIZE 5

// int random[SIZE] = {2, 5, 3, 4, 1};
// int sortAlt[SIZE] = {1, 2, 3, 4, 5};
// int sortDesc[SIZE] = {5, 4, 3, 2, 1};

int arr[SIZE] = {5, 4, 3, 2, 1};
int count = 0, countShellSort = 0, countQuickSort = 0, countMergeSort = 0;

int compare(const void *a, const void *b) { return (*(int *)a - *(int *)b); }

#define SWAP(a, b)                                                             \
  do {                                                                         \
    if (&(a) == &(b))                                                          \
      break;                                                                   \
    (a) ^= (b);                                                                \
    (b) ^= (a);                                                                \
    (a) ^= (b);                                                                \
  } while (0)

void insertionSort(int *arr, int n) {
  for (int i = 1; i < n; i++) {
    int key = arr[i];
    int j = i - 1;
    count += 2;

    while (j >= 0 && arr[j] > key) {
      arr[j + 1] = arr[j];
      j--;
      count += 2;
    }

    arr[j + 1] = key;
    count++;
  }
}

void shellSort(int *arr, int n) {
  for (int gap = n / 2; gap > 0; gap /= 2) { // log(n)
    for (int i = gap; i < n; i++) {          // n
      int temp = arr[i];                     // 1
      int j;                                 // 1
      count += 2;

      for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) { // O(n^2)
        arr[j] = arr[j - gap];                                 // 1
        count++;
      }

      arr[j] = temp; // 1
      count++;
    }
  }
}
// O(n^2)
// Ω(n log(n))

int partition(int *arr, int left, int right) {
  int pivot = arr[left]; // 1

  int i = left + 1; // 1
  int j = right;    // 1
  count += 3;

  while (i <= j) {
    while (i <= j && arr[i] <= pivot) {
      i++; // 1
      count++;
    }

    while (i <= j && arr[j] > pivot) {
      j--; // 1
      count++;
    }

    if (i < j) {
      SWAP(arr[i], arr[j]);
      count++;
    }
  }

  SWAP(arr[left], arr[j]);
  count += 2; // SWAP + return below
  return j;   // 1
}

void quickSort(int *arr, int left, int right) {
  while (left < right) {
    int pivotIndex = partition(arr, left, right);
    count++;

    if (pivotIndex - left < right - pivotIndex) {
      quickSort(arr, left, pivotIndex - 1);
      left = pivotIndex + 1;
      count += 2;
    }

    else {
      quickSort(arr, pivotIndex + 1, right);
      right = pivotIndex - 1;
      count += 2;
    }
  }
}

void merge(int *arr, int start, int mid, int end) {
  int temp[(end - start) + 1] = {}; // 1
  count++;

  int i = start, j = mid + 1, k = 0; // 3
  count += 3;
  while (i <= mid && j <= end) { // Executa no máximo (end - start vezes)
    if (arr[i] < arr[j]) {       // 1
      temp[k++] = arr[i++];
      count++;
    } else {
      temp[k++] = arr[j++]; // 1
      count++;
    }
  }

  while (i <= mid) {
    temp[k++] = arr[i++]; // 1
    count++;
  }

  while (j <= end) {
    temp[k++] = arr[j++]; // 1
    count++;
  }

  for (i = start; i <= end; i++) {
    arr[i] = temp[i - start]; // 1
    count++;
  }
}
// Ω(n)
// O(n)

void mergeSort(int *arr, int left, int right) {
  if (left < right) {                    // 1
    int mid = left + (right - left) / 2; // 1
    count++;

    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);

    merge(arr, left, mid, right); // Θ(m), onde m = (right - left + 1)
  }
}
// Ω(nlog(n))
// O(nlog(n))

int main() {
  insertionSort(arr, SIZE);
  printf("Insertion Sort count = %d\n", count);
  count = 0;

  shellSort(arr, SIZE);
  printf("Shell Sort count = %d\n", count);
  count = 0;

  quickSort(arr, 0, SIZE - 1);
  printf("Quick Sort count = %d\n", count);
  count = 0;

  mergeSort(arr, 0, SIZE - 1);
  printf("Merge Sort count = %d\n", count);
  count = 0;
}
