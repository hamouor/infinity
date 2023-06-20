#include <unistd.h>
#include <time.h>
#include <sys/types.h>

#include "uid.h"

uid_ty UIDGenerate(void)
{
	static unsigned int id_count = 0;
	uid_ty result;
	
	result.timestamp = time(0);
	if (BAD_TIME == result.timestamp)
	{
		return bad_uid;
	}
	
	result.pid = getpid();
	
	__sync_lock_test_and_set(&result.count, __sync_fetch_and_add(&id_count, 1));
	
	return result;
}

int UIDIsEqual(uid_ty uid1, uid_ty uid2)
{
	return ((uid1.count == uid2.count) && (uid1.pid == uid2.pid));
}

int UIDIsBadUid(uid_ty uid)
{
	return UIDIsEqual(uid, bad_uid);
}
