#ifndef __KT_H__
#define __KT_H__

/******************************************************************************/
/*  		                    KNIGHT TOUR	            		              */
/******************************************************************************/
/*******************************************************************************
* DESCRIPTION: A program that calculates a knight tour on an 8 X 8 board, when
*              the knight starts from a random position. The program returns
*              the path of the knight.
* AUTHOR: Dark knight
* REVIEWER: Knight Rider
* DATE: 15/06/2022
* VERSION: 0.0.1
*******************************************************************************/

/*******************************************************************************
* Function:     A function that moves the knight on a 8 X 8 board and visits
*               every square exactly once.
* Arguments:    An array, a starting index
* Return value: 0 for success; non-zero if timed out before reached solution

* Notes:		Complexity - O(infinity * 0).
*******************************************************************************/
#define BOARD_SIZE 64

int KnightTour(int path[BOARD_SIZE], int start_index);


#endif      /* __KT_H__ */