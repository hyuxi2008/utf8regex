/**
 * Copyright © 2009 Jakub Wilk <jwilk@jwilk.net>
 *
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version
 * 2.1 as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 */

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
