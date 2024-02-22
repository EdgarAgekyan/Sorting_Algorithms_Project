This program works with four different types of sorting algorithms, the Quick Sort, Heap Sort, Shell Sort, and Batcher Sort algorithms. To run this program, first compile by running the Makefile, which can be done by typing "make all" into the terminal. Then run the created executable with -H. "./sorting -H" This will print out a menu that shows how a user can interact with the program. <br/>

Files:<br/>
batcher.c - batcher sort implementation<br/>
batcher.h - header file<br/>
shell.c - shell sort implementation<br/>
shell.h - header file<br/>
gaps.h - includes gaps array to be used with shell sort<br/>
heap.c - heap sort implementation<br/>
heap.h. - header file<br/>
quick.c - quick sort implementation<br/>
quick.h - header file<br/>
set.c - function implementations to work with created Sets data type<br/>
set.h - header file<br/>
stats.c - statistics functions used for manipulating and gathering data<br/>
stats.h - header file<br/>
sorting.c - implements main function to call algorithms; this is where the menu is created for the user to interact with.<br/>
