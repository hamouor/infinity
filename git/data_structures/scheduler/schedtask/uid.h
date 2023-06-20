#ifndef __UID_H__
#define __UID_H__

#include <stddef.h>
#include <sys/types.h>

typedef struct uid
{
    pid_t pid;
    unsigned int count;
    time_t timestamp;
} uid_ty;

/*******************************************************************************
*  Description:     Generate UID
*  Return value:    Returns bad_uid if failes
/*******************************************************************************/
uid_ty UIDGenerate(void);

/*******************************************************************************
*  Description:     Compare UID      
*  Parameters:      Two user IDs, UID1 and UID2
*  Return value:    1 if equal else 0 
*  Complexity:      O(1)
/*******************************************************************************/
int UIDIsEqual(uid_ty UID1, uid_ty UID2);

int UIDIsBadUid(uid_ty UID);

extern const uid_ty bad_uid;

#endif