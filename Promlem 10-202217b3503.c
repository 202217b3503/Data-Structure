
#include <stdio.h>

/* Function to merge the subarrays of a[] */
void merge(int a[], int beg, int mid, int end) {
    int i, j, k;
    int n1 = mid - beg + 1;
    int n2 = end - mid;

    // Temporary arrays
    int LeftArray[n1], RightArray[n2];

    // Copy data to temp arrays
    for (i = 0; i < n1; i++)
        LeftArray[i] = a[beg + i];
    for (j = 0; j < n2; j++)
        RightArray[j] = a[mid + 1 + j];

    // Initial indexes
    i = 0;  // Initial index of LeftArray
    j = 0;  // Initial index of RightArray
    k = beg; // Initial index of merged subarray

    // Merge the temp arrays back into a[]
    while (i < n1 && j < n2) {
        if (LeftArray[i] <= RightArray[j]) {
            a[k] = LeftArray[i];
            i++;
        } else {
            a[k] = RightArray[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of LeftArray, if any
    while (i < n1) {
        a[k] = LeftArray[i];
        i++;
        k++;
    }

    // Copy the remaining elements of RightArray, if any
    while (j < n2) {
        a[k] = RightArray[j];
        j++;
        k++;
    }
}

void mergeSort(int a[], int beg, int end) {
    if (beg < end) {
        int mid = (beg + end) / 2;
        mergeSort(a, beg, mid);
        mergeSort(a, mid + 1, end);
        merge(a, beg, mid, end);
    }
}

/* Function to print the array */
void printArray(int a[], int n) {
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

int main() {
    int a[] = { 12, 31, 25, 8, 32, 17, 40, 42 };
    int n = sizeof(a) / sizeof(a[0]);
    printf("Before sorting array elements are - \n");
    printArray(a, n);
    mergeSort(a, 0, n - 1);
    printf("After sorting array elements are - \n");
    printArray(a, n);

 return 0;
}