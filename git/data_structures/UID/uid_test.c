#include<stdio.h>

#include"uid.h"

int main()
{
    uid_ty uid1, uid2;

    uid1 = UIDGenerate();
    uid2 = UIDGenerate();
    
    if (UIDIsEqual(uid1, uid2))
    {
        printf("%d,%d", uid1.pid, uid2.pid);
    }
    
    if (UIDIsEqual(uid1, uid1))
    {
        printf("fine\n");
    }
    printf("%d,%d\n", uid1.pid, uid2.pid);

    return 0;
}