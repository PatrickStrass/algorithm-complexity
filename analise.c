#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000
#define ITERATIONS 10
#define MIN_VALUE 0
#define MAX_VALUE 1500
#define ORDERED 1

void swap(int *x, int *y) {
  if (x == y)
    return;

  *x ^= *y ^= *x ^= *y;
}

// Hoare partition
int partition(int *array, int left, int right) {
  int pivot = array[left];

  int i = left + 1;
  int j = right;
  while (i <= j) {
    while (i <= j && array[i] <= pivot)
      i++;

    while (i <= j && array[j] > pivot)
      j--;

    if (i < j)
      swap(&array[i], &array[j]);
  }

  swap(&array[left], &array[j]);

  return j;
}

void quickSort(int *array, int left, int right) {
  if (left < right) {
    int pivotIndex = partition(array, left, right);

    quickSort(array, left, pivotIndex - 1);
    quickSort(array, pivotIndex + 1, right);
  }
}

bool isPrime(int number) {
  if (number <= 1)
    return false;

  if (number == 2 || number == 3)
    return true;

  if (number % 2 == 0 || number % 3 == 0)
    return false;

  for (int i = 5; i <= sqrt(number); i += 6)
    if (number % i == 0 || number % (i + 2) == 0)
      return false;

  return true;
}

void countPrimeNumbers(int *array) {
  int count = 0;

  for (int i = 0; i < SIZE; i++)
    if (isPrime(array[i]))
      count++;
}

void initializeArray(int *array) {
  for (int i = MIN_VALUE; i < SIZE; i++) {
    srand(time(NULL));

#if ORDERED == 0
    array[i] = rand() % (MAX_VALUE + MIN_VALUE);
#else
    array[i] = i;
#endif
  }
}

int main() {
  clock_t startFunction, endFunction;

  double times[7]; // 0 - tGenerate; 1 - tSort; 2 - tPrimes; 3 -
                   // TTotal; 4 - tGenerateTotal; 5 - tSortTotal; 6 -
                   // tPrimesTotal

  double tGeneratePercent, tSortPercent, tPrimesPercent, tAverage;

  FILE *csv;
  int arr[SIZE];

  csv = fopen("result.csv", "a+");

  if (csv == NULL) {
    printf("Error to open file");
    return 1;
  }

  fprintf(csv, "Scenario ; Execution ; TGenerate (ms) ; TSort (ms) ; TPrimes "
               "(ms) ; TTotal (ms) ; %%TSort ; %%TPrimes ;\n");

  for (int i = 0; i < ITERATIONS; i++) {
    startFunction = clock();
    initializeArray(arr);
    endFunction = clock();
    times[0] =
        ((double)(endFunction - startFunction) / CLOCKS_PER_SEC) * 1000.0;
    times[4] += times[0];

    startFunction = clock();
    quickSort(arr, 0, SIZE - 1);
    endFunction = clock();
    times[1] =
        ((double)(endFunction - startFunction) / CLOCKS_PER_SEC) * 1000.0;
    times[5] += times[1];

    startFunction = clock();
    countPrimeNumbers(arr);
    endFunction = clock();
    times[2] =
        ((double)(endFunction - startFunction) / CLOCKS_PER_SEC) * 1000.0;
    times[6] += times[2];

    times[3] = times[0] + times[1] + times[2];
    tSortPercent = (times[1] / times[3]) * 100.0;
    tPrimesPercent = (times[2] / times[3]) * 100.0;
    tAverage += times[3];

    printf("Scenario %d\n"
           "TTotal: %f ms\n"
           "TGenerate: %f ms\n"
           "TSort: %f ms\n"
           "TPrimes: %f ms\n"
           "%%TSort: %3.2f%%\n"
           "%%TPrimes: %3.2f%%\n\n",
           i + 1, times[3], times[0], times[1], times[2], tSortPercent,
           tPrimesPercent);

    fprintf(csv, "S%d ; %dk%s ; %f ; %f ; %f ; %f ; %3.2f%% ; %3.2f%% ;\n",
            i + 1, SIZE / 1000, (ORDERED ? " *sorted" : ""), times[0], times[1],
            times[2], times[3], tSortPercent, tPrimesPercent);
  }

  fprintf(csv, "\n");

  tAverage /= ITERATIONS;

  printf("Statistic\n"
         "Execution: %d%s\n"
         "TAverage: %f ms\n",
         SIZE, (ORDERED ? " *sorted" : ""), tAverage);

  fclose(csv);

  return 0;
}
