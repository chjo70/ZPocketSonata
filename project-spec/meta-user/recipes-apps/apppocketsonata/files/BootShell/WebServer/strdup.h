/*
**  Portable, public domain strdup() by Bob Stout
*/

#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _MSC_VER

#else
char *strdup(const char *string);

#endif

#ifdef __cplusplus
}
#endif

