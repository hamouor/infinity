#include <stdlib.h>     /* malloc, free */
#include <assert.h>     /* assert       */
#include <math.h>       /*pow           */

#include"dhcp.h"
#include"trie.h"

#define BITS_IN_CHAR 8


enum {
	ZERO,
	ONE,
	NUM_BITS
};


struct dhcp
{
    trie_ty *trie; 
    ip_ty subnet;
};


static void CopyIp(ip_ty *a, ip_ty b);


dhcp_ty *DHCPCreate(const ip_ty subnet)
{
    dhcp_ty *new_dhcp = NULL;
    trie_ty *new_trie = NULL;
    ip_ty ip0 = {{0,0,0,0}}, ipl = {{0,0,0,255}}, ipl2 = {{0,0,0,254}}, return_ip;
    int i = 0;

    for(; NUM_PARTS > i; ++i)
    {
        if(!subnet.ip[i])
        {
            break;
        }
    }
    new_trie = TrieCreate((NUM_PARTS - i) * BITS_IN_CHAR);

    if(!new_trie)
    {
        return NULL;
    }

    new_dhcp = (dhcp_ty*)malloc(sizeof(dhcp_ty));

    if(!new_dhcp)
    {
        TrieDestroy(new_trie);
        return NULL;
    }

    new_dhcp->trie = new_trie;
    new_dhcp->subnet = subnet;
    DHCPAllocateIP(new_dhcp, &return_ip, ip0);
    DHCPAllocateIP(new_dhcp, &return_ip, ipl);
    DHCPAllocateIP(new_dhcp, &return_ip, ipl2);

    return new_dhcp;
}

void DHCPDestroy(dhcp_ty *dhcp)
{
    assert(dhcp);

    TrieDestroy(dhcp->trie);

    free(dhcp);
}

ERROR_TY DHCPAllocateIP(dhcp_ty *dhcp, ip_ty *return_ip, const ip_ty host)
{
    ERROR_TY err = SUCCESS;
    size_t height = 0;

    assert(dhcp);

    height = TrieGetHeight(dhcp->trie);

    CopyIp(return_ip, host);

    err = TrieCreateNewPath(dhcp->trie, return_ip->ip + NUM_PARTS - height/8);

    if(err && return_ip->ip[(3 - height / BITS_IN_CHAR)] == 0)
    {
        return ALLOCATION_FAILED;
    }

    if(err)
    {
        return IS_FULL;
    }

    return err;
}

static void CopyIp(ip_ty *a, ip_ty b)
{
    int i = 0;

    for(; i < NUM_PARTS; ++i)
    {
        a->ip[i] = b.ip[i];
    }
}

ERROR_TY DHCPFree(dhcp_ty *dhcp, ip_ty ip)
{
    ERROR_TY err = SUCCESS;
    size_t height = 0;

    assert(dhcp);

    height = TrieGetHeight(dhcp->trie);

    err = TrieFreePath(dhcp->trie, ip.ip + NUM_PARTS - height/BITS_IN_CHAR);

    return err;
}

size_t DHCPCountFree(const dhcp_ty *dhcp)
{
    size_t ret_val = 0;

    assert(dhcp);

    return pow(2, TrieGetHeight(dhcp->trie)) - TrieSize(dhcp->trie);
    
}
