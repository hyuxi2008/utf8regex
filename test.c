/*
 * Copyright © 2009 Jakub Wilk <jwilk@jwilk.net>
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

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "regex.h"

#define C1 "a"
#define C2 "\xce\xb1" /* GREEK SMALL LETTER ALPHA */
#define C3 "\xe0\xa4\x85" /* DEVANAGARI LETTER A */
#if WCHAR_MAX >= 0x10ffff
#define C4 "\xf4\x80\x80\x80" /* Plane 15 Private Use, First */
#else
#define C4 "\xef\xbc\xa1" /* FULLWIDTH LATIN CAPITAL LETTER A */
#endif

int test_utf8()
{
  int rc;
  regex_t preg;
  const char *string = C1 C2 C3 C4;
  const char *regex = "^" C1 "[" C2 "][" C3 "][" C4 "]$";
  rc = regcomp(&preg, regex, REG_EXTENDED | REG_NOSUB);
  /* A match is expected for UTF-8 encoding *only*. */
  if (rc != 0)
  {
    errno = (rc == REG_ESPACE) ? ENOMEM : EINVAL;
    return -1;
  }
  rc = regexec(&preg, string, 0, NULL, 0);
  regfree(&preg);
  if (rc != 0)
  {
    errno = EILSEQ;
    return 1;
  }
  return 0;
}

#undef C1
#undef C2
#undef C3
#undef C4

int main(int argc, char **argv)
{
#if WCHAR_MAX < 0x10ffff
  fprintf(stderr, "Warning: this system does not support the full Unicode range.\n");
#endif
  int x = test_utf8();
  if (x != 0)
    perror(NULL);
  return x;
}

/* vim:set ts=2 sts=2 sw=2 et: */
