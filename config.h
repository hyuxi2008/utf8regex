/*
 * Copyright © 2009, 2010 Jakub Wilk <jwilk@jwilk.net>
 *
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 2.1 of the
 * License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 */

#ifndef UTF8_REGEX_CONFIG_H
#define UTF8_REGEX_CONFIG_H 1

#define HAVE_STDBOOL_H 1

#ifdef _WIN32
#define HAVE_MALLOC_H 1
#else
#define HAVE_ALLOCA_H 1
#endif

#define HAVE_LANGINFO_H 1
#define HAVE_LANGINFO_CODESET

#define HAVE_LOCALE_H 1

#define HAVE_WCHAR_H 1
#define HAVE_WCTYPE_H 1
#define HAVE_WCRTOMB 1
#define HAVE_MBRTOWC 1
#define HAVE_WCSCOLL 1

#undef MAX
#define MAX(a, b) ((a < b) ? (b) : (a))

#define __OPTION_EGLIBC_LOCALE_CODE 1

#endif
