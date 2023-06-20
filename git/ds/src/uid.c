#include <sys/types.h>      /* getpid  */
#include <unistd.h>         /* getpid  */
#include <time.h>           /* time    */

#include "uid.h"

#define NOT_EQUAL 0

extern const uid_ty bad_uid = {0, 0, 0};

uid_ty UIDGenerate(void)
{
    uid_ty new_uid = bad_uid;
    static unsigned int count = 0;

    new_uid.pid = (pid_t)getpid;
    new_uid.count = ++count;
    new_uid.timestamp = time(0);

    if (0 == new_uid.pid || 0 == new_uid.count || 0 == new_uid.timestamp)
    {
        return bad_uid;
    }

    return new_uid;
}

int UIDIsEqual(uid_ty UID1, uid_ty UID2)
{
    if (UID1.pid == UID2.pid && UID1.timestamp == UID2.timestamp)
    {
        return UID1.count == UID2.count;
    }
    
    return NOT_EQUAL;
}

int UIDIsBadUid(uid_ty UID)
{
    return UIDIsEqual(UID, bad_uid);
}
