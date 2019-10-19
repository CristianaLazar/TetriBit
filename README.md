#Tetribit - homework 1
##Description
This program is a simplified variant of the classic Tetris game. Tetribit was
realized with bitwise operations, so the map, the pieces, the transformations 
applied on the pieces are bitwise operations. For an easier implementation,
the pieces cannot be rotated by user, they can be only moved right and left.
##Dependencies
 * <stdio.h> - Defines core input and output functions
 
 * <stdlib.h> - Defines numeric conversion functions, pseudo-random numbers 
 generation functions, memory allocation, process control functions
 
 * <math.h> -  	Defines common mathematical functions. 
 
 * <stdint-gcc.h>
 
 ##Table of content
 1. [Installation instructions](#introduction)
 2. [Operating instructions](#operating)
    1. [Starting the program](#starting)
    2. [Running the program](#running)
       1. [Generating the game map](#generating)
       2. [Enter the number of pieces](#number)
       3. [Enter the pieces](#pieces)
 
 ## Installation instructions <a name="introduction"></a>
 Clone or download the repository.
 ## Operating instructions <a name="operating"></a>
 ###Starting the program <a name="starting"></a>
 In current folder open a terminal and run the Makefile with *make build* command
 to generate the executable (tetribit) and *make run* command to run the executable.
 ###Running the program <a name="running"></a>
 ####Generating the game map <a name="generating"></a>
 Enter an number smaller that 18446744073709551615 
 (number whose 64-bit binary representation will have all bits equal to one).
 This number represent the map, the bits equal with 1 are occupied zones and 
 bits equal with 0 are empty zones. 
 ####Enter the number of pieces <a name="number"></a>
 Enter an int number *M*, what represent the number of pieces.
 ####Enter the pieces<a name="number"></a>
 Enter *M* unsigned long long numbers, what represent the pieces.
 
 Examples of pieces:
            
            1. ****#*** = 8
            
            2. ******## = 3
            
            3. ****#*** = 2056
               ****#***
            
            4. ****##** = 3084
               ****##** 
             
            5. ***#**** = 2072
               **##****
               
            6. ***#**** = 4120
               ***##***
               
            7. ***##*** = 6160
               ***#****	
               
            8. ***##*** = 6152
               ****#***	
              
 
 Enter 8 numbers what represent the transformations applied 
 on the pieces. Every pieces is succeeded by these 8 numbers.
 These numbers can be both positive and negative. Thus, a positive number will
 generate a right move and a negative number a left move, but without going over
 the game board. After each transformation, the piece will automatically descend 
 with one row (that is as long as there is no collision, in this case the piece
 will stop and all the other transformations will be ignored).
 
##Files
Contains a C file (Tetribit.c) and a MAKEFILE file.
       