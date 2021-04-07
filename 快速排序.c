#include <stdio.h>

int partition(int A[], int low, int high);
void quickSort(int A[], int low, int high);
void Print(int A[], int len);

int main(void)
{
  int A[] = { -1, 10, 2, 3, 1, 9, 5, 7, 8, 6, 4 };
  quickSort(A, 1, 10);
  Print(A, 11);
  return 0;
}


int partition(int A[], int low, int high)
{
  int pivot; // 基准

  pivot = A[low];
  while (low < high) {
    while (low < high && A[high] >= pivot)
      --high;
    A[low] = A[high];
    while (low < high && A[low] < pivot)
      ++low;
    A[high] = A[low];
  }
  A[low] = pivot;
  return low;
}

void quickSort(int A[], int low, int high)
{
  if (low < high) {
    int pivot = partition(A, low, high);
    quickSort(A, low, pivot - 1);
    quickSort(A, pivot + 1, high);
  }
}

void Print(int A[], int len)
{
  for (int i = 1; i != len; ++i)
    printf("%d ", A[i]);
  putchar('\n');
}
