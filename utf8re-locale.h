#ifndef UTF8RE_LOCALE_H
#define UTF8RE_LOCALE_H

/* The following are actually redefinitions of <stdlib.h> */

#include <stdlib.h>

#undef MB_CUR_MAX
#define MB_CUR_MAX 4

#if MB_LEN_MAX < 4
#undef MB_LEN_MAX
#define MB_LEN_MAX 4
#endif

#endif
