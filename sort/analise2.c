#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000
#define ITERATIONS 10
#define MIN_VALUE 0
#define MAX_VALUE 1500
#define ORDERED 0

void insertionSort(int *arr, int n) {
  for (int i = 1; i < n; i++) {
    int key = arr[i];
    int j = i - 1;

    while (j >= 0 && arr[j] > key) {
      arr[j + 1] = arr[j];
      j--;
    }

    arr[j + 1] = key;
  }
}

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

int main() {
  clock_t startFunction, endFunction;
  double times[2]; // 0 - Insertion Sort time; 1 - Shell Sort time;
  FILE *csv;
  int arr[SIZE];

  csv = fopen("sort_results.csv", "a+");

  if (csv == NULL) {
    printf("Error to open file");
    return 1;
  }

  fprintf(csv, "Insertion Sort ; \nInput ; Execution time (ms) ;\n");
  printf("Insertion Sort time(s):\n");

  for (int i = 0; i < ITERATIONS; i++) {
    initializeArray(arr);

    startFunction = clock();
    insertionSort(arr, SIZE);
    endFunction = clock();

    times[0] =
        ((double)(endFunction - startFunction) / CLOCKS_PER_SEC) * 1000.0;

    printf("%f ms\n", times[0]);
    fprintf(csv, "%dk%s ; %f ms\n", SIZE / 1000, (ORDERED ? " *sorted" : ""),
            times[0]);
  }

  printf("\n");
  fprintf(csv, "\nShell Sort ; \nInput ; Execution time (ms) ;\n");
  printf("Shell Sort time(s):\n");

  for (int i = 0; i < ITERATIONS; i++) {
    initializeArray(arr);

    startFunction = clock();
    shellSort(arr, SIZE);
    endFunction = clock();

    times[1] =
        ((double)(endFunction - startFunction) / CLOCKS_PER_SEC) * 1000.0;

    printf("%f ms\n", times[1]);
    fprintf(csv, "%dk%s ; %f ms\n", SIZE / 1000, (ORDERED ? " *sorted" : ""),
            times[1]);
  }

  printf("\n");

  printf("Input: %dk\nIterations: %d\nSorted: %s", SIZE / 1000, ITERATIONS,
         ORDERED ? " true" : " false");

  fclose(csv);

  return 0;
}
