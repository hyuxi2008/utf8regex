#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "regex.h"

#define C1 "a"
#define C2 "\xce\xb1" /* GREEK SMALL LETTER ALPHA */
#define C3 "\xe0\xa4\x85" /* DEVANAGARI LETTER A */
#define C4 "\xf4\x80\x80\x80" /* Plane 15 Private Use, First */

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
  int x = test_utf8();
  if (x != 0)
    perror(NULL);
  return x;
}

/* vim:set ts=2 sw=2 et: */
