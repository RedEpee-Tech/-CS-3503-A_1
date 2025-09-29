# CS 3503 Assignment 2.0 (previously 1.0) - Advanced Number Base Conversion

## Author
Joseph Montalvo 

## Description
 My implementation of Owl Tech’s simple and advanced number base conversion utility.

## Build Instructions
 1 Install GCC (Use MinGW. On Linux/Mac, GCC is usually pre-installed)
 
 2 Open a terminal or command prompt in your project directory (where main.c, convert.c, and convert.h are located).
 
 3 Compile the code in GCC using the input 'gcc main.c convert.c -o main.exe' (exclude .exe if on linux/MacOS )
 
 4 Before running the code, change the input file to the desired a2_test.txt(advanced conversion) or A1_inputs.txt(simple conversion) file
 
 4 Run the code using main.exe (make sure a2_test.txt is included if testing advanced conversion. Use A1_inputs.txt to test simple base conversions)
 
 5 Once the test results are run, they will be added to outputs.txt 

## Test Results
 If done correctly, the outputs.txt should state near the bottom:
 
  For A1_inputs.txt(simple conversion):
  "Summary:100/100 PASSED"
  
  For a2_test.txt(advanced conversion):
  "Summary:51/51 PASSED"
  
## Notes
Since this code is in a low-level language (C), understanding how char and uint32_t work in C instead of a standard int/char in c++ or java took a while to understand. Understanding them ended up being key to using C. Also, learning how low-level computing treats numbers is important for creating both simple and advanced number base conversions.
