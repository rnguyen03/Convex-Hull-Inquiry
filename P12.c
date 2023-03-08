#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void loadObjects(int* array); //Opens data file and loads contents into array
int mergeSort(int array[], int buffer[], int left, int right); //Partitions the array into subarrays and calls itself recursively to execute mergesort
int merge(int array[], int buffer[], int left, int mid, int right); //merges sorted subarrays and counts the inversions

int main(int argc, char* argv[]) {
    clock_t begin; //Declare time variable for begin
    clock_t end; //Declare time variable for end
    int* array = (int*)malloc(sizeof(int) * 50000); //Allocate size of array
    int* buffer = (int*)malloc(sizeof(int) * 50000); //Dynamically allocate a buffer array

    loadObjects(array); //Load objects in array

    begin = clock(); //Begin clock
    int count = mergeSort(array, buffer, 0, 50000 - 1); //Call sort to count inversions
    end = clock(); //End clock
    
    double time = ((double)end - begin) / CLOCKS_PER_SEC * 1000; //Convert time to milliseconds
    printf("Inversion count is %d \n", count);  //Print count
    printf("Execution Time: %f ms\n", time); //Display execution time

    free(array); //Free array
    free(buffer); //Free buffer
    return 0;
}

void loadObjects(int* array) {
    FILE* pfile; //Initialize file pointer
    pfile = fopen("data_A2_Q1.txt", "r"); //Open data file

    //Return if there's an error
    if (pfile == NULL) {
        printf("\nError can't open %s\n", "data A2 Q1.txt"); //Display user error message
        return;
    }

    for (int i = 0; i < 50000; i++) {
        fscanf(pfile, "%d", &array[i]); //Read in all 50000 integers
    }

    fclose(pfile); //Close file
}

int mergeSort(int array[], int buffer[], int left, int right) {
    int mid = 0; //initialize midpoint
    int count = 0; //initialize count
    if (left < right) {
        mid = left + (right - left) / 2; //Calculate midpoint minimizing integer overflow
        //Divide the subarray in half
        count += mergeSort(array, buffer, left, mid); //Recuresively sort/count left side
        count += mergeSort(array, buffer, mid + 1, right); //Recuresively sort/count right side
        //Merge both sorted subarrays
        count += merge(array, buffer, left, mid + 1, right);//Sort the merge/collect the count
    }
    return count; //Return the amount of inversions
}


int merge(int array[], int buffer[], int left, int mid, int right) {
    int count = 0;

    int i = left; //Set iterator variable for array equal to left 
    int j = mid; //Set iterator variable for array equal to middle
    int k = left; //Set iterator variable for buffer equal to left

    //Break loop if left pointer is greater than middle value or right pointer is greter than right value
    //if either subarray is finished iterating
    while ((i <= mid - 1) && (j <= right)) {

        if (array[i] <= array[j]) {
            //if left pointer value is smaller or equal to right pointer value then store the value in the buffer
            buffer[k++] = array[i++];
        }
        else {
            //store the value in buffer
            buffer[k++] = array[j++];
            //increment the count by (mid - i) because the arrays are sorted so once a[i] < a[j], the rest are inversions
            count = count + (mid - i);
        }
    }

    //Copy any leftover elements of left subarray to the buffer
    while (i <= mid - 1) {
        buffer[k++] = array[i++];
    }

    //Copy any leftover elements of right subarray to the buffer
    while (j <= right) {
        buffer[k++] = array[j++];
    }

    //Copy sorted buffer back to the original array
    for (i = left; i <= right; i++) {
        array[i] = buffer[i];
    }

    return count; //Return the count
}