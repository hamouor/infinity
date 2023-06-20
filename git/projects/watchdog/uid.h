#ifndef __UID_H__
#define __UID_H__

#include <stddef.h>
#include <sys/types.h>

typedef struct uid uid_ty;

/*******************************************************************************
* Description:		Returns a UID object.
* Return value:		UID
*******************************************************************************/
uid_ty UIDGenerate(void);

/*******************************************************************************
* Description:		Checks if two UIDs are identical.
* Parameters: 		Two UID objects uid1, uid2.
* Return value:		1 if equal, 0 if not.
*******************************************************************************/
int UIDIsEqual(uid_ty uid1, uid_ty uid2);

/*******************************************************************************
* Description:		Check if UID given is a bad_uid      
* Parameters:		UID
* Return value:		1 if uid is bad_uid else 0 
*******************************************************************************/
int UIDIsBadUid(uid_ty UID);

/* DO NOT TOUCH!!! This struct is for the compiler only! It may change! */
struct uid
{
    pid_t pid;
    pid_t tid;
    unsigned int count;
    time_t timestamp;
};
static const uid_ty bad_uid = { 0, 0, 0, 0 };

#define BAD_TIME (time_t)-1


#endif /* __UID_H__ */
