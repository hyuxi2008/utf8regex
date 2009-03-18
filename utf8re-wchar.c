/**
 * Copyright © 2009 Jakub Wilk <ubanus@users.sf.net>
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

#include <errno.h>
#include <stdbool.h>

#include "utf8re-wchar.h"

wint_t utf8re_btowc(int c)
{
  return (c >= L'\0' && c <= L'\x7f') ? c : WEOF;
}

int utf8re_mbsinit(const mbstate_t *ps)
{
  return ps == NULL || ps->remaining == 0;
}

static mbstate_t utf8re_state = { .bytes = 0, .wc = 0 };

static char utf8re_remaining[128] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
  3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0,
};

static inline bool is_unicode_char(wchar_t ch)
{
  if (ch < 0 || ch >= 0x110000)
    return false;
  if (ch >= 0xd800 && ch < 0xe000) /* lone surrogates */
    return false;
  if (ch >= 0xfdd0 && ch < 0xfdf0) /* non-characters */
    return false;
  if ((ch & 0xfffe) == 0xfffe) /* non-characters */
    return false;
  return true;
}

size_t utf8re_mbrtowc(wchar_t *pwc, const char *s, size_t n, mbstate_t *ps)
{
  size_t m;
  if (ps == NULL)
    ps = &utf8re_state;
  if (s == NULL)
  {
    if (ps->remaining > 0)
    {
      ps->remaining = 0;
      errno = EILSEQ;
      return (size_t) -1;
    }
    return 0;
  }
  for (m = 0; m < n; m++, s++)
  {
    const unsigned char c = (unsigned char)*s;
    if (ps->remaining == 0)
    {
      if (c < 0x80)
      {
        ps->wc = c;
        m++;
        break;
      }
      else
      {
        ps->remaining = utf8re_remaining[c - 0x80];
        if (ps->remaining == 0)
        {
          errno = EILSEQ;
          return (size_t) -1;
        }
        ps->bytes = ps->remaining + 1;
        ps->wc = c & ((1 << (8 - ps->bytes)) - 1);
      }
    }
    else
    {
      if ((c & 0xc0) == 0x80)
      {
        ps->wc <<= 6;
        ps->wc |= c & 0x3f;
        if (--ps->remaining == 0)
        {
          m++;
          break;
        }
      }
      else
      {
        errno = EILSEQ;
        return (size_t) -1;
      }
    }
  }
  if (ps->remaining == 0)
  {
    if (!is_unicode_char(ps->wc))
    {
      errno = EILSEQ;
      return (size_t) -1;
    }
    if (ps->bytes > 2 && (ps->wc >> (5 * ps->bytes - 4)) == 0)
    {
      /* Overlong UTF-8 sequence. */
      errno = EILSEQ;
      return (size_t) -1;
    }
    if (pwc != NULL)
      *pwc = ps->wc;
    return (ps->wc == 0) ? 0 : m;
  }
  return (size_t) -2;
}

size_t utf8re_wcrtomb(char *s, wchar_t wc, mbstate_t *ps)
{
  size_t bytes;
  if (!is_unicode_char(wc))
  {
    errno = EILSEQ;
    return (size_t) -1;
  }
  if (wc < 0x80)
  {
    bytes = 1;
    if (s != NULL)
      s[0] = wc;
  }
  else
  {
    for (bytes = 2; bytes < 4; bytes++)
      if (wc < (1 << (5 * bytes + 1)))
         break;
    if (s != NULL)
    {
      size_t i;
      s[0] = (0xff00 >> bytes) & 0xff;
      for (i = bytes; i; i--)
      {
        s[i] = 0x80 | (wc & 0x3f);
        wc >>= 6;
      }
      s[0] |= wc;
    }
  }
  if (ps != NULL)
    ps->remaining = 0;
  return bytes;
}

/* vim:set ts=2 sw=2 et:*/
