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

#ifndef UTF8RE_WCHAR_H
#define UTF8RE_WCHAR_H 1

#include <wchar.h>

#undef btowc
#define btowc utf8re_btowc

#undef mbstate_t
#define mbstate_t utf8re_mbstate_t

#undef mbsinit
#define mbsinit utf8re_mbsinit

#undef mbrtowc
#define mbrtowc utf8re_mbrtowc

#undef wcrtomb
#define wcrtomb utf8re_wcrtomb

wint_t utf8re_btowc(int c);

typedef struct
{
  unsigned int remaining;
  unsigned int bytes;
  wchar_t wc;
} utf8re_mbstate_t;

int utf8re_mbsinit(const mbstate_t *ps);
size_t utf8re_mbrtowc(wchar_t *pwc, const char *s, size_t n, mbstate_t *ps);
size_t utf8re_wcrtomb(char *s, wchar_t wc, mbstate_t *ps);

/* vim:set ts=2 sw=2 et:*/

#endif
