#pragma once
#include <iostream>

class Sorting
{
public:
	void BubbleSort(int* arr, int size);
    /*-----------------------------------------------------------------------
     Bubble Sort

     Bubble Sort swaps adjacent elements that are in the wrong order.
     The element then goes to the end of the list.
     The sorting is performed again on the unsorted part of the array.
     -----------------------------------------------------------------------*/

    void SelectionSort(int* arr, int size);
    /*-----------------------------------------------------------------------
     Selection Sort

     Selection Sort finds the smallest number in the list and puts it first.
     It finds the smallest number in the unsorted set and puts it second.
     It keeps looping through this process for n-1 times, n being the number
     of elements in the array.
     -----------------------------------------------------------------------*/
    
    void InsertionSort(int* arr, int size);
    /*-----------------------------------------------------------------------
     Insertion Sort

     Insertion sort is a simple sorting algorithm that works similar to the 
     way you sort playing cards in your hands. The array is virtually split 
     into a sorted and an unsorted part. Values from the unsorted part are 
     picked and placed at the correct position in the sorted part.
     -----------------------------------------------------------------------*/

    void quickSort(int* arr, int left, int right);
    /*-----------------------------------------------------------------------
     QuickSort

     1. Choose an element to be the pivot
     2. Arrange the list so that all the smaller elements are on its left
        and all the greater elements are on its right.
     3. Divide the (sub)-list into two smaller sub-lists.
     4. Each list is then sorted in the same way
     -----------------------------------------------------------------------*/
    
    void MergeSort(int* arrayA, int* arrayB, int low, int high);

private:
    void swap(int* xp, int* yp)
    {
        int temp = *xp;
        *xp = *yp;
        *yp = temp;
    }

    int partition(int* arr, int low, int high);

    void merge(int* arrayA, int* arrayB, int low, int mid, int high);
};

void Sorting::BubbleSort(int* arr, int size)
{	
    int i, j;

    for (i = 0; i < size - 1; i++)
    {
        for (j = 0; j < size - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(&arr[j], &arr[j + 1]);

            }
        }
    }
}

void Sorting::SelectionSort(int* arr, int size)
{
    int i, j, current_minimum_index;

    // One by one move boundary of unsorted subarray
    for (i = 0; i < size - 1; i++)
    {
        // Find the minimum element in unsorted array
        current_minimum_index = i;

        for (j = i + 1; j < size; j++)
        {
            if (arr[j] < arr[current_minimum_index])
            {
                current_minimum_index = j;
            }
        }

        // Swap the found minimum element with the first element
        swap(&arr[current_minimum_index], &arr[i]);
    }
}

void Sorting::InsertionSort(int* arr, int size)
{
    int i, key, j;
    for (i = 1; i < size; i++)
    {
        key = arr[i];
        j = i - 1;

        /* Move elements of arr[0..i-1], that are
        greater than key, to one position ahead
        of their current position */
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

/***** QuickSort Algorthim *****/
int Sorting::partition(int* arr, int low, int high)
{
    int pivot = arr[high];    // pivot
    int i = (low - 1);  // Index of smaller element

    for (int j = low; j <= high - 1; j++)
    {
        // If current element is smaller than or
        // equal to pivot
        if (arr[j] <= pivot)
        {
            i++;    // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void Sorting::quickSort(int* arr, int left, int right)
{
    if (right < left)
        return;

    /* pi is partitioning index, arr[p] is now
       at right place */
    int pi = partition(arr, left, right);
    
    /* Separately sort elements before
       partition and after partition */
    quickSort(arr, left, pi - 1);
    quickSort(arr, pi + 1, right);

}//-- End of QuickSort Algorithm

void Sorting::MergeSort(int* arrayA, int* arrayB, int low, int high)
{
    int mid;
    if (high < low)
        return;

}

void Sorting::merge(int* arrayA, int* arrayB, int low, int mid, int high)
{
    int h, i, j, k;

}
