#include<stdlib.h> /*system*/
#include<string.h>/*strcmp*/

#include "ws4.h"
#include "ws4.c"

int main(int argc, char *funcname[]) /*funcname will house the users selection of implementing function*/
{
	system("stty -icanon -echo"); /*prevents screen echo of user pressed keys*/
	if (strcmp((*(funcname+1)), "if")) /*comparing the users selection of function to our menue*/
	{
		InteractIf();
	}
	if (strcmp((*(funcname+1)), "switch"))
	{
		InteractSwitch();
	}
	if (strcmp((*(funcname+1)), "lut"))
	{
		InteractLut();
	}		
	system("stty icanon echo"); /*un-prevents screen echo of user pressed keys*/
	return 0;
}

