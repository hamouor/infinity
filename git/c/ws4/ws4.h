#ifndef __WS4_H__
#define __WS4_H__

/*scanf of char entered by user. switch case of each input char to respond t for t a for a end for esc*/
void InteractSwitch();
/*scanf of char entered by user. if statement for each input char to respond t for t a for a end for esc*/
void InteractIf();
/*scanf of char entered by user. array of function pointers is searched for each input char to respond t for t a for a end for esc*/
void InteractLut();
/*function printing T for use in the function pointer array of interactlut*/
void PrintT();
/*function printing A for use in the function pointer array of interactlut*/
void PrintA();

#endif
