#include <errno.h>

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
    if (ps->wc >= 0x10ffff
        || ps->wc == 0xfffe || ps->wc == 0xffff /* non-characters */
        || (ps->wc >= 0xd800 && ps->wc <= 0xdfff) /* lone surrogates */
    )
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
  if (wc < 0
      || wc >= 0x10ffff
      || wc == 0xfffe || wc == 0xffff /* non-characters */
      || (wc >= 0xd800 && wc <= 0xdfff) /* lone surrogates */
  )
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
