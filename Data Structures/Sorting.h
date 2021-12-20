#pragma once

class Sorting
{
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


     -----------------------------------------------------------------------*/

    void swap(int* xp, int* yp)
    {
        int temp = *xp;
        *xp = *yp;
        *yp = temp;
    }
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
