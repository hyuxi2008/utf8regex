#ifndef UTF8_REGEX_CONFIG_H
#define UTF8_REGEX_CONFIG_H 1

#define HAVE_STDBOOL_H 1

#ifdef _WIN32
#define HAVE_MALLOC_H 1
#else
#define HAVE_ALLOCA_H 1
#endif

#endif
