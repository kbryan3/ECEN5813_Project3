## PES Project Three Readme

Student Name: Kyle Bryan

##### Running Code, General description

This code is written to be run on either the FRDM board or in a Linux PC
environment.  For the FRDM board a .axf file is generated to be run with
MCUExpresso on a FRDM-KL25Z development board and for the Linux PC
a .out file is generated.  Choosing which file the user wants is done via the
makefile in the /Debug folder.  There are 4 total targets:

- fb_run: Runs memory test on FRDM board without logger on(LED flashes)
- fb_debug: fb_run plus serial output with logger outputting results via serial
- pc_run: Runs memory test on Linux machine, no logger info
- pc_debug: pc_run plus logger enabled, outputting results to terminal

When implementing the makefile, make sure you are pointing to the debug folder
as all the files are referenced under the assumption that is where the makefile
is.  When making either of the PC builds add TARGET = PC to the end of the make
command.  
e.g:

*Running on Linux machine*  
"make -r -f makefile -j8 pc_debug TARGET=PC"  
"make -r -f makefile -j8 pc_run TARGET=PC"

*Running in MCUExpresso*  
"make -r -f makefile -j8 fb_run"
"make -r -f makefile -j8 fb_debug"

##### Repository Contents
###### Source Code
*main.c*, *led_control.h*, *led_control.c*, *logger.h*,*logger.c*,
*pattern_generator.c/.h*, *memory_test.c/.h *makefile*

This project runs a set of memory tests on both the KL25Z and a linux computer.
It also contains a logger to output information during the testing, and toggles
the KL25Z LED based on success(Green)/Failure(Red) of memory test. pattern_generator
generats a pattern to write into memory, memory_test contains the function for
operating on the memory locations, led_control turns LEDs on and off, and
logger is used to print debug/runtime info to the console/terminal.

###### Extra Project Documents
*PES Project 3 Screenshot.pdf* , *UML Activity_Sequence Diagrams.pdf*, *Demo
for Project3.MOV*  

These documents are in the /.bin folder and are other(non-source code) project3
deliverables.  They include a screenshot of the outputs, UML diagrams and a Demo
video of the code running.


#### Observations for Project:
Though able to get the project to run, I feel as though I am not quite sure of
"best practices", especially with regards to returning pointers from a function.
I had some difficulty with the pointers and the locations I was getting, as well
as going from the uint32_t* to being able to affect individual bytes until doing
some further reading on the matter.  