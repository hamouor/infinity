#include <stdio.h>
#include <string.h>

#include <stdlib.h>

#include "dhcp.h"

typedef unsigned char uchar;

typedef enum {
	YAY,
	NAY
} state;

static state TestingGrounds();
static void PrintIp(ip_ty ip);
static void CreateIp(ip_ty *ip, uchar AA, uchar BB, uchar CC, uchar DD);
static int IpVersusIp(ip_ty soul, ip_ty mate);


int main()
{
	state WasIGoodDaddy = YAY;

	WasIGoodDaddy += TestingGrounds();


	if(!WasIGoodDaddy)
	{
		printf("Congratulation on passing the tests. Please reffer to the kitchen area for a cookie\n");
	}

	return WasIGoodDaddy;
}


static state TestingGrounds()
{
	ip_ty subnet_ip;
	ip_ty host_ip, host_ip2, host_ip3;
	ip_ty return_ip, check_ip;
	state status = YAY;
	dhcp_ty *dhcp = NULL;
	unsigned char AA = 193, BB = 172, CC = 9, DD = 0, EE = 1;
	CreateIp(&subnet_ip, AA, BB, DD, DD);
	CreateIp(&host_ip, AA, BB, DD, DD);
	CreateIp(&check_ip, AA, BB, DD, EE);
	CreateIp(&host_ip2, AA, BB, CC, DD);
	CreateIp(&host_ip3, DD, DD, DD, DD);
	CreateIp(&return_ip, DD, DD, DD, DD);

	dhcp = DHCPCreate(subnet_ip);
	if(!dhcp)
	{
		printf("Failed to create DHCP");
		status = NAY;
	}

	if(DHCPCountFree(dhcp) != 65533)
	{
		printf("Size is not 65022 as it should be. did allocate the static ips? got: %ld\n", DHCPCountFree(dhcp));
		status = NAY;
	}

	/* Check if we send x.x.x.0 that we recieve x.x.x.1 */
	DHCPAllocateIP(dhcp, &return_ip, host_ip);
	if(IpVersusIp(return_ip, check_ip))
	{
		printf("Didn't get the right IP address. got: ");
		PrintIp(return_ip);
		printf("Expected: ");
		PrintIp(check_ip);
		status = NAY;
	}


	/* Check if we send x.x.9.0 that we recieve x.x.9.0 */
	DHCPAllocateIP(dhcp, &return_ip, host_ip2);
	if(IpVersusIp(return_ip, host_ip2))
	{
		printf("Didn't get the right IP address. got: ");
		PrintIp(return_ip);
		printf("Expected: ");
		PrintIp(host_ip2);
		status = NAY;
	}
	
	if(DHCPCountFree(dhcp) != 65531)
	{
		printf("Size has not updated after allocating 2 IPS\n");
		status = NAY;
	}
	
	/* Check if we freed x.x.9.0 */
	if(DHCPFree(dhcp, return_ip))
	{
		printf("Failed to free IP");
		status = NAY;
	}

	/* Check if we failed to free x.x.9.0 again */
	if(!DHCPFree(dhcp, return_ip))
	{
		printf("Didn't fail to free a free IP");
		status = NAY;
	}

	/* Check if we failed to free x.x.0.0 */
	if(!DHCPFree(dhcp, host_ip3))
	{
		printf("Didn't fail to free a saved IP");
		status = NAY;
	}

	if(DHCPCountFree(dhcp) != 65533)
	{
		printf("Size has not updated after freeing 1 IP\n");
		status = NAY;
	}

	DHCPDestroy(dhcp);


	return status;
}

static void CreateIp(ip_ty *ip, uchar AA, uchar BB, uchar CC, uchar DD)
{
	ip->ip[A] = AA;
	ip->ip[B] = BB;
	ip->ip[C] = CC;
	ip->ip[D] = DD;
}

static int IpVersusIp(ip_ty soul, ip_ty mate)
{
	int are_we_soul_mates = 0;
	are_we_soul_mates += (soul.ip[A] != mate.ip[A]);
	are_we_soul_mates += (soul.ip[B] != mate.ip[B]);
	are_we_soul_mates += (soul.ip[C] != mate.ip[C]);
	are_we_soul_mates += (soul.ip[D] != mate.ip[D]);

	return are_we_soul_mates;
}

static void PrintIp(ip_ty ip)
{
	int i = 0;
	for(i = 0; i < NUM_PARTS; ++i)
	{
		i == NUM_PARTS - 1 ? printf("%d", ip.ip[i]) : printf("%d.", ip.ip[i]);
	}
	printf("\n");
}