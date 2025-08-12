#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100000
#define REPETITION 10
#define MIN_VALUE 0
#define MAX_VALUE 1500

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

  for (int i = 2; i < sqrt(number); i++)
    if (number % i == 0)
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
  srand(time(NULL));

  for (int i = 0; i < SIZE; i++)
    array[i] = rand() % (MAX_VALUE + MIN_VALUE);
}

int main() {
  clock_t start, end;
  clock_t startTotal, endTotal;
  clock_t startFunction, endFunction;

  double tExecucao, tGerar, tOrdenarDesordenado, tOrdenarOrdenado,
      tPrimosDesordenado, tPrimosOrdenado, tTotal, tOrdenarPercent,
      tPrimosPercent, tMedia;

  int arr[SIZE];

  startTotal = clock();
  for (int i = 0; i < REPETITION; i++) {
    start = clock();

    startFunction = clock();
    initializeArray(arr);
    endFunction = clock();
    tGerar = ((double)(endFunction - startFunction) / CLOCKS_PER_SEC) * 1000.0;

    // Time to count primes in unsorted array
    startFunction = clock();
    countPrimeNumbers(arr);
    endFunction = clock();
    tPrimosDesordenado =
        ((double)(endFunction - startFunction) / CLOCKS_PER_SEC) * 1000.0;

    // Time to sort array
    startFunction = clock();
    quickSort(arr, 0, SIZE - 1);
    endFunction = clock();
    tOrdenarDesordenado =
        ((double)(endFunction - startFunction) / CLOCKS_PER_SEC) * 1000.0;

    // Time to count primes in sorted array
    startFunction = clock();
    countPrimeNumbers(arr);
    endFunction = clock();
    tPrimosOrdenado =
        ((double)(endFunction - startFunction) / CLOCKS_PER_SEC) * 1000.0;

    // Time to re-sort array
    startFunction = clock();
    quickSort(arr, 0, SIZE - 1);
    endFunction = clock();
    tOrdenarOrdenado =
        ((double)(endFunction - startFunction) / CLOCKS_PER_SEC) * 1000.0;

    end = clock();
    tExecucao = ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;

    // Metrics
    printf("Cenário %d\n"
           "Execução: %6.4f ms\n"
           "TGerar: %6.4f ms\n"
           "TOrdenar (desordenado): %6.4f ms\n"
           "TOrdenar (ordenado): %6.4f ms\n"
           "TPrimos (desordenado): %6.4f ms\n"
           "TPrimos (ordenado): %6.4f ms\n\n",
           i + 1, tExecucao, tGerar, tOrdenarDesordenado, tOrdenarOrdenado,
           tPrimosDesordenado, tPrimosOrdenado);
  }

  endTotal = clock();
  tTotal = ((double)(endTotal - startTotal) / CLOCKS_PER_SEC) * 1000.0;
  tOrdenarPercent = ((tOrdenarOrdenado + tOrdenarDesordenado) / tTotal) * 100.0;
  tPrimosPercent = ((tPrimosOrdenado + tPrimosDesordenado) / tTotal) * 100.0;
  tMedia = tTotal / REPETITION;

  printf("TTotal: %6.4f ms\n\n", tTotal);

  // Statistic
  printf("Estatística\n"
         "n: %d\n"
         "%%TOrdenar: %3.2f%%\n"
         "%%TPrimos: %3.2f%%\n"
         "TMedia: %6.4f ms\n",
         SIZE, tOrdenarPercent, tPrimosPercent, tMedia);

  return 0;
}
