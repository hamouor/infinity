#ifndef __WS9_H__
#define __WS9_H__
#include <stddef.h>/*size_t*/

/*implements the library function memset. for more info: man memset*/
void* Memset(void* dest, int val, unsigned int len);

/*implements the library function memcpy. for more info: man memcpy*/
void *Memcpy(void *dest, const void * src, size_t n);

void *Memmove(void *dest, const void * src, size_t n);

#endif
