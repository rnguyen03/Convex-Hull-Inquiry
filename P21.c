#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define NUM_ELEMENTS 30000
#define MAX_EXTREME 150

//Object to hold x and y values
typedef struct point {
    double x;
    double y;
} Point;

void loadObjects(Point* hull); //Load data into an array of point objects
void generateHull(Point* list, Point* hull, int* size); //Finds and stores the extreme points
void cclockWiseHullSort(Point* hull, int size); //Sorts the extreme points of the hull (counter-clockwise)
int xpointCMP(const void* a, const void* b); //Helper function to help compare x values between two points
void displayHull(Point hull[], int size); //Displays the list of extreme points of the convex hull (counter-clockwise)
void userMenu(Point* hull, int* pt1, int* pt2, int size); //Prompts user for input, and saves the user's choice 
void findShortestPath(Point* hull, int start, int end, int size); //Calculate and display shortest path of convex hull
double distance(Point p1, Point p2); //Return the distance between two points

int main(int argc, char* argv[]) {
    clock_t begin; //Declare time variable for begin
    clock_t end; //Declare time variable for end
    int size = 0; //Declare size variable
    Point* points = (Point*)malloc(sizeof(Point) * NUM_ELEMENTS); //Allocate size of array
    Point* hull = (Point*)malloc(sizeof(Point) * MAX_EXTREME); //Initialize hull array
    int choice1 = -1; //Declare user choice 1 variable
    int choice2 = -1; //Declare user choice 2 variable

    loadObjects(points); //Load objects in array
    
    begin = clock(); //Begin clock
    generateHull(points, hull, &size); //Generate convex hull
    end = clock(); //End clock

    free(points); //Free array after generating hull
    double time = ((double)end - begin) / CLOCKS_PER_SEC * 1000; //Convert time to milliseconds
    cclockWiseHullSort(hull, size); //Sort the extreme points into a hull
    displayHull(hull, size); //Display Hull to user
    printf("Execution Time: %f ms\n", time);
    userMenu(hull, &choice1, &choice2, size); //Prompt user input

    findShortestPath(hull, choice1, choice2, size); //Find and display shortest path of convex hull

    free(hull); //Free hull
    return 0;
}

//Load points from file and copy into point object array
void loadObjects(Point* list) {
    FILE* pfile; //Initialize file pointer
    pfile = fopen("data_A2_Q2.txt", "r"); //Open data file

    //Return if there's an error
    if (pfile == NULL) {
        printf("\nError can't open %s\n", "data A2 Q1.txt"); //Display user error message
        return;
    }

    for (int i = 0; i < NUM_ELEMENTS; i++) {
        list[i].x = 0.0; //initialize x value
        list[i].y = 0.0; //initialize y value
        fscanf(pfile, "%lf %lf", &list[i].x, &list[i].y); //read in the values into their respective object and member
    }

    fclose(pfile); //Close file
}

//Create list of extreme points from a list of points
void generateHull(Point* points, Point* hull, int* length) {
    int size = 0;
    for (int i = 0; i < NUM_ELEMENTS; i++) {
        for (int j = 0; j < NUM_ELEMENTS; j++) {
            int left = 0; //Initialize left counter
            int right = 0; //Initialize right counter
            double a = points[j].y - points[i].y; //y2 - y1
            double b = points[i].x - points[j].x; //x1 - x2
            double c = (points[i].x * points[j].y) - (points[j].x * points[i].y); //(x1 - y2) * (x2 - y1)

            for (int k = 0; k < NUM_ELEMENTS; k++) {
                if (k == i || k == j) {
                    continue;
                }
                double side = (a * points[k].x) + (b * points[k].y); //Calculate the side the point is one
                if (side < c) {
                    left = 1; //Side is less than c set left variable
                }
                if (side == c) {
                    left = 1; //C is equal to side, set both and break
                    right = 1;
                    break;
                }
                else {
                    right = 1; //Else set right side
                }
                if (left == right) {
                    //Not an edge
                    break;
                }
            }

            if (left != right) {
                hull[size] = points[i];
                size++;
            }

        }
    }
    *length = size;
}

//Sort extreme points counter-clockwise.
void cclockWiseHullSort(Point* hull, int size) {
    Point* buffer = (Point*)malloc(sizeof(Point) * size); //allocate memory for buffer
 
    //Copy values into temp array
    for (int i = 0; i < size; i++) {
        buffer[i] = hull[i];
    }
    int leftPTR = 0; //Set left pointer
    int rightPTR = size - 1; //Set right pointer

    qsort(buffer, size, sizeof(Point), xpointCMP); //Sort points by x value in ascending order

    Point point1 = buffer[0]; //Take the point with smallest x-value
    Point point2 = buffer[size - 1]; //Take the point with the largest value

    //Create a line using the two points, then iterate through the array. If the point is above the line place it in the front
    //If the point is below, place it behind.
    for (int i = 0; i < size; i++) {
        if ((buffer[i].x - point1.x) * (point2.y - point1.y) - (buffer[i].y - point1.y) * (point2.x - point1.x) > 0) {
            hull[leftPTR] = buffer[i]; //Replace point at left pointer with new value
            leftPTR++; //Move left pointer to the right
        }
        else {
            hull[rightPTR] = buffer[i]; //Replace point at right pointer with new value
            rightPTR--; //Move right pointer to the left
        }
    }
    free(buffer);
}

//Helper function for qsort. Compares two points and returns -1, 0, 1 depending on x values.
int xpointCMP(const void* a, const void* b) {
    Point* x1= (Point*)a; //Cast a as a Point
    Point* x2= (Point*)b; //Cast b as a Point
    return(x1->x > x2->x) - (x1->x < x2->x); //if x1 x-value greater return 1, if equal return 0, else -1
}

//Displays the current convex hull and numbers the points
void displayHull(Point hull[], int size) {
    printf("\nConvex Hull (counter-clockwise):\n");
    for (int i = 0; i < size; i++) {
        printf("%d. (%.1lf, %.1lf)\n", i + 1, hull[i].x, hull[i].y);
    }
    printf("%d. (%.1lf, %.1lf)\n", 1, hull[0].x, hull[0].y);
}

//Gathers user inputs and stores them in integer variables
void userMenu(Point* hull, int* pt1, int* pt2, int size) {
    int count = 0;
    int selection = -1;
    printf("\nSelect two points to find the shortest path around.\n");
    printf("To select a point, enter the corresponding index on the left.\n");
    do {
        if (count == 0) {
            printf("Select the start point: ");
        }
        else {
            printf("Select the end point: ");
        }
        scanf("%d", &selection);
        printf("\n");
        if (0 < selection && selection <= size && selection != *pt1 + 1) {
            if (selection ) {
                if (count == 0) {
                    *pt1 = selection - 1;
                }
                else {
                    *pt2 = selection - 1;
                }
                selection = -1;
                count++;
            }
        }
        else {
            printf("Invalid option, try again!\n");
        }

    } while (count < 2);
    printf("Finding the shortest path..\n");
}

//Calculates and displays the shortest path
void findShortestPath(Point* hull, int start, int end, int size) {
    int toRight = start + 1; //Pointer going rightwards of the array
    int rPrev = start; //Stores the previous value of toRight
    int toLeft = start - 1; //Pointer going leftwards of the array
    int lPrev = start; //Stores the previous value of toLeft
    double countercw = 0.0; //Distance clockwise (toRight)(++)
    double cw = 0.0; //Distnace counter clockwise (toLeft)(--)
    int rCount = 0; //Track number of points ccw
    int lCount = 0; //Track number of points cw
    Point* clockwise = (Point*)malloc(sizeof(Point) * size); //Allocate memory to track points going cw
    int* cwArr = (int*)malloc(sizeof(int) * size); //Allocate memory to track indicies of points going cw
    Point* counterclockwise = (Point*)malloc(sizeof(Point) * size); //Allocate memory to track points going ccw
    int* countercwArr = (int*)malloc(sizeof(int) * size); //Allocate memory to track indicies of points going ccw

    //Correct Indicies if out of array
    if (toLeft < 0) {
        toLeft = size - 1;
    }
    if (lPrev < 0) {
        lPrev = size - 1;
    }
    if (toRight > size - 1) {
        toRight = 0;
    }
    if (rPrev > size - 1) {
        rPrev = 0;
    }

    //Traverse the hull counter-clockwise
    while (toRight != end) {
        //If counter-clockwise pointer is out of bounds, correct it
        if (toRight > size - 1) {
            toRight = 0;
        }
        if (rPrev > size - 1) {
            rPrev = 0;
        }
        //If counter-clockwise pointer is not finished, add the next point and save relevant data
        countercw += distance(hull[rPrev], hull[toRight]);
        countercwArr[rCount] = toRight;
        counterclockwise[rCount] = hull[toRight];
        if (toRight != end) {
            rPrev++;
            toRight++;
        }
        rCount++;
    }
    countercw += distance(hull[rPrev], hull[toRight]);  //Add end distance

    //Traverse the hull clockwise
    while (toLeft != end) {
        //If clockwise pointer is out of bounds, correct it
        if (toLeft < 0) {
            toLeft = size - 1;
        }
        if (lPrev < 0) {
            lPrev = size - 1;
        }
        //If clockwise pointer is not finished, add the next point and save relevant data
        cw += distance(hull[lPrev], hull[toLeft]);
        cwArr[lCount] = toLeft;
        clockwise[lCount] = hull[toLeft];
        if (toLeft != end) {
            lPrev--;
            toLeft--;
        }
        lCount++;
    }
    cw += distance(hull[lPrev], hull[toLeft]); //Add end distance

    //Display Shortest Path
    if (cw < countercw) {
        printf("\nTHE SHORTEST PATH IS Clockwise.\n\n");
        printf("The path includes the following points:\n");
        if (lCount == 0) {
            printf("%d. %.1lf, %.1lf\n", start + 1, hull[start].x, hull[start].y); //Print start
            printf("%d. %.1lf, %.1lf\n", end + 1, hull[end].x, hull[end].y); //Print end
        }
        else {
            printf("%d. %.1lf, %.1lf\n", start + 1, hull[start].x, hull[start].y); //Print start
            for (int i = 0; i < lCount; i++) {
                printf("%d. %.1lf, %.1lf\n", cwArr[i] + 1, clockwise[i].x, clockwise[i].y); //Print Stored points
            }
            printf("%d. %.1lf, %.1lf\n", end + 1, hull[end].x, hull[end].y); //Print end
        }
    }
    else {
        printf("\nTHE SHORTEST PATH IS Counter-Clockwise.\n\n");
        printf("The path includes the following points:\n");
        if (rCount == 0) {
            printf("%d. %.1lf, %.1lf\n", start + 1, hull[start].x, hull[start].y); //Print start
            printf("%d. %.1lf, %.1lf\n", end + 1, hull[end].x, hull[end].y); //Print end
        }
        else {
            printf("%d. %.1lf, %.1lf\n", start + 1, hull[start].x, hull[start].y); //Print start
            for (int i = 0; i < rCount; i++) {
                printf("%d. %.1lf, %.1lf\n", countercwArr[i] + 1, counterclockwise[i].x, counterclockwise[i].y); //Print Stored points
            }
            printf("%d. %.1lf, %.1lf\n", end + 1, hull[end].x, hull[end].y); //Print end
        }
    }
    //Display both distances
    printf("Clockwise Distance: %.1lf\n", cw);
    printf("Counter-Clockwise Distance: %.1lf\n", countercw);

    //Free dynamically allocated arrays
    free(counterclockwise);
    free(clockwise);
    free(countercwArr);
    free(cwArr);
}

//Calculates the distance between two points
double distance(Point p1, Point p2) {
    return sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y)); //sqrt((x2 - x1)^2 + (y2 - y1)^2)
}