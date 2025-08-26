#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 500000
#define ITERATIONS 10
#define MIN_VALUE 0
#define MAX_VALUE 1500
#define ORDERED 0

// int compare(const void *a, const void *b) { return (*(int *)a - *(int *)b); }

#define SWAP(a, b)                                                             \
  do {                                                                         \
    if (&(a) == &(b))                                                          \
      break;                                                                   \
    (a) ^= (b);                                                                \
    (b) ^= (a);                                                                \
    (a) ^= (b);                                                                \
  } while (0)

void shellSort(int *arr, int n) {
  for (int gap = n / 2; gap > 0; gap /= 2) {
    for (int i = gap; i < n; i++) {
      int temp = arr[i];

      int j;
      for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
        arr[j] = arr[j - gap];

      arr[j] = temp;
    }
  }
}

int partition(int *arr, int left, int right) {
  int pivot = arr[left];

  int i = left + 1;
  int j = right;
  while (i <= j) {
    while (i <= j && arr[i] <= pivot)
      i++;

    while (i <= j && arr[j] > pivot)
      j--;

    if (i < j)
      SWAP(arr[i], arr[j]);
  }

  SWAP(arr[left], arr[j]);

  return j;
}

void quickSort(int *arr, int left, int right) {
  while (left < right) {
    int pivotIndex = partition(arr, left, right);

    if (pivotIndex - left < right - pivotIndex) {
      quickSort(arr, left, pivotIndex - 1);
      left = pivotIndex + 1;
    }

    else {
      quickSort(arr, pivotIndex + 1, right);
      right = pivotIndex - 1;
    }
  }
}

void merge(int *arr, int start, int mid, int end) {
  int temp[(end - start) + 1] = {};

  int i = start, j = mid + 1, k = 0;
  while (i <= mid && j <= end) {
    if (arr[i] < arr[j])
      temp[k++] = arr[i++];
    else
      temp[k++] = arr[j++];
  }

  while (i <= mid)
    temp[k++] = arr[i++];

  while (j <= end)
    temp[k++] = arr[j++];

  for (i = start; i <= end; i++)
    arr[i] = temp[i - start];
}

void mergeSort(int *arr, int left, int right) {
  if (left < right) {

    int mid = left + (right - left) / 2;

    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);

    merge(arr, left, mid, right);
  }
}

void initializeArray(int *array) {
  srand(time(NULL));

  for (int i = MIN_VALUE; i < SIZE; i++) {

#if ORDERED == 0
    array[i] = rand() % (MAX_VALUE + MIN_VALUE);
#else
    array[i] = i;
#endif
  }
}

int arr[SIZE];

int main() {
  clock_t startFunction, endFunction;
  double times[3]; // 0 - Shell Sort; 1 - Quick Sort; 2 - Merge Sort;
  FILE *csv;

  csv = fopen("sort_results3.csv", "a+");

  if (csv == NULL) {
    printf("Error to open file");
    return 1;
  }

  fprintf(csv, "Shell Sort %s ; \nInput ; Execution time (ms) ;\n",
          (ORDERED ? "- sorted" : ""));
  printf("Shell Sort time(s):\n");
  for (int j = 0; j < ITERATIONS; j++) {
    initializeArray(arr);

    startFunction = clock();
    shellSort(arr, SIZE);
    endFunction = clock();

    times[0] =
        ((double)(endFunction - startFunction) / CLOCKS_PER_SEC) * 1000.0;

    printf("%f ms\n", times[0]);
    fprintf(csv, "%dk ; %f ms\n", SIZE / 1000, times[0]);
  }

  printf("\n");
  fprintf(csv, "\n");

  fprintf(csv, "Quick Sort %s ; \nInput ; Execution time (ms) ;\n",
          (ORDERED ? "- sorted" : ""));
  printf("Quick Sort time(s):\n");
  for (int j = 0; j < ITERATIONS; j++) {
    initializeArray(arr);

    startFunction = clock();
    quickSort(arr, 0, SIZE - 1);
    // qsort(arr, SIZE, sizeof(int), compare);
    endFunction = clock();

    times[1] =
        ((double)(endFunction - startFunction) / CLOCKS_PER_SEC) * 1000.0;

    printf("%f ms\n", times[1]);
    fprintf(csv, "%dk ; %f ms\n", SIZE / 1000, times[1]);
  }

  printf("\n");
  fprintf(csv, "\n");

  fprintf(csv, "Merge Sort %s ; \nInput ; Execution time (ms) ;\n",
          (ORDERED ? "- sorted" : ""));
  printf("Merge Sort time(s):\n");
  for (int j = 0; j < ITERATIONS; j++) {
    initializeArray(arr);

    startFunction = clock();
    mergeSort(arr, 0, SIZE - 1);
    endFunction = clock();

    times[2] =
        ((double)(endFunction - startFunction) / CLOCKS_PER_SEC) * 1000.0;

    printf("%f ms\n", times[2]);
    fprintf(csv, "%dk ; %f ms\n", SIZE / 1000, times[2]);
  }

  printf("\n");
  printf("Input: %dk\nIterations: %d\nSorted: %s\n\n", SIZE / 1000, ITERATIONS,
         ORDERED ? " true" : " false");
  fprintf(csv, "\n");

  fclose(csv);

  return 0;
}
