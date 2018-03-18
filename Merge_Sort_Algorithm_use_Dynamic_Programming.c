#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define INT_MAX 2147483647

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

#define LOG2(X) \
            (8 * sizeof(unsigned int) - Count_Leading_Zero((unsigned int) X) - 1)

int  Count_Leading_Zero(unsigned int);
void Merge_Sort(int, int *);
void Merge(int, int, int, int *, int *);

int main(void)
{
    int length, array_length;

    printf("Please enter the length of data: ");
    scanf("%d", &length);

    /* Check if the length of array is the power of two */
    if ((length & (length - 1)) || (length == 1)) {
        array_length = 2 << LOG2(length);
    } else {
        array_length = length;
    }

    int data[array_length];

    /* Get random values */
    srand((unsigned int) time(NULL));
    for (int i = 0; i < array_length; i++) {
        if (i < length) {
            data[i] = rand() % length;
        } else {
            /* Expand array and fill the value */
            data[i] = INT_MAX;
        }
    }

    printf("\nRaw data is:\n ");
    for (int i = 0; i < length; i++) {
        printf("%d  ", data[i]);
    }

    Merge_Sort(array_length, data);

    printf("\n\nSorted data is:\n ");
    for (int i = 0; i < length; i++) {
        printf("%d  ", data[i]);
    }
    printf("\n");
    
    return 0;
}

int Count_Leading_Zero(unsigned int number)
{
    if (number == 0) return 32;

    int count = 0;
    if (number <= 0x0000FFFF) { count += 16; number <<= 16; }
    if (number <= 0x00FFFFFF) { count +=  8; number <<=  8; }
    if (number <= 0x0FFFFFFF) { count +=  4; number <<=  4; }
    if (number <= 0x3FFFFFFF) { count +=  2; number <<=  2; }
    if (number <= 0x7FFFFFFF) { count +=  1; number <<=  1; }

    return count;
}

void Merge_Sort(int length, int *num)
{
    /* Size variable is mean that the size of the subarray to be merged */
    int low, mid, high, size;

    int  temp[length];
    bool flag = false;

    memcpy(temp, num, sizeof(temp[0]) * length);

    /* Merge subarrays of size one, then merge subarrays of size two,
    ** and then merge subarrays of size four, and so on. */
    for (size = 1; size < length; size *= 2) {
        for (low = 0; low < length - (2 * size) + 1; low += 2 * size) {
            mid  = low + size - 1;
            high = MIN(low + (2 * size) - 1, length - 1);

            if (flag == false) {
                Merge(low, mid, high, num, temp);
            } else {
                Merge(low, mid, high, temp, num);
            }
        }
        flag ^= 1;
    }

    if (flag == false) {
        memcpy(num, temp, sizeof(num[0]) * length);
    }
}

void Merge(int low, int mid, int high, int *dest, int *src)
{
    int i = low, j = mid + 1, k = low;

    while (i <= mid && j <= high) {
        if (src[i] < src[j]) {
            dest[k] = src[i];
            i++;
        } else {
            dest[k] = src[j];
            j++;
        }
        k++;
    }

    if (i > mid) {
        for (; j <= high; j++, k++) {
            dest[k] = src[j];
        }
    } else {
        for (; i <= mid; i++, k++) {
            dest[k] = src[i];
        }
    }
}
