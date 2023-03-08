# ALOGRITHM ANALYSIS
**Author:** Ryan Nguyen  

## About
Each file contains a program that corresponds to the respective assignment questions/requirements. `P11`/`P12` count the number of inversions required in a given data file. `P21`/`P22` solve the convex hull problem and calculate the shortest path around.  

## To Compile
1. Run `make all` in the command line  
2. Then run each respective file using `./FILE`  
   (Ex) `./P21`  

## P11.c Analysis
This program counts the amount of conversions in a data file. It takes a brute force approach and is very similar to bubble sort. This program loads the data into an array and then counts the inversions. The output should be as follows (time will obviously vary):  
Inversion count is 623897407
Execution Time: 4640.625000 ms

## P12.c Analysis
This program counts the amount of conversions in a data file. It takes a divide and conquer approach and is very similar to merge sort. This program loads the data into an array and then counts the inversions. The output should be as follows (time will obviously vary):
Inversion count is 623897407
Execution Time: 15.625000 ms

## P21.c Analysis
This program solves the convex hull problem. It takes a brute force approach. The first step is to load in the data into the respective objects (point array). Then the extreme points are found using triple nested loops, and then sorted into a convex hull going counter-clockwise. Then the program should display the following (more description after):  
Convex Hull (counter-clockwise):

1. (122.9, 621.9)
2. (145.7, 517.0)
3. (272.6, 240.1)
4. (1156.3, 24.3)
5. (3943.7, 32.0)
6. (5616.9, 37.6)
7. (6265.4, 73.0)
8. (6434.5, 1065.1)
9. (6416.4, 3607.9)
10. (6382.1, 5517.2)
11. (6163.4, 6092.8)
12. (5961.6, 6274.5)
13. (5561.2, 6328.5)
14. (4336.6, 6384.0)
15. (3839.0, 6397.2)
16. (2238.7, 6426.4)
17. (1769.3, 6414.2)
18. (484.1, 6266.3)
19. (128.3, 6091.3)
20. (120.9, 6008.0)
21. (30.8, 3064.0)
22. (28.3, 1205.6)
23. (122.9, 621.9)
Execution Time: 25500.000000 ms

Select two points to find the shortest path around. To select a point, enter the corresponding index on the left.  

Select the start point:  

As usual the time may vary. After that, the user is prompted to