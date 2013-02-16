/**
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

#ifndef UTF8RE_LANGINFO_H
#define UTF8RE_LANGINFO_H

#define nl_langinfo utf8re_langinfo
#define CODESET 0

static inline char *utf8re_langinfo(int item)
{
  if (item == CODESET)
    return "UTF-8";
  return "";
}

/* vim:set ts=2 sw=2 et: */

#endif
