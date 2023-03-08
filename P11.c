#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void loadObjects(int* array); //Opens data file and loads contents into array
int bForce(int array[], int size); //Uses bubble sort to count conversions

int main(int argc, char* argv[]) {
	clock_t begin; //Declare time variable for begin
	clock_t end; //Declare time variable for end

	int* array = (int*)malloc(sizeof(int) * 50000); //Allocate size of array
	loadObjects(array); //Load objects in array

	begin = clock(); //Begin clock
	int count = bForce(array, 50000); //Call sort to count inversions
	end = clock(); //End clock

	double time = ((double)end - begin) / CLOCKS_PER_SEC * 1000; //Convert time to milliseconds
	printf("Inversion count is %d \n", count); //Print count
	printf("Execution Time: %f ms\n", time); //Display execution time

	free(array); //Free array
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

int bForce(int array[], int size) {
	int count = 0; //Initialize count
	//Iterate through the array from the beginning
	for (int i = 0; i < size - 1; i++) {
		//Iterate through every other element starting from i + 1
		for (int j = i + 1; j < size; j++) {
			if (array[i] > array[j]) {
				count++; //Increment count if there's an inversion
			}
		}
	}
	return count; //Return count
}
