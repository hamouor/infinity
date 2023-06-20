#ifndef __DHCP_H__
#define __DHCP_H__

/******************************************************************************/
/*  		                        DHCP	            		              */
/******************************************************************************/
/*******************************************************************************
* DESCRIPTION:  Dynamic Host Configuration Protocol
                A network management protocol used to automate the process
                of configuring devices on IP networks 
* AUTHOR: Batman
* REVIEWER: Bruce Wayne
* DATE: 12/06/2022
* VERSION: 0.0.3
*******************************************************************************/

#include <stddef.h> /* size_t */



enum {
	A,
    B,
    C,
    D,
	NUM_PARTS
};

typedef enum {
	SUCCESS,
	ALLOCATION_FAILED,
	IS_FULL,
	BAD_IP
} ERROR_TY;

typedef struct dhcp dhcp_ty;

typedef struct ip
{
    char ip[NUM_PARTS];
} ip_ty;

/* To C */


/********/

/*******************************************************************************
* Function:     Creates a DHCP
* Arguments:    An array that represents the subnet ID mask
* Return value: A pointer to the dhcp; NULL on failure.
* Notes:		Complexity - O(1).
*******************************************************************************/
dhcp_ty *DHCPCreate(const ip_ty subnet);

/*******************************************************************************
* Function:     Destroy a DHCP
* Arguments:    Pointer to DHCP type
* Notes:		Complexity - O(n).
*******************************************************************************/
void DHCPDestroy(dhcp_ty *dhcp);

/*******************************************************************************
* Function:     Allocates the requested IP by the user if it is available, 
*               otherwise allocates the next IP address avilable if there is one.
* Arguments:    A pointer to DHCP, An array for the return ip and an array for
				an\ requested ip(optional)
* Return value: ERROR_TY return value according to the error(or SUCCESS)
* Notes:		Complexity - O(log(n))
*******************************************************************************/
ERROR_TY DHCPAllocateIP(dhcp_ty *dhcp, ip_ty *return_ip, const ip_ty host);

/*******************************************************************************
* Function:     Frees an IP address
* Arguments:    dhcp type, IP type
* Return value: ERROR_TY return value according to the error(or SUCCESS)
* Notes:		Complexity - O(log(n)). 
*******************************************************************************/
ERROR_TY DHCPFree(dhcp_ty *dhcp, const ip_ty ip);

/*******************************************************************************
* Function:     counts the number of free adresses
* Arguments:   	A dhcp.
* Return value: the number of free adresses
* Notes:		Complexity - O(n). undefined behaviour if dhcp doesn't exist
*******************************************************************************/
size_t DHCPCountFree(const dhcp_ty *dhcp);


#endif      /* __DHCP_H__ */
