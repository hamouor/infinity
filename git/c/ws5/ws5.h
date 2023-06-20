#ifndef __WS5_H__
#define __WS5_H__

void PrintThisInt(int val);
/*establishes an array of structs int and printing function and uses its construct to print the int*/
void ThePrintMe();
/*recieves a string of file name and requests operation from user. defaults to append*/
int Interact(char* file_name);
/*prepend string to file. must recieve a string longer than 1*/
int Prepend(char* file_name, char* dataToPrepend);
/*returns a value causing interact to leave the program*/
int Exit(char* file_name, char* dataToAppend);
/*counts the number of lines in a file*/
int Count(char* file_name, char* dataToAppend);
/*removes file by file name*/
int Rem(char* file_name, char* dataToAppend);
/*appends string to file*/
int Append(char* file_name, char* dataToAppend);
/*requests user to enter file name and sends it to interact*/
void EnterFile();

#endif
