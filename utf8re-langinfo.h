#ifndef UTF8RE_LANGINFO_H
#define UTF8RE_LANGINFO_H

#define nl_langinfo utf8re_langinfo
#define CODESET 0

static char *utf8re_langinfo(int item)
{
  if (item == CODESET)
    return "UTF-8";
  return "";
}

/* vim:set ts=2 sw=2 et: */

#endif
