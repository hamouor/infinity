#include"dhcp.h"
#include"trie.h"
#include <stdio.h>
int main ()
{
    dhcp_ty* test = NULL;
    ip_ty ip = {{123,124,125,0}}, req = {{0,0,0,1}}, ret;





    test = DHCPCreate(ip);
    printf("%d\n",DHCPAllocateIP(test, &ret, req));
    printf("%d\n", ret.ip[3]);

    printf("%d\n",DHCPAllocateIP(test, &ret, req));
    printf("%d\n", ret.ip[3]);

    printf("%d\n",DHCPAllocateIP(test, &ret, req));
    printf("%d\n", ret.ip[3]);
    
    printf("%d\n",DHCPFree(test, req));

    printf("%d\n",DHCPAllocateIP(test, &ret, req));
    printf("%d\n", ret.ip[3]);
    
    printf("%ld\n", DHCPCountFree(test));

    DHCPDestroy(test);

    return 0;
}