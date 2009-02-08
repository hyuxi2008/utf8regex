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

#endif
