<<<<<<< HEAD
#include <iostream>
#include <math.h>
using namespace std;

// declaring global variables
int timer;

int timerWorker1 = 0;
int timerWorker2 = 0;

void swap(int &a, int &b)
{
    int temp = a;
    timer += 5;
    a = b;
    timer += 5;
    b = temp;
    timer += 5;
}

void selectionSort(int *arr, const int length)
{
    timer = 0;
    
    int wallIndex = length - 1;
    for (; wallIndex > 0; wallIndex--)
    {
        
        int maxIndex = 0;
        for (int i = 0; i < wallIndex; i++)
        {
            // comparing heights, adding 1 to timer
            timer++;
            if (arr[i] > arr[maxIndex])
            {
                maxIndex = i;
            }
        }
        
        if (wallIndex != maxIndex)
        {
            swap(arr[wallIndex], arr[maxIndex]);
        }
    }
}

void insertionSort(int *arr, const int length)
{
    timer = 0;
    
    int key;
    for (int i = 1; i < length; i++)
    {
        key = arr[i];
        timer += 5;
        int k = i - 1;
        // before entering while loop, pair of trees are compared
        timer++;
        while (k >= 0 && key < arr[k])
        {
            timer++;
            arr[k + 1] = arr[k];
            timer += 5;
            k--;
        }
        arr[k + 1] = key;
        timer += 5;
    }
}

void bubbleSort(int *arr, const int length)
{
    timer = 0;
    
    bool sorted = false;
    for (int forward = 1; forward < length && !sorted; forward++)
    {
        sorted = true;
        for (int i = 0; i < length - forward; i++)
        {
            int nextIndex = i + 1;
            // comparing pair of trees
            timer++;
            if (arr[i] > arr[nextIndex])
            {

                swap(arr[i], arr[nextIndex]);
                sorted = false;
            }
        }
    }
}
void partition(int *&arr, int first, int last, int &pivotIndex)
{
    int pivot = arr[first];
    int lastS1 = first;
    int firstUnknown = first + 1;
    for (; firstUnknown <= last; firstUnknown++)
    {
        // comparing pair of trees
        timer++;
        if (arr[firstUnknown] < pivot)
        {
            lastS1++;
            swap(arr[firstUnknown], arr[lastS1]);
        }
    }
    swap(arr[first], arr[lastS1]);
    pivotIndex = lastS1;
}
void quickSort(int *arr, int first, int last)
{

    
    int pivotIndex;
    
    if (first < last)
    {

        partition(arr, first, last, pivotIndex);

        quickSort(arr, first, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, last);
    }
}

int *generate_random_array(int size)
{
    srand((unsigned int)time(NULL));
    int *random_arr = new int[size];
    for (int i = 0; i < size; i++)
    {
        random_arr[i] = rand();
    }
    return random_arr;
}

int *generate_almost_sorted_array(int size)
{
    srand((unsigned int)time(NULL));
    int *random_array = generate_random_array(size);

    bubbleSort(random_array, size);
    timer = 0;

    int swap_count = size * 0.03;
    if (swap_count == 0)
    {
        swap_count = 1;
    }
    for (int i = 0; i < swap_count; i++)
    {
        int first_index = rand() % size;
        int second_index = size - first_index;
        int temp = random_array[first_index];
        random_array[first_index] = random_array[second_index];
        random_array[second_index] = temp;
    }
    return random_array;
}
// THIS ALGORITHM IS FOR TASK3 SIMULATING 2 WORKERS WORKING ON DIFFERENT BRANCHES. EACH WORKER HAS UNIQUE DURATION, THAT IS USED FOR COST CALCULATION.
void partition(int *&arr, int first, int last, int &pivotIndex, int &timerWorker)
{
    int pivot = arr[first];
    int lastS1 = first;
    int firstUnknown = first + 1;
    for (; firstUnknown <= last; firstUnknown++)
    {
        timerWorker++;
        if (arr[firstUnknown] < pivot)
        {
            lastS1++;
            timerWorker+=15;
            swap(arr[firstUnknown], arr[lastS1]);
        }
    }
    timerWorker+=15;
    swap(arr[first], arr[lastS1]);
    pivotIndex = lastS1;
}

void quickSort2(int *arr, int first, int last, int &timerWorker)
{
    if (first < last)
    {
        int pivotIndex;
        partition(arr, first, last, pivotIndex, timerWorker);

        quickSort2(arr, first, pivotIndex - 1, timerWorker);
        quickSort2(arr, pivotIndex + 1, last, timerWorker);
    }
}
//NOTE! TO TEST FUNCTIONALITY AND RUN SIMULATIONS, I COMMENTED OUT CODES BELOW INSTEAD OF CREATING MULTIPLE CPP FILES.
int main()
{

    // int *truck1 = generate_random_array(8);
    // int *truck2 = generate_random_array(16);
    // int *truck3 = generate_random_array(32);
    // int *truck4 = generate_random_array(64);
    // int *truck5 = generate_random_array(128);
    // int *truck6 = generate_random_array(256);
    // int *truck7 = generate_random_array(512);
    // int *truck8 = generate_random_array(1024);
    // int *truck9 = generate_random_array(2048);
    // int *truck10 = generate_random_array(4096);

    // int *truck1 = generate_almost_sorted_array(8);
    // int *truck2 = generate_almost_sorted_array(16);
    // int *truck3 = generate_almost_sorted_array(32);
    // int *truck4 = generate_almost_sorted_array(64);
    // int *truck5 = generate_almost_sorted_array(128);
    // int *truck6 = generate_almost_sorted_array(256);
    // int *truck7 = generate_almost_sorted_array(512);
    // int *truck8 = generate_almost_sorted_array(1024);
    // int *truck9 = generate_almost_sorted_array(2048);
    // int *truck10 = generate_almost_sorted_array(4096);

    // insertionSort(truck1, 8);
    // cout << "Total duration for insertion sort for size " << 8 << " is " << timer << endl;
    // insertionSort(truck2, 16);
    // cout << "Total duration for insertion sort for size " << 16 << " is " << timer << endl;
    // insertionSort(truck3, 32);
    // cout << "Total duration for insertion sort for size " << 32 << " is " << timer << endl;
    // insertionSort(truck4, 64);
    // cout << "Total duration for insertion sort for size " << 64 << " is " << timer << endl;
    // insertionSort(truck5, 128);
    // cout << "Total duration for insertion sort for size " << 128 << " is " << timer << endl;
    // insertionSort(truck6, 256);
    // cout << "Total duration for insertion sort for size " << 256 << " is " << timer << endl;
    // insertionSort(truck7, 512);
    // cout << "Total duration for insertion sort for size " << 512 << " is " << timer << endl;
    // insertionSort(truck8, 1024);
    // cout << "Total duration for insertion sort for size " << 1024 << " is " << timer << endl;
    // insertionSort(truck9, 2048);
    // cout << "Total duration for insertion sort for size " << 2048 << " is " << timer << endl;
    // insertionSort(truck10, 4096);
    // cout << "Total duration for insertion sort for size " << 4096 << " is " << timer << endl;

    // selectionSort(truck1, 8);
    // cout << "Total duration for selection sort for size " << 8 << " is " << timer << endl;
    // selectionSort(truck2, 16);
    // cout << "Total duration for selection sort for size " << 16 << " is " << timer << endl;
    // selectionSort(truck3, 32);
    // cout << "Total duration for selection sort for size " << 32 << " is " << timer << endl;
    // selectionSort(truck4, 64);
    // cout << "Total duration for selection sort for size " << 64 << " is " << timer << endl;
    // selectionSort(truck5, 128);
    // cout << "Total duration for selection sort for size " << 128 << " is " << timer << endl;
    // selectionSort(truck6, 256);
    // cout << "Total duration for selection sort for size " << 256 << " is " << timer << endl;
    // selectionSort(truck7, 512);
    // cout << "Total duration for selection sort for size " << 512 << " is " << timer << endl;
    // selectionSort(truck8, 1024);
    // cout << "Total duration for selection sort for size " << 1024 << " is " << timer << endl;
    // selectionSort(truck9, 2048);
    // cout << "Total duration for selection sort for size " << 2048 << " is " << timer << endl;
    // selectionSort(truck10, 4096);
    // cout << "Total duration for selection sort for size " << 4096 << " is " << timer << endl;

    // bubbleSort(truck1, 8);
    // cout << "Total duration for bubble sort for size " << 8 << " is " << timer << endl;
    // bubbleSort(truck2, 16);
    // cout << "Total duration for bubble sort for size " << 16 << " is " << timer << endl;
    // bubbleSort(truck3, 32);
    // cout << "Total duration for bubble sort for size " << 32 << " is " << timer << endl;
    // bubbleSort(truck4, 64);
    // cout << "Total duration for bubble sort for size " << 64 << " is " << timer << endl;
    // bubbleSort(truck5, 128);
    // cout << "Total duration for bubble sort for size " << 128 << " is " << timer << endl;
    // bubbleSort(truck6, 256);
    // cout << "Total duration for bubble sort for size " << 256 << " is " << timer << endl;
    // bubbleSort(truck7, 512);
    // cout << "Total duration for bubble sort for size " << 512 << " is " << timer << endl;
    // bubbleSort(truck8, 1024);
    // cout << "Total duration for bubble sort for size " << 1024 << " is " << timer << endl;
    // bubbleSort(truck9, 2048);
    // cout << "Total duration for bubble sort for size " << 2048 << " is " << timer << endl;
    // bubbleSort(truck10, 4096);
    // cout << "Total duration for bubble sort for size " << 4096 << " is " << timer << endl;

    // quickSort(truck1, 0, 7);
    // cout << "Total duration for quick sort for size " << 8 << " is " << timer << endl;
    // quickSort(truck2, 0, 15);
    // cout << "Total duration for quick sort for size " << 16 << " is " << timer << endl;
    // quickSort(truck3, 0, 31);
    // cout << "Total duration for quick sort for size " << 32 << " is " << timer << endl;
    // quickSort(truck4, 0, 63);
    // cout << "Total duration for quick sort for size " << 64 << " is " << timer << endl;
    // quickSort(truck5, 0, 127);
    // cout << "Total duration for quick sort for size " << 128 << " is " << timer << endl;
    // quickSort(truck6, 0, 255);
    // cout << "Total duration for quick sort for size " << 256 << " is " << timer << endl;
    // quickSort(truck7, 0, 511);
    // cout << "Total duration for quick sort for size " << 512 << " is " << timer << endl;
    // quickSort(truck8, 0, 1023);
    // cout << "Total duration for quick sort for size " << 1024 << " is " << timer << endl;
    // quickSort(truck9, 0, 2047);
    // cout << "Total duration for quick sort for size " << 2048 << " is " << timer << endl;
    // quickSort(truck10, 0, 4095);
    // cout << "Total duration for quick sort for size " << 4096 << " is " << timer << endl;
    // Assuming truckX arrays are already defined and filled with data

    // quickSort2(truck2, 0, 3, timerWorker1);
    // quickSort2(truck2, 4, 7, timerWorker2);
    // cout<< "Duration for worker 1 :" << timerWorker1<< endl;
    // cout<<"Duration for worker 2:" << timerWorker2<< endl;

    // timerWorker1 = 0;
    // timerWorker2 = 0;

    // quickSort2(truck2, 0, 7, timerWorker1);
    // quickSort2(truck2, 8, 15, timerWorker2);
    // cout<< "Duration for worker 1 :" << timerWorker1<< endl;
    // cout<<"Duration for worker 2:" << timerWorker2<< endl;

    // timerWorker1 = 0;
    // timerWorker2 = 0;
    
    // quickSort2(truck3, 0, 15, timerWorker1);
    // quickSort2(truck3, 16, 31, timerWorker2);
    // cout<< "Duration for worker 1 :" << timerWorker1<< endl;
    // cout<<"Duration for worker 2:" << timerWorker2<< endl;

    // timerWorker1 = 0;
    // timerWorker2 = 0;
    
    // quickSort2(truck4, 0, 31, timerWorker1);
    // quickSort2(truck4, 32, 63, timerWorker2);
    // cout<< "Duration for worker 1 :" << timerWorker1<< endl;
    // cout<<"Duration for worker 2:" << timerWorker2<< endl;

    // timerWorker1 = 0;
    // timerWorker2 = 0;

    // quickSort2(truck5, 0, 63, timerWorker1);
    // quickSort2(truck5, 64, 127, timerWorker2);
    // cout<< "Duration for worker 1 :" << timerWorker1<< endl;
    // cout<<"Duration for worker 2:" << timerWorker2<< endl;

    // timerWorker1 = 0;
    // timerWorker2 = 0;
  
    // quickSort2(truck6, 0, 127, timerWorker1);
    // quickSort2(truck6, 128, 255, timerWorker2);
    // cout<< "Duration for worker 1 :" << timerWorker1<< endl;
    // cout<<"Duration for worker 2:" << timerWorker2<< endl;

    // timerWorker1 = 0;
    // timerWorker2 = 0;

    // quickSort2(truck7, 0, 255, timerWorker1);
    // quickSort2(truck7, 256, 511, timerWorker2);
    // cout<< "Duration for worker 1 :" << timerWorker1<< endl;
    // cout<<"Duration for worker 2:" << timerWorker2<< endl;

    // timerWorker1 = 0;
    // timerWorker2 = 0;

    // quickSort2(truck8, 0, 511, timerWorker1);
    // quickSort2(truck8, 512, 1023, timerWorker2);
    // cout<< "Duration for worker 1 :" << timerWorker1<< endl;
    // cout<<"Duration for worker 2:" << timerWorker2<< endl;

    // timerWorker1 = 0;
    // timerWorker2 = 0;

    // quickSort2(truck9, 0, 1023, timerWorker1);
    // quickSort2(truck9, 1024, 2047, timerWorker2);
    // cout<< "Duration for worker 1 :" << timerWorker1<< endl;
    // cout<<"Duration for worker 2:" << timerWorker2<< endl;

    // timerWorker1 = 0;
    // timerWorker2 = 0;
    
    // quickSort2(truck10, 0, 2047, timerWorker1);
    // quickSort2(truck10, 2048, 4095, timerWorker2);
    // cout<< "Duration for worker 1 :" << timerWorker1<< endl;
    // cout<<"Duration for worker 2:" << timerWorker2<< endl;


    return 0;
=======
#include <iostream>
#include <math.h>
using namespace std;

// declaring global variables
int timer;

int timerWorker1 = 0;
int timerWorker2 = 0;

void swap(int &a, int &b)
{
    int temp = a;
    timer += 5;
    a = b;
    timer += 5;
    b = temp;
    timer += 5;
}

void selectionSort(int *arr, const int length)
{
    timer = 0;
    
    int wallIndex = length - 1;
    for (; wallIndex > 0; wallIndex--)
    {
        
        int maxIndex = 0;
        for (int i = 0; i < wallIndex; i++)
        {
            // comparing heights, adding 1 to timer
            timer++;
            if (arr[i] > arr[maxIndex])
            {
                maxIndex = i;
            }
        }
        
        if (wallIndex != maxIndex)
        {
            swap(arr[wallIndex], arr[maxIndex]);
        }
    }
}

void insertionSort(int *arr, const int length)
{
    timer = 0;
    
    int key;
    for (int i = 1; i < length; i++)
    {
        key = arr[i];
        timer += 5;
        int k = i - 1;
        // before entering while loop, pair of trees are compared
        timer++;
        while (k >= 0 && key < arr[k])
        {
            timer++;
            arr[k + 1] = arr[k];
            timer += 5;
            k--;
        }
        arr[k + 1] = key;
        timer += 5;
    }
}

void bubbleSort(int *arr, const int length)
{
    timer = 0;
    
    bool sorted = false;
    for (int forward = 1; forward < length && !sorted; forward++)
    {
        sorted = true;
        for (int i = 0; i < length - forward; i++)
        {
            int nextIndex = i + 1;
            // comparing pair of trees
            timer++;
            if (arr[i] > arr[nextIndex])
            {

                swap(arr[i], arr[nextIndex]);
                sorted = false;
            }
        }
    }
}
void partition(int *&arr, int first, int last, int &pivotIndex)
{
    int pivot = arr[first];
    int lastS1 = first;
    int firstUnknown = first + 1;
    for (; firstUnknown <= last; firstUnknown++)
    {
        // comparing pair of trees
        timer++;
        if (arr[firstUnknown] < pivot)
        {
            lastS1++;
            swap(arr[firstUnknown], arr[lastS1]);
        }
    }
    swap(arr[first], arr[lastS1]);
    pivotIndex = lastS1;
}
void quickSort(int *arr, int first, int last)
{

    
    int pivotIndex;
    
    if (first < last)
    {

        partition(arr, first, last, pivotIndex);

        quickSort(arr, first, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, last);
    }
}

int *generate_random_array(int size)
{
    srand((unsigned int)time(NULL));
    int *random_arr = new int[size];
    for (int i = 0; i < size; i++)
    {
        random_arr[i] = rand();
    }
    return random_arr;
}

int *generate_almost_sorted_array(int size)
{
    srand((unsigned int)time(NULL));
    int *random_array = generate_random_array(size);

    bubbleSort(random_array, size);
    timer = 0;

    int swap_count = size * 0.03;
    if (swap_count == 0)
    {
        swap_count = 1;
    }
    for (int i = 0; i < swap_count; i++)
    {
        int first_index = rand() % size;
        int second_index = size - first_index;
        int temp = random_array[first_index];
        random_array[first_index] = random_array[second_index];
        random_array[second_index] = temp;
    }
    return random_array;
}
// THIS ALGORITHM IS FOR TASK3 SIMULATING 2 WORKERS WORKING ON DIFFERENT BRANCHES. EACH WORKER HAS UNIQUE DURATION, THAT IS USED FOR COST CALCULATION.
void partition(int *&arr, int first, int last, int &pivotIndex, int &timerWorker)
{
    int pivot = arr[first];
    int lastS1 = first;
    int firstUnknown = first + 1;
    for (; firstUnknown <= last; firstUnknown++)
    {
        timerWorker++;
        if (arr[firstUnknown] < pivot)
        {
            lastS1++;
            timerWorker+=15;
            swap(arr[firstUnknown], arr[lastS1]);
        }
    }
    timerWorker+=15;
    swap(arr[first], arr[lastS1]);
    pivotIndex = lastS1;
}

void quickSort2(int *arr, int first, int last, int &timerWorker)
{
    if (first < last)
    {
        int pivotIndex;
        partition(arr, first, last, pivotIndex, timerWorker);

        quickSort2(arr, first, pivotIndex - 1, timerWorker);
        quickSort2(arr, pivotIndex + 1, last, timerWorker);
    }
}
//NOTE! TO TEST FUNCTIONALITY AND RUN SIMULATIONS, I COMMENTED OUT CODES BELOW INSTEAD OF CREATING MULTIPLE CPP FILES.
int main()
{

    // int *truck1 = generate_random_array(8);
    // int *truck2 = generate_random_array(16);
    // int *truck3 = generate_random_array(32);
    // int *truck4 = generate_random_array(64);
    // int *truck5 = generate_random_array(128);
    // int *truck6 = generate_random_array(256);
    // int *truck7 = generate_random_array(512);
    // int *truck8 = generate_random_array(1024);
    // int *truck9 = generate_random_array(2048);
    // int *truck10 = generate_random_array(4096);

    // int *truck1 = generate_almost_sorted_array(8);
    // int *truck2 = generate_almost_sorted_array(16);
    // int *truck3 = generate_almost_sorted_array(32);
    // int *truck4 = generate_almost_sorted_array(64);
    // int *truck5 = generate_almost_sorted_array(128);
    // int *truck6 = generate_almost_sorted_array(256);
    // int *truck7 = generate_almost_sorted_array(512);
    // int *truck8 = generate_almost_sorted_array(1024);
    // int *truck9 = generate_almost_sorted_array(2048);
    // int *truck10 = generate_almost_sorted_array(4096);

    // insertionSort(truck1, 8);
    // cout << "Total duration for insertion sort for size " << 8 << " is " << timer << endl;
    // insertionSort(truck2, 16);
    // cout << "Total duration for insertion sort for size " << 16 << " is " << timer << endl;
    // insertionSort(truck3, 32);
    // cout << "Total duration for insertion sort for size " << 32 << " is " << timer << endl;
    // insertionSort(truck4, 64);
    // cout << "Total duration for insertion sort for size " << 64 << " is " << timer << endl;
    // insertionSort(truck5, 128);
    // cout << "Total duration for insertion sort for size " << 128 << " is " << timer << endl;
    // insertionSort(truck6, 256);
    // cout << "Total duration for insertion sort for size " << 256 << " is " << timer << endl;
    // insertionSort(truck7, 512);
    // cout << "Total duration for insertion sort for size " << 512 << " is " << timer << endl;
    // insertionSort(truck8, 1024);
    // cout << "Total duration for insertion sort for size " << 1024 << " is " << timer << endl;
    // insertionSort(truck9, 2048);
    // cout << "Total duration for insertion sort for size " << 2048 << " is " << timer << endl;
    // insertionSort(truck10, 4096);
    // cout << "Total duration for insertion sort for size " << 4096 << " is " << timer << endl;

    // selectionSort(truck1, 8);
    // cout << "Total duration for selection sort for size " << 8 << " is " << timer << endl;
    // selectionSort(truck2, 16);
    // cout << "Total duration for selection sort for size " << 16 << " is " << timer << endl;
    // selectionSort(truck3, 32);
    // cout << "Total duration for selection sort for size " << 32 << " is " << timer << endl;
    // selectionSort(truck4, 64);
    // cout << "Total duration for selection sort for size " << 64 << " is " << timer << endl;
    // selectionSort(truck5, 128);
    // cout << "Total duration for selection sort for size " << 128 << " is " << timer << endl;
    // selectionSort(truck6, 256);
    // cout << "Total duration for selection sort for size " << 256 << " is " << timer << endl;
    // selectionSort(truck7, 512);
    // cout << "Total duration for selection sort for size " << 512 << " is " << timer << endl;
    // selectionSort(truck8, 1024);
    // cout << "Total duration for selection sort for size " << 1024 << " is " << timer << endl;
    // selectionSort(truck9, 2048);
    // cout << "Total duration for selection sort for size " << 2048 << " is " << timer << endl;
    // selectionSort(truck10, 4096);
    // cout << "Total duration for selection sort for size " << 4096 << " is " << timer << endl;

    // bubbleSort(truck1, 8);
    // cout << "Total duration for bubble sort for size " << 8 << " is " << timer << endl;
    // bubbleSort(truck2, 16);
    // cout << "Total duration for bubble sort for size " << 16 << " is " << timer << endl;
    // bubbleSort(truck3, 32);
    // cout << "Total duration for bubble sort for size " << 32 << " is " << timer << endl;
    // bubbleSort(truck4, 64);
    // cout << "Total duration for bubble sort for size " << 64 << " is " << timer << endl;
    // bubbleSort(truck5, 128);
    // cout << "Total duration for bubble sort for size " << 128 << " is " << timer << endl;
    // bubbleSort(truck6, 256);
    // cout << "Total duration for bubble sort for size " << 256 << " is " << timer << endl;
    // bubbleSort(truck7, 512);
    // cout << "Total duration for bubble sort for size " << 512 << " is " << timer << endl;
    // bubbleSort(truck8, 1024);
    // cout << "Total duration for bubble sort for size " << 1024 << " is " << timer << endl;
    // bubbleSort(truck9, 2048);
    // cout << "Total duration for bubble sort for size " << 2048 << " is " << timer << endl;
    // bubbleSort(truck10, 4096);
    // cout << "Total duration for bubble sort for size " << 4096 << " is " << timer << endl;

    // quickSort(truck1, 0, 7);
    // cout << "Total duration for quick sort for size " << 8 << " is " << timer << endl;
    // quickSort(truck2, 0, 15);
    // cout << "Total duration for quick sort for size " << 16 << " is " << timer << endl;
    // quickSort(truck3, 0, 31);
    // cout << "Total duration for quick sort for size " << 32 << " is " << timer << endl;
    // quickSort(truck4, 0, 63);
    // cout << "Total duration for quick sort for size " << 64 << " is " << timer << endl;
    // quickSort(truck5, 0, 127);
    // cout << "Total duration for quick sort for size " << 128 << " is " << timer << endl;
    // quickSort(truck6, 0, 255);
    // cout << "Total duration for quick sort for size " << 256 << " is " << timer << endl;
    // quickSort(truck7, 0, 511);
    // cout << "Total duration for quick sort for size " << 512 << " is " << timer << endl;
    // quickSort(truck8, 0, 1023);
    // cout << "Total duration for quick sort for size " << 1024 << " is " << timer << endl;
    // quickSort(truck9, 0, 2047);
    // cout << "Total duration for quick sort for size " << 2048 << " is " << timer << endl;
    // quickSort(truck10, 0, 4095);
    // cout << "Total duration for quick sort for size " << 4096 << " is " << timer << endl;
    // Assuming truckX arrays are already defined and filled with data

    // quickSort2(truck2, 0, 3, timerWorker1);
    // quickSort2(truck2, 4, 7, timerWorker2);
    // cout<< "Duration for worker 1 :" << timerWorker1<< endl;
    // cout<<"Duration for worker 2:" << timerWorker2<< endl;

    // timerWorker1 = 0;
    // timerWorker2 = 0;

    // quickSort2(truck2, 0, 7, timerWorker1);
    // quickSort2(truck2, 8, 15, timerWorker2);
    // cout<< "Duration for worker 1 :" << timerWorker1<< endl;
    // cout<<"Duration for worker 2:" << timerWorker2<< endl;

    // timerWorker1 = 0;
    // timerWorker2 = 0;
    
    // quickSort2(truck3, 0, 15, timerWorker1);
    // quickSort2(truck3, 16, 31, timerWorker2);
    // cout<< "Duration for worker 1 :" << timerWorker1<< endl;
    // cout<<"Duration for worker 2:" << timerWorker2<< endl;

    // timerWorker1 = 0;
    // timerWorker2 = 0;
    
    // quickSort2(truck4, 0, 31, timerWorker1);
    // quickSort2(truck4, 32, 63, timerWorker2);
    // cout<< "Duration for worker 1 :" << timerWorker1<< endl;
    // cout<<"Duration for worker 2:" << timerWorker2<< endl;

    // timerWorker1 = 0;
    // timerWorker2 = 0;

    // quickSort2(truck5, 0, 63, timerWorker1);
    // quickSort2(truck5, 64, 127, timerWorker2);
    // cout<< "Duration for worker 1 :" << timerWorker1<< endl;
    // cout<<"Duration for worker 2:" << timerWorker2<< endl;

    // timerWorker1 = 0;
    // timerWorker2 = 0;
  
    // quickSort2(truck6, 0, 127, timerWorker1);
    // quickSort2(truck6, 128, 255, timerWorker2);
    // cout<< "Duration for worker 1 :" << timerWorker1<< endl;
    // cout<<"Duration for worker 2:" << timerWorker2<< endl;

    // timerWorker1 = 0;
    // timerWorker2 = 0;

    // quickSort2(truck7, 0, 255, timerWorker1);
    // quickSort2(truck7, 256, 511, timerWorker2);
    // cout<< "Duration for worker 1 :" << timerWorker1<< endl;
    // cout<<"Duration for worker 2:" << timerWorker2<< endl;

    // timerWorker1 = 0;
    // timerWorker2 = 0;

    // quickSort2(truck8, 0, 511, timerWorker1);
    // quickSort2(truck8, 512, 1023, timerWorker2);
    // cout<< "Duration for worker 1 :" << timerWorker1<< endl;
    // cout<<"Duration for worker 2:" << timerWorker2<< endl;

    // timerWorker1 = 0;
    // timerWorker2 = 0;

    // quickSort2(truck9, 0, 1023, timerWorker1);
    // quickSort2(truck9, 1024, 2047, timerWorker2);
    // cout<< "Duration for worker 1 :" << timerWorker1<< endl;
    // cout<<"Duration for worker 2:" << timerWorker2<< endl;

    // timerWorker1 = 0;
    // timerWorker2 = 0;
    
    // quickSort2(truck10, 0, 2047, timerWorker1);
    // quickSort2(truck10, 2048, 4095, timerWorker2);
    // cout<< "Duration for worker 1 :" << timerWorker1<< endl;
    // cout<<"Duration for worker 2:" << timerWorker2<< endl;


    return 0;
>>>>>>> d31cd898ec1b48b67a2f0f52e80fbb0a87770448
}